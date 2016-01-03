#include "tellstick-node.h"

using namespace v8;

namespace TellstickNode {

  struct Work {
    uv_work_t  request;
    Persistent<Function> callback;
    std::string errorString;
    Sensor::Vector* sensors = NULL;
    Device::Vector* devices = NULL;
  };

  void CreateObject(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);
    DeviceNode::NewInstance(args);
  }

  void GetDevice(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    int id = args[0]->NumberValue();
    Device* device = Device::getDevice(id);

    if(device==NULL) {
      args.GetReturnValue().Set(v8::Null(isolate));
      return;
    }

    Local<Function> cons = Local<Function>::New(isolate, DeviceNode::constructor);
    Local<Object> instance = cons->NewInstance();
    DeviceNode* obj = DeviceNode::getObjectInternal(instance);
    obj->setDevice(device);

    args.GetReturnValue().Set(instance);
  }

  Handle<Array> GetDevicesWrapped(Device::Vector* d) {
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);
    v8::Handle<v8::Array> devices = Array::New(isolate);

    int i=0;
    for (Device::Vector::iterator it = d->begin(); it != d->end(); ++it) {
      Local<Function> cons = Local<Function>::New(isolate, DeviceNode::constructor);
      Local<Object> instance = cons->NewInstance();
      DeviceNode* obj = DeviceNode::getObjectInternal(instance);
      Device* device = new Device(*(*it));
      obj->setDevice(device);
      devices->Set(i++, instance);
    }
    return devices;
  }

  void GetDevices(const FunctionCallbackInfo<Value>& args) {
    Device::Vector* devices = Device::getDevices();
    args.GetReturnValue().Set(GetDevicesWrapped(devices));
    delete devices;
  }

  void GetDevicesAsync(const FunctionCallbackInfo<Value>& args)  {
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    Work * work = new Work();
    work->request.data = work;

    Local<Function> callback = Local<Function>::Cast(args[0]);
    work->callback.Reset(isolate, callback);

    // kick of the worker thread
    uv_queue_work(uv_default_loop(),&work->request,WorkDevicesAsync,WorkAsyncComplete);
    args.GetReturnValue().Set(Undefined(isolate));
  }

  void WorkDevicesAsync(uv_work_t *req) {
    Work *work = static_cast<Work *>(req->data);

    // this is the worker thread, lets build up the results
    // allocated results from the heap because we'll need
    // to access in the event loop later to send back
    work->devices = Device::getDevices();
  }

  void GetSensor(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    int id = args[0]->NumberValue();
    Sensor* sensor = Sensor::getSensor(id);

    if(sensor==NULL) {
      args.GetReturnValue().Set(v8::Null(isolate));
      return;
    }

    Local<Function> cons = Local<Function>::New(isolate, DeviceNode::constructor);
    Local<Object> instance = cons->NewInstance();
    SensorNode* obj = SensorNode::getObjectInternal(instance);
    obj->setSensor(sensor);

    args.GetReturnValue().Set(instance);
  }

  Handle<Array> GetSensorsWrapped(Sensor::Vector* s) {
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);
    v8::Handle<v8::Array> sensors = Array::New(isolate);

    int i=0;
    for (Sensor::Vector::iterator it = s->begin(); it != s->end(); ++it) {
      Local<Function> cons = Local<Function>::New(isolate, SensorNode::constructor);
      Local<Object> instance = cons->NewInstance();
      SensorNode* obj = SensorNode::getObjectInternal(instance);
      Sensor* sensor = new Sensor(*(*it));
      obj->setSensor(sensor);
      sensors->Set(i++, instance);
    }

    return sensors;
  }

  void GetSensors(const FunctionCallbackInfo<Value>& args) {
    Sensor::Vector* sensors = Sensor::getSensors();
    args.GetReturnValue().Set(GetSensorsWrapped(sensors));
    delete sensors;
  }

  // called by libuv worker in separate thread
  static void WorkAsyncSensors(uv_work_t *req) {
    Work *work = static_cast<Work *>(req->data);

    // this is the worker thread, lets build up the results
    // allocated results from the heap because we'll need
    // to access in the event loop later to send back
    work->sensors = Sensor::getSensors();
  }

  void GetSensorsAsync(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    Work * work = new Work();
    work->request.data = work;

    Local<Function> callback = Local<Function>::Cast(args[0]);
    work->callback.Reset(isolate, callback);

    // kick of the worker thread
    uv_queue_work(uv_default_loop(),&work->request,WorkAsyncSensors,WorkAsyncComplete);
    args.GetReturnValue().Set(Undefined(isolate));
  }

  // called by libuv in event loop when async function completes
  void WorkAsyncComplete(uv_work_t *req, int status) {
      Isolate * isolate = Isolate::GetCurrent();
      v8::HandleScope handleScope(isolate);

      Work *work = static_cast<Work *>(req->data);

      // the work has been done, and now we pack the results
      // vector into a Local array on the event-thread's stack.

      v8::Handle<v8::Array> array = Array::New(isolate);

      if(work->devices!=NULL) {
        int i=0;
        for (Device::Vector::iterator it = work->devices->begin(); it != work->devices->end(); ++it) {
          Local<Function> cons = Local<Function>::New(isolate, DeviceNode::constructor);
          Local<Object> instance = cons->NewInstance();
          DeviceNode* obj = DeviceNode::getObjectInternal(instance);
          Device* device = new Device(*(*it));
          obj->setDevice(device);
          array->Set(i++, instance);
        }

        delete work->devices;
      } else if(work->sensors!=NULL) {
        int i=0;
        for (Sensor::Vector::iterator it = work->sensors->begin(); it != work->sensors->end(); ++it) {
          Local<Function> cons = Local<Function>::New(isolate, SensorNode::constructor);
          Local<Object> instance = cons->NewInstance();
          SensorNode* obj = SensorNode::getObjectInternal(instance);
          Sensor* sensor = new Sensor(*(*it));
          obj->setSensor(sensor);
          array->Set(i++, instance);
        }
        delete work->sensors;
      }

      // set up return arguments
      const unsigned argc = 2;
      Handle<Value> argv[argc] = { v8::Null(isolate), array };

      // execute the callback
      // https://stackoverflow.com/questions/13826803/calling-javascript-function-from-a-c-callback-in-v8/28554065#28554065
      Local<Function>::New(isolate, work->callback)->Call(isolate->GetCurrentContext()->Global(), argc, argv);

      // Free up the persistent function callback
      work->callback.Reset();

      delete work;
  }

  void TellstickInit(const v8::FunctionCallbackInfo<v8::Value>&) {
    Tellstick::init();
  }
  void TellstickClose(const v8::FunctionCallbackInfo<v8::Value>&) {
    Tellstick::close();
  }

  void Init(Handle<Object> exports) {
    NODE_SET_METHOD(exports, "createObject", CreateObject);
    NODE_SET_METHOD(exports, "getDevice", GetDevice);
    NODE_SET_METHOD(exports, "getDevices", GetDevices);
    NODE_SET_METHOD(exports, "getDevicesAsync", GetDevicesAsync);
    NODE_SET_METHOD(exports, "getSensor", GetSensor);
    NODE_SET_METHOD(exports, "getSensors", GetSensors);
    NODE_SET_METHOD(exports, "getSensorsAsync", GetSensorsAsync);

    NODE_SET_METHOD(exports, "init", TellstickInit);
    NODE_SET_METHOD(exports, "close", TellstickClose);

    DeviceNode::Init(exports);
    SensorNode::Init(exports);
  }
}

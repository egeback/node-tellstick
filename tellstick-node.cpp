#include "tellstick-node.h"

using namespace v8;

namespace TellstickNode {

  void CreateObject(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);
    DeviceNode::NewInstance(args);
  }

  void GetDevice(const FunctionCallbackInfo<Value>& args) {
    int id = args[0]->NumberValue();
    Device* device = Device::getDevice(id);

    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    Local<Function> cons = Local<Function>::New(isolate, DeviceNode::constructor);
    Local<Object> instance = cons->NewInstance();
    DeviceNode* obj = DeviceNode::getObjectInternal(instance);
    obj->setDevice(device);

    args.GetReturnValue().Set(instance);
  }

  void GetDevices(const FunctionCallbackInfo<Value>& args) {
    Device::Vector* d = Device::getDevices();

    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);
    v8::Handle<v8::Array> devices = Array::New(isolate);

    int i=0;
    for (Device::Vector::iterator it = d->begin(); it != d->end(); ++it) {
      Local<Function> cons = Local<Function>::New(isolate, DeviceNode::constructor);
      Local<Object> instance = cons->NewInstance();
      DeviceNode* obj = DeviceNode::getObjectInternal(instance);
      obj->setDevice((*it));
      devices->Set(i++, instance);
    }
    d = NULL;

    args.GetReturnValue().Set(devices);
  }

  void GetSensor(const FunctionCallbackInfo<Value>& args) {
    int id = args[0]->NumberValue();
    Sensor* sensor = Sensor::getSensor(id);

    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    Local<Function> cons = Local<Function>::New(isolate, DeviceNode::constructor);
    Local<Object> instance = cons->NewInstance();
    SensorNode* obj = SensorNode::getObjectInternal(instance);
    obj->setSensor(sensor);

    args.GetReturnValue().Set(instance);
  }

  void GetSensors(const FunctionCallbackInfo<Value>& args) {
    Sensor::Vector* s = Sensor::getSensors();

    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);
    v8::Handle<v8::Array> sensors = Array::New(isolate);

    int i=0;
    for (Sensor::Vector::iterator it = s->begin(); it != s->end(); ++it) {
      Local<Function> cons = Local<Function>::New(isolate, SensorNode::constructor);
      Local<Object> instance = cons->NewInstance();
      SensorNode* obj = SensorNode::getObjectInternal(instance);
      obj->setSensor((*it));
      sensors->Set(i++, instance);
    }
    s = NULL;

    args.GetReturnValue().Set(sensors);

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
    NODE_SET_METHOD(exports, "getSensor", GetSensor);
    NODE_SET_METHOD(exports, "getSensors", GetSensors);

    NODE_SET_METHOD(exports, "init", TellstickInit);
    NODE_SET_METHOD(exports, "close", TellstickClose);

    DeviceNode::Init(exports);
    SensorNode::Init(exports);
  }
}

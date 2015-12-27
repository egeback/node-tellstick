#include "sensor-node.h"
#include <vector>
#include <string>

using namespace v8;

Persistent<Function> SensorNode::constructor;

SensorNode::SensorNode() {
  _sensor = NULL;
}

SensorNode::~SensorNode() {
  if(_sensor!=NULL) {
    delete _sensor;
    _sensor = NULL;
  }
}

void SensorNode::New(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  if (args.IsConstructCall()) {
    // Invoked as constructor: `new DeviceNode()`
    SensorNode* obj = new SensorNode();
    obj->Wrap(args.This());
    args.GetReturnValue().Set(args.This());
  } else {
    // Invoked as plain function `DeviceNode(...)`, turn into construct call.
    Local<Function> cons = Local<Function>::New(isolate, constructor);
    args.GetReturnValue().Set(cons->NewInstance());
  }
}

void SensorNode::NewInstance(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  const unsigned argc = 1;
  Handle<Value> argv[argc] = { args[0] };
  Local<Function> cons = Local<Function>::New(isolate, constructor);
  Local<Object> instance = cons->NewInstance(argc, argv);

  args.GetReturnValue().Set(instance);
}

//Getters
void SensorNode::GetId(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  Sensor* sensor = getSensorBinding(args)->_sensor;
  args.GetReturnValue().Set(Integer::New(isolate, sensor->getId()));
}

void SensorNode::GetModel(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  Sensor* sensor = getSensorBinding(args)->_sensor;
  args.GetReturnValue().Set(String::NewFromUtf8(isolate, sensor->getModel().c_str()));
}

void SensorNode::GetProtocol(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  Sensor* sensor = getSensorBinding(args)->_sensor;
  args.GetReturnValue().Set(String::NewFromUtf8(isolate, sensor->getProtocol().c_str()));
}

//Actions
Local<Object> getValueObject(const Sensor::Value* value, Isolate* isolate) {
  Local<Object> obj = Object::New(isolate);
  obj->Set(String::NewFromUtf8(isolate, "value"), Number::New(isolate, value->value));
  obj->Set(String::NewFromUtf8(isolate, "timestamp"), String::NewFromUtf8(isolate, value->timestamp.c_str()));
  obj->Set(String::NewFromUtf8(isolate, "timestamp_raw"), Integer::New(isolate, value->timestamp_raw));

  return obj;
}


void SensorNode::GetTemperature(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  args.GetReturnValue().Set(getValueObject(getSensorBinding(args)->_sensor->getTemperature(), isolate));
}

void SensorNode::GetHumidity(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  args.GetReturnValue().Set(getValueObject(getSensorBinding(args)->_sensor->getHumidity(), isolate));
}

//Other
void SensorNode::setSensor(Sensor* sensor) {
  this->_sensor = sensor;
}

SensorNode* SensorNode::getObjectInternal(Local<Object> obj) {
  return ObjectWrap::Unwrap<SensorNode>(obj);
}

SensorNode* SensorNode::getSensorBinding(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  return ObjectWrap::Unwrap<SensorNode>(args.Holder());
}

//Init
void SensorNode::Init(v8::Handle<v8::Object> exports) {
  Isolate* isolate = exports->GetIsolate();

  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
  tpl->SetClassName(String::NewFromUtf8(isolate, "SensorNode"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  NODE_SET_PROTOTYPE_METHOD(tpl, "getId", SensorNode::GetId);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getModel", SensorNode::GetModel);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getProtocol", SensorNode::GetProtocol);

  NODE_SET_PROTOTYPE_METHOD(tpl, "getTemperature", SensorNode::GetTemperature);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getHumidity", SensorNode::GetHumidity);


  constructor.Reset(isolate, tpl->GetFunction());
  exports->Set(String::NewFromUtf8(isolate, "SensorNode"),
               tpl->GetFunction());
}

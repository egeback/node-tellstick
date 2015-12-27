#include "device-node.h"

using namespace v8;

Persistent<Function> DeviceNode::constructor;

DeviceNode::DeviceNode() {
  _device = NULL;
}

DeviceNode::~DeviceNode() {
  if(_device!=NULL) {
    delete _device;
    _device = NULL;
  }
}

void DeviceNode::New(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  if (args.IsConstructCall()) {
    // Invoked as constructor: `new DeviceNode()`
    DeviceNode* obj = new DeviceNode();
    obj->Wrap(args.This());
    args.GetReturnValue().Set(args.This());
  } else {
    // Invoked as plain function `DeviceNode(...)`, turn into construct call.
    Local<Function> cons = Local<Function>::New(isolate, constructor);
    args.GetReturnValue().Set(cons->NewInstance());
  }
}

void DeviceNode::NewInstance(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  const unsigned argc = 1;
  Handle<Value> argv[argc] = { args[0] };
  Local<Function> cons = Local<Function>::New(isolate, constructor);
  Local<Object> instance = cons->NewInstance(argc, argv);

  args.GetReturnValue().Set(instance);
}

DeviceNode* DeviceNode::getObjectInternal(Local<Object> obj) {
  return ObjectWrap::Unwrap<DeviceNode>(obj);
}

DeviceNode* DeviceNode::getDeviceBinding(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  return ObjectWrap::Unwrap<DeviceNode>(args.Holder());
}

//Getters
void DeviceNode::GetName(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  Device* device = getDeviceBinding(args)->_device;
  args.GetReturnValue().Set(String::NewFromUtf8(isolate, device->getName().c_str()));
}

void DeviceNode::GetId(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  Device* device = getDeviceBinding(args)->_device;
  args.GetReturnValue().Set(Integer::New(isolate, device->getId()));
}

void DeviceNode::GetModel(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  Device* device = getDeviceBinding(args)->_device;
  args.GetReturnValue().Set(String::NewFromUtf8(isolate, device->getModel().c_str()));
}

void DeviceNode::GetProtocol(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  Device* device = getDeviceBinding(args)->_device;
  args.GetReturnValue().Set(String::NewFromUtf8(isolate, device->getProtocol().c_str()));
}

void DeviceNode::GetDeviceType(const v8::FunctionCallbackInfo<v8::Value>&) args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  Device* device = getDeviceBinding(args)->_device;
  args.GetReturnValue().Set(String::NewFromUtf8(isolate, device->getDeviceType().c_str()));
}

void DeviceNode::GetLastSentValue(const v8::FunctionCallbackInfo<v8::Value>&) args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  Device* device = getDeviceBinding(args)->_device;
  args.GetReturnValue().Set(String::NewFromUtf8(isolate, device->getLastSentValue().c_str()));
}

void DeviceNode::GetMethods(const v8::FunctionCallbackInfo<v8::Value>&) args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  Device* device = getDeviceBinding(args)->_device;
  v8::Handle<v8::Array> methods;
  args.GetReturnValue().Set(String::NewFromUtf8(isolate, device->getName().c_str()));
}

void DeviceNode::GetDimValue(const v8::FunctionCallbackInfo<v8::Value>&) args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  Device* device = getDeviceBinding(args)->_device;
  args.GetReturnValue().Set(Integer::New(isolate, device->getDimValue());
}

void DeviceNode::IsOn(const v8::FunctionCallbackInfo<v8::Value>&) args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  Device* device = getDeviceBinding(args)->_device;
  args.GetReturnValue().Set(Boolean::New(isolate, device->isOn));
}

void DeviceNode::IsDimmable(const v8::FunctionCallbackInfo<v8::Value>&) args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  Device* device = getDeviceBinding(args)->_device;
  args.GetReturnValue().Set(Boolean::New(isolate, device->isDimmable));
}

//Internal set device
void DeviceNode::setDevice(Device* device) {
  this->_device = device;
}

//Init
void DeviceNode::Init(v8::Handle<v8::Object> exports) {
  Isolate* isolate = exports->GetIsolate();

  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
  tpl->SetClassName(String::NewFromUtf8(isolate, "DeviceNode"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  NODE_SET_PROTOTYPE_METHOD(tpl, "getName", DeviceNode::GetName);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getId", DeviceNode::GetId);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getModel", DeviceNode::GetModel);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getProtocol", DeviceNode::GetProtocol);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getDeviceType", DeviceNode::GetDeviceType);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getLastSentValue", DeviceNode::GetLastSentValue);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getMethods", DeviceNode::GetMethods);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getDimValue", DeviceNode::GetDimValue);
  NODE_SET_PROTOTYPE_METHOD(tpl, "isOn", DeviceNode::IsOn);
  NODE_SET_PROTOTYPE_METHOD(tpl, "isDimmable", DeviceNode::IsDimmable);

  constructor.Reset(isolate, tpl->GetFunction());
  exports->Set(String::NewFromUtf8(isolate, "DeviceNode"),
               tpl->GetFunction());
}

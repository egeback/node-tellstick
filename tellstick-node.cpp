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

  void Init(Handle<Object> exports) {
    NODE_SET_METHOD(exports, "createObject", CreateObject);
    NODE_SET_METHOD(exports, "getDevice", GetDevice);
    DeviceNode::Init(exports);
    NODE_SET_METHOD(exports, "getName", DeviceNode::GetName);
  }
}

#ifndef DEVICE_NODE_H
#define DEVICE_NODE_H

#include <node.h>
#include <node_object_wrap.h>
#include <device.h>
#include <iostream>

class DeviceNode : public node::ObjectWrap {
  public:
    void setDevice(Device* device);
    //Wrapped
    static v8::Persistent<v8::Function> constructor;
    static void Init(v8::Handle<v8::Object>);
    static void NewInstance(const v8::FunctionCallbackInfo<v8::Value>& args);
    static DeviceNode* getObjectInternal(v8::Local<v8::Object>);
    static void GetName(const v8::FunctionCallbackInfo<v8::Value>&);
    static void GetId(const v8::FunctionCallbackInfo<v8::Value>&);
    static void GetModel(const v8::FunctionCallbackInfo<v8::Value>&);
    static void GetProtocol(const v8::FunctionCallbackInfo<v8::Value>&);
    static void GetDeviceType(const v8::FunctionCallbackInfo<v8::Value>&);
    static void GetLastSentValue(const v8::FunctionCallbackInfo<v8::Value>&);
    static void GetMethods(const v8::FunctionCallbackInfo<v8::Value>&);
    static void GetDimValue(const v8::FunctionCallbackInfo<v8::Value>&);
    static void IsOn(const v8::FunctionCallbackInfo<v8::Value>&);
    static void IsDimmable(const v8::FunctionCallbackInfo<v8::Value>&);

  private:
    explicit DeviceNode();
    ~DeviceNode();

    static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
    static DeviceNode* getDeviceBinding(const v8::FunctionCallbackInfo<v8::Value>&);
    Device *_device;
};

#endif

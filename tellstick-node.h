#ifndef TELLSTICK_NODE_H
#define TELLSTICK_NODE_H
#include <nan.h>
#include <v8.h>
#include "device-node.h"
#include "sensor-node.h"
#include <tellstick.h>

namespace TellstickNode {
  void Init(v8::Handle<v8::Object>);
  void CreateObject(const v8::FunctionCallbackInfo<v8::Value>&);
  void GetDevice(const v8::FunctionCallbackInfo<v8::Value>&);
  void GetDevices(const v8::FunctionCallbackInfo<v8::Value>&);
  void GetSensor(const v8::FunctionCallbackInfo<v8::Value>&);
  void GetSensors(const v8::FunctionCallbackInfo<v8::Value>&);
  void TellstickInit(const v8::FunctionCallbackInfo<v8::Value>&);
  void TellstickClose(const v8::FunctionCallbackInfo<v8::Value>&);
}

NODE_MODULE(TellstickNode, TellstickNode::Init)

#endif

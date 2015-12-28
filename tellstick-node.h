#ifndef TELLSTICK_NODE_H
#define TELLSTICK_NODE_H
#include <nan.h>
#include <v8.h>
#include "device-node.h"
#include "sensor-node.h"
#include <tellstick.h>
#include <uv.h>
#include <string>

namespace TellstickNode {
  void Init(v8::Handle<v8::Object>);
  void CreateObject(const v8::FunctionCallbackInfo<v8::Value>&);

  void GetDevice(const v8::FunctionCallbackInfo<v8::Value>&);
  void GetDevices(const v8::FunctionCallbackInfo<v8::Value>&);
  void GetDevicesAsync(const v8::FunctionCallbackInfo<v8::Value>&);
  void WorkDevicesAsync(uv_work_t *req);
  v8::Handle<v8::Array> GetDevicesWrapped();

  void GetSensor(const v8::FunctionCallbackInfo<v8::Value>&);
  void GetSensors(const v8::FunctionCallbackInfo<v8::Value>&);
  void GetSensorsAsync(const v8::FunctionCallbackInfo<v8::Value>&);
  void WorkSensorsAsync(uv_work_t *req);
  v8::Handle<v8::Array> GetSensorsWrapped();

  void WorkAsyncComplete(uv_work_t *req, int status);

  void TellstickInit(const v8::FunctionCallbackInfo<v8::Value>&);
  void TellstickClose(const v8::FunctionCallbackInfo<v8::Value>&);
}

NODE_MODULE(TellstickNode, TellstickNode::Init)

#endif

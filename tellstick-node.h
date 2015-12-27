#ifndef TELLSTICK_NODE_H
#define TELLSTICK_NODE_H
#include <nan.h>
#include <v8.h>
#include "device-node.h"

namespace TellstickNode {
  void Init(v8::Handle<v8::Object>);
  void CreateObject(const v8::FunctionCallbackInfo<v8::Value>&);
}

NODE_MODULE(TellstickNode, TellstickNode::Init)

#endif

#ifndef SENSOR_NODE_H
#define SENSOR_NODE_H

#include <node.h>
#include <node_object_wrap.h>
#include <sensor.h>
#include <v8.h>

class SensorNode : public node::ObjectWrap {
  public:
    void setSensor(Sensor* sensor);
    //Wrapped
    static v8::Persistent<v8::Function> constructor;
    static void Init(v8::Handle<v8::Object>);
    static void NewInstance(const v8::FunctionCallbackInfo<v8::Value>& args);
    static SensorNode* getObjectInternal(v8::Local<v8::Object>);

    //GETTERS
    static void GetId(const v8::FunctionCallbackInfo<v8::Value>&);
    static void GetModel(const v8::FunctionCallbackInfo<v8::Value>&);
    static void GetProtocol(const v8::FunctionCallbackInfo<v8::Value>&);
    static void GetTemperature(const v8::FunctionCallbackInfo<v8::Value>&);
    static void GetHumidity(const v8::FunctionCallbackInfo<v8::Value>&);
  private:
    explicit SensorNode();
    ~SensorNode();

    static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
    static SensorNode* getSensorBinding(const v8::FunctionCallbackInfo<v8::Value>&);
    static int getIntParameter(const v8::FunctionCallbackInfo<v8::Value>& args);

    Sensor *_sensor;
};

#endif

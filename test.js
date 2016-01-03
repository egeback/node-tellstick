var tellstick = require('./build/Release/tellstick.node');

var device = tellstick.getDevice(1);
console.log(device.getId() + ": " + device.getName() + ", isOn: " + device.isOn() + " supportsDim: " + device.isDimmable());
device.turnOn();

var devices = tellstick.getDevices();
var sensors = tellstick.getSensors();
var sensor = sensors[1];
console.log(sensor.getProtocol());
console.log(sensor.getHumidity());

var device2 = tellstick.getDevice(2);
if(device2 === null) {
  console.log("Device does not exist");
} else {
  console.log(device2.getName());
}

//if(sensor.getHumidity()!==null) {
//  console.log(sensor.getHumidity().value);
//}

/*
console.log("Devices");
devices.forEach(function(device){
  console.log(device.getId() + ": " + device.getName());
});*/

var id = 30;
console.log("Sensors");
sensors.forEach(function(sensor){
  if(sensor.getId()==id) {
    console.log(sensor.getId() + ": " + sensor.getModel() + ", " + sensor.getProtocol() + ", " + sensor.getTemperature().value + ", " + sensor.getTemperature().timestamp);
    if(sensor.getHumidity()!==null) {
      console.log("Humidity value: " + sensor.getHumidity().value);
    }
  }
});

var s = tellstick.getSensor(232);
if(s!==null)
  console.log(s.getProtocol());
//console.log(sensor.getModel());

/*
console.log("Devices Async");
tellstick.getDevicesAsync(function(err, devices) {
  devices.forEach(function(device){
    console.log(device.getId() + ": " + device.getName());
  });
});


console.log("Sensors ASync");
tellstick.getSensorsAsync(function(err, sensors) {
  sensors.forEach(function(sensor){
    console.log(sensor.getId() + ": " + sensor.getModel() + ", " + sensor.getProtocol() + ", " + sensor.getTemperature().value + ", " + sensor.getTemperature().timestamp);
  });
});*/

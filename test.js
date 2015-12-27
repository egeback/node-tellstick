var tellstick = require('./build/Release/hello.node');

var device = tellstick.getDevice(1);
console.log(device.getId() + ": " + device.getName());
device.turnOff();

var devices = tellstick.getDevices();
var sensors = tellstick.getSensors();


console.log("Devices");
devices.forEach(function(device){
  console.log(device.getId() + ": " + device.getName());
});

console.log("Sensors");
sensors.forEach(function(sensor){
  console.log(sensor.getId() + ": " + sensor.getModel() + ", " + sensor.getProtocol() + ", " + sensor.getTemperature().value + ", " + sensor.getTemperature().timestamp);
});

var tellstick = require('./build/Release/tellstick.node');

var device = tellstick.getDevice(1);
console.log(device.getId() + ": " + device.getName());
device.turnOff();

var devices = tellstick.getDevices();
var sensors = tellstick.getSensors();
var sensor = sensors[1];
console.log(sensor.getProtocol());
console.log(sensor.getHumidity());

//if(sensor.getHumidity()!==null) {
//  console.log(sensor.getHumidity().value);
//}

/*
console.log("Devices");
devices.forEach(function(device){
  console.log(device.getId() + ": " + device.getName());
});*/

console.log("Sensors");
sensors.forEach(function(sensor){
  console.log(sensor.getId() + ": " + sensor.getModel() + ", " + sensor.getProtocol() + ", " + sensor.getTemperature().value + ", " + sensor.getTemperature().timestamp);
  if(sensor.getHumidity()!==null) {
    console.log("Humidity value: " + sensor.getHumidity().value);
  }
});
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

var tellstick = require('./build/Release/hello.node');

var device1 = tellstick.createObject();
var device2 = tellstick.getDevice(1);
console.log(device2.getName());

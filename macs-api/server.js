'use strict';

/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 16/02/16.
 * Contributors:
 */

// Instantiate a new OSC Serial Port.
var serialPort = new osc.SerialPort({
	devicePath: "/dev/ttyAMA0",
	bitrate: "9600"
});


serialPort.on("message", function (oscMsg) {
	console.log("An OSC message was received!", oscMsg);
});

// Open the port.
serialPort.open();
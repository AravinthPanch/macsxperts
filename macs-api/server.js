'use strict';

/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 16/02/16.
 * Contributors:
 */

var osc = require("osc"),
	http = require("http"),
	ws = require("ws"),
	express = require("express"),
	basicAuth = require('basic-auth-connect'),
	app = express(),
	webServer = app.listen(3001, function () {
		console.log("OSC Serial <=> Browser Relay is started");
	}),
	webSocket = new ws.Server({
		server: webServer
	}),
	oscSocket,
	oscSerial = new osc.SerialPort({
		devicePath: "/dev/ttyAMA0",
		bitrate: "115200"
	});


app.use(basicAuth('guest', 'macs@gp15'));
app.use("/", express.static(__dirname));

webSocket.on("connection", function (browserSocket) {
	// On Client connection
	console.log("Client Connected");

	// Attach Browser Websocket to OSC Websocket
	oscSocket = new osc.WebSocketPort({
		socket: browserSocket
	});

	// Relay Browser OSC Message to Serial
	oscSocket.on("message", function (browserMsg) {
		console.log("Browser ", browserMsg);
		oscSerial.send(browserMsg);
	});

	// Relay Serial OSC Message to Browser
	oscSerial.on("message", function (serialMsg) {
		console.log("Serial ", serialMsg);
		oscSocket.send(serialMsg);
	});


	oscSocket.send({
		address: "/ph/",
		args: 5.8
	});

	oscSocket.send({
		address: "/ec/",
		args: 1200
	});

	oscSocket.send({
		address: "/temp/",
		args: 25.5
	});
});


// Open OSC via Serial
oscSerial.open();
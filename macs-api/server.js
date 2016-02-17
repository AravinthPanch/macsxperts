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
	app = express(),
	webServer = app.listen(8081, function () {
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


webSocket.on("connection", function (browserSocket) {
	// On Client connection
	console.log("Client Connected");

	// Attach Browser Websocket to OSC Websocket
	oscSocket = new osc.WebSocketPort({
		socket: browserSocket
	});

	// Relay Browser OSC Message to Serial
	oscSocket.on("message", function (browserMsg) {
		oscSerial.send(browserMsg);
	});

	// Relay Serial OSC Message to Browser
	oscSerial.on("message", function (serialMsg) {
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


'use strict';

/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 17/02/16.
 * Contributors:
 */

var oscPort = new osc.WebSocketPort({
	url: "ws://localhost:3001"
});

oscPort.on("open", function () {
	console.log("OSC Serial <=> Browser Relay is started");
});

oscPort.on("message", function (oscMsg) {
	console.log("OSC", oscMsg);
	switch (oscMsg.address) {
		case "/ph/":
			$("#phValue").html(oscMsg.args[0]);
			break;
		case "/ec/":
			$("#ecValue").html(oscMsg.args[0]);
			break;
		case "/temp/":
			$("#tempValue").html(oscMsg.args[0]);
			break;
	}
});

oscPort.open();
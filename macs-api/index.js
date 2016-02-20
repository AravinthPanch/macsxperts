'use strict';

/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 17/02/16.
 * Contributors:
 */

var oscPort = new osc.WebSocketPort({
	url: "ws://macsxperts.local:3001"
});

oscPort.on("open", function () {
	console.log("OSC Serial <=> Browser Relay is started");
});

oscPort.on("message", function (oscMsg) {
	console.log("OSC", oscMsg);
	switch (oscMsg.address) {
		case "/sense/ph/":
			var phValue = oscMsg.args[0];
			$("#phValue").html(phValue.toFixed(2));
			break;
		case "/sense/ec/":
			var ecValue = oscMsg.args[0];
			$("#ecValue").html(Math.round(ecValue));
			break;
		case "/sense/temp/":
			var tempValue = oscMsg.args[0];
			$("#tempValue").html(tempValue.toFixed(2));
			break;
	}
});

oscPort.open();
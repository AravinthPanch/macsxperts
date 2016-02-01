/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 01/02/16.
 * Contributors:
 */

var express = require('express');
var app = express();
var path = require('path');
var basicAuth = require('basic-auth-connect');
const spawn = require('child_process').spawn;

app.use(basicAuth('guest', 'macs@gp15'));

app.use('/cam', express.static(__dirname));

app.get('/', function (req, res) {

	const ls = spawn('mjpg_streamer', ['-i', "/usr/lib/input_uvc.so -d /dev/video0 -y -r 640x480 -f 10", '-o', "/usr/lib/output_http.so -p 8090"]);

	ls.stdout.on('data', (data) => {
		console.log(`stdout: ${data}`);
	});

	ls.stderr.on('data', (data) => {
		console.log(`stderr: ${data}`);
	});

	ls.on('close', (code) => {
		console.log(`mjpg process exited with code ${code}`);
	});

	setTimeout(function () {
		res.redirect('/cam');
	}, 2000);

});

app.listen(3000, function () {
	console.log('Big Brother is listening on port 3000!');
});
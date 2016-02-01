/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 01/02/16.
 * Contributors:
 */

const spawn = require('child_process').spawn;
const ls = spawn('mjpg_streamer', ['-i', "/usr/lib/input_uvc.so -d /dev/video0 -y -r 640x480 -f 10", '-o',
	"/usr/lib/output_http.so -p 8090"]);

ls.stdout.on('data', (data) => {
	console.log(`stdout: ${data}`);
});

ls.stderr.on('data', (data) => {
	console.log(`stderr: ${data}`);
});

ls.on('close', (code) => {
	console.log(`child process exited with code ${code}`);
});

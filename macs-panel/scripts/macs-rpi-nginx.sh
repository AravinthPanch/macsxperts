server {
	listen 80 default_server;
	listen [::]:80 default_server;

	root /home/aravinth/macsxperts/macs-panel/big-brother;
	index index.html index.htm index.nginx-debian.html;

	server_name _;

	location /ara {
		fastcgi_pass unix:/var/run/fcgiwrap.socket;
		include /etc/nginx/fastcgi_params;
		fastcgi_param DOCUMENT_ROOT /home/aravinth/macsxperts/macs-panel/big-brother;
		fastcgi_param SCRIPT_FILENAME /home/aravinth/cpuinfo.sh;
	}
}

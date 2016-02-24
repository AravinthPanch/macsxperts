
.htaccess on bigbrother.macsxperts.com server

RewriteEngine On
RewriteRule ^(.*)$ http://localhost:3000/$1 [P]

On macs-rpi

ssh -N -R 3000:localhost:3000 aravinth@aravinth.info
ssh -N -R 3000:localhost:3000 macxpert@macsxperts.com
ssh -N -R 2222:localhost:22 macxpert@macsxperts.com

debug on server
ssh -l aravinth -p 3000 localhost
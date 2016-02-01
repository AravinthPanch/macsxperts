pm2 start app.js --name="big-brother" --watch

sudo su -c "env PATH=$PATH:/usr/local/bin pm2 startup linux -u aravinth --hp /home/aravinth"

pm2 resurrect                 # Restore previously save processes

pm2 logs big-brother
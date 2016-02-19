/**
   Author: Aravinth Panchadcharam
   Email: me@aravinth.info
   Date: 17/02/16.
   Project: Macsxperts Vertical Farming Solutions
   Description: Macsperts API Interface via Serial Port
*/

// Libraries
#include "macs_api.h"

SLIPEncodedSerial SLIPSerial(Serial1);
OSCMessage ph("/sense/ph/");
OSCMessage ec("/sense/ec/");
OSCMessage temp("/sense/temp/");
OSCMessage pumpOne("/actuate/pump/1/");
OSCMessage pumpTwo("/actuate/pump/2/");
OSCMessage pumpThree("/actuate/pump/3/");

macs_api::macs_api() {
  SLIPSerial.begin(115200);
}

void macs_api::sendPh(float phValue) {
  sendFloat(phValue, &ph);
}

void macs_api::sendEc(float ecValue) {
  sendFloat(ecValue, &ec);
}

void macs_api::sendTemp(float tempValue) {
  sendFloat(tempValue, &temp);
}

void macs_api::sendPump(int pumpNumber, int status) {
  switch (pumpNumber) {
  case 1:
    sendInt(status, &pumpOne);
    break;
  case 2:
    sendInt(status, &pumpTwo);
    break;
  case 3:
    sendInt(status, &pumpThree);
    break;
  }
}

void macs_api::sendFloat(float value, OSCMessage *msg) {
  msg->add(value);

  SLIPSerial.beginPacket();
  msg->send(SLIPSerial);

  SLIPSerial.endPacket();
  msg->empty();
}

void macs_api::sendInt(int value, OSCMessage *msg) {
  msg->add(value);

  SLIPSerial.beginPacket();
  msg->send(SLIPSerial);

  SLIPSerial.endPacket();
  msg->empty();
}



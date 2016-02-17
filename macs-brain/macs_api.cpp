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
OSCMessage phMsg("/ph/");
OSCMessage ecMsg("/ec/");
OSCMessage tempMsg("/temp/");

macs_api::macs_api() {
  SLIPSerial.begin(115200);
}

void macs_api::sendPh(float phValue) {
  send(phValue, &phMsg);
}

void macs_api::sendEc(float ecValue) {
  send(ecValue, &ecMsg);
}

void macs_api::sendTemp(float tempValue) {
  send(tempValue, &tempMsg);
}

void macs_api::send(float value, OSCMessage *msg) {
  msg->add(value);

  SLIPSerial.beginPacket();
  msg->send(SLIPSerial);

  SLIPSerial.endPacket();
  msg->empty();
}



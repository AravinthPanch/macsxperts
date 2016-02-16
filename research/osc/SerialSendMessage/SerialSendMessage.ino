/*
  Make an OSC message and send it over serial
*/

#include <OSCMessage.h>
#include <SLIPEncodedSerial.h>
SLIPEncodedSerial SLIPSerial(Serial1);
int counter = 0;

void setup() {
  //begin SLIPSerial just like Serial
  // set this as high as you can reliably run on your platform
  SLIPSerial.begin(9600);  
}


void loop() {
  //the message wants an OSC address as first argument
  OSCMessage msg("/analog/0");
  msg.add((int32_t)counter);

  SLIPSerial.beginPacket();
  // send the bytes to the SLIP stream
  msg.send(SLIPSerial);
  // mark the end of the OSC Packet
  SLIPSerial.endPacket();
  // free space occupied by message
  msg.empty();
  delay(1000);
}

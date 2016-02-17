/**
   Author: Aravinth Panchadcharam
   Email: me@aravinth.info
   Date: 17/02/16.
   Project: Macsxperts Vertical Farming Solutions
   Description: Macsperts API Interface via Serial Port
*/

// Libraries
#include "Arduino.h"
#include <OSCMessage.h>
#include <SLIPEncodedSerial.h>

// Declarations

class macs_api
{
  private:

  public:
    macs_api();
    void send(float value, OSCMessage *msg);
    void sendPh(float phValue);
    void sendEc(float ecValue);
    void sendTemp(float tempValue);
};

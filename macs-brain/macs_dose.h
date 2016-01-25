/**
   Author: Aravinth Panchadcharam
   Email: me@aravinth.info
   Date: 23/01/16.
   Project: Macsxperts Aeroponics Vertical Farming
   Description: 12V DC Peristaltic Dosing Pump
*/

// Libraries
#include "Arduino.h"

// Declarations
#define pumpOne12EnablePin 28
#define pumpOne1Apin 30
#define pumpOne2Apin 38

class macs_dose
{
  private:
    bool pumpOne12EnablePinStatus = false;
    bool pumpOne1ApinStatus = false;
    bool pumpOne2ApinStatus = false;
    bool pumpOneStatus = false;
    
  public:
    macs_dose();    
    String startPumpOne();
    String stopPumpOne();
    bool getPumpOneStatus();
};

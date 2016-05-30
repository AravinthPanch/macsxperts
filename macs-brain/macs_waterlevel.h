/**
   Author:
   Email:
   Date: 30/05/16.
   Project: Macsxperts Vertical Farming Solutions
   Description: Water Level Measurement using Float Switch
*/

// Libraries
#include "Arduino.h"

// Declarations
//TODO: Choose free GPIO pins of the controller. 
#define floatSwitch1pin 2
#define floatSwitch2pin 3
#define floatSwitch3pin 4
#define floatSwitch4pin 5

class macs_waterlevel
{
private:
  bool floatSwitch1Status = false;
  bool floatSwitch2Status = false;
  bool floatSwitch3Status = false;
  bool floatSwitch4Status = false;

public:
  // Constructor
  macs_waterlevel();

  // Float switch Status
  bool getFloatSwitch1Status();
  bool getFloatSwitch2Status();
  bool getFloatSwitch3Status();
  bool getFloatSwitch4Status();
};

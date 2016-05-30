/*
 * macs_waterlevel.h
 *
 *  Created on: May 24, 2016
 *      Author: ganesh
 */
#include "Arduino.h"
#define floatSwitch1pin 2
#define floatSwitch2pin 3
#define floatSwitch3pin 4
#define floatSwitch4pin 5
#define ledpin1 9
#define ledpin2 10
#define ledpin3 11
#define ledpin4 12


class macs_waterlevel{
private:
	bool ledpin1status = false;
	bool ledpin2status = false;
	bool ledpin3status = false;
	bool ledpin4status = false;

public:
  // Constructor
  macs_waterlevel();

  // Float switch Status
  bool getFloatSwitch1Status();
  bool getFloatSwitch2Status();
  bool getFloatSwitch3Status();
  bool getFloatSwitch4Status();
};

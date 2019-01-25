/**
   Author:
   Email:
   Date: 30/05/16.
   Project: Macsxperts Vertical Farming Solutions
   Description: Water Level controller using Float Switch
*/

// Libraries
#include "macs_waterlevel.h"

// Constructor
macs_waterlevel::macs_waterlevel() {
	pinMode(floatSwitch1pin, INPUT);
	pinMode(floatSwitch2pin, INPUT);
	pinMode(floatSwitch3pin, INPUT);
	pinMode(floatSwitch4pin, INPUT);
}

bool macs_waterlevel::getFloatSwitch1Status() {
	return floatSwitch1Status;
}

bool macs_waterlevel::getFloatSwitch2Status() {
	return floatSwitch2Status;
}

bool macs_waterlevel::getFloatSwitch3Status() {
	return floatSwitch3Status;
}

bool macs_waterlevel::getFloatSwitch4Status() {
	return floatSwitch4Status;
}
/**
   Author: Aravinth Panchadcharam
   Email: me@aravinth.info
   Date: 19/01/16.
   Project: Macsxperts Vertical Farming Solutions
   Description: Resource Factory
*/

// Libraries
#include "macs_resource.h"


macs_resource::macs_resource() {
	resourceTable[0]("0xPHx1", "Low pH");
	resourceTable[1]("0xP1x1", "P1: ON");
	resourceTable[2]("0xP1x0", "P1: OFF");

	resourceTable[3]("0xECx1", "P2,3: ON");
	resourceTable[4]("0xECx0", "P2,3: OFF");
	resourceTable[5]("0xECx2", "High EC");

	resourceTable[6]("0xP2x1", "P2: ON");
	resourceTable[7]("0xP2x0", "P2: OFF");
	resourceTable[8]("0xP3x1", "P3: ON");
	resourceTable[9]("0xP3x0", "P3: OFF");

	resourceTable[10]("0xP1x11", "P1 is switched ON");
	resourceTable[11]("0xP1x00", "P1 is switched OFF");
	resourceTable[12]("0xP2x11", "P2 is switched ON");
	resourceTable[13]("0xP2x00", "P2 is switched OFF");
	resourceTable[14]("0xP3x11", "P3 is switched ON");
	resourceTable[15]("0xP3x00", "P3 is switched OFF");
}

String macs_resource::getText(char* code) {	
	return (String)resourceTable.getValueOf(code);
}
/**
   Author: Aravinth Panchadcharam
   Email: me@aravinth.info
   Date: 19/01/16.
   Project: Macsxperts Vertical Farming Solutions
   Description: Resource Factory
*/

// Libraries
#include "Arduino.h"
#include "lib/HashMap/HashMap.h"

// Declarations
#define resourceTableSize 20

class macs_resource
{
private:	
	// storage
	HashType<char*, char*> resourceArray[resourceTableSize];

	//handles the storage [search,retrieve,insert]
	HashMap<char*, char*> resourceTable = HashMap<char*, char*>(resourceArray , resourceTableSize);

public:
	// constructor
	macs_resource();	
	String getText(char* code);
};
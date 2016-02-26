/**
   Author: Aravinth Panchadcharam
   Email: me@aravinth.info
   Date: 23/01/16.
   Project: Macsxperts Vertical Farming Solutions
   Description: 12V DC Peristaltic Dosing Pump
*/

// Libraries
#include "Arduino.h"

// Declarations
#define pumpOne12EnablePin 34
#define pumpOne1Apin 36
#define pumpOne2Apin 38

#define pumpTwo34EnablePin 40
#define pumpTwo3Apin 42
#define pumpTwo4Apin 32

#define pumpThree12EnablePin 28
#define pumpThree1Apin 30
#define pumpThree2Apin 44

#define pumpFour34EnablePin 46
#define pumpFour3Apin 48
#define pumpFour4Apin 26

#define pHmin 5.5
#define pHmax 6.5
#define ecMin 1200
#define ecMax 1600
#define phDosingInterval 1
#define ecDosingInterval 5

class macs_dose
{
private:  
  // EC & pH parameters
  float ecValue;
  float phValue;

  // Pump One Pin Status
  bool pumpOne12EnablePinStatus = false;
  bool pumpOne1ApinStatus = false;
  bool pumpOne2ApinStatus = false;
  bool pumpOneStatus = false;

  // Pump Three Pin Status
  bool pumpTwo34EnablePinStatus = false;
  bool pumpTwo3ApinStatus = false;
  bool pumpTwo4ApinStatus = false;
  bool pumpTwoStatus = false;

  // Pump Three Pin Status
  bool pumpThree12EnablePinStatus = false;
  bool pumpThree1ApinStatus = false;
  bool pumpThree2ApinStatus = false;
  bool pumpThreeStatus = false;

  // Pump Four Pin Status
  bool pumpFour34EnablePinStatus = false;
  bool pumpFour3ApinStatus = false;
  bool pumpFour4ApinStatus = false;
  bool pumpFourStatus = false;

  // pH Down Pump
  int pumpOneTimer = 0;

  // EC: Nutrient A Pump
  int pumpTwoTimer = 0;

  // EC: Nutrient B Pump
  int pumpThreeTimer = 0;

  // EC: Nutrient C Pump
  int pumpFourTimer = 0;

  // Test Function
  int testPumpTimer = 1;
  bool testPumpStatus = false;

  // Motor Drive
  void startPump(int enablePin, bool* enablePinVar,
                 int firstPin, bool* firstPinVar,
                 int secondPin, bool* secondPinVar,
                 bool* pumpStatus, int pumpNumber);

  void stopPump(int enablePin, bool* enablePinVar,
                int firstPin, bool* firstPinVar,
                int secondPin, bool* secondPinVar,
                bool* pumpStatus, int pumpNumber);

  // Pump One
  char* startPumpOne();
  char* stopPumpOne();

  // Pump Two
  String startPumpTwo();
  String stopPumpTwo();

  // Pump Three
  String startPumpThree();
  String stopPumpThree();

  // Pump Four
  String startPumpFour();
  String stopPumpFour();

public:
  // Constructor
  macs_dose();

  // Pump Status
  bool getPumpOneStatus();
  bool getPumpTwoStatus();
  bool getPumpThreeStatus();
  bool getPumpFourStatus();

  // EC & pH balance logic
  char* balancePh(float phValue);
  char* balanceEc(float ecValue);

  // Test Function
  String testPump(int pumpNr, int seconds);
  void setTestPumpStatus(bool status);
};

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

#define pHmin 5.5
#define pHmax 6.5
#define ecMin 1200
#define ecMax 1600

class macs_dose
{
private:
  float ecValue;
  float phValue;

  bool pumpOne12EnablePinStatus = false;
  bool pumpOne1ApinStatus = false;
  bool pumpOne2ApinStatus = false;
  bool pumpOneStatus = false;

  bool pumpTwo34EnablePinStatus = false;
  bool pumpTwo3ApinStatus = false;
  bool pumpTwo4ApinStatus = false;
  bool pumpTwoStatus = false;

  bool pumpThree12EnablePinStatus = false;
  bool pumpThree1ApinStatus = false;
  bool pumpThree2ApinStatus = false;
  bool pumpThreeStatus = false;

  int pumpOneTimer = 0;
  int pumpOneTimerInterval = 5;

  int pumpTwoTimer = 0;
  int pumpTwoTimerInterval = 5;

  int pumpThreeTimer = 0;
  int pumpThreeTimerInterval = 5;

  int testPumpTimer = 1;
  bool testPumpStatus = false;

  void startPump(int enablePin, bool* enablePinVar,
                 int firstPin, bool* firstPinVar,
                 int secondPin, bool* secondPinVar,
                 bool* pumpStatus, int pumpNumber);

  void stopPump(int enablePin, bool* enablePinVar,
                int firstPin, bool* firstPinVar,
                int secondPin, bool* secondPinVar,
                bool* pumpStatus, int pumpNumber);

public:
  macs_dose();
  String startPumpOne();
  String stopPumpOne();
  bool getPumpOneStatus();

  String startPumpTwo();
  String stopPumpTwo();
  bool getPumpTwoStatus();

  String startPumpThree();
  String stopPumpThree();
  bool getPumpThreeStatus();

  String balancePh(float phValue);
  String balanceEc(float ecValue);

  String testPump(int pumpNr, int seconds);
  void setTestPumpStatus(bool status);
};

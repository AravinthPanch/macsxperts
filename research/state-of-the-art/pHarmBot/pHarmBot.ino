#include <OneWire.h>
#include <DallasTemperature.h>
#include <EEPROM.h>

/* I2C interface requirements */
#include <Wire.h>

#include <farmBot.h>

/* allowcation of 1024 EEPROM  */
const byte I2CID = 0;  

int number = 0;
int state = 0;
double temp;
/* end I2C interface requirements */

// Pin assignment
const int flowMeterPin = 2;       // water flow meter pin in serial
const int pumpPin = 13;           // circulation pump pin out
const int tankLowPin = 7;         // water low sensor pin in   HIGH means water is Low
const int tankHighPin = 8;        // water high sensor pin in  LOW means water is Full
const int waterFillPin = 6;       // water  fill valve pin out
const int ONE_WIRE_BUS = 3;       // water temperature pin in
const int phDoserPin = 12;
const int ecDoserPin = 4;
const int supDoserPin = 9;
const int phDoserBtnPin = 10;

const int NORMAL = 1;             // processing state
const int FILLTANK = 2;           // processing state
const int FLOWSAMPLERATE = 1000;  // 1 second
const int OFF = 0;                // device mode
const int ON = 1;                 // device mode
const int AUTO = 3;               // device mode

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// Assign the addresses of your 1-Wire temp sensors.
// See the tutorial on how to obtain these addresses:
// http://www.hacktronics.com/Tutorials/arduino-1-wire-address-finder.html

DeviceAddress waterThermometer = { 0x28, 0xFF, 0xA7, 0xF2, 0x05, 0x00, 0x00, 0x69 };
//DeviceAddress outsideThermometer = { 0x28, 0x6B, 0xDF, 0xDF, 0x02, 0x00, 0x00, 0xC0 };
//DeviceAddress dogHouseThermometer = { 0x28, 0x59, 0xBE, 0xDF, 0x02, 0x00, 0x00, 0x9F };

volatile int flowMeterCnt = 10;        // measuring the rising edges of the signal
int systemMode = NORMAL;          // processing state (NORMAL, FILLTANK)
int pumpMode = AUTO;              // pump mode
int pumpState = LOW;              // pump current state
int pumpOnTime = 1;              // minutes that pump is ON
int pumpOffTime = 2;             // minutes that pump is OFF
unsigned long pumpTimer = 0;      // clock time when pump state should toggle

byte waterFillMode = AUTO;         // tank fill valve mode
byte waterFillState = LOW;         // tank fill valve current state
unsigned long fillInterval  = 60000;   // time since last fill one minute

byte waterTempMSB = 80;            // thermometer integer full units ie. 93
byte waterTempLSB = 2;            // thermometer rounded to one decimal place to the right ie. .2 so together 93.2
byte waterTempTarget = 87;
byte waterTempDelta = 5;
int waterTempSampleRate = 3;      // seconds between samples
unsigned long waterTempTimer = 0;

unsigned long flowTimer = 0;      // clock time when flowMeter should be sampled

int phDoserState = LOW;           // off
unsigned long phDoserTimer = 0;
byte phDoseMl = 5;                // number of ml to dose each time

byte cmdRecieved = 0;
int cmdCnt;
int command;

DEBOUNCE_DEF tankLowSensor = { tankLowPin , LOW, LOW, LOW, 0 };       // HIGH = tank empty 
DEBOUNCE_DEF tankHighSensor = { tankHighPin , LOW, LOW, LOW, 0 };     // HIGH = tank not full
DEBOUNCE_DEF phDoserBtn = { phDoserBtnPin , LOW, LOW, LOW, 0 };           // LOW = button pushed

void setup() {
  Serial.begin(9600);
  
  pinMode(pumpPin, OUTPUT);     
  digitalWrite(pumpPin, pumpState);      // set initial pump state 
  
  pinMode(waterFillPin, OUTPUT);   
  digitalWrite(waterFillPin, waterFillState); // set initial water fill value state 

  pinMode(tankLowPin, INPUT);
  digitalWrite(tankLowPin, HIGH);            // turn on pullup resistors; open switch state is HIGH
  
  pinMode(tankHighPin, INPUT);
  digitalWrite(tankHighPin, HIGH);           // turn on pullup resistors; open switch state is HIGH

  pinMode(tankHighPin, INPUT);
  digitalWrite(tankHighPin, HIGH);           // turn on pullup resistors; open switch state is HIGH

  pinMode(phDoserPin, OUTPUT);     
  digitalWrite(phDoserPin, phDoserState);      // set initial pump state 

  i2cSetup();
  oneWireSetup();
//  flowSetup();

} // setup

void loop() {
 
  debouncePin(tankLowSensor); // read tankLow switch  
  debouncePin(tankHighSensor); // read tankHigh switch
  debouncePin(phDoserBtn); // read tankHigh switch
  
  switch (systemMode) {
     case NORMAL: normalMode(); break;
     case FILLTANK: fillTankMode(); break;
     default: normalMode(); break;
  }  
  
} // loop

void normalMode()
{
  if (pumpMode == AUTO) pumpControl();
  if (phDoserState == HIGH || phDoseMl > 0) checkPhDoser();
/*
  if (phDoseMl == 0 && phDoserBtn.pinStable == HIGH && phDoserBtn.pinState == LOW)    // pushed manual dose
  {
    phDoseMl = 3;
    checkPhDoser();
  }
*/ 
} // normalMode

void checkPhDoser()
{
  if (phDoseMl > 0)
  {
    phDoserTimer = setSecondsTimer(phDoseMl);  // one milli liter per second
    phDoserState = HIGH;
    digitalWrite(phDoserPin, phDoserState);  
    Serial.print("Doser is ");
    Serial.print(phDoserState);
    Serial.print(" for ");
    Serial.println(phDoseMl);
    phDoseMl = 0;
  }
  if (checkTimer(phDoserTimer) == HIGH) {          // timer went off
    phDoserState = LOW;                            // turn doser off    
    digitalWrite(phDoserPin, phDoserState);  
    Serial.println("Doser Off");
  }
}

void checkWaterTemp()
{
  if (checkTimer(waterTempTimer) == HIGH) {
    getWaterTemp();
    waterTempTimer = setSecondsTimer(waterTempSampleRate);   
//    Serial.print("sample temp \n");
  }
} //checkWaterTemp

void pumpControl()
{
  if (tankLowSensor.pinStable == HIGH && tankLowSensor.pinState == HIGH) { // low water; turn off pump
    systemMode = FILLTANK;
    pumpState = LOW;
    digitalWrite(pumpPin, pumpState);  
    pumpTimer = millis();
  } else { // water in tank    
      if (checkTimer(pumpTimer) == HIGH) {
        pumpState = !pumpState;
        if (pumpState == HIGH) Serial.println("Pump On");
        if (pumpState == LOW) Serial.println("Pump Off");
        digitalWrite(pumpPin, pumpState);
        if (pumpState == HIGH) {
            pumpTimer = setMinutesTimer(pumpOnTime);
         } else {
            pumpTimer = setMinutesTimer(pumpOffTime);
         }
      }     
    }  
}  // pumpControl

void fillTankMode()
{
  if (tankHighSensor.pinStable == HIGH && tankHighSensor.pinState == LOW) {
    systemMode = NORMAL;
    Serial.print("tank full\n");
    waterFillState = LOW;
    digitalWrite(waterFillPin, waterFillState); //  turn off water fill valve
  } else if (tankLowSensor.pinStable == HIGH && tankLowSensor.pinState == HIGH ) {
    waterFillState = HIGH;
    digitalWrite(waterFillPin, waterFillState); //  turn on water fill valve
    Serial.print("Water low\n");
  } else {
      Serial.print("Filling tank\n");
  }
} // fillTankMode

unsigned long setMinutesTimer(int waitTime)
{ 
  unsigned long endTime;

   endTime = millis() + (waitTime * 60000);  // convert back to milliseconds from minutes
   return endTime;
} // setMinutesTimer

unsigned long setSecondsTimer(int waitTime)
{ 
  unsigned long endTime;

   endTime = millis() + (waitTime * 1000);  // convert back to milliseconds from seconds
   return endTime;
} // setSecondsTimer

int checkTimer(unsigned long timer)
{
   if (millis() > timer) {return HIGH;}
   else {return LOW;}
} // checkTimer

void debouncePin(DEBOUNCE_DEF& target) {
  long debounceDelay = 50;    // the debounce time; increase if the output flickers

   // read the state of the pin into a local variable:
  int reading = digitalRead(target.pin);

  // check to see if pin state has changed and you've waited
  // long enough since the last test to ignore any noise:  
  if (reading != target.pinState) {
    // reset the debouncing timer
    target.lastDebounceTime = millis();
    target.pinStable = LOW;
        if (target.pinOldState == LOW) {target.pinOldState = HIGH;} else {target.pinOldState = LOW;}
 } 
  
  if ((millis() - target.lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:
	  target.pinStable = HIGH;
   }
  target.pinState = reading;
} // debouncePin

/*
  Flow meter functions
*/

void flowMeterRpm ()     //This is the function that the interupt calls
{
  flowMeterCnt++;  //This function measures the rising and falling edge of the hall effect sensors signal
} // flowMeterRpm

void flowSetup() //
{
  pinMode(flowMeterPin, INPUT); //initializes digital pin as an input
  attachInterrupt(0, flowMeterRpm, RISING); //and the interrupt is attached
} // flowSetup

void flowMeter()
{
// reading liquid flow rate using Seeeduino and Water Flow Sensor from Seeedstudio.com
// Code adapted by Charles Gantt from PC Fan RPM code written by Crenn @thebestcasescenario.com
// http:/themakersworkbench.com http://thebestcasescenario.com http://seeedstudio.com

int Calc;                              

  if (checkTimer(flowTimer) == HIGH) {// Wait 1 second
    cli();                            // Disable interrupts
    Calc = (flowMeterCnt * 60 / 7.5); // (Pulse frequency x 60) / 7.5Q, = flow rate in L/hour
    Serial.print (Calc, DEC);         // Prints the number calculated above
    Serial.print (" L/hour\r\n");     // Prints "L/hour" and returns a  new line

    setSecondsTimer(FLOWSAMPLERATE);
    flowMeterCnt = 0;                 // Set NbTops to 0 ready for calculations
    sei();                            // Enables interrupts
  }
  
} // flowMeter

/*
  End Flow Meter Functions
*/

/* IC2 support */


void i2cSetup() {
  EEPROM.write(I2CID, 0x8);
  // set default i2c ID if not yet defined
 // if (EEPROM.read(I2CID)==0) { EEPROM.write(I2CID, 0x4); }
 
 // initialize i2c as slave
 Wire.begin(8);
 
 // define callbacks for i2c communication
 Wire.onReceive(i2cCommand);
 Wire.onRequest(myRequest);
} // i2cSetup

byte i2cResponse[32];
int index = 0;

void myRequest() {    // callback for sending data
  Wire.write(i2cResponse[index]);
  ++index;
}
  
void i2cCommand(int byteCount){ // callback for received data
  unsigned char received;
//  int cmdCnt;
//  int command;
  int output;
 
  cmdCnt = Wire.available();
  if (cmdCnt > 0 ) {
    cmdRecieved++;
    command = Wire.read();      // first byte is the command
    switch (command)
    {
      case 1:    // set Pump Mode (Off =0, On=1, Auto=3)
        if (cmdCnt == 2 ) {     // next byte is the mode
          pumpMode = Wire.read();      
          switch (pumpMode) {
            case ON: if (tankLowSensor.pinStable == HIGH && tankLowSensor.pinState == LOW) {pumpState = HIGH; } break;
            case OFF: pumpState = LOW; break;
           }
           digitalWrite(pumpPin, pumpState);
           Serial.print("Pump state = ");
           Serial.print(pumpState);
           Serial.print("\n");
        }
        break;
      
      case 2:    // set Pump auto ON time
        if (cmdCnt == 3 ) {    // next 2 bytes is the time
          received = Wire.read();
          output = (received << 8);  // shift to high byte
          received = Wire.read();
          output = output + received; // add in low byte
          pumpOnTime = output;      // ON time in seconds
  Serial.print("Pump auto ON time = ");
  Serial.println(pumpOnTime);
        }
        break;
      
      case 3:    // set Pump auto OFF time
        if (cmdCnt == 3 ) {    // next 2 bytes is the time
          received = Wire.read();
          output = (received << 8);  // shift to high byte
          received = Wire.read();
          output = output + received; // add in low byte
          pumpOnTime = output;      // OFF time in seconds
  Serial.print("Pump auto OFF time = ");
  Serial.println(pumpOffTime);
       }
        break;
        
      case 4:    // set water Fill Value Mode (Off, On, Auto)
        if (cmdCnt == 2 ) {    // next byte is the mode
          waterFillMode = Wire.read();    
          switch (waterFillMode) {
            case ON: if (tankHighSensor.pinStable == HIGH && tankHighSensor.pinState == HIGH) {waterFillState = HIGH; } break; // only on if not full
            case OFF: waterFillState = LOW;  break;
            case AUTO: if (tankHighSensor.pinStable == HIGH && tankHighSensor.pinState == LOW) {waterFillState = LOW; } break; // turn off if full
          }
          digitalWrite(waterFillPin, waterFillState);
  Serial.print("water Fill Mode = ");
  Serial.println(waterFillMode);
        }
         break;

      case 5:    // turn on phDoser for x seconds
        if (cmdCnt == 2 ) {    // next byte is the number of seconds
          phDoseMl = Wire.read();
          digitalWrite(phDoserPin, HIGH);  
        }
        break;

      case 6:    // turn on phDoser 
        digitalWrite(phDoserPin, HIGH);  
        break;

      case 7:    // turn off phDoser
        digitalWrite(phDoserPin, LOW);  
        break;
              
      case 8:
          i2cRequest();
          index = 0;
          break;
      
       default:
         Serial.print("Command not supported ");
         Serial.println(command);
         break;
   } // end switch 
  } // end if cmdCnt
  
} // ic2Command
 

void i2cRequest() {    // callback for sending data
  byte i2cResponseLen = 0;                 // response length
  unsigned long currentTime = millis();
  unsigned long transitionTime = 0;
  byte pumpStatus = 0;
  byte waterLevel = 0;
  byte refillStatus = 0;
  byte waterTempSettings = 0;
 
    pumpStatus = (pumpMode << 6) | (pumpState << 5);
    if (tankHighSensor.pinState == LOW) { waterLevel = 2; } // Full
    else if (tankLowSensor.pinState == HIGH) { waterLevel = 0;} // Low
    else { waterLevel = 1;}  // Adequate
    waterLevel = waterLevel << 3;
    refillStatus = (waterFillMode << 1) | waterFillState;
    
    i2cResponse[i2cResponseLen] = pumpStatus | waterLevel | refillStatus; 
    i2cResponseLen++;  
   
    if (currentTime < pumpTimer) {transitionTime = pumpTimer - currentTime;} else {transitionTime = 0;}
    transitionTime = transitionTime / 60000;  // convert to minutes
    i2cResponse[i2cResponseLen] = (byte)(transitionTime >> 8); // high byte
    i2cResponseLen++;
    
    i2cResponse[i2cResponseLen] = (byte)transitionTime; // low byte
    i2cResponseLen++;
    
    i2cResponse[i2cResponseLen] = (byte)(pumpOnTime >> 8); // high byte in minutes
    i2cResponseLen++;
    i2cResponse[i2cResponseLen] = (byte)pumpOnTime; // low byte
    i2cResponseLen++;
    
    i2cResponse[i2cResponseLen] = (byte)(pumpOffTime >> 8); // high byte in minutes
    i2cResponseLen++;
    i2cResponse[i2cResponseLen] = (byte)pumpOffTime; // low byte
    i2cResponseLen++;
        
    fillInterval = fillInterval / 60000;             // convert to minutes
    i2cResponse[i2cResponseLen] = (byte)(fillInterval >> 8);  // high byte
    i2cResponseLen++;
    i2cResponse[i2cResponseLen] = (byte)fillInterval;  // low byte
    i2cResponseLen++;

    i2cResponse[i2cResponseLen] = (byte)(flowMeterCnt >> 8); // high byte
    i2cResponseLen++;
    i2cResponse[i2cResponseLen] = (byte)flowMeterCnt; // low byte
    i2cResponseLen++;  

    i2cResponse[i2cResponseLen] = (byte)(waterTempMSB);  // left of decimal byte
    i2cResponseLen++;
    i2cResponse[i2cResponseLen] = (byte)(waterTempLSB);  // right if decimal byte
    i2cResponseLen++;
    
    i2cResponse[i2cResponseLen] = waterTempTarget;  // byte
    i2cResponseLen++;  

    i2cResponse[i2cResponseLen] = waterTempDelta;  // byte
    i2cResponseLen++;    // compensate for zero based array 24
 /* 
  Wire.write(i2cResponse, i2cResponseLen);
  */
} // i2cRequest
 
// end I2C support
// git clone http://github.com/jrowberg/i2cdevlib


// Reads DS18B20 "1-Wire" digital temperature sensors.
// Tutorial: http://www.hacktronics.com/Tutorials/arduino-1-wire-tutorial.html

void oneWireSetup()
{
  // Start up the library
  sensors.begin();
  sensors.setResolution(waterThermometer, 10); // set the resolution to 10 bit (good enough?)
//  sensors.setResolution(outsideThermometer, 10);
//  sensors.setResolution(dogHouseThermometer, 10);
} // oneWireSetup

float getTemperature(DeviceAddress deviceAddress)
{
  float tempF = 0;
  float tempC = sensors.getTempC(deviceAddress);
  if (tempC == -127.00) {
    Serial.print("Error getting temperature");
  } else {
    tempF = DallasTemperature::toFahrenheit(tempC);
    Serial.print("C: ");
    Serial.print(tempC);
    Serial.print(" F: ");
    Serial.print(DallasTemperature::toFahrenheit(tempC));
    Serial.print("\n");;
  }
  return tempF;
}

void getWaterTemp()
{ 
  float tempF = 0;
  double leftPart;
  double rightPart;
  double newRight;
  sensors.requestTemperatures();
  tempF = getTemperature(waterThermometer);
 
  rightPart = modf(tempF, &leftPart);
  waterTempMSB = (byte)leftPart;
  newRight = rightPart*10;
  rightPart = modf(newRight, &leftPart);
  waterTempLSB = (byte)leftPart;
}  // getWaterTemp
// end DS18B20 support


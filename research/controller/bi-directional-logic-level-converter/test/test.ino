#include <TimerOne.h>

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(writeRoutine);
}

void writeRoutine() {
  Serial1.print(millis() / 1000);
  Serial1.print(" : ");
  Serial1.println("Hola");
}

void loop() {
  if (Serial1.available()) {
    int inByte = Serial1.read();
    Serial.write(inByte);
  }
}

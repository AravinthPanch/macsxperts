/* sketch 
turn on a LED when the button is pressed
turn it off when the button is not pressed (or released)
*/
int pinButton = 8; //the pin where we connect the button
int LED = 2; //the pin we connect the LED
 
void setup() {
  pinMode(pinButton, INPUT); //set the button pin as INPUT
  pinMode(LED, OUTPUT); //set the LED pin as OUTPUT
}
 
void loop() {
     //write 0 or low to led pin
  int stateButton = digitalRead(pinButton); //read the state of the button
  if(stateButton == 1) { //if is pressed
     digitalWrite(LED, HIGH); //write 1 or HIGH to led pin
  } else { //if not pressed
     digitalWrite(LED, LOW);  //write 0 or low to led pin
  }
}

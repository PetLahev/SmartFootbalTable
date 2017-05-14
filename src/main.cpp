/*
  Smart Foosball table
*/

#include "Arduino.h"
#include "TM1637Display.h"

void setup() {
  pinMode(A0, OUTPUT); // Set buzzer - pin 9 as an output
}

void loop() {
  tone(A0, 1000); // Send 1KHz sound signal...
  delay(1000);        // ...for 1 sec
  noTone(A0);     // Stop sound...
  delay(1000);        // ...for 1sec
}

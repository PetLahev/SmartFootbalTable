/*
Based on the Debaouncer class from Anton Pechinsky
https://github.com/apechinsky/arduino-libs/blob/master/Debouncer/

Performs specific logic for 4 buttons on the display board
*/
#include "Arduino.h"
#include "DebouncerFootball.h"

DebouncerFootball::DebouncerFootball() {
    // default value, looks like this will work even it looks too high
    this->bounceTime = 500;
    this->sizeOfArray = 4; // ideally get it dynamically
    this->changedPin = 0;
    this->valueTimestamp = 0;
    this->resetS = false;
}

void DebouncerFootball::init(int pins[4]) {
    this->buttonPins = pins;
}

bool DebouncerFootball::update() {

  int newValue = 0;
  bool valueChanged[4];
  int changedPins[4];

  unsigned long r = millis() - valueTimestamp;
  bool bounceCompleted = r > bounceTime;
  if (!bounceCompleted)  return false;

  bool hasChange = false; resetS = false;
  for (int i = 0; i < sizeOfArray; i++) {
      newValue = digitalRead(buttonPins[i]);
      changedPins[i] = buttonPins[i];
      valueChanged[i] = newValue == HIGH;
      if (valueChanged[i]) hasChange = true;
  }

  if (hasChange) {
    // find out which pin has changed
    // if both buttons on one board are pressed
    // then this is a reset state
    // assuming that the boths pins are coupled
    int multiChange1 = 0;
    int multiChange2 = 0;
    for (int i = 0; i < sizeOfArray; i++) {
        if (valueChanged[i]) {
          changedPin = changedPins[i];
          if (i < 2 ) multiChange1 +=1;
          if (i > 1 ) multiChange2 +=1;
        }
    }

    if (multiChange1 == 2 || multiChange2 == 2) {
      resetS = true;
    }

    valueTimestamp = millis();
    return true;
  }
  return false;
}

int DebouncerFootball::getChangedPin() {
  return changedPin;
}

bool DebouncerFootball::resetState() {
  return resetS;
}

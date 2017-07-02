/*
Based on the Debaouncer class from Anton Pechinsky
https://github.com/apechinsky/arduino-libs/blob/master/Debouncer/
*/
#ifndef DebouncerFootball_h
#define DebouncerFootball_h

#include <inttypes.h>

/*
Specific debouncing class for smart football table project
Handles all 4 buttons we use for changing score
*/
class DebouncerFootball {

public:
  /**
   * Constructor
  **/
  DebouncerFootball();

  /**
   * Have this method because I don't know yet how to properly initialize
   * the array in aconstructor (want to do that after the pins are set)
   * @param buttonPins - pins of the UP/DOWN buttons on the display
  **/
  void init(int buttonPins[4]);

  /**
   * Performs main debounce logic. Goes through all given pins
   * and checks if value has changed from LOW to HIGH
   *
   * @return true - if any value of any pin changed
   *         false - no change anywhere
  **/
  bool update();

  /**
   * Returns the pin where the changed happened
   *
   * @return the pin number where a state changed
  **/
  int getChangedPin();

  /**
   * Specific logic for pressing both buttons and the same time
   * If the buttons are pressed for 3 seconds this function returns true
   * @return true  - if both buttons are pressed for >= default debunce value
   *         false -
  **/
  bool resetState();

private:
  /**
   * http://forum.arduino.cc/index.php?topic=117393.0
   * If I'm passing an array the type in the class where the array is assigned
   * must be 'int *buttonPins'
  **/
  int* buttonPins;
  int bounceTime;
  int changedPin;
  int sizeOfArray;
  bool resetS;
  unsigned long valueTimestamp;
};

#endif

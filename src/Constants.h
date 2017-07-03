/*
  Contains all shared constatnts
*/

#ifndef Constants_h
#define Constants_h

#include <stdint.h>
#include "TM1637Display.h"

const uint8_t AHOJ[] = {
  SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G,   // A
  SEG_B | SEG_C | SEG_E | SEG_F | SEG_G,           // H
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
  SEG_B | SEG_C | SEG_D | SEG_E                    // J
  };

const uint8_t GOAL[] = {
    SEG_A | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,   // G
    SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
    SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G,   // A
    SEG_E | SEG_F | SEG_D                            // l
    };

const int BUZZER_PIN = 14;

/*
  Defines pins for the test button and LED pin
*/
const int TEST_BTN = 2;
const int TEST_LED = 3;

/*
  Defines pins for both displays
*/
const int DISP1_CLK = 9;
const int DISP1_DIO = 10;
const int DISP2_CLK = 5;
const int DISP2_DIO = 6;

/*
  Defines pins of buttons for both displays
*/
const int BTN_DISP1_UP = 11;
const int BTN_DISP1_DOWN = 12;
const int BTN_DISP2_UP = 7;
const int BTN_DISP2_DOWN = 8;

#endif

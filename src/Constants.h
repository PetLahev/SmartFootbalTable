/*
  Contains all shared constatnts
*/
#include <stdint.h>
#include "TM1637Display.h"

const uint8_t AHOJ[] = {
  SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G,   // A
  SEG_B | SEG_C | SEG_E | SEG_F | SEG_G,           // H
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
  SEG_B | SEG_C | SEG_D | SEG_E                    // J
  };

#define BUZZER_PIN 14

/*
  Defines pins for the test button and LED pin
*/
#define TEST_BTN 2
#define TEST_LED 3

/*
  Defines pins for both displays
*/
#define DISP1_CLK 9
#define DISP1_DIO 10
#define DISP2_CLK 5
#define DISP2_DIO 6

/*
  Defines pins of buttons for both displays
*/
#define BTN_DISP1_UP 11
#define BTN_DISP1_DOWN 12
#define BTN_DISP2_UP 7
#define BTN_DISP2_DOWN 8

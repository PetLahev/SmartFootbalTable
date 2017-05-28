/*
  Smart Foosball table
*/

#include "Arduino.h"
#include "TM1637Display.h"

#define TEST_BTN 2
#define TEST_LED 3

#define DISP1_CLK 9
#define DISP1_DIO 10
#define DISP2_CLK 5
#define DISP2_DIO 6

const uint8_t AHOJ[] = {
  SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G,   // A
  SEG_B | SEG_C | SEG_E | SEG_F | SEG_G,           // H
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
  SEG_B | SEG_C | SEG_D | SEG_E                    // J
  };

TM1637Display disp1(DISP1_CLK, DISP1_DIO);
TM1637Display disp2(DISP2_CLK, DISP2_DIO);

void setup() {
  pinMode(A0, OUTPUT);          // Set buzzer - pin 9 as an output
  pinMode(TEST_LED, OUTPUT);
  pinMode(TEST_BTN, INPUT);
  disp1.setBrightness(10);
  disp2.setBrightness(10);

  // welcome message
  disp1.setSegments(AHOJ);
  disp2.setSegments(AHOJ);

  tone(A0, 1000); // Send 1KHz sound signal...
  delay(1000);        // ...for 1 sec
  noTone(A0);
  delay(1000);

  disp1.showNumberDecEx(0, 2, true);
  delay(1000);
}

void loop() {

  if (digitalRead(TEST_BTN) == LOW) {
    // move this to standalone file (ino or cpp)
    tone(A0, 400);
    delay(200);
    noTone(A0);

    digitalWrite(TEST_LED, HIGH);
    delay(200);
    digitalWrite(TEST_LED, LOW);
    delay(200);
    digitalWrite(TEST_LED, HIGH);
    delay(200);
    digitalWrite(TEST_LED, LOW);

    const int TEST_DELAY = 800;
    int k;
    uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };
    data[0] = 0b01001001;
    data[1] = disp1.encodeDigit(1);
    data[2] = disp1.encodeDigit(2);
    data[3] = disp1.encodeDigit(3);

    for(k = 3; k >= 0; k--) {
    	disp1.setSegments(data, 1, k);
    	delay(TEST_DELAY);
    }

    disp1.showNumberDecEx(0, 2, true);

    tone(A0, 2000);
    delay(100);
    tone(A0, 400);
    delay(100);
    noTone(A0);

  }
}

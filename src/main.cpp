/*
  Smart Foosball table
*/

#include "Arduino.h"
#include "TM1637Display.h"
#include "main.h"
#include "DebouncerFootball.h"
#include "Constants.h"
#include "globals.h"
#include "scoreController.h"

scoreController score;
DebouncerFootball deb;

void setup() {

  Serial.begin(9600);
  Serial.println("Kick off");

  // initialize all pins and setup the variables and objects
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(TEST_LED, OUTPUT);
  pinMode(TEST_BTN, INPUT);
  pinMode(BTN_DISP1_UP, INPUT);
  pinMode(BTN_DISP1_DOWN, INPUT);
  pinMode(BTN_DISP2_UP, INPUT);
  pinMode(BTN_DISP2_DOWN, INPUT);
  disp1.setBrightness(10);
  disp2.setBrightness(10);

  disp1.setSegments(AHOJ);
  disp2.setSegments(AHOJ);

  // button pins array
  int pins[4] = {BTN_DISP1_UP, BTN_DISP1_DOWN, BTN_DISP2_UP, BTN_DISP2_DOWN };
  deb.init(pins);

  tone(A0, 1000); // Send 1KHz sound signal...
  delay(1000);   // ...for 1 sec
  noTone(A0);

  // this will clear the welcome text
  score.scoreDisplay1(false);
  score.scoreDisplay2(false);

  delay(1000);
}

void loop() {

  bool hasChanged = deb.update();
  if (hasChanged && deb.resetState())  {
    Serial.println("RESET state");
    score.reset();
    return;
  }

  if (hasChanged) {
      switch (deb.getChangedPin()) {
        case BTN_DISP1_UP:
          Serial.println("GOAL!!! Team 1");
          score.scoreDisplay1(true);
          break;
        case BTN_DISP1_DOWN:
          Serial.println("LOOSER 1");
          score.scoreDisplay1(false);
          break;
        case BTN_DISP2_UP:
          Serial.println("GOAL!!! Team 2");
          score.scoreDisplay2(true);
          break;
        case BTN_DISP2_DOWN:
          Serial.println("LOOSER 2");
          score.scoreDisplay2(false);
          break;
      }
  }

  if (digitalRead(TEST_BTN) == LOW) {

    /* TODO: move this to standalone file (ino or cpp) and make it working with
             both displays
    */
    tone(A0, 400, 500);
    /*//delay(200);
    //noTone(A0);

    blinkLed();

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
      blinkLed();
    }

    disp1.showNumberDecEx(0, 2, true);

    tone(A0, 2000);
    delay(100);
    tone(A0, 400);
    delay(100);
    noTone(A0);
*/
  }
  delay(10);
}

void blinkLed() {
  digitalWrite(TEST_LED, HIGH);
  delay(200);
  digitalWrite(TEST_LED, LOW);
  delay(200);
  digitalWrite(TEST_LED, HIGH);
  delay(200);
  digitalWrite(TEST_LED, LOW);
}

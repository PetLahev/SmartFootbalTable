/**
* 
**/
#include "Arduino.h"
#include "stdint.h"
#include "Constants.h"
#include "Globals.h"
#include "testButton.h"

testButton::testButton() {
}

void testButton::runTest() {

  const int testDelay = 200;
  const int maxNumber = 99;
  uint8_t data1[] = { 0xff, 0xff, 0xff, 0xff };
  uint8_t data2[] = { 0xff, 0xff, 0xff, 0xff };

  playTone();

  for(int i = 0; i <= maxNumber; i++) {

    int remind1 = 0;
    if (i > 9) remind1 = i/10;
    int scoreTeam2 = (maxNumber-i);
    int remind2 = 0;
    if (scoreTeam2 > 9) remind2 = scoreTeam2/10;
    int digit1 = i % 10;
    int digit2 = scoreTeam2 % 10;

    data1[0] = disp1.encodeDigit(remind1);
    data1[1] = disp1.encodeDigit(digit1);
    data1[2] = disp1.encodeDigit(remind2);
    data1[3] = disp1.encodeDigit(digit2);

    data2[0] = data1[2];
    data2[1] = data1[3];
    data2[2] = data1[0];
    data2[3] = data1[1];

    data1[1] += 128;
    data2[1] += 128;

    disp1.setSegments(data1);
    disp2.setSegments(data2);
    delay(testDelay);
    digitalWrite(TEST_LED, (i % 2) == 0);
  }

  disp1.setSegments(AHOJ);
  disp2.setSegments(DOOH);
  delay(testDelay);

  disp1.setSegments(GOAL);
  disp2.setSegments(COOL);
  delay(testDelay);

  disp1.setSegments(COOL);
  disp2.setSegments(GOAL);
  delay(testDelay);

  disp1.setSegments(DOOH);
  disp2.setSegments(AHOJ);
  delay(testDelay);

  disp1.showNumberDecEx(0, 0b10000000, true);
  disp2.showNumberDecEx(0, 0b10000000, true);

  playTone();
}

void testButton::playTone() {
  tone(BUZZER_PIN, 400);
  delay(400);
  noTone(BUZZER_PIN);
}

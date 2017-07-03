/*
  Smart Foosball table
*/

#include "Arduino.h"
#include "TM1637Display.h"
#include "main.h"
#include "DebouncerFootball.h"
#include "Constants.h"

TM1637Display disp1(DISP1_CLK, DISP1_DIO);
TM1637Display disp2(DISP2_CLK, DISP2_DIO);

/*
TODO: Move to standalone class
Responsible for all functions around scores
*/
class Score {
private:
  int score1;
  int score2;
  uint8_t data1[4];
  uint8_t data2[4];

  void changeScore() {

    int remind1 = 0;
    if (score1 > 9) remind1 = score1/10;
    int remind2 = 0;
    if (score2 > 9) remind2 = score2/10;
    int digit1 = score1 % 10;
    int digit2 = score2 % 10;

    data1[0] = disp1.encodeDigit(remind1);
    data2[0] = disp2.encodeDigit(remind2);
    data1[1] = disp1.encodeDigit(digit1);
    data2[1] = disp2.encodeDigit(digit2);

    // swap the result for the other team
    data1[2] = data2[0];
    data2[2] = data1[0];
    data1[3] = data2[1];
    data2[3] = data1[1];

    data1[1] = data1[1]+128;
    data2[1] = data2[1]+128;
    disp1.setSegments(data1);
    disp2.setSegments(data2);
  }

public:
  void showWelcomeMessage() {
    disp1.setSegments(AHOJ);
    disp2.setSegments(AHOJ);
  }
  void scoreDisplay1(bool up) {
    if (up) {
      if (score1 < 99) {
       score1 +=1;
      }
      else {
        score1 = 0;
      }
      tone(A0, 900);
      delay(100);
      noTone(A0);
    }
    else {
      if (score1 > 0) score1 -=1;
      tone(A0, 500);
      delay(100);
      noTone(A0);
    }
    changeScore();
  }
  void scoreDisplay2(bool up) {
    if (up) {
      if (score2 < 99) {
       score2 +=1;
      }
      else {
        score2 = 0;
      }
    }
    else {
      if (score2 > 0) score2 -=1;
    }
    changeScore();
  }
};

Score scoreController;
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

  scoreController.showWelcomeMessage();

  // button pins array
  int pins[4] = {BTN_DISP1_UP, BTN_DISP1_DOWN, BTN_DISP2_UP, BTN_DISP2_DOWN };
  deb.init(pins);

  tone(A0, 1000); // Send 1KHz sound signal...
  delay(1000);   // ...for 1 sec
  noTone(A0);
  delay(1000);

  disp1.showNumberDecEx(0, 2, true);
  disp2.showNumberDecEx(0, 2, true);
  delay(1000);
}

void loop() {

  bool hasChanged = deb.update();
  if (hasChanged && deb.resetState())  {
    Serial.println("RESET state");
    return;
  }

  if (hasChanged) {
      switch (deb.getChangedPin()) {
        case BTN_DISP1_UP:
          Serial.println("GOAL!!! Team 1");
          scoreController.scoreDisplay1(true);
          break;
        case BTN_DISP1_DOWN:
          Serial.println("LOOSER 1");
          scoreController.scoreDisplay1(false);
          break;
        case BTN_DISP2_UP:
          Serial.println("GOAL!!! Team 2");
          scoreController.scoreDisplay2(true);
          break;
        case BTN_DISP2_DOWN:
          Serial.println("LOOSER 2");
          scoreController.scoreDisplay2(false);
          break;
      }
  }

  if (digitalRead(TEST_BTN) == LOW) {

    /* TODO: move this to standalone file (ino or cpp) and make it working with
             both displays
    */
    tone(A0, 400);
    delay(200);
    noTone(A0);

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

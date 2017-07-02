/*
  Smart Foosball table
*/

#include "Arduino.h"
#include "TM1637Display.h"
#include "main.h"
#include "DebouncerFootball.h"

#define TEST_BTN 2
#define TEST_LED 3
#define BTN_HOME_UP 11
#define BTN_AWAY_UP 7
#define BTN_HOME_DOWN 12
#define BTN_AWAY_DOWN 8


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

/*
Responsible for all functions around scores
*/
class Score {
private:
  int score1;
  int score2;
  uint8_t data1[3];
  uint8_t data2[3];

  void changeScore() {

    int remind1 = 0;
    if (score1 > 9) remind1 = score1/10;
    int remind2 = 0;
  //  if (score2 > 9) remind2 = score2/10;
    int digit1 = score1 %10;
    int digit2 = score2;

    data1[0] = disp1.encodeDigit(remind1);
    data2[0] = disp2.encodeDigit(remind2);
    data1[1] = disp1.encodeDigit(digit1);
    data2[1] = disp2.encodeDigit(digit2);
    data1[2] = disp1.encodeDigit(remind2);
    data2[2] = disp2.encodeDigit(remind1);
    data1[3] = disp1.encodeDigit(digit2);
    data2[3] = disp2.encodeDigit(digit1);

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
    }
    else {
      if (score1 > 0) score1 -=1;
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
  Serial.println("Start");
  // initialize all pins and setup the variables and objects
  pinMode(A0, OUTPUT);    // Set buzzer - pin 9 as an output
  pinMode(TEST_LED, OUTPUT);
  pinMode(TEST_BTN, INPUT);
  pinMode(BTN_HOME_UP, INPUT);
  disp1.setBrightness(10);
  disp2.setBrightness(10);

  scoreController.showWelcomeMessage();
  // button pins array
  int pins[4] = {BTN_HOME_UP, BTN_HOME_DOWN, BTN_HOME_UP, BTN_HOME_DOWN };
  deb.init(pins);

  tone(A0, 1000); // Send 1KHz sound signal...
  delay(1000);   // ...for 1 sec
  noTone(A0);
  delay(1000);

  disp1.showNumberDecEx(0, 2, true);
  delay(1000);
}

void loop() {

  bool hasChanged = deb.update();
  if (hasChanged && deb.resetState())  {
    return;
  }

  if (hasChanged) {
      switch (deb.getChangedPin()) {
        case BTN_HOME_UP:
          scoreController.scoreDisplay1(true);
          break;
        case BTN_HOME_DOWN:
          scoreController.scoreDisplay1(false);
          break;
        case BTN_AWAY_UP:
          scoreController.scoreDisplay2(true);
          break;
        case BTN_AWAY_DOWN:
          scoreController.scoreDisplay2(false);
          break;
      }
  }

  if (digitalRead(TEST_BTN) == LOW) {

    // move this to standalone file (ino or cpp)
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

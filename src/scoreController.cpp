
#include "Constants.h"
#include "globals.h"
#include "Arduino.h"
#include "scoreController.h"

scoreController::scoreController() {
   reset();
}

void scoreController::scoreDisplay1(bool up) {

  updateScore(score1, up);
  if (up) {
    playGoalTone();
    displayGoalText1();
  }
  else {
    playLoseTone();
  }

  if (score1 == goalsPerGame) {
    Serial.println("Team 1 won the game!");
    gamesWon1 +=1;
    Serial.print("The score is ");
    Serial.print(gamesWon1);
    Serial.print(" : ");
    Serial.println(gamesWon2);
    resetGame();
  }

  displayScore();
}

void scoreController::scoreDisplay2(bool up) {

  updateScore(score2, up);
  if (up) {
    playGoalTone();
    displayGoalText2();
  }
  else {
    playLoseTone();
  }

  if (score2 == goalsPerGame) {
    Serial.println("Team 2 won the game!");
    gamesWon2 +=1;
    Serial.print("The score is ");
    Serial.print(gamesWon1);
    Serial.print(" : ");
    Serial.println(gamesWon2);
    resetGame();
  }

  displayScore();
}

void scoreController::reset() {
  score1=0;
  score2=0;
  games=0;
  gamesWon1=0;
  gamesWon2=0;
  for(int i=0;i<arraySize;i++) {
    data1[i]= 0;
    data2[i]= 0;
  }
  displayScore();  
}

/**
* It resets the game but the match continues
**/
void scoreController::resetGame() {
  score1=0;
  score2=0;
  for(int i=0;i<this->arraySize;i++) {
    this->data1[i]= 0;
    this->data2[i]= 0;
  }
  disp1.setSegments(this->data1);
  disp2.setSegments(this->data2);
}

void scoreController::displayScore() {

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

/**
*  Updates given score according to the up flag
*
* @params &score - referenced score to be updated
*         up - if true the score will be increased otherwise decreased
**/
void scoreController::updateScore(int &score, bool up) {
  if (up) {
    if (score1 < 99) {
     score +=1;
    }
    else {
      score = 0;
    }
  }
  else {
    if (score > 0) score -=1;
  }
}

void scoreController::playGoalTone() {
  tone(BUZZER_PIN, 900);
  delay(100);
  noTone(BUZZER_PIN);
}

void scoreController::playLoseTone() {
  tone(BUZZER_PIN, 500);
  delay(100);
  noTone(BUZZER_PIN);
}

void scoreController::displayGoalText1() {
  disp1.setSegments(GOAL);
  delay(300);
  displayScore();
  delay(300);
  disp1.setSegments(GOAL);
  delay(300);
}

void scoreController::displayGoalText2() {
  disp2.setSegments(GOAL);
  delay(300);
  displayScore();
  delay(300);
  disp2.setSegments(GOAL);
  delay(300);
}

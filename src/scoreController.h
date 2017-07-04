
#ifndef scoreController_h
#define scoreController_h

#include <stdint.h>

class scoreController {
public:
  /**
  *  Constructor
  **/
  scoreController();

  /**
  *  Updates score for the team 1
  *  @params up - if the score should increase
  **/
  void scoreDisplay1(bool up);

  /**
  *  Updates score for the team 2
  *  @params up - if the score should increase
  **/
  void scoreDisplay2(bool up);

  /**
  *  Resets all internal variables (starts the game from begining)
  **/
  void reset();

private:
  // The sice of data arrays (ideally we should get it dynamically)
  const int arraySize = 4;
  // When this number will be reached in any of the team,
  // the team won the game
  const int goalsPerGame = 10;
  // If a team won three games then the team won the whole match
  const int gamesPerMatch = 3;
  int score1;
  int score2;
  int games;
  int gamesWon1;
  int gamesWon2;
  uint8_t data1[4];
  uint8_t data2[4];

  void displayScore();
  void updateScore(int& score, bool up);
  void playGoalTone();
  void playLoseTone();
  void resetGame();
  void logGameResult(const char* team);
  void gameWonTheme(bool team1Won);
  
  // TODO: How to pass reference to the display?
  void displayGoalText1();
  void displayGoalText2();
};

#endif

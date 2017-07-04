
#ifndef testButton_h
#define testButton_h

class testButton {
  public:
    /**
    * Constructor
    **/
    testButton();

    /**
    * Runs the test for both displays, buzzer and LED
    **/
    void runTest();

private:
    void playTone();
};

#endif

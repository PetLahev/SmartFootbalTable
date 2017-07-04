/*
*  Provides access to globaly available objects
*/

#include "globals.h"
#include "Constants.h"
#include "TM1637Display.h"

/**
*  Initializes TM1637 display with CLK and DI pins
*  This object will be accessible anywhere in the project
**/
TM1637Display disp1(DISP1_CLK, DISP1_DIO);

/**
*  Initializes TM1637 display with CLK and DI pins
*  This object will be accessible anywhere in the project
**/
TM1637Display disp2(DISP2_CLK, DISP2_DIO);

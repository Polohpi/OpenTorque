#ifndef INIT_H
#define INIT_H

#include "Tool.h"

#define HEIGHTOLED 39
#define WIDHTOLED 104
#define HEIGHTCHAR 32
#define WIDHTCHAR 24
#define DELAYBUZZON 0
#define DELAYBUZZOFF 1000

#define BUZZ 10
#define BUTTONENTER 9
#define BUTTONUP 8
#define BUTTONDOWN 7
#define DELAYBUTTON 20
#define DELAYTARE 2000

//#define DEBUG

float Torque = 0;
float valmeasure = 0;
float oldvalmeasure = 0;
float bdl = 500;
float prctbuzz =0.5;


int buzzstate = LOW;
int target = 20;

unsigned long prevbuzzmillis = 0;

unsigned long millisMeasure = 0;
unsigned long millisButton = 0;
unsigned long millisTare = 0;

boolean dec = false;
boolean hec = false;

boolean tare = false;

#define DELAYMEASURE 100

boolean buttonUPstate = false;
boolean buttonDOWNstate = false;
boolean buttonENTERstate = false;


#endif

#ifndef INIT_H
#define INIT_H

#include "Tool.h"

#define HEIGHTOLED 39
#define WIDHTOLED 104
#define HEIGHTCHAR 32
#define WIDHTCHAR 24

float Torque = 0;
float valmeasure = 0;
float oldvalmeasure = 0;
float bdl = 1000;

unsigned long millisMeasure = 0;

boolean dec = false;
boolean hec = false;

boolean tare = false;

#define DELAYMEASURE 100


#endif

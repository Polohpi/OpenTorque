#ifndef INTERACTION_H
#define INTERACTION_H

#include "Init.h"

void buttonUP()
{
  if(millis() > millisMeasure + DELAYBUTTON)
  {
    buttonUPstate = true;
    #ifdef DEBUG
    Serial.println("ButtonUP");
    #endif
    millisMeasure = millis();
  }
  yield();
}

void buttonDOWN()
{  
  buttonDOWNstate = true;
  #ifdef DEBUG
  Serial.println("ButtonDOWN");
  #endif

    if(millis() > millisMeasure + DELAYBUTTON)
    {
    buttonDOWNstate = true;
    #ifdef DEBUG
    Serial.println("ButtonDOWN");
    #endif
    millisMeasure = millis();
    }
    
  yield();
}

void buttonENTER()
{

  buttonENTERstate = true;
  #ifdef DEBUG
  Serial.println("ButtonENTER");
  #endif

  if(millis() > millisMeasure + DELAYBUTTON)
  {
    buttonENTERstate = true;
    #ifdef DEBUG
    Serial.println("ButtonENTER");
    #endif
    millisMeasure = millis();
  }

  yield();
}


#endif

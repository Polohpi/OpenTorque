#ifndef INTERACTION_H
#define INTERACTION_H

#include "Init.h"

void buttonUP()
{
  if(millis() > millisButton + DELAYBUTTON)
  {
    if(buttonUPstate == false)
    {
    buttonUPstate = true;
    }
    #ifdef DEBUGOT
    Serial.println("ButtonUP");
    #endif
  }
  yield();
}

void buttonDOWN()
{ 
  if(millis() > millisButton + DELAYBUTTON)
  {
    if(buttonDOWNstate == false)
    {
    buttonDOWNstate = true;
    }
    #ifdef DEBUGOT
    Serial.println("ButtonDOWN");
    #endif
  }
  yield();
}

void buttonENTER()
{
  if(millis() > millisButton + DELAYBUTTON)
  {
    if(buttonENTERstate == false)
    {
    buttonENTERstate = true;
    }
    #ifdef DEBUGOT
    Serial.println("ButtonENTER");
    #endif
  }
  yield();
}


#endif

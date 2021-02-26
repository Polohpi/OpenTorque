#ifndef INTERACTION_H
#define INTERACTION_H

#include "Init.h"
#include "Page.h"
#include "Tool.h"

void buttonUP()
{
  if(millis() > millisButton + DELAYBUTTON)
  {
    buttonUPstate = true;
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
    buttonDOWNstate = true;
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
    buttonENTERstate = true;
    #ifdef DEBUGOT
    Serial.println("ButtonENTER");
    #endif
  }
  yield();
}


#endif

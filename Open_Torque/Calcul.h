#ifndef CALCUL_H
#define CALCUL_H

#include "Init.h"

void Measure()
{
  if(millis() > millisMeasure + DELAYMEASURE)
  {
  valmeasure = loadcell.read();
  if(valmeasure<50)
  {
    valmeasure = 0;
  }
  millisMeasure = millis();
  }
  yield();
}

#endif

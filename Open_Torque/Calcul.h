#ifndef CALCUL_H
#define CALCUL_H

#include "Init.h"

void Measure()
{
  if(millis() > millisMeasure + DELAYMEASURE)
  {
  float i = loadcell.read();
  if(i<40000)
  {
    valmeasure =i;
  }
  if(valmeasure<75)
  {
    valmeasure = 0;
  }
  
  millisMeasure = millis();
  }
  Torque = (valmeasure/1000*9.81)*(bdl/1000);
  #ifdef DEBUG
  Serial.println("valmeasure : " + (String)valmeasure);
  Serial.println("Torque : " + (String)Torque);
  #endif  
  yield();
}

  int calculaxb()
{  
  int i = Torque*((DELAYBUZZOFF-DELAYBUZZON)/(target-target*prctbuzz))+(DELAYBUZZON*target-DELAYBUZZOFF*target*prctbuzz)/(target-target*prctbuzz);
  //
  #ifdef DEBUG
  Serial.println("axb : " + String(i));
  #endif
  return i;
  yield();
}

void WatchTargetBuzz()
{
  if(Torque > target*prctbuzz && valmeasure > 200)
  {
    unsigned long currentMillis = millis();
    if(DELAYBUZZOFF-calculaxb() > 20)
    {
      if(currentMillis - prevbuzzmillis >= DELAYBUZZOFF-calculaxb())
      {
        prevbuzzmillis = currentMillis;
        if(buzzstate == LOW){buzzstate = HIGH;}
        else{buzzstate = LOW;}
        digitalWrite(BUZZ, buzzstate);
      }
    }
    else
    {
      digitalWrite(BUZZ, HIGH);
    } 
  } 
  else{digitalWrite(BUZZ, LOW);}

  yield();
}

#endif

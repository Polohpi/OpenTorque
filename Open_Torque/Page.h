#ifndef PAGE_H
#define PAGE_H

#include "Tool.h"
#include "Init.h"
#include "Calcul.h"

void Acceuil()
{
  ssd1306_setFixedFont(comic_sans_font24x32_123);
  //ssd1306_setFixedFont(ssd1306xled_font8x16);

  if(valmeasure < oldvalmeasure -10 || valmeasure > oldvalmeasure +10)
  { 
  //ssd1306_clearScreen();
  char s[40];
  Torque = valmeasure/1000*9.81/0.4;  
  Serial.println("torque : " + (String)Torque);
  sprintf(s, "%d", (int)Torque);
  oldvalmeasure = valmeasure;
  ssd1306_printFixed(0, 16, s, STYLE_BOLD);
  Serial.println("val : " + (String)valmeasure); 
  }
  yield();
  delay(100);
}

#endif

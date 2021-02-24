#ifndef PAGE_H
#define PAGE_H

#include "Tool.h"
#include "Init.h"
#include "Calcul.h"

void Acceuil()
{
  int posx = 70;
  int posy = 15;
  ssd1306_clearScreen();
  delay(10);
  
  while(1){
  ssd1306_setFixedFont(comic_sans_font24x32_123);
  ssd1306_setFixedFont(ssd1306xled_font8x16);
  ssd1306_printFixed(posx+30, HEIGHTOLED-posy+14, "N/m", STYLE_NORMAL);

  if(tare == true){tare = false;ssd1306_clearScreen();}
  
  Torque = (valmeasure/1000*9.81)/(bdl/1000);
  ssd1306_setFixedFont(comic_sans_font24x32_123);
  printval(posx, posy, Torque);
  ssd1306_setFixedFont(ssd1306xled_font8x16);  

  Serial.println("torque : " + (String)Torque);
  Serial.println("val : " + (String)valmeasure); 

  yield();
  delay(100);
  }
}

#endif

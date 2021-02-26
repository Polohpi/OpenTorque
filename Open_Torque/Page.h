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
  #ifdef DEBUGOT
  Serial.println("Acceuil");
  #endif
  
  delay(10);
  
  while(1)
  {
    if(tare == false)
    {
      if(buttonENTERstate == true)
      {
        millisButton = millis();
        millisTare = millis();
        buttonENTERstate = false;
        Tare();
      }
      if(valmeasure<200)
      {
        ssd1306_setFixedFont(comic_sans_font24x32_123);
        printval(posx, posy, target);
        if(buttonUPstate == true) 
        {
          millisButton = millis();
          buttonUPstate = false;
          target++;
          eeprom.write(target, ADD_EEPROM);
        }
        if(buttonDOWNstate == true)
        {
          millisButton = millis();
          buttonDOWNstate = false;
          if(target > TORQUEMIN)
          {
            target--;
          }
          eeprom.write(target, ADD_EEPROM);
        }
      }
      else
      {
        if(tare == true){tare = false;ssd1306_clearScreen();} 
        ssd1306_setFixedFont(comic_sans_font24x32_123);
        printval(posx, posy, Torque);
      }
      ssd1306_setFixedFont(ssd1306xled_font8x16);
      ssd1306_printFixed(posx+30, HEIGHTOLED-posy+14, "N/m", STYLE_NORMAL);
    }
  yield();
  }
}

#endif

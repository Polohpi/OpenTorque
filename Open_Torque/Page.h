#ifndef PAGE_H
#define PAGE_H

#include "Tool.h"
#include "Init.h"

void WeightPage()
{
  
}

void ManualPage()
{
  
}

void LeverPage()
{
  
}

void CalibrationPage()
{
  
}

void AngularPage()
{
  
}

void LongPage()
{
  
}

void USPage()
{
  
}

void AcceuilPage()
{
  int posx = 70;
  int posy = 15;
  ssd1306_clearScreen();
  
  #ifdef DEBUGOT
  Serial.println("Acceuil");
  #endif
  
  while(1)
  {
    if(PauseAcceuil == false)
    {
      ssd1306_setFixedFont(ssd1306xled_font8x16);
      ssd1306_printFixed(posx+30, HEIGHTOLED-posy+14, "N/m", STYLE_NORMAL);
      
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
        
        if(buttonENTERstate == true)
        { 
          millisButton = millis();
          buttonENTERstate = false;
          MainMenuSelectionState = true;
          break;
        }
      }
      else
      {
        ssd1306_setFixedFont(comic_sans_font24x32_123);
        printval(posx, posy, Torque);
      }
    }
  yield();
  }
}

#endif

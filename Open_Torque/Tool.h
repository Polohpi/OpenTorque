#ifndef TOOL_h
#define TOOL_h

#include "Init.h"
#include <HX711.h>
#include "ssd1306.h"
#include <Scheduler.h>
#include <Buzzer.h>
#include "AT24C256.h"

AT24C256 eeprom = AT24C256();
HX711 loadcell = HX711();
Buzzer buzzer(9);
SAppMenu MainMenu;
SAppMenu ModeMenu;
SAppMenu SettingMenu;
SAppMenu TorqueMenu;
SAppMenu UnitMenu;
SAppMenu ScrewMenu;

void printval(int x, int y, int value)
{
  if(value<500) //this avoid to print wrong value like 13322223. 
  {
    char s[10];
    //move text to the left and val dec to true because pf 2 digits 
    if(value>9 && value <100){x = x - WIDHTCHAR; dec = true;}

    //same with 3 digits 
    if(value>99){x = x - WIDHTCHAR*2; hec = true;}

    //if value is <10 and was >10 before then clear screen. This helps to not having the screen blink all the time because of screen cleaning at every cycle. 
    if(value <10){if(dec == true){dec = false;ssd1306_clearScreen();}}

    //same with value <100 that was >100 before
    if(value <100){if(hec == true){hec = false; ssd1306_clearScreen();}}
    
    sprintf(s, "%d", value);
    ssd1306_printFixed(x, HEIGHTOLED-y, s, STYLE_BOLD);
  }
  yield();
}

void Tare()
{
  ssd1306_clearScreen();
  
  while(millis() < millisTare + DELAYTARE)
  {
  loadcell.tare();
  ssd1306_setFixedFont(ssd1306xled_font8x16);
  ssd1306_printFixed(25, 30, "TARE OK !", STYLE_BOLD);
  }
  ssd1306_clearScreen();
  MainMenuSelectionState = true;
  
  yield();
}

void SetUnit()
{
  if(WeightUnit == G)
  {
    WeightRatio = 1;
    
    if(LongUnit == CM){Unit = "g/cm";LongRatio = 10;}
    if(LongUnit == DM){Unit = "g/dm";LongRatio = 100;}
    if(LongUnit == M){Unit = "g/m";LongRatio = 1000;}
    if(LongUnit == INCH){Unit = "g/in";LongRatio = 25.4;}
    if(LongUnit == FEET){Unit = "g/ft";LongRatio = 304.8;}
  }

  if(WeightUnit == KG)
  {
    WeightRatio = 0.001;
    if(LongUnit == CM){Unit = "Kg/cm";LongRatio = 10;}
    if(LongUnit == DM){Unit = "Kg/dm";LongRatio = 100;}
    if(LongUnit == M){Unit = "Kg/m";LongRatio = 1000;}
    if(LongUnit == INCH){Unit = "Kg/in";LongRatio = 25.4;}
    if(LongUnit == FEET){Unit = "Kg/ft";LongRatio = 304.8;}
  }
  
  if(WeightUnit == N)
  {
    WeightRatio = 0.00980665;
    if(LongUnit == CM){Unit = "N/cm";LongRatio = 10;}
    if(LongUnit == DM){Unit = "N/dm";LongRatio = 100;}
    if(LongUnit == M){Unit = "N/m";LongRatio = 1000;}
    if(LongUnit == INCH){Unit = "N/in";LongRatio = 25.4;}
    if(LongUnit == FEET){Unit = "N/ft";LongRatio = 304.8;}
  }

  if(WeightUnit == DN)
  {
    WeightRatio = 0.0980665;
    if(LongUnit == CM){Unit = "dN/cm";LongRatio = 10;}
    if(LongUnit == DM){Unit = "dN/dm";LongRatio = 100;}
    if(LongUnit == M){Unit = "dN/m";LongRatio = 1000;}
    if(LongUnit == INCH){Unit = "dN/in";LongRatio = 25.4;}
    if(LongUnit == FEET){Unit = "dN/ft";LongRatio = 304.8;}
  }

  if(WeightUnit == POUND)
  {
    WeightRatio = 0.00220462;
    if(LongUnit == CM){Unit = "lb/cm";LongRatio = 10;}
    if(LongUnit == DM){Unit = "lb/dm";LongRatio = 100;}
    if(LongUnit == M){Unit = "lb/m";LongRatio = 1000;}
    if(LongUnit == INCH){Unit = "lb/in";LongRatio = 25.4;}
    if(LongUnit == FEET){Unit = "lb/ft";LongRatio = 304.8;}
  }
  
  if(WeightUnit == OUNCE)
  {
    WeightRatio = 0.035375;
    if(LongUnit == CM){Unit = "oz/cm";LongRatio = 10;}
    if(LongUnit == DM){Unit = "oz/dm";LongRatio = 100;}
    if(LongUnit == M){Unit = "oz/m";LongRatio = 1000;}
    if(LongUnit == INCH){Unit = "oz/in";LongRatio = 25.4;}
    if(LongUnit == FEET){Unit = "oz/ft";LongRatio = 304.8;}
  }
  
   Serial.println("WeightUnit ; " + String(WeightUnit));
   Serial.println("LongUnit ; " + String(LongUnit));
   
  Serial.println("SetUnit : " + String(Unit));
  
}

void GetUnity()
{
  
}
#endif

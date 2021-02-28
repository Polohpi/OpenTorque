#ifndef PAGE_H
#define PAGE_H

#include "Tool.h"
#include "Init.h"

int GetLastMode()
{
  int i = eeprom.read(LASTMODE_ADD_EEPROM);
  return i;
}

void WeightUnitPage()
{
  int posx = 35;
  int posy = 15;
  ssd1306_clearScreen();

  while(1)
  {
    ssd1306_setFixedFont(ssd1306xled_font8x16);
    const char *charUnit;
    if(WeightUnit == G){charUnit = "g";}
    if(WeightUnit == KG){charUnit = "Kg";}
    if(WeightUnit == N){charUnit = "N";}
    if(WeightUnit == DN){charUnit = "dN";}
    if(WeightUnit == POUND){charUnit = "Pound";}
    if(WeightUnit == OUNCE){charUnit = "Ounce";}
    
    ssd1306_printFixed(posx+30, HEIGHTOLED-posy+14, charUnit, STYLE_NORMAL);
    
    if(buttonUPstate == true) 
      {
        millisButton = millis();
        buttonUPstate = false;
        if(WeightUnit < 5)
        {
        ssd1306_clearScreen();
        WeightUnit++;
        }
      }
            
      if(buttonDOWNstate == true)
      {
        millisButton = millis();
        buttonDOWNstate = false;
        if(WeightUnit > 0)
        {
          ssd1306_clearScreen();
          WeightUnit--;
        }
      }
      
      if(buttonENTERstate == true)
      { 
        millisButton = millis();
        buttonENTERstate = false;
        eeprom.write(WeightUnit, WEIGHTUNIT_ADD_EEPROM);
        SetUnit();
        UnitMenuSelectionState = true;
        goto labelMenu;
      }

    yield();
  }
  labelMenu:
  yield();
}

void WeightPage()
{
  if(GetLastMode() != WEIGHTMODE)
  {
    eeprom.write(WEIGHTMODE, LASTMODE_ADD_EEPROM);
  }
  int posx = 55;
  int posy = 15;
  const char *charUnit;
  ssd1306_clearScreen();


  while(1)
  {
    ssd1306_setFixedFont(comic_sans_font24x32_123);
    printval(posx, posy, valmeasure*WeightRatio);
    ssd1306_setFixedFont(ssd1306xled_font8x16);
    
    if(WeightUnit == G){charUnit = "g";}
    if(WeightUnit == KG){charUnit = "Kg";}
    if(WeightUnit == N){charUnit = "N";}
    if(WeightUnit == DN){charUnit = "dN";}
    if(WeightUnit == POUND){charUnit = "lb";}
    if(WeightUnit == OUNCE){charUnit = "oz";}
    
    ssd1306_printFixed(posx+30, HEIGHTOLED-posy+14, charUnit, STYLE_NORMAL);
    
      
      if(buttonENTERstate == true)
      { 
        millisButton = millis();
        buttonENTERstate = false;
        MainMenuSelectionState = true;
        goto labelMenu;
      }

    yield();
  }
  labelMenu:
  yield();
}

void ManualPage()
{
  if(GetLastMode() != MANUALMODE)
  {
    eeprom.write(MANUALMODE, LASTMODE_ADD_EEPROM);
  }
  int posx = 55;
  int posy = 15;
  ssd1306_clearScreen();
  Serial.println(String(Unit));
  
  #ifdef DEBUGOT
  Serial.println("Manual");
  #endif
  
  while(1)
  {
    ssd1306_setFixedFont(ssd1306xled_font8x16);
    ssd1306_printFixed(posx+30, HEIGHTOLED-posy+14, Unit, STYLE_NORMAL);
    
    if(valmeasure<200)
    {
      ssd1306_setFixedFont(comic_sans_font24x32_123);
      printval(posx, posy, target);
      
      if(buttonUPstate == true) 
      {
        millisButton = millis();
        buttonUPstate = false;
        target++;
        eeprom.write(target, TARGET_ADD_EEPROM);
      }
            
      if(buttonDOWNstate == true)
      {
        millisButton = millis();
        buttonDOWNstate = false;
        if(target > TORQUEMIN)
        {
          target--;
        }
        eeprom.write(target, TARGET_ADD_EEPROM);
      }
      
      if(buttonENTERstate == true)
      { 
        millisButton = millis();
        buttonENTERstate = false;
        
        MainMenuSelectionState = true;
        goto labelMenu;
      }
    }
    else
    {
      ssd1306_setFixedFont(comic_sans_font24x32_123);
      printval(posx, posy, Torque);
    }
    yield();
  }
  labelMenu:
  yield();
}

void LeverPage()
{
  int posx = 25;
  int posy = 25;
  ssd1306_clearScreen();
  char s[10];
  while(1)
  {
    ssd1306_setFixedFont(ssd1306xled_font8x16);
    sprintf(s, "%d", lever);
    ssd1306_printFixed(posx+30, HEIGHTOLED-posy+14, s, STYLE_NORMAL);
    
    if(buttonUPstate == true) 
      {
        millisButton = millis();
        buttonUPstate = false;
        if(lever < LEVERMAX)
        {
          ssd1306_clearScreen();
          lever += 100;
        }
      }
            
      if(buttonDOWNstate == true)
      {
        millisButton = millis();
        buttonDOWNstate = false;
        if(lever > LEVERMIN)
        {
          ssd1306_clearScreen();
          lever -= 100;
        }
      }
      
      if(buttonENTERstate == true)
      { 
        millisButton = millis();
        buttonENTERstate = false;
        
        eeprom.write(lever/10, LEVER_ADD_EEPROM);
        //eeprom.write(200, LEVER_ADD_EEPROM);
        SettingMenuSelectionState = true;
        goto labelMenu;
      }

    yield();
  }
  labelMenu:
  yield();
}

void CalibrationPage()
{
  
}

void AngularPage()
{
  
}

void LongPage()
{
  int posx = 25;
  int posy = 25;
  ssd1306_clearScreen();

  while(1)
  {
    ssd1306_setFixedFont(ssd1306xled_font8x16);
    const char *charUnit;
    if(LongUnit == CM){charUnit = "centimeter";}
    if(LongUnit == DM){charUnit = "decimeter";}
    if(LongUnit == M){charUnit = "meter";}
    if(LongUnit == INCH){charUnit = "inch";}
    if(LongUnit == FEET){charUnit = "Feet";}
    
    ssd1306_printFixed(posx+30, HEIGHTOLED-posy+14, charUnit, STYLE_NORMAL);
    
    if(buttonUPstate == true) 
      {
        millisButton = millis();
        buttonUPstate = false;
        if(LongUnit < 4)
        {
        ssd1306_clearScreen();
        LongUnit++;
        }
      }
            
      if(buttonDOWNstate == true)
      {
        millisButton = millis();
        buttonDOWNstate = false;
        if(LongUnit > 0)
        {
          ssd1306_clearScreen();
          LongUnit--;
        }
      }
      
      if(buttonENTERstate == true)
      { 
        millisButton = millis();
        buttonENTERstate = false;
        
        eeprom.write(LongUnit, LONGUNIT_ADD_EEPROM);
        SetUnit();
        UnitMenuSelectionState = true;
        goto labelMenu;
      }

    yield();
  }
  labelMenu:
  yield();
}

void USPage()
{
  
}

void MetricPage()
{
  
}

void DoLastMode()
{
  if(GetLastMode() == MANUALMODE)
  {
    ManualPage();
  }
  else if (GetLastMode() == METRICMODE)
  {
    
  }
  else if (GetLastMode() == USMODE)
  {
    
  }
  else if (GetLastMode() == ANGULARMODE)
  {
    
  }
  else if (GetLastMode() == WEIGHTMODE)
  {
    WeightPage();
  }
}

#endif

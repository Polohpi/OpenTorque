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
  boolean resume = false;

  Serial.println("WeightUnitPage");
  
  while(resume == false)
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
          Serial.println("UP");
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
          Serial.println("DOWN");
          ssd1306_clearScreen();
          WeightUnit--;
        }
      }
      
      if(buttonENTERstate == true)
      { 
        millisButton = millis();
        buttonENTERstate = false;
        Serial.println("ENTER");
        eeprom.write(WeightUnit, WEIGHTUNIT_ADD_EEPROM);
        SetUnit();
        UnitMenuSelectionState = true;
        resume = true;
      }
    yield();
  }
  yield();
}

void ScalePage()
{
  if(GetLastMode() != SCALEMODE)
  {
    eeprom.write(SCALEMODE, LASTMODE_ADD_EEPROM);
  }
  int posx = 55;
  int posy = 15;
  const char *charUnit;
  ssd1306_clearScreen(); 

  boolean resume = false;

  while(resume == false)
  {
    ssd1306_setFixedFont(comic_sans_font24x32_123);
    printval(posx, posy, valmeasure*WeightRatio);
    ssd1306_setFixedFont(ssd1306xled_font8x16);
    ssd1306_printFixed(0, 0, "Scale", STYLE_NORMAL);
    
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
      resume = true;
    }

    yield();
  }
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
  
  Serial.println("Manual");
  //Serial.println("Val : " + (String)EEPROMFloatRead());

  boolean resume = false;
  while(resume == false)
  {
    ssd1306_setFixedFont(ssd1306xled_font8x16);
    ssd1306_printFixed(posx+30, HEIGHTOLED-posy+14, Unit, STYLE_NORMAL);
    ssd1306_printFixed(0, 0, "ManualT", STYLE_NORMAL);
    
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
        resume = true;
        //goto labelMenu;
      }
    }
    else
    {
      ssd1306_setFixedFont(comic_sans_font24x32_123);
      printval(posx, posy, Torque);
    }
    yield();
  }
  //labelMenu:
  yield();
}

void LeverPage()
{
  int posx = 25;
  int posy = 25;
  ssd1306_clearScreen();
  char s[10];
  boolean resume = false;
  while(resume == false)
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
        SettingMenuSelectionState = true;
        resume = true;
      }

    yield();
  }
  yield();
}

void CalibrationPage()
{
  int posx = 55;
  int posy = 15;
  int Calibrationtarget = 170;
  const char *charUnit;
  ssd1306_clearScreen();
  boolean resume = true;
  
  while(resume == true)
  {
    if(WeightUnit == G){charUnit = "g";}
    if(WeightUnit == KG){charUnit = "Kg";}
    if(WeightUnit == N){charUnit = "N";}
    if(WeightUnit == DN){charUnit = "dN";}
    if(WeightUnit == POUND){charUnit = "lb";}
    if(WeightUnit == OUNCE){charUnit = "oz";}
    ssd1306_setFixedFont(ssd1306xled_font8x16);
    ssd1306_printFixed(posx+30, HEIGHTOLED-posy+14, charUnit, STYLE_NORMAL);
    ssd1306_printFixed(0, 0, "Calibrattion", STYLE_NORMAL);
    
    if(valmeasure<50)
    {
      ssd1306_setFixedFont(comic_sans_font24x32_123);
      printval(posx, posy, Calibrationtarget);
      
      if(buttonUPstate == true) 
      {
        millisButton = millis();
        buttonUPstate = false;
        Calibrationtarget += 10;
      }
            
      if(buttonDOWNstate == true)
      {
        millisButton = millis();
        buttonDOWNstate = false;
        if(target > TORQUEMIN)
        {
          Calibrationtarget -= 10;
        }
      }
      
      if(buttonENTERstate == true)
      {
        millisButton = millis();
        buttonENTERstate = false;
        resume = false; 
      }
    }
    else
    {
      ssd1306_setFixedFont(comic_sans_font24x32_123);
      printval(posx, posy, valmeasure*WeightRatio);
      
      if(buttonENTERstate == true)
      {
        millisButton = millis();
        buttonENTERstate = false;
        millisCalibration = millis();
        LoadCellCalibrate(Calibrationtarget);
        
        resume = false;
      }
    }  
    yield();
  }
  SettingMenuSelectionState = true;
  yield();
}

void AngularPage()
{
  
}

void LengthPage()
{
  int posx = 25;
  int posy = 25;
  ssd1306_clearScreen();

  while(1)
  {
    ssd1306_setFixedFont(ssd1306xled_font8x16);
    const char *charUnit;
    if(LengthUnit == CM){charUnit = "centimeter";}
    if(LengthUnit == DM){charUnit = "decimeter";}
    if(LengthUnit == M){charUnit = "meter";}
    if(LengthUnit == INCH){charUnit = "inch";}
    if(LengthUnit == FEET){charUnit = "Feet";}
    
    ssd1306_printFixed(posx+30, HEIGHTOLED-posy+14, charUnit, STYLE_NORMAL);
    
    if(buttonUPstate == true) 
      {
        millisButton = millis();
        buttonUPstate = false;
        if(LengthUnit < 4)
        {
        ssd1306_clearScreen();
        LengthUnit++;
        }
      }
            
      if(buttonDOWNstate == true)
      {
        millisButton = millis();
        buttonDOWNstate = false;
        if(LengthUnit > 0)
        {
          ssd1306_clearScreen();
          LengthUnit--;
        }
      }
      
      if(buttonENTERstate == true)
      { 
        millisButton = millis();
        buttonENTERstate = false;
        
        eeprom.write(LengthUnit, LENGTHUNIT_ADD_EEPROM);
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
  else if (GetLastMode() == SCALEMODE)
  {
    ScalePage();
  }
}

#endif

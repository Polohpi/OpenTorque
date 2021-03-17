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
  if(GetLastMode() != ANGULARMODE)
  {
    eeprom.write(ANGULARMODE, LASTMODE_ADD_EEPROM);
  }
  
  int posx = 55;
  int posy = 15;

  int value;
  boolean resume = false;
  
  while(resume == false)
  {
    value = sqrt(sq(mpu6050.getAngleZ() - AngularTare));
    ssd1306_setFixedFont(ssd1306xled_font8x16);
    ssd1306_printFixed(posx+30, HEIGHTOLED-posy+14, "deg", STYLE_NORMAL);
    ssd1306_printFixed(0, 0, "Angular", STYLE_NORMAL);
    
    mpu6050.update();
    
    ssd1306_setFixedFont(comic_sans_font24x32_123);
    
    if(value < 2 )
    {
      printval(posx, posy, AngularTarget);
    }
    else
    {
      printval(posx, posy, value);
    }

    
    if(buttonUPstate == true) 
      {
        millisButton = millis();
        buttonUPstate = false;
        if(AngularTarget < 360)
        {
          ssd1306_clearScreen();
          AngularTarget += 5;
          eeprom.write(AngularTarget, ANGULARTARGET_ADD_EEPROM);
        }
      }
            
      if(buttonDOWNstate == true)
      {
        millisButton = millis();
        buttonDOWNstate = false;
        if(AngularTarget > 0)
        {
          ssd1306_clearScreen();
          AngularTarget -= 5;
          eeprom.write(AngularTarget, ANGULARTARGET_ADD_EEPROM);
        }
      }
      
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

void LengthPage()
{
  int posx = 25;
  int posy = 25;
  ssd1306_clearScreen();

  boolean resume = false;

  while(resume == false)
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
        resume = true;
      }

    yield();
  }
  yield();
}

void ImperialUNFPage()
{
  
}

void ImperialUNCPage()
{
  
}

void MetricPage()
{
  if(GetLastMode() != METRICMODE)
  {
    eeprom.write(METRICMODE, LASTMODE_ADD_EEPROM);
  }
  
  int posx = 35;
  int posy = 15;
  ssd1306_clearScreen();
  boolean resume = false;

  eeprom.write(0, METRICSIZE_ADD_EEPROM);
  eeprom.write(0, METRICGRADE_ADD_EEPROM);

  Serial.println("MetricPage");
  
  while(resume == false)
  {
    //ssd1306_setFixedFont(ssd1306xled_font5x7_AB);
    ussd1306_setFixedFont(ssd1306xled_font8x16);
    const char *charUnit;
    if(MetricSize == M4){charUnit = "M4";}
    if(MetricSize == M5){charUnit = "M5";}
    if(MetricSize == M6){charUnit = "M6";}
    if(MetricSize == M8){charUnit = "M8";}
    if(MetricSize == M10){charUnit = "M10";}
    if(MetricSize == M12){charUnit = "M12";}
    if(MetricSize == M14){charUnit = "M14";}
    if(MetricSize == M16){charUnit = "M16";}
    if(MetricSize == M18){charUnit = "M18";}
    if(MetricSize == M20){charUnit = "M20";}
    if(MetricSize == M22){charUnit = "M22";}
    if(MetricSize == M24){charUnit = "M24";}
    if(MetricSize == M27){charUnit = "M27";}

    ssd1306_printFixed(posx+15, HEIGHTOLED-posy+14, charUnit, STYLE_NORMAL);
    
    if(buttonUPstate == true) 
      {
        millisButton = millis();
        buttonUPstate = false;
        if(MetricSize < 12)
        {
          Serial.println("UP");
          ssd1306_clearScreen();
          MetricSize++;
          eeprom.write(MetricSize, METRICSIZE_ADD_EEPROM);
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
          MetricSize--;
          eeprom.write(MetricSize, METRICSIZE_ADD_EEPROM);
        }
      }
      
      if(buttonENTERstate == true)
      { 
        millisButton = millis();
        buttonENTERstate = false;
        Serial.println("ENTER");
        MainMenuSelectionState = true;
        resume = true;
      }
    yield();
  }
  yield();
}

void DoLastMode()
{
  if(GetLastMode() == MANUALMODE)
  {
    ManualPage();
  }
  else if (GetLastMode() == METRICMODE)
  {
    MetricPage();
  }
  else if (GetLastMode() == IMPERIALUNFMODE)
  {
    ImperialUNFPage();
  }
  else if (GetLastMode() == IMPERIALUNCMODE)
  {
    ImperialUNCPage();
  }
  else if (GetLastMode() == ANGULARMODE)
  {
    AngularPage();
  }
  else if (GetLastMode() == SCALEMODE)
  {
    ScalePage();
  }
}

#endif

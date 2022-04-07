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
    printval(posx, posy, WIDHTCHAR, valmeasure*WeightRatio);
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
  //this write the current mode number to the eeprom if this number was different before. This is used when coming to manualpage frome another one.
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
    ssd1306_printFixed(posx+30, HEIGHTOLED-posy+20, Unit, STYLE_NORMAL);
    ssd1306_printFixed(0, 0, "ManualT", STYLE_NORMAL);
    printval(110, 8, 8, target);
    
    if(valmeasure<200)
    {
      ssd1306_setFixedFont(comic_sans_font24x32_123);
      printval(posx, posy, WIDHTCHAR, Torque);
      
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
      }
    }
    else
    {
      ssd1306_setFixedFont(comic_sans_font24x32_123);
      printval(posx, posy, WIDHTCHAR, Torque);
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
    ssd1306_printFixed(0, 0, "Lever Setting", STYLE_NORMAL);
    
    sprintf(s, "%d mm", lever);
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
      printval(posx, posy, WIDHTCHAR, Calibrationtarget);
      
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
      printval(posx, posy, WIDHTCHAR, valmeasure*WeightRatio);
      
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
      printval(posx, posy, WIDHTCHAR, AngularTarget);
    }
    else
    {
      printval(posx, posy, WIDHTCHAR, value);
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
  
  int posx = 55;
  int posy = 15;
  ssd1306_clearScreen();
  boolean resume = false;



  Serial.println("MetricPage");
  
  while(resume == false)
  {
    ssd1306_setFixedFont(ssd1306xled_font8x16);
    ssd1306_printFixed(posx+30, HEIGHTOLED-posy+24, "N/m", STYLE_NORMAL);
    ssd1306_printFixed(0, 0, "Metric", STYLE_NORMAL);
    
    ssd1306_setFixedFont(ssd1306xled_font8x16);
    const char *SizeUnit;
    if(MetricSize == M4){SizeUnit = " M4";}
    if(MetricSize == M5){SizeUnit = " M5";}
    if(MetricSize == M6){SizeUnit = " M6";}
    if(MetricSize == M8){SizeUnit = " M8";}
    if(MetricSize == M10){SizeUnit = "M10";}
    if(MetricSize == M12){SizeUnit = "M12";}
    if(MetricSize == M14){SizeUnit = "M14";}
    if(MetricSize == M16){SizeUnit = "M16";}
    if(MetricSize == M18){SizeUnit = "M18";}
    if(MetricSize == M20){SizeUnit = "M20";}
    if(MetricSize == M22){SizeUnit = "M22";}
    if(MetricSize == M24){SizeUnit = "M24";}
    if(MetricSize == M27){SizeUnit = "M27";}

    const char *GradeUnit;
    if(MetricGrade == METRIC_5_6){GradeUnit =" G5.6";}
    if(MetricGrade == METRIC_5_8){GradeUnit = " G5.8";}
    if(MetricGrade == METRIC_6_8){GradeUnit = " G6.8";}
    if(MetricGrade == METRIC_8_8){GradeUnit = " G8.8";}
    if(MetricGrade == METRIC_9_8){GradeUnit = " G9_8";}
    if(MetricGrade == METRIC_10_9){GradeUnit = "G10.9";}
    if(MetricGrade == METRIC_12_9){GradeUnit = "G12.9";}

    const char *LubState;
    if(Lub == false){LubState = "NOLUB";}
    else(LubState = "  LUB");

    ssd1306_printFixed(87, 5, LubState, STYLE_NORMAL);
    ssd1306_printFixed(102, 35, SizeUnit, STYLE_NORMAL);
    ssd1306_printFixed(87, 20, GradeUnit, STYLE_NORMAL);

    if(valmeasure<200)
    { 
      ssd1306_setFixedFont(comic_sans_font24x32_123);
      
      if(Lub == false)
      {
        printval(posx, posy, WIDHTCHAR, round( Metric_NOLUB[MetricSize][MetricGrade] ));
      }
      else
      {
        printval(posx, posy, WIDHTCHAR, round( Metric_LUB[MetricSize][MetricGrade] ));
      }
      
      if(buttonUPstate == true) 
        {
          millisButton = millis();
          buttonUPstate = false;
          if(MetricSize < 12)
          {
            Serial.println("UP");
            //ssd1306_clearScreen();
            MetricSize++;
            eeprom.write(MetricSize, METRICSIZE_ADD_EEPROM);
          }
        }
              
        if(buttonDOWNstate == true)
        {
          millisButton = millis();
          buttonDOWNstate = false;
          if(MetricSize > 0)
          {
            Serial.println("DOWN");
            //ssd1306_clearScreen();
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
    }
    else
    {
      ssd1306_setFixedFont(comic_sans_font24x32_123);
      printval(posx, posy, WIDHTCHAR, Torque);
    }
    yield();
  }
  yield();
}

void MetricGradePage()
{
  int posx = 25;
  int posy = 25;
  ssd1306_clearScreen();
  boolean resume = false;

  
  while(resume == false)
  {
    ssd1306_setFixedFont(ssd1306xled_font8x16);
    ssd1306_printFixed(0, 0, "Metric Grade", STYLE_NORMAL);
    
    ssd1306_setFixedFont(ssd1306xled_font8x16);    
    const char *GradeUnit;
    if(MetricGrade == METRIC_5_6){GradeUnit ="G5.6";}
    if(MetricGrade == METRIC_5_8){GradeUnit = "G5.8";}
    if(MetricGrade == METRIC_6_8){GradeUnit = "G6.8";}
    if(MetricGrade == METRIC_8_8){GradeUnit = "G8.8";}
    if(MetricGrade == METRIC_9_8){GradeUnit = "G9_8";}
    if(MetricGrade == METRIC_10_9){GradeUnit = "G10.9";}
    if(MetricGrade == METRIC_12_9){GradeUnit = "G12.9";}
    
    ssd1306_printFixed(112, 0, GradeUnit, STYLE_NORMAL);   
     
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

void ImperialGradePage()
{
  int posx = 25;
  int posy = 25;
  ssd1306_clearScreen();
  char s[10];
  boolean resume = false;
  while(resume == false)
  {
    ssd1306_setFixedFont(ssd1306xled_font8x16);
    ssd1306_printFixed(0, 0, "Lever Setting", STYLE_NORMAL);
    
    sprintf(s, "%d mm", lever);
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

void ScrewLubPage()
{
  int posx = 25;
  int posy = 25;
  ssd1306_clearScreen();
  boolean resume = false;

  while(resume == false)
  {
    ssd1306_setFixedFont(ssd1306xled_font8x16);
    ssd1306_printFixed(0, 0, "Screw Lub", STYLE_NORMAL);

    if(Lub == false)
    {
      ssd1306_printFixed(posx+30, HEIGHTOLED-posy+14, " NO", STYLE_NORMAL);
    }
    else
    {
      ssd1306_printFixed(posx+30, HEIGHTOLED-posy+14, "YES", STYLE_NORMAL); 
    }
    
    if(buttonUPstate == true) 
      {
        millisButton = millis();
        buttonUPstate = false;
        if(Lub == false )
        {
          ssd1306_clearScreen();
          Lub = true;
        }
      }
            
      if(buttonDOWNstate == true)
      {
        millisButton = millis();
        buttonDOWNstate = false;
        if(Lub == true)
        {
          ssd1306_clearScreen();
          Lub = false;
        }
      }
      
      if(buttonENTERstate == true)
      { 
        millisButton = millis();
        buttonENTERstate = false;
        if(Lub == false)
        {
          eeprom.write(0, LUB_ADD_EEPROM);
        }
        else
        {
          eeprom.write(1, LUB_ADD_EEPROM);
        }
        SettingMenuSelectionState = true;
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

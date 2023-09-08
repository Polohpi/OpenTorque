/*
This page contain all of the tools used by the wrench. 
*/

#ifndef TOOL_h
#define TOOL_h

#include "Init.h"
#include "Page.h"
#include <HX711_ADC.h>
#include "ssd1306.h"
#include <Scheduler.h>
#include <Buzzer.h>
#include "AT24C256.h"
#include <MPU6050_tockn.h>
#include <Wire.h>


//creation of different object
AT24C256 eeprom = AT24C256();
HX711_ADC LoadCell(HX711DOUT, HX711SCK);
Buzzer buzzer(BUZZ);
MPU6050 mpu6050(Wire);

//creation of the menu objects
SAppMenu MainMenu;
SAppMenu ModeMenu;
SAppMenu SettingMenu;
SAppMenu TorqueMenu;
SAppMenu UnitMenu;
SAppMenu ScrewMenu;
SAppMenu ImperialMenu;
SAppMenu ScrewGradeMenu;


/*_____________________________________________________________EEPROM FLOAT WRITE ()________________________________________________________
used to write float values to eeprom. May be used to store calibration value. Not in use in this version
*/

void EEPROMFloatWrite(float Val)
{
  String valtxt = "";
  valtxt =(String)Val;
  
  #ifdef DEBUGOT
  for(int i= CALIBRATIONVALUE_ADD_EEPROM; i<valtxt.length()+CALIBRATIONVALUE_ADD_EEPROM; i++)
  {
    Serial.println("valtxt[" + (String)i+ "] : " + (String)valtxt[i-CALIBRATIONVALUE_ADD_EEPROM]);
    yield();
  }
  #endif

  for(int i = CALIBRATIONVALUE_ADD_EEPROM; i<valtxt.length()+1+CALIBRATIONVALUE_ADD_EEPROM; i++)
  {
    if(i == CALIBRATIONVALUE_ADD_EEPROM)
    {
      if(Val<0)
      {eeprom.write(0, i);}
      else
      {eeprom.write(1, i);}
    }
    else
    {
      if((String)valtxt[i-CALIBRATIONVALUE_ADD_EEPROM] == ".")
        {eeprom.write(10, i);}
      else 
      {eeprom.write(valtxt[i-CALIBRATIONVALUE_ADD_EEPROM]-48, i);}
    }
    
    if (i == valtxt.length()+CALIBRATIONVALUE_ADD_EEPROM)
    {
      eeprom.write(254, i);
    }
    yield();  
  }
}

/*_____________________________________________________________EEPROM FLOAT WRITE ()________________________________________________________
same thing to read float value from eeprom
*/

double EEPROMFloatRead()
{
  double valfloat;
  boolean resume = false;
  String val;
  
  while(resume == false)
  {
    if(eeprom.read(CALIBRATIONVALUE_ADD_EEPROM) == 0)
    {
      val += "-";
    }
    for(int i = CALIBRATIONVALUE_ADD_EEPROM + 1; eeprom.read(i) < 254;i++)
    {
      if(eeprom.read(i)==10)
      {
        val += ".";
      }
      else
      {
        val += String(eeprom.read(i));
      }
    }
    resume = true;
  }
  valfloat = val.toFloat();
  return valfloat;
}


/*_____________________________________________________________PRINT VAL________________________________________________________
printval is used to manage the number shown at screen
*/
void printval(int x, int y, int widht, int value)
{

  if(value<500) //this avoid to print wrong value like 13322223. 
  {
    char s[3];
    x = x - 2*widht;
    //move text to the left and val dec to true because of 2 digits 
    
    if(value<10)
    {
      sprintf(s, "  %d", value);
    }
    
    if(value>9 && value <100)
    {
      sprintf(s, " %d", value);
    }

    if(value>99)
    {
      sprintf(s, "%d", value);
    }
    
    ssd1306_printFixed(x, HEIGHTOLED-y, s, STYLE_BOLD);
  }
  yield();
}

/*_____________________________________________________________LoadCellTare()________________________________________________________
LoadCellTare is used to tare the loadcell
*/
void LoadCellTare()
{
  ssd1306_clearScreen();
  LoadCell.tareNoDelay();
  while(millis() < millisTare + DELAYTARE)
  {
    ssd1306_setFixedFont(ssd1306xled_font8x16);
    ssd1306_printFixed(25, 30, "TARE OK !", STYLE_BOLD);
    yield();
  }
  ssd1306_clearScreen();
  MainMenuSelectionState = true;
  
  yield();
}

/*_____________________________________________________________LoadCellCalibrate()________________________________________________________
LoadCellCalibrate is used to calibrate the loadcell
*/
void LoadCellCalibrate(int Val)
{

  float i = (float)Val;
  
  ssd1306_clearScreen();
  
  while(millis() < millisCalibration + DELAYCALIBRATION)
  {
    ssd1306_setFixedFont(ssd1306xled_font8x16);
    ssd1306_printFixed(25, 30, "CAL OK !", STYLE_BOLD);
    LoadCell.refreshDataSet();
    LoadCell.setCalFactor(LoadCell.getNewCalibration(i));
    //EEPROMFloatWrite((float)LoadCell.getNewCalibration(i));
    yield();
  }
  
  yield();
}

/*_____________________________________________________________SetUnits()________________________________________________________
SetUnit is used to set the "Unit" value that is used on screen. It also set the "Lengthratio" and "Weightvalue" value. Both are used in the function Measure() (see Calcul.h)
It's good to know that the basic measure available is in the ISO units kind of (g, m). Then the units set in the wrench are taken into account and the value is on screen

Raw loadcell value -> valmeasure -> Torque in whatever units is set -> screen
*/
void SetUnit()
{
  if(WeightUnit == G)
  {
    WeightRatio = 1;
    
    if(LengthUnit == CM){Unit = "g/cm";LengthRatio = 10;}
    if(LengthUnit == DM){Unit = "g/dm";LengthRatio = 100;}
    if(LengthUnit == M){Unit = "g/m";LengthRatio = 1000;}
    if(LengthUnit == INCH){Unit = "g/in";LengthRatio = 25.4;}
    if(LengthUnit == FEET){Unit = "g/ft";LengthRatio = 304.8;}
  }

  if(WeightUnit == KG)
  {
    WeightRatio = 0.001;
    if(LengthUnit == CM){Unit = "Kg/cm";LengthRatio = 10;}
    if(LengthUnit == DM){Unit = "Kg/dm";LengthRatio = 100;}
    if(LengthUnit == M){Unit = "Kg/m";LengthRatio = 1000;}
    if(LengthUnit == INCH){Unit = "Kg/in";LengthRatio = 25.4;}
    if(LengthUnit == FEET){Unit = "Kg/ft";LengthRatio = 304.8;}
  }
  
  if(WeightUnit == N)
  {
    WeightRatio = 0.00980665;
    if(LengthUnit == CM){Unit = "N/cm";LengthRatio = 10;}
    if(LengthUnit == DM){Unit = "N/dm";LengthRatio = 100;}
    if(LengthUnit == M){Unit = "N/m";LengthRatio = 1000;}
    if(LengthUnit == INCH){Unit = "N/in";LengthRatio = 25.4;}
    if(LengthUnit == FEET){Unit = "N/ft";LengthRatio = 304.8;}
  }

  if(WeightUnit == DN)
  {
    WeightRatio = 0.0980665;
    if(LengthUnit == CM){Unit = "dN/cm";LengthRatio = 10;}
    if(LengthUnit == DM){Unit = "dN/dm";LengthRatio = 100;}
    if(LengthUnit == M){Unit = "dN/m";LengthRatio = 1000;}
    if(LengthUnit == INCH){Unit = "dN/in";LengthRatio = 25.4;}
    if(LengthUnit == FEET){Unit = "dN/ft";LengthRatio = 304.8;}
  }

  if(WeightUnit == POUND)
  {
    WeightRatio = 0.00220462;
    if(LengthUnit == CM){Unit = "lb/cm";LengthRatio = 10;}
    if(LengthUnit == DM){Unit = "lb/dm";LengthRatio = 100;}
    if(LengthUnit == M){Unit = "lb/m";LengthRatio = 1000;}
    if(LengthUnit == INCH){Unit = "lb/in";LengthRatio = 25.4;}
    if(LengthUnit == FEET){Unit = "lb/ft";LengthRatio = 304.8;}
  }
  
  if(WeightUnit == OUNCE)
  {
    WeightRatio = 0.035375;
    if(LengthUnit == CM){Unit = "oz/cm";LengthRatio = 10;}
    if(LengthUnit == DM){Unit = "oz/dm";LengthRatio = 100;}
    if(LengthUnit == M){Unit = "oz/m";LengthRatio = 1000;}
    if(LengthUnit == INCH){Unit = "oz/in";LengthRatio = 25.4;}
    if(LengthUnit == FEET){Unit = "oz/ft";LengthRatio = 304.8;}
  }
   Serial.println("WeightUnit ; " + String(WeightUnit));
   Serial.println("LengthUnit ; " + String(LengthUnit));
   Serial.println("SetUnit : " + String(Unit));
   yield();

}


/*_____________________________________________________________LoadCellRead()________________________________________________________
Fucntion called the get the raw data from the cell. Used in Measure(). See Calcul.h
*/
float LoadCellRead()
{
  static boolean newDataReady = 0;
  const int serialPrintInterval = 0; //increase value to slow down serial print activity

  // check for new data/start next conversion:
  if (LoadCell.update()) newDataReady = true;

  // get smoothed value from the dataset:
  if (newDataReady) 
  {
    unsigned long t = 0;
    float i;
    if (millis() > t + serialPrintInterval) {
      i = LoadCell.getData();
      newDataReady = 0;
      t = millis();
    }

    return i;
  }
}


#endif

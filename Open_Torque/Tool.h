#ifndef TOOL_h
#define TOOL_h

#include "Init.h"
#include <HX711_ADC.h>
#include "ssd1306.h"
#include <Scheduler.h>
#include <Buzzer.h>
#include "AT24C256.h"

AT24C256 eeprom = AT24C256();
HX711_ADC LoadCell(HX711SCK, HX711DOUT);
Buzzer buzzer(BUZZ);

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

void LoadCellCalibrate(float i)
{
  ssd1306_clearScreen();
  
  while(millis() < millisCalibration + DELAYCALIBRATION)
  {
    ssd1306_setFixedFont(ssd1306xled_font8x16);
    ssd1306_printFixed(25, 30, "CAL OK !", STYLE_BOLD);
    LoadCell.refreshDataSet();
    LoadCell.setCalFactor(LoadCell.getNewCalibration(i));
    yield();
  }
  SettingMenuSelectionState = true;
  
  yield();
}

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

void GetUnity()
{
  
}
#endif

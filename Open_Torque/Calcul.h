#ifndef CALCUL_H
#define CALCUL_H

#include "Init.h"
#include "Interaction.h"
#include "Page.h"

/*_____________________________________________________________MEASURE________________________________________________________
Measure is a function that tkaes the raw value from the loadcell 
*/
void Measure()
{
  if(millis() > millisMeasure + DELAYMEASURE)
  {
    float i = LoadCellRead();
    if(i<40000)
    {
      valmeasure =i;
    }
    if(valmeasure<40)
    {
      valmeasure = 0;
    }
    millisMeasure = millis();
  }
  Torque = (valmeasure*WeightRatio)*(lever/LengthRatio);
  //#ifdef DEBUGOT
//  Serial.println("valmeasure : " + (String)valmeasure);
//  Serial.println("Torque : " + (String)Torque);
  //#endif  
  yield();
}

  int calculaxb()
{  
  int i = Torque*((DELAYBUZZOFF-DELAYBUZZON)/(target-target*prctbuzz))+(DELAYBUZZON*target-DELAYBUZZOFF*target*prctbuzz)/(target-target*prctbuzz);
  //
  #ifdef DEBUGOT
  Serial.println("axb : " + String(i));
  #endif
  return i;
  yield();
}

/*_____________________________________________________________WATCH TARGET BUZZ ()________________________________________________________
This function is used to make a buzz noize the bips faster as the value read by the wrench reach the target value
*/
void WatchTargetBuzz()
{
  if(Torque > target*prctbuzz && valmeasure > 200)
  {
    unsigned long currentMillis = millis();
    if(DELAYBUZZOFF-calculaxb() > 20)
    {
      if(currentMillis - prevbuzzmillis >= DELAYBUZZOFF-calculaxb())
      {
        prevbuzzmillis = currentMillis;
        if(buzzstate == LOW){buzzstate = HIGH;}
        else{buzzstate = LOW;}
        digitalWrite(BUZZ, buzzstate);
      }
    }
    else
    {
      digitalWrite(BUZZ, HIGH);
    } 
  } 
  else{digitalWrite(BUZZ, LOW);}
  yield();
}

/*_____________________________________________________________IMPERIAL MENU SELECTION ()________________________________________________________
this menu select the wich of the UNF or UNC mode to launch
*/

void ImperialMenuSelection()
{
  if(ImperialMenuSelectionState == true)
  {
    ImperialMenuSelectionState = false;
    ssd1306_clearScreen();
    boolean resume = false; 
    while(resume == false)
    {
      ssd1306_setFixedFont(ssd1306xled_font8x16);
      ssd1306_showMenu( &ImperialMenu );
      
      if(buttonENTERstate == true)
      {
        millisButton = millis();
        buttonENTERstate = false;
        
        if(ssd1306_menuSelection(&ImperialMenu) == 0)
        {
          ssd1306_clearScreen();
          ScrewMenuSelectionState = true;
          resume = true; 
        }
        if(ssd1306_menuSelection(&ImperialMenu) == 1)
        {
          ssd1306_clearScreen();
          ImperialUNCPage();
          resume = true;
        }
        if(ssd1306_menuSelection(&ImperialMenu) == 2)
        {
          ssd1306_clearScreen();
          ImperialUNFPage();
          resume = true;
        }
      }
      
      if(buttonDOWNstate == true)
      {
        millisButton = millis();
        buttonDOWNstate = false;
        ssd1306_menuDown(&ImperialMenu);
        ssd1306_updateMenu(&ImperialMenu);
      }
      if(buttonUPstate == true)
      {
        millisButton = millis();
        buttonUPstate = false;
        ssd1306_menuUp(&ImperialMenu);
        ssd1306_updateMenu(&ImperialMenu);
      }
      yield();
    }
  }
  yield();
}

/*_____________________________________________________________SCREW MENU SELECTION STATE ()________________________________________________________
This menu is used to select wich of the preset screw mdoe to use betwen metric and imperial
*/
void ScrewMenuSelection()
{
  if(ScrewMenuSelectionState == true)
  {
    ScrewMenuSelectionState = false;
    ssd1306_clearScreen();
    boolean resume = false;
    
    while(resume == false)
    {
      ssd1306_setFixedFont(ssd1306xled_font8x16);
      ssd1306_showMenu( &ScrewMenu );
      
      if(buttonENTERstate == true)
      {
        millisButton = millis();
        buttonENTERstate = false;
        
        if(ssd1306_menuSelection(&ScrewMenu) == 0)
        {
          ssd1306_clearScreen();
          TorqueMenuSelectionState = true;
          resume = true; 
        }
        if(ssd1306_menuSelection(&ScrewMenu) == 1)
        {
          ssd1306_clearScreen();
          MetricPage();
          resume = true;
        }
        if(ssd1306_menuSelection(&ScrewMenu) == 2)
        {
          ssd1306_clearScreen();
          ImperialMenuSelectionState = true;
          resume = true;
        }
      }
      if(buttonDOWNstate == true)
      {
        millisButton = millis();
        buttonDOWNstate = false;
        ssd1306_menuDown(&ScrewMenu);
        ssd1306_updateMenu(&ScrewMenu);
      }
      if(buttonUPstate == true)
      {
        millisButton = millis();
        buttonUPstate = false;
        ssd1306_menuUp(&ScrewMenu);
        ssd1306_updateMenu(&ScrewMenu);
      }
      yield();
    }
  }
  yield();
}

/*_____________________________________________________________SCREW MENU SELECTION STATE ()________________________________________________________
This menu is used to select wich of the torque mode to use (preset screws or manual)
*/
void TorqueMenuSelection()
{
  if(TorqueMenuSelectionState == true)
  {
    TorqueMenuSelectionState = false;
    ssd1306_clearScreen();
    boolean resume = false;
    while(resume == false)
    {
      ssd1306_setFixedFont(ssd1306xled_font8x16);
      //ssd1306_setFixedFont(ssd1306xled_font6x8);
      ssd1306_showMenu( &TorqueMenu );
      
      if(buttonENTERstate ==true)
      {
        millisButton = millis();
        buttonENTERstate = false;
        if(ssd1306_menuSelection(&TorqueMenu) == 0)
        {
          ssd1306_clearScreen();
          ModeMenuSelectionState = true ;
          resume = true;
        }
        if(ssd1306_menuSelection(&TorqueMenu) == 1)
        {
          ssd1306_clearScreen();
          ManualPage();
          resume = true;
        }
        if(ssd1306_menuSelection(&TorqueMenu) == 2)
        {
          ssd1306_clearScreen();
          ScrewMenuSelectionState = true;
          resume = true;
        }
      }
      if(buttonDOWNstate == true)
      {
        millisButton = millis();
        buttonDOWNstate = false;
        ssd1306_menuDown(&TorqueMenu);
        ssd1306_updateMenu(&TorqueMenu);
      }
      if(buttonUPstate == true)
      {
        millisButton = millis();
        buttonUPstate = false;
        ssd1306_menuUp(&TorqueMenu);
        ssd1306_updateMenu(&TorqueMenu);
      }
      yield();
    }
  }
  yield();
}

/*_____________________________________________________________MODE MENU SELECTION ()________________________________________________________
This menu is used to select wich of the mode to use between torque related mode, angular and scale
*/
void ModeMenuSelection()
{
  if(ModeMenuSelectionState == true)
  {
    ModeMenuSelectionState = false;
    ssd1306_clearScreen();
    boolean resume = false;
    while(resume == false)
    {
      ssd1306_setFixedFont(ssd1306xled_font8x16);
      ssd1306_showMenu( &ModeMenu );
      
      if(buttonENTERstate ==true)
      {
        millisButton = millis();
        buttonENTERstate = false;
        if(ssd1306_menuSelection(&ModeMenu) == 0)
        {
          ssd1306_clearScreen();
          MainMenuSelectionState = true;
          resume = true;
        }
        if(ssd1306_menuSelection(&ModeMenu) == 1)
        {
          ssd1306_clearScreen();
          TorqueMenuSelectionState = true;
          resume = true;
        }
        if(ssd1306_menuSelection(&ModeMenu) == 2)
        {
          ssd1306_clearScreen();
          AngularPage();
          resume = true;
        }
        if(ssd1306_menuSelection(&ModeMenu) == 3)
        {
          ssd1306_clearScreen();
          ScalePage();
          resume = true;
        }
      }
      if(buttonDOWNstate == true)
      {
        millisButton = millis();
        buttonDOWNstate = false;
        ssd1306_menuDown(&ModeMenu);
        ssd1306_updateMenu(&ModeMenu);
      }
      if(buttonUPstate == true)
      {
        millisButton = millis();
        buttonUPstate = false;
        ssd1306_menuUp(&ModeMenu);
        ssd1306_updateMenu(&ModeMenu);
      }
      yield();
    }
  }
  yield();
}

/*_____________________________________________________________UNIT MENU SELECTION ()________________________________________________________
This menu is used to select wich of unit type to change
*/

void UnitMenuSelection()
{
  if(UnitMenuSelectionState == true)
  {
    UnitMenuSelectionState = false;
    ssd1306_clearScreen();
    boolean resume = false;
    while(resume == false)
    {
      ssd1306_setFixedFont(ssd1306xled_font8x16);
      ssd1306_showMenu( &UnitMenu );
      if(buttonENTERstate ==true)
      {
        millisButton = millis();
        buttonENTERstate = false;
        if(ssd1306_menuSelection(&UnitMenu) == 0)
        {
          ssd1306_clearScreen();
          SettingMenuSelectionState = true;
          resume = true;
        }
        if(ssd1306_menuSelection(&UnitMenu) == 1)
        {
          ssd1306_clearScreen();
          WeightUnitPage();
          resume = true;
        }
        if(ssd1306_menuSelection(&UnitMenu) == 2)
        {
          ssd1306_clearScreen();
          LengthPage();
          resume = true;
        }
      }
      if(buttonDOWNstate == true)
      {
        millisButton = millis();
        buttonDOWNstate = false;
        ssd1306_menuDown(&UnitMenu);
        ssd1306_updateMenu(&UnitMenu);
      }
      if(buttonUPstate == true)
      {
        millisButton = millis();
        buttonUPstate = false;
        ssd1306_menuUp(&UnitMenu);
        ssd1306_updateMenu(&UnitMenu);
      }
      yield();
    }
  }
  yield();
}

/*_____________________________________________________________SETTING MENU SELECTION ()________________________________________________________
This menu is used to change the main setting of the wrench (lever, screw grade, lub and calibration)
*/

void SettingMenuSelection()
{
  if(SettingMenuSelectionState == true)
  {
    SettingMenuSelectionState = false;
    ssd1306_clearScreen();
    boolean resume = false;
    
    while(resume == false)
    {
      ssd1306_setFixedFont(ssd1306xled_font8x16);
      ssd1306_showMenu( &SettingMenu );
      if(buttonENTERstate == true)
      {
        millisButton = millis();
        buttonENTERstate = false;
        if(ssd1306_menuSelection(&SettingMenu) == 0)
        {
          ssd1306_clearScreen();
          MainMenuSelectionState = true;
          resume = true;
        }
        if(ssd1306_menuSelection(&SettingMenu) == 1)
        {
          ssd1306_clearScreen();
          LeverPage();
          resume = true;
        }
        if(ssd1306_menuSelection(&SettingMenu) == 2)
        {
          ssd1306_clearScreen();
          UnitMenuSelectionState = true;
          resume = true;
        }
        if(ssd1306_menuSelection(&SettingMenu) == 3)
        {
          ssd1306_clearScreen();
          ScrewGradeMenuSelectionState = true;
          resume = true;
        }
        if(ssd1306_menuSelection(&SettingMenu) == 4)
        {
          ssd1306_clearScreen();
          ScrewLubPage();
          resume = true;
        }
        if(ssd1306_menuSelection(&SettingMenu) == 5)
        {
          ssd1306_clearScreen();
          CalibrationPage();
          resume = true;
        }
      }
      if(buttonDOWNstate == true)
      {
        millisButton = millis();
        buttonDOWNstate = false;
        ssd1306_menuDown(&SettingMenu);
        ssd1306_updateMenu(&SettingMenu);
      }
      if(buttonUPstate == true)
      {
        millisButton = millis();
        buttonUPstate = false;
        ssd1306_menuUp(&SettingMenu);
        ssd1306_updateMenu(&SettingMenu);
      }
      yield();
    }
  }
  yield();
}

/*_____________________________________________________________MAIN MENU SELECTION ()________________________________________________________
This main menu is used to quick tare theloadcell, acces mode settings etc
*/

void MainMenuSelection()
{
  if(MainMenuSelectionState == true)
  {
    ssd1306_clearScreen();
    boolean resume = false;
    
    while(resume == false)
    {
      MainMenuSelectionState = false;
      ssd1306_setFixedFont(ssd1306xled_font8x16);
      ssd1306_showMenu( &MainMenu );
      
      if(buttonENTERstate ==true)
      {
        millisButton = millis();
        buttonENTERstate = false;
        
        if(ssd1306_menuSelection(&MainMenu) == 0)
        {
          ssd1306_clearScreen();
          DoLastMode();
          resume = true;
        }
        if(ssd1306_menuSelection(&MainMenu) == 1)
        {
          ssd1306_clearScreen();
          AngularTare = mpu6050.getAngleZ();
          millisTare = millis();
          LoadCellTare();
          resume = true;
          DoLastMode();
        }
        if(ssd1306_menuSelection(&MainMenu) == 2)
        {
          ssd1306_clearScreen();
          ModeMenuSelectionState = true;
          resume = true;
        }
        if(ssd1306_menuSelection(&MainMenu) == 3)
        {
          ssd1306_clearScreen();
          SettingMenuSelectionState = true;
          resume = true; 
        }
      }
      if(buttonDOWNstate == true)
      {
        millisButton = millis();
        buttonDOWNstate = false;
        ssd1306_menuDown(&MainMenu);
        ssd1306_updateMenu(&MainMenu);
      }
      if(buttonUPstate == true)
      {
        millisButton = millis();
        buttonUPstate = false;
        ssd1306_menuUp(&MainMenu);
        ssd1306_updateMenu(&MainMenu);
      }
      yield();
    }
  }
  yield();
}

/*_____________________________________________________________SCREW GRADE MENU SELECTION STATE ()________________________________________________________
This menu is used to change the grade of metric and imperial screws
*/
void ScrewGradeMenuSelection()
{
  if(ScrewGradeMenuSelectionState == true)
  {
    ScrewGradeMenuSelectionState = false;
    ssd1306_clearScreen();
    boolean resume = false;
    
    while(resume == false)
    {
      ssd1306_setFixedFont(ssd1306xled_font8x16);
      ssd1306_showMenu( &ScrewGradeMenu );
      
      if(buttonENTERstate == true)
      {
        millisButton = millis();
        buttonENTERstate = false;
        if(ssd1306_menuSelection(&ScrewGradeMenu) == 0)
        {
          ssd1306_clearScreen();
          SettingMenuSelectionState = true;
          resume = true;
        }
        if(ssd1306_menuSelection(&ScrewGradeMenu) == 1)
        {
          ssd1306_clearScreen();
          MetricGradePage();
          resume = true;
        }
        if(ssd1306_menuSelection(&ScrewGradeMenu) == 2)
        {
          ssd1306_clearScreen();
          ImperialGradePage();
          resume = true;
        }
      }
      if(buttonDOWNstate == true)
      {
        millisButton = millis();
        buttonDOWNstate = false;
        ssd1306_menuDown(&ScrewGradeMenu);
        ssd1306_updateMenu(&ScrewGradeMenu);
      }
      if(buttonUPstate == true)
      {
        millisButton = millis();
        buttonUPstate = false;
        ssd1306_menuUp(&ScrewGradeMenu);
        ssd1306_updateMenu(&ScrewGradeMenu);
      }
      yield();
    }
  }
  yield();
}

#endif

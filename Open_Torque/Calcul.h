#ifndef CALCUL_H
#define CALCUL_H

#include "Init.h"
#include "Interaction.h"
#include "Page.h"

void Measure()
{
  if(millis() > millisMeasure + DELAYMEASURE)
  {
    float i = loadcell.read();
    if(i<40000)
    {
      valmeasure =i;
    }
    if(valmeasure<75)
    {
      valmeasure = 0;
    }
    millisMeasure = millis();
  }
  Torque = (valmeasure*WeightRatio)*(lever/LongRatio);
  #ifdef DEBUGOT
  Serial.println("valmeasure : " + (String)valmeasure);
  Serial.println("Torque : " + (String)Torque);
  #endif  
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

void ScrewMenuSelection()
{
  if(ScrewMenuSelectionState == true)
  {
    ssd1306_clearScreen();
    while(1)
    {
      ssd1306_setFixedFont(ssd1306xled_font8x16);
      ssd1306_showMenu( &TorqueMenu );
      
      if(buttonENTERstate == true)
      {
        millisButton = millis();
        buttonENTERstate = false;
        
        if(ssd1306_menuSelection(&ScrewMenu) == 0)
        {
          ssd1306_clearScreen();
          TorqueMenuSelectionState = true;
          ScrewMenuSelectionState = false;
          goto labelMenu;
        }
        if(ssd1306_menuSelection(&ScrewMenu) == 1)
        {
          ssd1306_clearScreen();
          TorqueMenuSelectionState = false;
          ManualPage();
          goto labelMenu;
        }
        if(ssd1306_menuSelection(&ScrewMenu) == 2)
        {
          ssd1306_clearScreen();
          TorqueMenuSelectionState = false;
          USPage();
          goto labelMenu; 
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
  labelMenu:
  yield();
}

void TorqueMenuSelection()
{
  if(TorqueMenuSelectionState == true)
  {
    ssd1306_clearScreen();
    while(1)
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
          TorqueMenuSelectionState = false;
          ModeMenuSelectionState = true ;
          goto labelMenu;
        }
        if(ssd1306_menuSelection(&TorqueMenu) == 1)
        {
          ssd1306_clearScreen();
          TorqueMenuSelectionState = false;
          ManualPage();
          goto labelMenu;
        }
        if(ssd1306_menuSelection(&TorqueMenu) == 2)
        {
          ssd1306_clearScreen();
          TorqueMenuSelectionState = false;
          ScrewMenuSelectionState = true;
          goto labelMenu;
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
  labelMenu:
  yield();
}

void ModeMenuSelection()
{
  if(ModeMenuSelectionState == true)
  {
    ssd1306_clearScreen();
    while(1)
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
          ModeMenuSelectionState = false;
          MainMenuSelectionState = true;
          goto labelMenu;
        }
        if(ssd1306_menuSelection(&ModeMenu) == 1)
        {
          ssd1306_clearScreen();
          ModeMenuSelectionState = false;
          TorqueMenuSelectionState = true;
          goto labelMenu;
        }
        if(ssd1306_menuSelection(&ModeMenu) == 2)
        {
          ssd1306_clearScreen();
          ModeMenuSelectionState = false;
          AngularPage();
          goto labelMenu;
        }
        if(ssd1306_menuSelection(&ModeMenu) == 3)
        {
          ssd1306_clearScreen();
          ModeMenuSelectionState = false;
          WeightPage();
          goto labelMenu;
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
  labelMenu:
  yield();
}

void UnitMenuSelection()
{
  if(UnitMenuSelectionState == true)
  {
    ssd1306_clearScreen();
    while(1)
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
          UnitMenuSelectionState = false;
          SettingMenuSelectionState = true;
          goto labelMenu;
        }
        if(ssd1306_menuSelection(&UnitMenu) == 1)
        {
          ssd1306_clearScreen();
          UnitMenuSelectionState = false;
          WeightUnitPage();
          goto labelMenu;
        }
        if(ssd1306_menuSelection(&UnitMenu) == 2)
        {
          ssd1306_clearScreen();
          UnitMenuSelectionState = false;
          LongPage();
          goto labelMenu;
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
  labelMenu:
  yield();
}

void SettingMenuSelection()
{
  if(SettingMenuSelectionState == true)
  {
    ssd1306_clearScreen();
    while(1)
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
          SettingMenuSelectionState = false;
          MainMenuSelectionState = true;
          goto labelMenu;
        }
        if(ssd1306_menuSelection(&SettingMenu) == 1)
        {
          ssd1306_clearScreen();
          SettingMenuSelectionState = false;
          LeverPage();
          goto labelMenu;
        }
        if(ssd1306_menuSelection(&SettingMenu) == 2)
        {
          ssd1306_clearScreen();
          SettingMenuSelectionState = false; 
          UnitMenuSelectionState = true;
          goto labelMenu;
        }
        if(ssd1306_menuSelection(&SettingMenu) == 3)
        {
          ssd1306_clearScreen();
          SettingMenuSelectionState = false;
          CalibrationPage();
          goto labelMenu;
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
  labelMenu:
  yield();
}

void MainMenuSelection()
{
  if(MainMenuSelectionState == true)
  {
    ssd1306_clearScreen();
    while(1)
    {
      ssd1306_setFixedFont(ssd1306xled_font8x16);
      ssd1306_showMenu( &MainMenu );
      if(buttonENTERstate ==true)
      {
        millisButton = millis();
        buttonENTERstate = false;
        
        if(ssd1306_menuSelection(&MainMenu) == 0)
        {
          ssd1306_clearScreen();
          MainMenuSelectionState = false;
          DoLastMode();
          goto labelMenu;
        }
        if(ssd1306_menuSelection(&MainMenu) == 1)
        {
          ssd1306_clearScreen();
          millisTare = millis();
          MainMenuSelectionState = false;
          Tare();
          goto labelMenu;
        }
        if(ssd1306_menuSelection(&MainMenu) == 2)
        {
          ssd1306_clearScreen();
          MainMenuSelectionState = false;
          ModeMenuSelectionState = true;
          goto labelMenu;
        }
        if(ssd1306_menuSelection(&MainMenu) == 3)
        {
          ssd1306_clearScreen();
          MainMenuSelectionState = false;
          SettingMenuSelectionState = true;
          goto labelMenu;
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
  labelMenu:
  yield();
}

#endif

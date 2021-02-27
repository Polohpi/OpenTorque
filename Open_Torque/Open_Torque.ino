#include "Page.h"
#include "Tool.h"
#include "Init.h"
#include "Calcul.h"
#include "Interaction.h"

void setup() {

  Serial.begin(9600);
  loadcell.setup();
  loadcell.tare();
  ssd1306_128x64_i2c_init();
  Scheduler.startLoop(Measure);
  Scheduler.startLoop(WatchTargetBuzz);
  
  Scheduler.startLoop(MainMenuSelection);
  Scheduler.startLoop(ModeMenuSelection);
  Scheduler.startLoop(TorqueMenuSelection);
  Scheduler.startLoop(ScrewMenuSelection);
  Scheduler.startLoop(SettingMenuSelection);
  Scheduler.startLoop(UnityMenuSelection);
  
  #ifdef DEBUGOT
  Serial.println("Setup");
  #endif
  
  ssd1306_clearScreen();

  pinMode(BUTTONUP, INPUT_PULLUP);
  pinMode(BUTTONDOWN, INPUT_PULLUP);
  pinMode(BUTTONENTER, INPUT_PULLUP);
  pinMode(BUZZ, OUTPUT);
  digitalWrite(BUZZ, LOW);
  
  attachInterrupt(digitalPinToInterrupt(BUTTONUP), buttonUP, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTONDOWN), buttonDOWN, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTONENTER), buttonENTER, FALLING);

  target = eeprom.read(ADD_EEPROM);
  
  ssd1306_createMenu( &MainMenu, MainItems, sizeof(MainItems) / sizeof(char *) );
  ssd1306_createMenu( &ModeMenu, ModeItems, sizeof(ModeItems) / sizeof(char *) );
  ssd1306_createMenu( &SettingMenu, SettingItems, sizeof(SettingItems) / sizeof(char *) );
  ssd1306_createMenu( &TorqueMenu, TorqueItems, sizeof(TorqueItems) / sizeof(char *) );
  ssd1306_createMenu( &UnityMenu, UnityItems, sizeof(UnityItems) / sizeof(char *) );
  ssd1306_createMenu( &ScrewMenu, ScrewItems, sizeof(ScrewItems) / sizeof(char *) );
  
}

void loop() {
    AcceuilPage(); 
    yield();
}

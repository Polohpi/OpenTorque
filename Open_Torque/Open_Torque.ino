#include "Page.h"
#include "Tool.h"
#include "Init.h"
#include "Calcul.h"
#include "Interaction.h"

void setup() {

  Serial.begin(9600);
  loadcell.setup(-41.5);
  loadcell.tare();
  ssd1306_128x64_i2c_init();
  Scheduler.startLoop(Measure);
  Scheduler.startLoop(WatchTargetBuzz);
  
  Scheduler.startLoop(MainMenuSelection);
  Scheduler.startLoop(ModeMenuSelection);
  Scheduler.startLoop(TorqueMenuSelection);
  Scheduler.startLoop(ScrewMenuSelection);
  Scheduler.startLoop(SettingMenuSelection);
  Scheduler.startLoop(UnitMenuSelection);
  
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

  target = eeprom.read(TARGET_ADD_EEPROM);
  LastMode = eeprom.read(LASTMODE_ADD_EEPROM);
  WeightUnit = eeprom.read(WEIGHTUNIT_ADD_EEPROM);
  LongUnit = eeprom.read(LONGUNIT_ADD_EEPROM);
  lever = eeprom.read(LEVER_ADD_EEPROM)*10;

  SetUnit();
  
  ssd1306_createMenu( &MainMenu, MainItems, sizeof(MainItems) / sizeof(char *) );
  ssd1306_createMenu( &ModeMenu, ModeItems, sizeof(ModeItems) / sizeof(char *) );
  ssd1306_createMenu( &SettingMenu, SettingItems, sizeof(SettingItems) / sizeof(char *) );
  ssd1306_createMenu( &TorqueMenu, TorqueItems, sizeof(TorqueItems) / sizeof(char *) );
  ssd1306_createMenu( &UnitMenu, UnitItems, sizeof(UnitItems) / sizeof(char *) );
  ssd1306_createMenu( &ScrewMenu, ScrewItems, sizeof(ScrewItems) / sizeof(char *) );
}

void loop() {
  DoLastMode();
  while(1)
  {
    yield();
  }
}

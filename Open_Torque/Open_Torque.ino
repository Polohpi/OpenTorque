#include "Init.h"
#include "Page.h"
#include "Calcul.h"
#include "Tool.h"
#include "Interaction.h"

void setup() {

  Serial.begin(9600);
  LoadCell.begin();
  
  unsigned long stabilizingtime = 2000; // preciscion right after power-up can be improved by adding a few seconds of stabilizing time
  boolean _tare = true; //set this to false if you don't want tare to be performed in the next step
  
  LoadCell.start(stabilizingtime, _tare);
  
  if (LoadCell.getTareTimeoutFlag() || LoadCell.getSignalTimeoutFlag()) 
  {
    Serial.println("Timeout, check MCU>HX711 wiring and pin designations");
    while (1);
  }
  LoadCell.setCalFactor(1); // user set calibration value (float), initial value 1.0 may be used for this sketch
  Serial.println("Startup is complete");
  while (!LoadCell.update());
  LoadCell.tare();
  
  ssd1306_128x64_i2c_init();

  mpu6050.begin();
  mpu6050.calcGyroOffsets();
  Scheduler.startLoop(Measure);
  Scheduler.startLoop(WatchTargetBuzz);
  
  Scheduler.startLoop(MainMenuSelection);
  Scheduler.startLoop(ModeMenuSelection);
  Scheduler.startLoop(TorqueMenuSelection);
  Scheduler.startLoop(ScrewMenuSelection);
  Scheduler.startLoop(SettingMenuSelection);
  Scheduler.startLoop(UnitMenuSelection);
  Scheduler.startLoop(ImperialMenuSelection);
  
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
  LengthUnit = eeprom.read(LENGTHUNIT_ADD_EEPROM);
  lever = eeprom.read(LEVER_ADD_EEPROM)*10;
  AngularTarget = eeprom.read(ANGULARTARGET_ADD_EEPROM);
  //ImperialGrade = eeprom.read(IMPERIALGRADE_ADD_EEPROM);
  //ImperialSize = eeprom.read(IMPERIALSIZE_ADD_EEPROM);
  //ImperialThread = eeprom.read(IMPERIALTHREAD_ADD_EEPROM);
  //MetricGrade = eeprom.read(METRICGRADE_ADD_EEPROM);
  //MetricSize = eeprom.read(METRICSIZE_ADD_EEPROM);
  //CalibrationVal = EEPROMFloatRead();

  SetUnit();
  
  ssd1306_createMenu( &MainMenu, MainItems, sizeof(MainItems) / sizeof(char *) );
  ssd1306_createMenu( &ModeMenu, ModeItems, sizeof(ModeItems) / sizeof(char *) );
  ssd1306_createMenu( &SettingMenu, SettingItems, sizeof(SettingItems) / sizeof(char *) );
  ssd1306_createMenu( &TorqueMenu, TorqueItems, sizeof(TorqueItems) / sizeof(char *) );
  ssd1306_createMenu( &UnitMenu, UnitItems, sizeof(UnitItems) / sizeof(char *) );
  ssd1306_createMenu( &ScrewMenu, ScrewItems, sizeof(ScrewItems) / sizeof(char *) );
  ssd1306_createMenu( &ImperialMenu, ImperialItems, sizeof(ImperialItems) / sizeof(char *) );

  LoadCell.setCalFactor(EEPROMFloatRead());
  Serial.println("val : " + String(EEPROMFloatRead()));

}

void loop() {
  DoLastMode();
  while(1)
  {
    yield();
  }
}

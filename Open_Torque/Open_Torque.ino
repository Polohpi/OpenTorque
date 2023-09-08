#include "Init.h"
#include "Page.h"
#include "Calcul.h"
#include "Tool.h"
#include "Interaction.h"

/*

External libraries used (see Tool.h) : 
- HX711_ADC : https://github.com/olkal/HX711_ADC
- ssd1306 : https://github.com/lexus2k/ssd1306
- Buzzer : https://github.com/gmarty2000/arduino-BUZZER
- AT24C256 : https://github.com/polohpi/AT24C256
- MPU6050_tockn : https://github.com/Tockn/MPU6050_tockn


This page is for the initialisation of some library, screen menu etc. In order : 

- Launch Serial
- Initialisation of the loadcell, tare
- Initialisation of the screen
- Initialisation of the MCU for angular measurement
- Launch of the loop that checks for action in menu (when you want to enter in a menu from a main page), checks if measurment reach the target value
- Set the PinModes
- Set the attahcinterrupts for the buttons
- read already existing info from the eeprom (last mode used, last units used etc ...)
- Set the units (see Tool.h)
- Creation of the menu, The order within the menu is show later on in the code
- Void Loop starts and bring back the wrench the latest mode used

*/
void setup() {

  Serial.begin(9600);
  #ifdef DEBUGOT
  Serial.println("Setup");
  #endif

  LoadCell.begin();
  unsigned long stabilizingtime = 2000; // preciscion right after power-up can be improved by adding a few seconds of stabilizing time
  boolean _tare = true; //set this to false if you don't want tare to be performed in the next step
  
  LoadCell.start(stabilizingtime, _tare);
  
  if (LoadCell.getTareTimeoutFlag() || LoadCell.getSignalTimeoutFlag()) 
  {
    Serial.println("Timeout, check MCU>HX711 wiring and pin designations");
    while (1);
  }
  else
  {
    LoadCell.setCalFactor(-113.43); // user set calibration value (float), initial value 1.0 may be used for this sketch
    Serial.println("Startup is complete");
  }
  while (!LoadCell.update());
  LoadCell.tare();
  
  ssd1306_128x64_i2c_init();
  ssd1306_clearScreen();

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
  Scheduler.startLoop(ScrewGradeMenuSelection);

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
  lever = eeprom.read(LEVER_ADD_EEPROM)*10; //lever value is stored in cm
  AngularTarget = eeprom.read(ANGULARTARGET_ADD_EEPROM);
  //ImperialGrade = eeprom.read(IMPERIALGRADE_ADD_EEPROM);
  //ImperialSize = eeprom.read(IMPERIALSIZE_ADD_EEPROM);
  //ImperialThread = eeprom.read(IMPERIALTHREAD_ADD_EEPROM);
  MetricGrade = eeprom.read(METRICGRADE_ADD_EEPROM);
  MetricSize = eeprom.read(METRICSIZE_ADD_EEPROM);
  //CalibrationVal = EEPROMFloatRead();

  if(eeprom.read(LUB_ADD_EEPROM) == 0)
  {Lub = false;}
  else 
  {Lub = true;}

  SetUnit();

/*

The menus are organised as such :

 -Main
   Tare
   -mode
     -Torque
       Manual
       -Screw
         Metric
         Imperial
     Angular
     Scale
   -Settings
     Lever
     -unit
       Weight
       Length
     -Screw grade
       Metric
       Imperial
     -Calibration
     -Lub
    
*/
  ssd1306_createMenu( &MainMenu, MainItems, sizeof(MainItems) / sizeof(char *) ); //first menu : Tare Mode Settings
  ssd1306_createMenu( &ModeMenu, ModeItems, sizeof(ModeItems) / sizeof(char *) ); //torque angular scale
  ssd1306_createMenu( &SettingMenu, SettingItems, sizeof(SettingItems) / sizeof(char *) ); //Lever unit Screw Grade
  ssd1306_createMenu( &TorqueMenu, TorqueItems, sizeof(TorqueItems) / sizeof(char *) ); // Manual Screw
  ssd1306_createMenu( &UnitMenu, UnitItems, sizeof(UnitItems) / sizeof(char *) ); //Weight Length
  ssd1306_createMenu( &ScrewMenu, ScrewItems, sizeof(ScrewItems) / sizeof(char *) ); // Metric Imperial
  ssd1306_createMenu( &ImperialMenu, ImperialItems, sizeof(ImperialItems) / sizeof(char *) ); //unc thread unf thread
  ssd1306_createMenu( &ScrewGradeMenu, ScrewGradeItems, sizeof(ScrewGradeItems) / sizeof(char *) ); //unc thread unf thread

  
  //LoadCell.setCalFactor(EEPROMFloatRead());
  //Serial.println("val : " + String(EEPROMFloatRead()));

}

void loop() {
  DoLastMode();
  while(1)
  {
    yield(); // yield is used for the microcontroller to find time to execute all the "Scheduler" loops set earlier 
  }
}

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
}

void loop() {
    Acceuil(); 
}

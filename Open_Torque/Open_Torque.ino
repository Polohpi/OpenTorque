#include "Page.h"
#include "Tool.h"
#include "Init.h"
#include "Calcul.h"

void setup() {

  Serial.begin(9600);
  loadcell.setup();
  loadcell.tare();
  ssd1306_128x64_i2c_init();
  Scheduler.startLoop(Measure);

}

void loop() {
    Acceuil(); 
}

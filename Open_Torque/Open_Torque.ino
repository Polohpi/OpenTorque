#include "Page.h"
#include "Tool.h"
#include "Init.h"

void setup() {

  Serial.begin(9600);
  loadcell.setup();
  ssd1306_128x64_i2c_init();

}

void loop() {
    Acceuil(); 

}

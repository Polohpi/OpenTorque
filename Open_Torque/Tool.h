#ifndef TOOL_h
#define TOOL_h

#include "Init.h"
#include <HX711.h>
#include "ssd1306.h"
#include <Scheduler.h>

HX711 loadcell = HX711();

void printval(int x, int y, int value)
{
  if(value<500) //this avoid to print wrong value like 13322223. 
  {
    char s[10];
    //moove text to the left and val dec to true because pf 2 digits 
    if(value>9 && value <100)
    {x = x - WIDHTCHAR; dec = true;}

    //same with 3 digits 
    if(value>99)
    {x = x - WIDHTCHAR*2; hec = true;}

    //if value is <10 and was >10 before then clear screen. This helps to not having the screen blink all the time because of screen cleaning at every cycle. 
    if(value <10)
    {if(dec == true){dec = false;ssd1306_clearScreen();}}

    //same with value <100 that was >100 before
    if(value <100)
    {if(hec == true){hec = false; ssd1306_clearScreen();}}
    
    sprintf(s, "%d", value);
    ssd1306_printFixed(x, HEIGHTOLED-y, s, STYLE_BOLD);
  }
}

void Tare()
{
  loadcell.tare();
  //Serial.println("Tare done");
  tare = true; 
}


#endif

#ifndef PAGE_H
#define PAGE_H

#include "Tool.h"
#include "Init.h"

void Acceuil()
{
  ssd1306_setFixedFont(ssd1306xled_font6x8);
  ssd1306_clearScreen();
  for (int i =0; i<10; i++)
  {
      char s[] = "";
  sprintf(s, "Temperature = ", String(i));
  ssd1306_printFixed(0, 16, s, STYLE_BOLD);
  delay(1000);
  }
  
  while(1);
}

#endif

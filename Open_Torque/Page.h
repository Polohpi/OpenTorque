#ifndef PAGE_H
#define PAGE_H

#include "Tool.h"
#include "Init.h"

/*_____________________________________________________________GET LAST MODE ()________________________________________________________
this function is used to check the latest mode used by reading an int value from the eeprom. See "mode selection value" in init.h
*/
int GetLastMode()
{
  int i = eeprom.read(LASTMODE_ADD_EEPROM);
  return i;
}

/*_____________________________________________________________GET LAST MODE ()________________________________________________________
this is the page used the change the weight unit used in MANUALMODE, SCALEMODE, UNSCREWMODE
*/
void WeightUnitPage()
{
  int posx = 35; //coordinate of the unit postion
  int posy = 15;

  ssd1306_clearScreen();
  boolean resume = false; //resume is a value that is used to end the loop of the page and go to the menu at exit when enter is pressed

  #ifdef DEBUGOT
  Serial.println("WeightUnitPage");
  #endif

  while (resume == false)
  {
    //here, an int value (Weightunit) is compared to the default value declared in init.h to define the char value (charUnit) that is used on screen
    ssd1306_setFixedFont(ssd1306xled_font8x16);
    const char *charUnit;
    if (WeightUnit == G) {
      charUnit = "g";
    }
    if (WeightUnit == KG) {
      charUnit = "Kg";
    }
    if (WeightUnit == N) {
      charUnit = "N";
    }
    if (WeightUnit == DN) {
      charUnit = "dN";
    }
    if (WeightUnit == POUND) {
      charUnit = "Pound";
    }
    if (WeightUnit == OUNCE) {
      charUnit = "Ounce";
    }

    // keep printing on screen the charUnit selected

    ssd1306_printFixed(posx + 30, HEIGHTOLED - posy + 14, charUnit, STYLE_NORMAL);

    //if the up button is pressed, add 1 to the weightUnit value
    if (buttonUPstate == true)
    {
      millisButton = millis(); //used in interaction.h
      buttonUPstate = false;
      if (WeightUnit < 5)
      {
        #ifdef DEBUGOT
        Serial.println("UP");
        #endif
        ssd1306_clearScreen();
        WeightUnit++;
      }
    }

    //same thing with the down button. Substract.
    if (buttonDOWNstate == true)
    {
      millisButton = millis();
      buttonDOWNstate = false;
      if (WeightUnit > 0)
      {
        #ifdef DEBUGOT
        Serial.println("DOWN");
        #endif

        ssd1306_clearScreen();
        WeightUnit--;
      }
    }

    //if enter is pressed, 
    if (buttonENTERstate == true)
    {
      millisButton = millis();
      buttonENTERstate = false;

      #ifdef DEBUGOT
      Serial.println("ENTER");
      #endif

      eeprom.write(WeightUnit, WEIGHTUNIT_ADD_EEPROM);
      SetUnit(); // seetool.h
      UnitMenuSelectionState = true; //return to menu Unit Seclection
      resume = true; //get out of the loop and end WeightUnitPage function. 
    }
    yield();
  }
  yield();
}

/*_____________________________________________________________SCALE PAGE ()________________________________________________________
this is the page for the Scale MODE
*/
void ScalePage()
{
  //Write down the current mode to eeprom if different from the current one
  if (GetLastMode() != SCALEMODE)
  {
    eeprom.write(SCALEMODE, LASTMODE_ADD_EEPROM);
  }


  int posx = 55;
  int posy = 15;
  const char *charUnit;
  ssd1306_clearScreen();

  boolean resume = false; //used to end the while loop

  while (resume == false)
  {
    ssd1306_setFixedFont(comic_sans_font24x32_123);
    printval(posx, posy, WIDHTCHAR, valmeasure * WeightRatio);
    ssd1306_setFixedFont(ssd1306xled_font8x16);
    ssd1306_printFixed(0, 0, "Scale", STYLE_NORMAL);

    if (WeightUnit == G) {
      charUnit = "g";
    }
    if (WeightUnit == KG) {
      charUnit = "Kg";
    }
    if (WeightUnit == N) {
      charUnit = "N";
    }
    if (WeightUnit == DN) {
      charUnit = "dN";
    }
    if (WeightUnit == POUND) {
      charUnit = "lb";
    }
    if (WeightUnit == OUNCE) {
      charUnit = "oz";
    }

    ssd1306_printFixed(posx + 30, HEIGHTOLED - posy + 14, charUnit, STYLE_NORMAL);


    if (buttonENTERstate == true)
    {
      millisButton = millis();
      buttonENTERstate = false;
      MainMenuSelectionState = true;
      resume = true;
    }

    yield();
  }
  yield();
}

/*_____________________________________________________________MANUAL PAGE ()________________________________________________________
this is the page for the MANUAL MODE. This mode is kind of the main one. You set a value with up and down and that's it. 
*/

void ManualPage()
{
  //this write the current mode number to the eeprom if this number was different before. This is used when coming to manualpage frome another one.
  if (GetLastMode() != MANUALMODE)
  {
    eeprom.write(MANUALMODE, LASTMODE_ADD_EEPROM);
  }
  int posx = 55;
  int posy = 15;
  ssd1306_clearScreen();

  Serial.println("Manual");
  //Serial.println("Val : " + (String)EEPROMFloatRead());

  boolean resume = false;
  while (resume == false)
  {
    ssd1306_setFixedFont(ssd1306xled_font8x16);
    ssd1306_printFixed(posx + 30, HEIGHTOLED - posy + 20, Unit, STYLE_NORMAL);
    ssd1306_printFixed(0, 0, "ManualT", STYLE_NORMAL);
    printval(110, 8, 8, target);

    if (valmeasure < 200)
    {
      ssd1306_setFixedFont(comic_sans_font24x32_123);
      printval(posx, posy, WIDHTCHAR, Torque);

      if (buttonUPstate == true)
      {
        millisButton = millis();
        buttonUPstate = false;
        target++;
        eeprom.write(target, TARGET_ADD_EEPROM);
      }

      if (buttonDOWNstate == true)
      {
        millisButton = millis();
        buttonDOWNstate = false;
        if (target > TORQUEMIN)
        {
          target--;
        }
        eeprom.write(target, TARGET_ADD_EEPROM);
      }

      if (buttonENTERstate == true)
      {
        millisButton = millis();
        buttonENTERstate = false;

        MainMenuSelectionState = true;
        resume = true;
      }
    }
    else
    {
      ssd1306_setFixedFont(comic_sans_font24x32_123);
      printval(posx, posy, WIDHTCHAR, Torque);
    }
    yield();
  }
  //labelMenu:
  yield();
}

/*_____________________________________________________________LEVER PAGE ()________________________________________________________
Page to set the lever length value. Lever length can be modify but increment of 100 mm regardless of the LenghtUnit that is currently set
*/

void LeverPage()
{
  int posx = 25;
  int posy = 25;
  ssd1306_clearScreen();
  char s[10];
  boolean resume = false;
  while (resume == false)
  {
    ssd1306_setFixedFont(ssd1306xled_font8x16);
    ssd1306_printFixed(0, 0, "Lever Setting", STYLE_NORMAL);

    sprintf(s, "%d mm", lever); //lever length can be modify but increment of 100 mm regardless of the LenghtUnit that is currently set
    ssd1306_printFixed(posx + 30, HEIGHTOLED - posy + 14, s, STYLE_NORMAL);

    if (buttonUPstate == true)
    {
      millisButton = millis();
      buttonUPstate = false;
      if (lever < LEVERMAX)
      {
        ssd1306_clearScreen();
        lever += 100;
      }
    }

    if (buttonDOWNstate == true)
    {
      millisButton = millis();
      buttonDOWNstate = false;
      if (lever > LEVERMIN)
      {
        ssd1306_clearScreen();
        lever -= 100;
      }
    }

    if (buttonENTERstate == true)
    {
      millisButton = millis();
      buttonENTERstate = false;

      eeprom.write(lever / 10, LEVER_ADD_EEPROM);
      SettingMenuSelectionState = true;
      resume = true;
    }

    yield();
  }
  yield();
}

/*_____________________________________________________________LEVER PAGE ()________________________________________________________
Page to set the lever length value. Lever length can be modify but increment of 100 mm regardless of the LenghtUnit that is currently set
*/

void CalibrationPage()
{
  int posx = 55;
  int posy = 15;
  int Calibrationtarget = 170;
  const char *charUnit;
  ssd1306_clearScreen();
  boolean resume = true;

  while (resume == true)
  {
    if (WeightUnit == G) {
      charUnit = "g";
    }
    if (WeightUnit == KG) {
      charUnit = "Kg";
    }
    if (WeightUnit == N) {
      charUnit = "N";
    }
    if (WeightUnit == DN) {
      charUnit = "dN";
    }
    if (WeightUnit == POUND) {
      charUnit = "lb";
    }
    if (WeightUnit == OUNCE) {
      charUnit = "oz";
    }
    ssd1306_setFixedFont(ssd1306xled_font8x16);
    ssd1306_printFixed(posx + 30, HEIGHTOLED - posy + 14, charUnit, STYLE_NORMAL);
    ssd1306_printFixed(0, 0, "Calibrattion", STYLE_NORMAL);

    if (valmeasure < 50)
    {
      ssd1306_setFixedFont(comic_sans_font24x32_123);
      printval(posx, posy, WIDHTCHAR, Calibrationtarget);

      if (buttonUPstate == true)
      {
        millisButton = millis();
        buttonUPstate = false;
        Calibrationtarget += 10;
      }

      if (buttonDOWNstate == true)
      {
        millisButton = millis();
        buttonDOWNstate = false;
        if (target > TORQUEMIN)
        {
          Calibrationtarget -= 10;
        }
      }

      if (buttonENTERstate == true)
      {
        millisButton = millis();
        buttonENTERstate = false;
        resume = false;
      }
    }
    else
    {
      ssd1306_setFixedFont(comic_sans_font24x32_123);
      printval(posx, posy, WIDHTCHAR, valmeasure * WeightRatio);

      if (buttonENTERstate == true)
      {
        millisButton = millis();
        buttonENTERstate = false;
        millisCalibration = millis();
        LoadCellCalibrate(Calibrationtarget);

        resume = false;
        SettingMenuSelectionState = true;
      }
    }
    yield();
  }
  //SettingMenuSelectionState = true;
  yield();
}

/*_____________________________________________________________ANGULAR PAGE ()________________________________________________________
This mode is used to tighten a screw without a specified torque but with an angle. 
*/
void AngularPage()
{
  if (GetLastMode() != ANGULARMODE)
  {
    eeprom.write(ANGULARMODE, LASTMODE_ADD_EEPROM);
  }

  int posx = 55;
  int posy = 15;

  int value;
  boolean resume = false;

  while (resume == false)
  {
    value = sqrt(sq(mpu6050.getAngleZ() - AngularTare)); //AngularTare is a "zero" value to do the zeroing
    ssd1306_setFixedFont(ssd1306xled_font8x16);
    ssd1306_printFixed(posx + 30, HEIGHTOLED - posy + 14, "deg", STYLE_NORMAL);
    ssd1306_printFixed(0, 0, "Angular", STYLE_NORMAL);

    mpu6050.update();

    ssd1306_setFixedFont(comic_sans_font24x32_123);

    if (value < 2 )
    {
      printval(posx, posy, WIDHTCHAR, AngularTarget);
    }
    else
    {
      printval(posx, posy, WIDHTCHAR, value);
    }


    if (buttonUPstate == true)
    {
      millisButton = millis();
      buttonUPstate = false;
      if (AngularTarget < 360)
      {
        ssd1306_clearScreen();
        AngularTarget += 5;
        eeprom.write(AngularTarget, ANGULARTARGET_ADD_EEPROM);
      }
    }

    if (buttonDOWNstate == true)
    {
      millisButton = millis();
      buttonDOWNstate = false;
      if (AngularTarget > 0)
      {
        ssd1306_clearScreen();
        AngularTarget -= 5;
        eeprom.write(AngularTarget, ANGULARTARGET_ADD_EEPROM);
      }
    }

    if (buttonENTERstate == true)
    {
      millisButton = millis();
      buttonENTERstate = false;
      MainMenuSelectionState = true;
      resume = true;
    }

    yield();
  }
  yield();
}

/*_____________________________________________________________LENGHT PAGE ()________________________________________________________
Page to set the lever length value. Lever length can be modify but increment of 100 mm regardless of the LenghtUnit that is currently set
*/

void LengthPage()
{
  int posx = 25;
  int posy = 25;
  ssd1306_clearScreen();

  boolean resume = false;

  while (resume == false)
  {
    ssd1306_setFixedFont(ssd1306xled_font8x16);

    const char *charUnit;
    if (LengthUnit == CM) {
      charUnit = "centimeter";
    }
    if (LengthUnit == DM) {
      charUnit = "decimeter";
    }
    if (LengthUnit == M) {
      charUnit = "meter";
    }
    if (LengthUnit == INCH) {
      charUnit = "inch";
    }
    if (LengthUnit == FEET) {
      charUnit = "Feet";
    }

    ssd1306_printFixed(posx + 30, HEIGHTOLED - posy + 14, charUnit, STYLE_NORMAL);

    if (buttonUPstate == true)
    {
      millisButton = millis();
      buttonUPstate = false;
      if (LengthUnit < 4)
      {
        ssd1306_clearScreen();
        LengthUnit++;
      }
    }

    if (buttonDOWNstate == true)
    {
      millisButton = millis();
      buttonDOWNstate = false;
      if (LengthUnit > 0)
      {
        ssd1306_clearScreen();
        LengthUnit--;
      }
    }

    if (buttonENTERstate == true)
    {
      millisButton = millis();
      buttonENTERstate = false;

      eeprom.write(LengthUnit, LENGTHUNIT_ADD_EEPROM);
      SetUnit();
      UnitMenuSelectionState = true;
      resume = true;
    }

    yield();
  }
  yield();
}

/*_____________________________________________________________IMPERIAL UNF PAGE ()________________________________________________________
this page used the array of values in init.h to provide a preset tightening value for each size of UNF screws. Press UP and DOWN to navigate trough the different sizes. 
*/

void ImperialUNFPage()
{
  if (GetLastMode() != IMPERIALUNFMODE)
  {
    eeprom.write(IMPERIALUNFMODE, LASTMODE_ADD_EEPROM);
  }

  WeightUnit = POUND;
  LengthUnit = FEET;

  int posx = 55;
  int posy = 15;
  ssd1306_clearScreen();
  boolean resume = false;



  Serial.println("ImperialPage");

  while (resume == false)
  {
    ssd1306_setFixedFont(ssd1306xled_font8x16);
    ssd1306_printFixed(posx + 28, HEIGHTOLED - posy + 24, "lb.ft", STYLE_NORMAL);
    ssd1306_printFixed(0, 0, "UNF", STYLE_NORMAL);

    ssd1306_setFixedFont(ssd1306xled_font8x16);

    const char *SizeUnit;
    if (ImperialSize == IMPERIAL_1_4) {
      SizeUnit = " 1/4";
    }
    if (ImperialSize == IMPERIAL_5_16) {
      SizeUnit = "5/16";
    }
    if (ImperialSize == IMPERIAL_3_8) {
      SizeUnit = " 3/8";
    }
    if (ImperialSize == IMPERIAL_7_16) {
      SizeUnit = "7/16";
    }
    if (ImperialSize == IMPERIAL_1_2) {
      SizeUnit = " 1/2";
    }
    if (ImperialSize == IMPERIAL_9_16) {
      SizeUnit = "9/16";
    }
    if (ImperialSize == IMPERIAL_5_8) {
      SizeUnit = " 5/8";
    }
    if (ImperialSize == IMPERIAL_3_4) {
      SizeUnit = " 3/4";
    }
    if (ImperialSize == IMPERIAL_7_8) {
      SizeUnit = " 7/8";
    }
    if (ImperialSize == IMPERIAL_1_0) {
      SizeUnit = "1 in";
    }


    const char *GradeUnit;
    if (ImperialGrade == IMPERIAL_G1) {
      GradeUnit = "  G1";
    }
    if (ImperialGrade == IMPERIAL_G2) {
      GradeUnit = "  G2";
    }
    if (ImperialGrade == IMPERIAL_G2) {
      GradeUnit = "  G5";
    }
    if (ImperialGrade == IMPERIAL_G7) {
      GradeUnit = "  G7";
    }
    if (ImperialGrade == IMPERIAL_G8) {
      GradeUnit = "  G8";
    }
    if (ImperialGrade == IMPERIAL_A449) {
      GradeUnit = "A449";
    }
    if (ImperialGrade == IMPERIAL_A490) {
      GradeUnit = "A490";
    }
    if (ImperialGrade == IMPERIAL_A36) {
      GradeUnit = " G36";
    }
    if (ImperialGrade == IMPERIAL_G1045) {
      GradeUnit = "1045";
    }
    if (ImperialGrade == IMPERIAL_G4140) {
      GradeUnit = "4140";
    }

    const char *LubState;
    if (Lub == false) {
      LubState = "NOLUB";
    }
    else(LubState = "  LUB");

    ssd1306_printFixed(87, 5, LubState, STYLE_NORMAL);
    ssd1306_printFixed(95, 35, SizeUnit, STYLE_NORMAL);
    ssd1306_printFixed(87, 20, GradeUnit, STYLE_NORMAL);

    if (valmeasure < 200)
    {
      ssd1306_setFixedFont(comic_sans_font24x32_123);

      if (Lub == false)
      {
        printval(posx, posy, WIDHTCHAR, round( Imperial_NOLUB_UNF[ImperialSize][ImperialGrade] ));
      }
      else
      {
        printval(posx, posy, WIDHTCHAR, round( Imperial_LUB_UNF[ImperialSize][ImperialGrade] ));
      }

      if (buttonUPstate == true)
      {
        millisButton = millis();
        buttonUPstate = false;
        if (ImperialSize < 9)
        {
          Serial.println("UP");
          ImperialSize++;
          eeprom.write(ImperialSize, IMPERIALSIZE_ADD_EEPROM);
        }
      }

      if (buttonDOWNstate == true)
      {
        millisButton = millis();
        buttonDOWNstate = false;
        if (ImperialSize > 0)
        {
          Serial.println("DOWN");
          ImperialSize--;
          eeprom.write(ImperialSize, IMPERIALSIZE_ADD_EEPROM);
        }
      }

      if (buttonENTERstate == true)
      {
        millisButton = millis();
        buttonENTERstate = false;
        Serial.println("ENTER");
        MainMenuSelectionState = true;
        resume = true;
      }
    }
    else
    {
      ssd1306_setFixedFont(comic_sans_font24x32_123);
      printval(posx, posy, WIDHTCHAR, Torque);
    }
    yield();
  }
  yield();
}

/*_____________________________________________________________IMPERIAL UNC PAGE ()________________________________________________________
this page used the array of values in init.h to provide a preset tightening value for each size of UNC screws. Press UP and DOWN to navigate trough the different sizes. 
*/

void ImperialUNCPage()
{
  if (GetLastMode() != IMPERIALUNCMODE)
  {
    eeprom.write(IMPERIALUNCMODE, LASTMODE_ADD_EEPROM);
  }

  WeightUnit = POUND;
  LengthUnit = FEET;

  int posx = 55;
  int posy = 15;
  ssd1306_clearScreen();
  boolean resume = false;



  Serial.println("UNCPage");

  while (resume == false)
  {
    ssd1306_setFixedFont(ssd1306xled_font8x16);
    ssd1306_printFixed(posx + 28, HEIGHTOLED - posy + 24, "lb.ft", STYLE_NORMAL);
    ssd1306_printFixed(0, 0, "UNC", STYLE_NORMAL);

    ssd1306_setFixedFont(ssd1306xled_font8x16);

    const char *SizeUnit;
    if (ImperialSize == IMPERIAL_1_4) {
      SizeUnit = " 1/4";
    }
    if (ImperialSize == IMPERIAL_5_16) {
      SizeUnit = "5/16";
    }
    if (ImperialSize == IMPERIAL_3_8) {
      SizeUnit = " 3/8";
    }
    if (ImperialSize == IMPERIAL_7_16) {
      SizeUnit = "7/16";
    }
    if (ImperialSize == IMPERIAL_1_2) {
      SizeUnit = " 1/2";
    }
    if (ImperialSize == IMPERIAL_9_16) {
      SizeUnit = "9/16";
    }
    if (ImperialSize == IMPERIAL_5_8) {
      SizeUnit = " 5/8";
    }
    if (ImperialSize == IMPERIAL_3_4) {
      SizeUnit = " 3/4";
    }
    if (ImperialSize == IMPERIAL_7_8) {
      SizeUnit = " 7/8";
    }
    if (ImperialSize == IMPERIAL_1_0) {
      SizeUnit = "1 in";
    }


    const char *GradeUnit;
    if (ImperialGrade == IMPERIAL_G1) {
      GradeUnit = "  G1";
    }
    if (ImperialGrade == IMPERIAL_G2) {
      GradeUnit = "  G2";
    }
    if (ImperialGrade == IMPERIAL_G2) {
      GradeUnit = "  G5";
    }
    if (ImperialGrade == IMPERIAL_G7) {
      GradeUnit = "  G7";
    }
    if (ImperialGrade == IMPERIAL_G8) {
      GradeUnit = "  G8";
    }
    if (ImperialGrade == IMPERIAL_A449) {
      GradeUnit = "A449";
    }
    if (ImperialGrade == IMPERIAL_A490) {
      GradeUnit = "A490";
    }
    if (ImperialGrade == IMPERIAL_A36) {
      GradeUnit = " G36";
    }
    if (ImperialGrade == IMPERIAL_G1045) {
      GradeUnit = "1045";
    }
    if (ImperialGrade == IMPERIAL_G4140) {
      GradeUnit = "4140";
    }

    const char *LubState;
    if (Lub == false) {
      LubState = "NOLUB";
    }
    else(LubState = "  LUB");

    ssd1306_printFixed(87, 5, LubState, STYLE_NORMAL);
    ssd1306_printFixed(95, 35, SizeUnit, STYLE_NORMAL);
    ssd1306_printFixed(87, 20, GradeUnit, STYLE_NORMAL);

    if (valmeasure < 200)
    {
      ssd1306_setFixedFont(comic_sans_font24x32_123);

      if (Lub == false)
      {
        printval(posx, posy, WIDHTCHAR, round( Imperial_NOLUB_UNC[ImperialSize][ImperialGrade] ));
      }
      else
      {
        printval(posx, posy, WIDHTCHAR, round( Imperial_LUB_UNC[ImperialSize][ImperialGrade] ));
      }

      if (buttonUPstate == true)
      {
        millisButton = millis();
        buttonUPstate = false;
        if (ImperialSize < 9)
        {
          Serial.println("UP");
          ImperialSize++;
          eeprom.write(ImperialSize, IMPERIALSIZE_ADD_EEPROM);
        }
      }

      if (buttonDOWNstate == true)
      {
        millisButton = millis();
        buttonDOWNstate = false;
        if (ImperialSize > 0)
        {
          Serial.println("DOWN");
          ImperialSize--;
          eeprom.write(ImperialSize, IMPERIALSIZE_ADD_EEPROM);
        }
      }

      if (buttonENTERstate == true)
      {
        millisButton = millis();
        buttonENTERstate = false;
        Serial.println("ENTER");
        MainMenuSelectionState = true;
        resume = true;
      }
    }
    else
    {
      ssd1306_setFixedFont(comic_sans_font24x32_123);
      printval(posx, posy, WIDHTCHAR, Torque);
    }
    yield();
  }
  yield();
}

/*_____________________________________________________________METRIC PAGE ()________________________________________________________
this page used the array of values in init.h to provide a preset tightening value for each size of Metric screws. Press UP and DOWN to navigate trough the different sizes. 
*/

void MetricPage()
{
  if (GetLastMode() != METRICMODE)
  {
    eeprom.write(METRICMODE, LASTMODE_ADD_EEPROM);
  }

  WeightUnit = N;
  LengthUnit = M;

  int posx = 55;
  int posy = 15;
  ssd1306_clearScreen();
  boolean resume = false;



  Serial.println("MetricPage");

  while (resume == false)
  {
    ssd1306_setFixedFont(ssd1306xled_font8x16);
    ssd1306_printFixed(posx + 28, HEIGHTOLED - posy + 24, "  N/m", STYLE_NORMAL);
    ssd1306_printFixed(0, 0, "Metric", STYLE_NORMAL);

    ssd1306_setFixedFont(ssd1306xled_font8x16);
    const char *SizeUnit;
    if (MetricSize == M4) {
      SizeUnit = " M4";
    }
    if (MetricSize == M5) {
      SizeUnit = " M5";
    }
    if (MetricSize == M6) {
      SizeUnit = " M6";
    }
    if (MetricSize == M8) {
      SizeUnit = " M8";
    }
    if (MetricSize == M10) {
      SizeUnit = "M10";
    }
    if (MetricSize == M12) {
      SizeUnit = "M12";
    }
    if (MetricSize == M14) {
      SizeUnit = "M14";
    }
    if (MetricSize == M16) {
      SizeUnit = "M16";
    }
    if (MetricSize == M18) {
      SizeUnit = "M18";
    }
    if (MetricSize == M20) {
      SizeUnit = "M20";
    }
    if (MetricSize == M22) {
      SizeUnit = "M22";
    }
    if (MetricSize == M24) {
      SizeUnit = "M24";
    }
    if (MetricSize == M27) {
      SizeUnit = "M27";
    }

    const char *GradeUnit;
    if (MetricGrade == METRIC_5_6) {
      GradeUnit = " G5.6";
    }
    if (MetricGrade == METRIC_5_8) {
      GradeUnit = " G5.8";
    }
    if (MetricGrade == METRIC_6_8) {
      GradeUnit = " G6.8";
    }
    if (MetricGrade == METRIC_8_8) {
      GradeUnit = " G8.8";
    }
    if (MetricGrade == METRIC_9_8) {
      GradeUnit = " G9.8";
    }
    if (MetricGrade == METRIC_10_9) {
      GradeUnit = "G10.9";
    }
    if (MetricGrade == METRIC_12_9) {
      GradeUnit = "G12.9";
    }

    const char *LubState;
    if (Lub == false) {
      LubState = "NOLUB";
    }
    else(LubState = "  LUB");

    ssd1306_printFixed(87, 5, LubState, STYLE_NORMAL);
    ssd1306_printFixed(102, 35, SizeUnit, STYLE_NORMAL);
    ssd1306_printFixed(87, 20, GradeUnit, STYLE_NORMAL);

    if (valmeasure < 200)
    {
      ssd1306_setFixedFont(comic_sans_font24x32_123);

      if (Lub == false)
      {
        printval(posx, posy, WIDHTCHAR, round( Metric_NOLUB[MetricSize][MetricGrade] ));
      }
      else
      {
        printval(posx, posy, WIDHTCHAR, round( Metric_LUB[MetricSize][MetricGrade] ));
      }

      if (buttonUPstate == true)
      {
        millisButton = millis();
        buttonUPstate = false;
        if (MetricSize < 12)
        {
          Serial.println("UP");
          //ssd1306_clearScreen();
          MetricSize++;
          eeprom.write(MetricSize, METRICSIZE_ADD_EEPROM);
        }
      }

      if (buttonDOWNstate == true)
      {
        millisButton = millis();
        buttonDOWNstate = false;
        if (MetricSize > 0)
        {
          Serial.println("DOWN");
          //ssd1306_clearScreen();
          MetricSize--;
          eeprom.write(MetricSize, METRICSIZE_ADD_EEPROM);
        }
      }

      if (buttonENTERstate == true)
      {
        millisButton = millis();
        buttonENTERstate = false;
        Serial.println("ENTER");
        MainMenuSelectionState = true;
        resume = true;
      }
    }
    else
    {
      ssd1306_setFixedFont(comic_sans_font24x32_123);
      printval(posx, posy, WIDHTCHAR, Torque);
      if (buttonENTERstate == true)
      {
        millisButton = millis();
        buttonENTERstate = false;
        Serial.println("ENTER");
        MainMenuSelectionState = true;
        resume = true;
      }
    }
    yield();
  }
  yield();
}

/*_____________________________________________________________METRIC GRADE PAGE ()________________________________________________________
this page is used to set the quality grade of metric screws. This will be taken into acocunt in the METRIC MODE 
*/
void MetricGradePage()
{
  int posx = 25;
  int posy = 25;
  ssd1306_clearScreen();
  boolean resume = false;


  while (resume == false)
  {
    ssd1306_setFixedFont(ssd1306xled_font8x16);
    ssd1306_printFixed(0, 0, "Metric Grade", STYLE_NORMAL);

    ssd1306_setFixedFont(ssd1306xled_font8x16);
    const char *GradeUnit;
    if (MetricGrade == METRIC_5_6) {
      GradeUnit = " G5.6";
    }
    if (MetricGrade == METRIC_5_8) {
      GradeUnit = " G5.8";
    }
    if (MetricGrade == METRIC_6_8) {
      GradeUnit = " G6.8";
    }
    if (MetricGrade == METRIC_8_8) {
      GradeUnit = " G8.8";
    }
    if (MetricGrade == METRIC_9_8) {
      GradeUnit = " G9.8";
    }
    if (MetricGrade == METRIC_10_9) {
      GradeUnit = "G10.9";
    }
    if (MetricGrade == METRIC_12_9) {
      GradeUnit = "G12.9";
    }

    ssd1306_printFixed(55, 28, GradeUnit, STYLE_NORMAL);

    if (buttonUPstate == true)
    {
      millisButton = millis();
      buttonUPstate = false;
      if (MetricGrade < 6)
      {
        ssd1306_clearScreen();
        MetricGrade++;
      }
    }

    if (buttonDOWNstate == true)
    {
      millisButton = millis();
      buttonDOWNstate = false;
      if (MetricGrade > 0)
      {
        ssd1306_clearScreen();
        MetricGrade--;
      }
    }

    if (buttonENTERstate == true)
    {
      millisButton = millis();
      buttonENTERstate = false;

      eeprom.write(MetricGrade, METRICGRADE_ADD_EEPROM);
      SettingMenuSelectionState = true;
      resume = true;
    }

    yield();
  }
  yield();
}

/*_____________________________________________________________IMPERIAL GRADE PAGE ()________________________________________________________
this page is used to set the quality grade of metric screws. This will be taken into acocunt in the METRIC MODE 
*/

void ImperialGradePage()
{
  int posx = 25;
  int posy = 25;
  ssd1306_clearScreen();
  boolean resume = false;


  while (resume == false)
  {
    ssd1306_setFixedFont(ssd1306xled_font8x16);
    ssd1306_printFixed(0, 0, "Imperial Grade", STYLE_NORMAL);

    ssd1306_setFixedFont(ssd1306xled_font8x16);
    const char *GradeUnit;

    if (ImperialGrade == IMPERIAL_G1) {
      GradeUnit = "  G1";
    }
    if (ImperialGrade == IMPERIAL_G2) {
      GradeUnit = "  G2";
    }
    if (ImperialGrade == IMPERIAL_G2) {
      GradeUnit = "  G5";
    }
    if (ImperialGrade == IMPERIAL_G7) {
      GradeUnit = "  G7";
    }
    if (ImperialGrade == IMPERIAL_G8) {
      GradeUnit = "  G8";
    }
    if (ImperialGrade == IMPERIAL_A449) {
      GradeUnit = "A449";
    }
    if (ImperialGrade == IMPERIAL_A490) {
      GradeUnit = "A490";
    }
    if (ImperialGrade == IMPERIAL_A36) {
      GradeUnit = " G36";
    }
    if (ImperialGrade == IMPERIAL_G1045) {
      GradeUnit = "G1045";
    }
    if (ImperialGrade == IMPERIAL_G4140) {
      GradeUnit = "G4140";
    }

    ssd1306_printFixed(55, 28, GradeUnit, STYLE_NORMAL);

    if (buttonUPstate == true)
    {
      millisButton = millis();
      buttonUPstate = false;
      if (ImperialGrade < 9)
      {
        ImperialGrade++;
      }
    }

    if (buttonDOWNstate == true)
    {
      millisButton = millis();
      buttonDOWNstate = false;
      if (ImperialGrade > 0)
      {
        ImperialGrade--;
      }
    }

    if (buttonENTERstate == true)
    {
      millisButton = millis();
      buttonENTERstate = false;

      eeprom.write(ImperialGrade, IMPERIALGRADE_ADD_EEPROM);
      SettingMenuSelectionState = true;
      resume = true;
    }

    yield();
  }
  yield();
}

/*_____________________________________________________________SCREW LUB PAGE ()________________________________________________________
this page is used to set if the tightening environement is lubed (copper grease) or not 
*/

void ScrewLubPage()
{
  int posx = 25;
  int posy = 25;
  ssd1306_clearScreen();
  boolean resume = false;

  while (resume == false)
  {
    ssd1306_setFixedFont(ssd1306xled_font8x16);
    ssd1306_printFixed(0, 0, "Screw Lub", STYLE_NORMAL);

    if (Lub == false)
    {
      ssd1306_printFixed(posx + 30, HEIGHTOLED - posy + 14, " NO", STYLE_NORMAL);
    }
    else
    {
      ssd1306_printFixed(posx + 30, HEIGHTOLED - posy + 14, "YES", STYLE_NORMAL);
    }

    if (buttonUPstate == true)
    {
      millisButton = millis();
      buttonUPstate = false;
      if (Lub == false )
      {
        ssd1306_clearScreen();
        Lub = true;
      }
    }

    if (buttonDOWNstate == true)
    {
      millisButton = millis();
      buttonDOWNstate = false;
      if (Lub == true)
      {
        ssd1306_clearScreen();
        Lub = false;
      }
    }

    if (buttonENTERstate == true)
    {
      millisButton = millis();
      buttonENTERstate = false;
      if (Lub == false)
      {
        eeprom.write(0, LUB_ADD_EEPROM);
      }
      else
      {
        eeprom.write(1, LUB_ADD_EEPROM);
      }
      SettingMenuSelectionState = true;
      resume = true;
    }

    yield();
  }
  yield();
}

/*_____________________________________________________________DO LAST MODE ()________________________________________________________
This function is used to get the wrench back to its last state
*/

void DoLastMode()
{
  if (GetLastMode() == MANUALMODE)
  {
    ManualPage();
  }
  else if (GetLastMode() == METRICMODE)
  {
    MetricPage();
  }
  else if (GetLastMode() == IMPERIALUNFMODE)
  {
    ImperialUNFPage();
  }
  else if (GetLastMode() == IMPERIALUNCMODE)
  {
    ImperialUNCPage();
  }
  else if (GetLastMode() == ANGULARMODE)
  {
    AngularPage();
  }
  else if (GetLastMode() == SCALEMODE)
  {
    ScalePage();
  }
}

#endif

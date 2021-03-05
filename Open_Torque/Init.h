#ifndef INIT_H
#define INIT_H

#define HEIGHTOLED 39
#define WIDHTOLED 104
#define HEIGHTCHAR 32
#define WIDHTCHAR 24
#define DELAYBUZZON 0
#define DELAYBUZZOFF 1000

#define BUZZ 10
#define BUTTONENTER 9
#define BUTTONUP 8
#define BUTTONDOWN 7
#define DELAYBUTTON 150
#define DELAYTARE 2000
#define DELAYCALIBRATION 1000
#define TORQUEMIN 2
#define LEVERMAX 1500
#define LEVERMIN 200

#define TARGET_ADD_EEPROM 0
#define LASTMODE_ADD_EEPROM 1
#define WEIGHTUNIT_ADD_EEPROM 2
#define LENGTHUNIT_ADD_EEPROM 3
#define LEVER_ADD_EEPROM 4
#define ANGULARTARGET_ADD_EEPROM 5
#define CALIBRATIONVALUE_ADD_EEPROM 10

#define MANUALMODE 0
#define METRICMODE 1
#define USMODE 2
#define ANGULARMODE 3
#define SCALEMODE 4
#define ANGULARMODE 5

#define G 0
#define KG 1
#define N 2
#define DN 3
#define POUND 4
#define OUNCE 5

#define CM 0
#define DM 1
#define M 2
#define INCH 3
#define FEET 4

#define HX711SCK 2
#define HX711DOUT 3


//#define DEBUGOT

float Torque = 0;
float valmeasure = 0;
float oldvalmeasure = 0;
int lever;
float prctbuzz =0.75;


int buzzstate = LOW;
int target;
int AngularTarget;
int AngularTare = 0;;
int LastMode;

int WeightUnit;
int LengthUnit;
const char *Unit;
float WeightRatio;
float LengthRatio;
double CalibrationVal;

unsigned long prevbuzzmillis = 0;

unsigned long millisMeasure = 0;
unsigned long millisButton = 0;
unsigned long millisTare = 0;
unsigned long millisCalibration = 0;

boolean dec = false;
boolean hec = false;

boolean PauseAcceuil = false;

#define DELAYMEASURE 100

boolean buttonUPstate = false;
boolean buttonDOWNstate = false;
boolean buttonENTERstate = false;
boolean buttonENTER2state = false;

boolean MainMenuSelectionState = false;
boolean ModeMenuSelectionState = false;
boolean TorqueMenuSelectionState = false;
boolean ScrewMenuSelectionState = false;
boolean SettingMenuSelectionState = false;
boolean UnitMenuSelectionState = false;

const char *MainItems[] =
{
    "Exit",
    "Tare",
    "Mode",
    "Setting",
};

const char *ModeItems[] =
{
    "Back",
    "Torque",
    "Angular",
    "Scale",
};

const char *SettingItems[] =
{
    "Back",
    "Lever",
    "Unit",
    "Calibration",
};

const char *TorqueItems[] =
{
    "Back",
    "Manual",
    "Screw",
};

const char *UnitItems[] =
{
    "Back",
    "Weight",
    "Length",
};

const char *ScrewItems[] =
{
    "Back",
    "Metric",
    "US",
};
#endif

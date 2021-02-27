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
#define DELAYBUTTON 100
#define DELAYBUTTON2 2000
#define DELAYTARE 2000
#define TORQUEMIN 2

#define ADD_EEPROM 0

//#define DEBUGOT

float Torque = 0;
float valmeasure = 0;
float oldvalmeasure = 0;
float bdl = 350;
float prctbuzz =0.75;


int buzzstate = LOW;
int target = 20;

unsigned long prevbuzzmillis = 0;

unsigned long millisMeasure = 0;
unsigned long millisButton = 0;
unsigned long millisTare = 0;

boolean dec = false;
boolean hec = false;

boolean PauseAcceuil = false;

#define DELAYMEASURE 50

boolean buttonUPstate = false;
boolean buttonDOWNstate = false;
boolean buttonENTERstate = false;
boolean buttonENTER2state = false;

boolean MainMenuSelectionState = false;
boolean ModeMenuSelectionState = false;
boolean TorqueMenuSelectionState = false;
boolean ScrewMenuSelectionState = false;
boolean SettingMenuSelectionState = false;
boolean UnityMenuSelectionState = false;

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
    "Weight",
};

const char *SettingItems[] =
{
    "Back",
    "Lever",
    "Unity",
    "Calibration",
};

const char *TorqueItems[] =
{
    "Back",
    "FreeMode",
    "Screw",
};

const char *UnityItems[] =
{
    "Back",
    "Weight",
    "Long",
};

const char *ScrewItems[] =
{
    "Back",
    "Metric",
    "US",
};
#endif

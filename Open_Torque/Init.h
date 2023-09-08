/*
This page is used for all the fixed values, delays, EEPROM addresses, physical pins, units. 

- stucture of all menus
- Array of data for the presaved torques values for metric UNF UNC screws


*/

#ifndef INIT_H
#define INIT_H

// screen
#define HEIGHTOLED 39
#define WIDHTOLED 104
#define HEIGHTCHAR 32
#define WIDHTCHAR 24


#define DELAYBUZZON 0
#define DELAYBUZZOFF 1000

//define pins
#define BUZZ 10
#define BUTTONENTER 9
#define BUTTONUP 8
#define BUTTONDOWN 7

//define delays in ms
#define DELAYBUTTON 150
#define DELAYTARE 2000
#define DELAYCALIBRATION 1000
#define DELAYMEASURE 100

//min max values
#define TORQUEMIN 2
#define LEVERMAX 2000
#define LEVERMIN 200

//define EEPROM addresses 
#define TARGET_ADD_EEPROM 0
#define LASTMODE_ADD_EEPROM 1
#define WEIGHTUNIT_ADD_EEPROM 2
#define LENGTHUNIT_ADD_EEPROM 3
#define LEVER_ADD_EEPROM 4
#define ANGULARTARGET_ADD_EEPROM 5
#define IMPERIALGRADE_ADD_EEPROM 6
#define METRICGRADE_ADD_EEPROM 7
#define IMPERIALSIZE_ADD_EEPROM 8
#define METRICSIZE_ADD_EEPROM 9
#define IMPERIALTHREAD_ADD_EEPROM 10
#define CALIBRATIONVALUE_ADD_EEPROM 15
#define LUB_ADD_EEPROM 16

//define mode selection value, used later on in the menu
#define MANUALMODE 0
#define METRICMODE 1
#define IMPERIALUNFMODE 2
#define IMPERIALUNCMODE 3
#define ANGULARMODE 4
#define SCALEMODE 5
#define UNSCREWMODE 6 //no created yet

//define weight units selection values
#define G 0
#define KG 1
#define N 2
#define DN 3
#define POUND 4
#define OUNCE 5

//define length units selection values 
#define CM 0
#define DM 1
#define M 2
#define INCH 3
#define FEET 4

//pins of the lodcell amplifier 
#define HX711SCK 2
#define HX711DOUT 3

//how many raws and columns for the presaved torque values. Same number of raws and columns for a lubed or dryed environment
#define METRIC_ROWS 13
#define METRIC_COLUMNS 7

//same for UNC screws
#define IMPERIAL_UNC_ROWS 10
#define IMPERIAL_UNC_COLUMNS 10

//same for UNF screws
#define IMPERIAL_UNF_ROWS 10
#define IMPERIAL_UNF_COLUMNS 9

//define metric selection value 
#define M4 0
#define M5 1
#define M6 2
#define M8 3
#define M10 4
#define M12 5
#define M14 6
#define M16 7
#define M18 8
#define M20 9
#define M22 10
#define M24 11
#define M27 12

//define imperial selection value 

#define IMPERIAL_1_4 0
#define IMPERIAL_5_16 1
#define IMPERIAL_3_8 2
#define IMPERIAL_7_16 3
#define IMPERIAL_1_2 4
#define IMPERIAL_9_16 5
#define IMPERIAL_5_8 6
#define IMPERIAL_3_4 7
#define IMPERIAL_7_8 8
#define IMPERIAL_1_0 9

//define imperial tread size selection value 
#define UNF 0
#define UNC 1

//define imperial grade  selection value
#define IMPERIAL_G1 0
#define IMPERIAL_G2 1
#define IMPERIAL_G5 2
#define IMPERIAL_G7 3
#define IMPERIAL_G8 4
#define IMPERIAL_A449 5
#define IMPERIAL_A490 6
#define IMPERIAL_A36 7
#define IMPERIAL_G1045 8
#define IMPERIAL_G4140 9

//define metric grade selection value 
#define METRIC_5_6 0
#define METRIC_5_8 1
#define METRIC_6_8 2
#define METRIC_8_8 3
#define METRIC_9_8 4
#define METRIC_10_9 5
#define METRIC_12_9 6

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

//those unit will contain and manipulate the values set earlier with #define
int WeightUnit;
int LengthUnit;
const char *Unit;
float WeightRatio;
float LengthRatio;
double CalibrationVal;
int ImperialThread;
int ImperialSize;
int ImperialGrade;
int MetricSize;
int MetricGrade;

unsigned long prevbuzzmillis = 0;

unsigned long millisMeasure = 0;
unsigned long millisButton = 0;
unsigned long millisTare = 0;
unsigned long millisCalibration = 500;


boolean PauseAcceuil = false;

boolean Lub;

// those value are just change by the attachInterrupt function. Those value are used by pages to react at the press of a button. See interaction.h
boolean buttonUPstate = false;
boolean buttonDOWNstate = false;
boolean buttonENTERstate = false;
boolean buttonENTER2state = false;

// those value are changed to true to show the menu. True the menu is on screen. False Page are on screen.
boolean MainMenuSelectionState = false;
boolean ModeMenuSelectionState = false;
boolean TorqueMenuSelectionState = false;
boolean ScrewMenuSelectionState = false;
boolean SettingMenuSelectionState = false;
boolean UnitMenuSelectionState = false;
boolean ImperialMenuSelectionState = false;
boolean ScrewGradeMenuSelectionState = false;


// Menu are in part, set here, There is also info in Open_Torque.ino
const char *MainItems[] =
{
    "Back",
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
    "Screw Grade",
    "Screw Lub",
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
    "Imperial",
};

const char *ImperialItems[] =
{
    "Back",
    "UNC thread",
    "UNF thread",
};

const char *ScrewGradeItems[] =
{
    "Back",
    "Metric",
    "Imperial",
};

//double float array, Metric torque with lubricated components (based on Facom data)
//those values are in N/m
//Max 450 N/m
//0 for N/A

float Metric_LUB[ METRIC_ROWS ] [ METRIC_COLUMNS ] = 
{ //5.6   5.8     6.8     8.8     9.8     10.9    12.9
  {1.03,  1.44,   2.09,   2.78,   3.16,   4.09,   4.79}, //M4
  {2.03,  2.85,   4.14,   5.5,    6.27,   8.1,    9.5},  //M5
  {3.53,  4.95,   7.1,    9.5,    10.84,  14,     16.4}, //M6
  {8.5,   11.9,   17.4,   23,     26.34,  34,     40},   //M8
  {16.8,  23,     34,     46,     52,     67,     79},   //M10
  {29,    40,     59,     79,     90,     116,    136},  //M12
  {46,    65,     95,     127,    143,    187,    219},  //M14
  {71,    100,    148,    198,    224,    291,    341},  //M16
  {99,    139,    205,    283,    0,      402,    0},    //M18
  {140,   196,    291,    402,    0,      0,      0},    //M20
  {192,   269,    400,    0,      0,      0,      0},    //M22
  {241,   338,    0,      0,      0,      0,      0},    //M24
  {355,   0,      0,      0,      0,      0,      0}     //M27
};

//double float array, Metric torque with non lubricated components (based on Facom data)
//those values are in N/m
//Max 450 N/m
//0 for N/A

float Metric_NOLUB[ METRIC_ROWS ] [ METRIC_COLUMNS ] =
{ //5.6   5.8     6.8     8.8     9.8     10.9    12.9
  {1.51,  2.11,   2.42,   3.22,   3.66,   4.74,   5.5},   //M4
  {3,     4.2,    4.81,   6.4,    7.27,   9.4,    11},    //M5
  {5.2,   7.2,    8.3,    11.1,   12.57,  16.3,   19.1},  //M6
  {12.6,  17.7,   20,     27,     30.62,  39,     46},    //M8
  {25,    35,     40,     53,     61,     78,     92},    //M10
  {43,    60,     69,     92,     105,    136,    159},   //M12
  {69,    97,     111,    148,    167,    218,    255},   //M14
  {108,   152,    174,    232,    262,    341,    399},   //M16
  {149,   209,    239,    330,    0,      0,      0},     //M18
  {213,   298,    341,    0,      0,      0,      0},     //M20
  {293,   411,    0,      0,      0,      0,      0},     //M22
  {366,   0,      0,      0,      0,      0,      0}      //M24
};

//double float array, Imperial UNC torque with lubricated components
//those value are in lbs.ft

float Imperial_LUB_UNC[ IMPERIAL_UNC_ROWS ] [ IMPERIAL_UNC_COLUMNS ] =
{ //G1  G2    G5    G7    G8    A449  A490  A36   1045    4140
  {3,   4,    7,    9,    10,   6,    10,   3,    3,      5}, // 1/4"
  {6,   9,    14,   18,   20,   12,   20,   6,    7,      9}, // 5/16"
  {10,  16,   25,   31,   35,   22,   35,   10,   12,     17},   // 3/8"
  {16,  25,   40,   50,   57,   35,   57,   16,   20,     27},     // 7/16"
  {24,  38,   61,   76,   86,   54,   86,   24,   30,     41},   // 1/2"
  {35,  55,   88,   110,  125,  78,   125,  35,   43,     59},   // 9/16"
  {48,  75,   122,  152,  172,  107,  172,  48,   60,     81},   // 5/8"
  {85,  134,  216,  270,  306,  190,  306,  85,   106,    143}, // 3/4"
  {136, 136,  348,  0,    0,    307,  0,    136,  170,    231}, // 7/8"
  {204, 204,  0,    0,    0,    0,    0,    204,  256,    0}    // 1"
};

//double float array, Imperial UNC torque with none lubricated components
//those value are in lbs.ft

float Imperial_NOLUB_UNC[ IMPERIAL_UNC_ROWS ] [ IMPERIAL_UNC_COLUMNS ] =
{ //G1  G2    G5    G7    G8    A449  A490  A36   1045    4140
  {4,   6,    9,    11,   13,   8,    13,   4,    4,      6}, // 1/4"
  {7,   12,   19,   24,   27,   17,   27,   7,    9,      12}, // 5/16"
  {13,  21,   33,   42,   47,   29,   47,   13,   16,     22},   // 3/8"
  {21,  33,   53,   67,   76,   47,   76,   21,   26,     35},   // 7/16"
  {32,  51,   82,   102,  115,  72,   115,  32,   40,     54},   // 1/2"
  {46,  73,   118,  147,  166,  104,  166,  46,   58,     78},   // 9/16"
  {64,  101,  162,  203,  230,  143,  230,  64,   79,     108},   // 5/8"
  {113, 179,  288,  0,    0,    254,  0,    113,  141,    191}, // 3/4"
  {182, 182,  0,    0,    0,    0,    0,    182,  227,    308}, // 7/8"
  {273, 0,    0,    0,    0,    0,    273,  341,  308,    0}    // 1"
};

//double float array, Imperial UNF torque with lubricated components
//those value are in lbs.ft

float Imperial_LUB_UNF[ IMPERIAL_UNF_ROWS ] [ IMPERIAL_UNF_COLUMNS ] =
{ //G1  G2    G5    G8    A449  A490  A36 1045    4140
  {3,   5,    8,    11,   7,    11,   3,    4,    5}, // 1/4"
  {6,   10,   16,   22,   14,   22,   6,    8,    10}, // 5/16"
  {11,  18,   28,   40,   25,   40,   11,   14,   19},   // 3/8"
  {18,  28,   45,   63,   39,   63,   18,   22,   30},   // 7/16"
  {27,  43,   69,   97,   61,   97,   27,   34,   46},   // 1/2"
  {39,  61,   98,   139,  87,   139,  39,   48,   65},   // 9/16"
  {54,  85,   138,  195,  121,  195,  54,   67,   91}, // 5/8"
  {94,  149,  241,  341,  212,  341,  94,   118,  160}, // 3/4
  {150, 150,  0,    0,    339,  0,    150,  188,  255}, // 7/8"
  {229, 229,  0,    0,    0,    0,    229,  287,  0}     // 1"
};

//double float array, Imperial UNF torque with none lubricated components
//those value are in lbs.ft

float Imperial_NOLUB_UNF[ IMPERIAL_UNF_ROWS ] [ IMPERIAL_UNF_COLUMNS ] =
{ //G1  G2    G5    G8    A449  A490  A36   1045  4140
  {4,   6,    10,   15,   9,    15,   4,    5,    7}, // 1/4"
  {8,   13,   21,   29,   18,   29,   8,    10,   14}, // 5/16"
  {15,  23,   38,   54,   33,   54,   15,   19,   25},   // 3/8"
  {23,  37,   60,   84,   53,   84,   23,   29,   40},   // 7/16"
  {36,  57,   92,   130,  81,   130,  36,   45,   61},   // 1/2"
  {51,  81,   131,  186,  116,  186,  51,   64,   87},   // 9/16"
  {72,  114,  184,  260,  162,  260,  72,   90,   122}, // 5/8"
  {126, 199,  322,  0,    283,  0,    126,  157,  213},    // 3/4"
  {201, 201,  0,    0,    0,    0,    201,  251,  340},    // 7/8"
  {306, 306,  0,    0,    0,    0,    306,  0,    0}     // 1"
};

#endif

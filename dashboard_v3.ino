#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>
#include "EMUcan.h"
#include <mcp2515.h>
#include <virtuabotixRTC.h>

// set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27,20,4);  

// EMU initialized with base ID 600:
EMUcan emucan(0x600);

// MCP2515 with chip select (CS) pin 10:
MCP2515 mcp2515(10);

// CLK -> 6 , DAT -> 7, Reset -> 8
virtuabotixRTC myRTC(6, 7, 8);

struct can_frame canMsg;

unsigned long previousMillis = 0;
unsigned long currentMillis = 0;
unsigned long average = 0;
unsigned long sampling = 0;

const long interval = 500;

byte displaySelect = 1;
byte numberOfScreen = 4 ;

const byte switchDisplay = 3;
const byte switchInitTime = 4;
const byte switchBrake = 5;
const byte switchClutch = 9;

boolean tableClear[] = {false, false, false, false, false, false, false, false, false, false, false, false, false, false}; //buttonDisplay, clearDisplayTime, clearDisplayPerf1, clearDisplayPerf2, clearDisplayPerf3, buttonInitTime, com1, com2, com3, com4, com5, com6, clutch, brake
boolean testDisplay = true;
struct can_frame canMsg1;
struct can_frame canMsg2;

float pulseWidth = 0;
float conso = 0;


double consoAverage = 0;

int speedVss = 0;
int rpm = 0;

const int injectorSize = 410;

void setup() {
    
  Serial.begin(115200); 
  initEmuCan();
  initDisplay();
  initButton();
  eepromRead();
  //moduleRTC
  //myRTC.setDS1302Time(second(), minute(), hour(), weekday(), day(), month() , year()); //Configuration du temps réel 
  //myRTC.setDS1302Time(0, 29, 9, 3, 29, 11 , 2023); //Configuration du temps réel 
}  

void loop() {
  
  myRTC.updateTime();

  calculConso();
  
  actionButton();
  
  displayToLCD();
  
}

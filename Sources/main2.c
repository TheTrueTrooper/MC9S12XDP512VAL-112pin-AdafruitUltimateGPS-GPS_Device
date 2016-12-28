#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "RYGLeds.h"
#include "Seg7.h"
#include "Switches.h"
#include "AtoD.h"
#include "LED.h" // note type lcd fix later
#include "stdio.h"
#include "math.h"
#include "ComSCI.h"
#include "Clock.h"
#include "GPSData.h"
#include "GPSParse.h"
#include "MessageMaker.h"
#include "GPS.h"
#include "CELL.h"
#include "JsonParse.h"
#include "GPSDirectFind.h"

enum StateValues 
{
   UserInput,
   ActiveSearch
};

byte State = UserInput;
byte TargetStringPostion;
char TargetString[20] = "                   ";
char InsertChar = ' ';

void MoveCharLeft() 
{
  TargetStringPostion--;
  if(TargetStringPostion > 19)
    TargetStringPostion = 19;
  TargetString[TargetStringPostion] = InsertChar;
  lcdClear();
  lcdSetRowCol(1, 0);
  lcdString(TargetString);
}

void MoveCharRight() 
{
  TargetStringPostion++;
  if(TargetStringPostion > 19)
    TargetStringPostion = 0;
  TargetString[TargetStringPostion] = InsertChar;
  lcdClear();
  lcdSetRowCol(1, 0);
  lcdString(TargetString);
}

void SetCharUp() 
{
  InsertChar++;
  if(InsertChar == '[') 
    InsertChar = ' ';
  else if(InsertChar == '!') 
    InsertChar = '0';
  else if(InsertChar == ':') 
    InsertChar = 'A';
    
  TargetString[TargetStringPostion] = InsertChar;
  lcdClear();
  lcdSetRowCol(1, 0);
  lcdString(TargetString);
}

void SetCharDown() 
{
  InsertChar--;
  if(InsertChar == '@') 
    InsertChar = '9';
  else if(InsertChar == '/') 
    InsertChar = ' ';
  else if(InsertChar == (char)31) 
    InsertChar = 'Z';
    
  TargetString[TargetStringPostion] = InsertChar;
  lcdClear();
  lcdSetRowCol(1, 0);
  lcdString(TargetString);
}

void SetState(byte MoveTo) 
{
    State = MoveTo;
    if(State == UserInput) 
    {
       lcdClear();
       lcdSetRowCol(0, 0);
       lcdString("Enter a target loc.");
       lcdSetRowCol(1, 0);
       lcdString(TargetString);
    } 
    else 
    {
       lcdClear();
       lcdSetRowCol(0, 0);
       lcdString("Location:");
       lcdSetRowCol(1, 0);
       lcdString("Target:");
       lcdSetRowCol(2, 0);
       lcdString("Direction:");
    }
}


///* use this to comment out if not using switches
void DoDowns(byte DebounceResult) 
{
// check special combos first in if
// then single standards va switches as else(can drop else if not required)
/*
    if(swTop+ swBottom == DebounceResult)
    {
    }
    else */
    
    if(State == UserInput)  
    switch(DebounceResult) 
    {
      case swCenter:
      SetState(ActiveSearch);
      break;
      case swRight:
      MoveCharRight();
      break;
      case swBottom:
      SetCharDown();
      break;
      case swLeft:
      MoveCharLeft();
      break;
      case swTop:
      SetCharUp();
      break;
    } 
    else if (State == ActiveSearch)
      if(DebounceResult == swCenter)
        SetState(UserInput); 
}

void DoHeld(byte DebounceResult) 
{   
// check special combos first in if
// then single standards va switches as else(can drop else if not required)
    /*if(swTop+ swBottom == DebounceResult)
    {
    }
    else) */
    if(State == UserInput)  
    switch(DebounceResult) 
    {
      case swCenter:
      SetState(ActiveSearch);
      break;
      case swRight:
      MoveCharRight();
      break;
      case swBottom:
      SetCharDown();
      break;
      case swLeft:
      MoveCharLeft();
      break;
      case swTop:
      SetCharUp();
      break;
    } 
}
//
// check special combos first in if
// then single standards va switches as else(can drop else if not required)
void DoUp(byte DebounceResult) 
{
    /*if(swTop+ swBottom == DebounceResult)
    {
    }
    else*/
      switch(DebounceResult) 
    {
      case swCenter:
      RedLedToggle();
      break;
      case swRight:
      break;
      case swBottom:
      break;
      case swLeft:
      break;
      case swTop:
      break; 
    }
    
}





void main(void) {
  /* put your own code here */
	//EnableInterrupts;
	//int out;

	//char* Print;
	//GPSDataType* DataOutr;
	
	//char Data[100] = "$GPGGA,181908.00,3404.7041778,N,07044.3966270,W,4,13,1.00,495.144,M,29.200,M,0.10,0000*40";
	//char Data[100] = "$GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47";
	
	//DataOutr = (GPSDataType*)malloc(sizeof(GPSDataType));
	
  //out = GPSParse (Data, DataOutr);
  
  //(void)sprintf(Print, "the status code of operation %i", out);
  
  //lcdString(Print);
  
  
  //lcdSetRowCol(0, 0);
 

  /*LedRYGInIt();                                         
  lcdInIt();
  RedLedToggle();
  InItSwitch(DoDowns, DoHeld, DoUp);
  ChangeButtonDelays(400, 150);
  */ 
  
  
  char PrintString[20];
  GPSDataType* CurrentData;
  GPSDataType* TargetData;
  GPSDirectionType* Direction;
  (*CurrentData).latitude = 53.4255161; 
  (*CurrentData).longitude =  -113.4173273;
  (*TargetData).latitude = 404.5721807;
  (*TargetData).longitude = -11.4984725;
  

  
  (void)FindDirection(&Direction, &CurrentData, &TargetData);
  
   
   
  lcdInIt();
  GPSInIt();
  InItSwitch(DoDowns, DoHeld, DoUp);
  
  SetState(UserInput);
  

  
  
  
  for(; ;) {
    ButtonCheck();
    Delay(400);
  
    switch(State) 
    {
      case UserInput:
       break;
      case ActiveSearch:
       lcdClear();
       lcdSetRowCol(0, 0);
       lcdString("Location:");
       lcdSetRowCol(1, 0);
       (void)sprintf(PrintString, "Lat: %f",(*CurrentData).latitude);  
       lcdString(PrintString);
       lcdSetRowCol(2, 0);
       (void)sprintf(PrintString, "Lon: %f",(*CurrentData).longitude); 
       lcdString(PrintString);
       ButtonCheck();
       Delay(400);
       ButtonCheck();
       Delay(4000);
       lcdClear();
       lcdSetRowCol(0, 0);
       lcdString("Target:");
       lcdSetRowCol(1, 0);
       (void)sprintf(PrintString, "Lat: %f",(*TargetData).latitude);  
       lcdString(PrintString);
       lcdSetRowCol(2, 0);
       (void)sprintf(PrintString, "Lon: %f",(*TargetData).longitude);  
       lcdString(PrintString);
       ButtonCheck();
       Delay(400);
       ButtonCheck();
       Delay(4000);
       lcdClear();
       lcdSetRowCol(0, 0);
       lcdString("Direction:");
       lcdSetRowCol(1, 0);
       (void)sprintf(PrintString, "Dis: %d Km",19.4);  
       lcdString(PrintString);
       lcdSetRowCol(2, 0);
       (void)sprintf(PrintString, "Bar: %d",170);  
       lcdString(PrintString);
       Delay(4000);
       lcdClear();
       break;
    }
   
   

  //SendString("Print this");
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
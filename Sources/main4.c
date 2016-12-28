#include <hidef.h>      /* common defines and macros */
#include "AtoD.h"
#include "LED.h" // note type lcd fix later
#include "stdio.h"
#include "math.h"
#include "GPSData.h"
#include "GPSParse.h"
#include "MessageMaker.h"
#include "GPS.h"
#include "CELL.h"
#include "JsonParse.h"
#include "GPSDirectFind.h"
#include "Switches.h"

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
  lcdSetRowCol(1, 0);
  lcdString(TargetString);
}

void MoveCharRight() 
{
  TargetStringPostion++;
  if(TargetStringPostion > 19)
    TargetStringPostion = 0;
  TargetString[TargetStringPostion] = InsertChar;
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
       lcdString("Getting Location");
       Delay(20);
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
  
  GPSDataType DataOut;
  GPSDataType CurrentLoc;
  GPSDataType TargetData;
  GPSDirectionType Direction;
  

  char string[100];
  char *Temp = NULL;
  byte size;
  byte i;
  byte BoolSuccess = 0;
  
  TargetData.latitude = 5356.78708;
  TargetData.longitude = -11350.50682;
  
  lcdInIt();  
  GPSInIt();
  InItSwitch(DoDowns, DoHeld, DoUp);
  /*
  do
  {
    
    size = 100;
    GPSGetSentence(string, &size);
    i = 0;
    do
    {
        free(Temp);
        lcdClear();
        lcdSetRowCol(0, 0);
        lcdString("Searching");
        Temp = FindGPSString(string, &i);
        lcdSetRowCol(1, 0);
        lcdString(Temp);
        //BoolSuccess = ParseGPGGA(Temp, &DataOut);
    }while(BoolSuccess == 0 && Temp[1] != '\0');
    lcdSetRowCol(2, 0);
    (void)sprintf(string, "Lat: %+f", DataOut.latitude);
    lcdString(string);
    lcdSetRowCol(3, 0);
    (void)sprintf(string, "Lon: %+f", DataOut.longitude);
    lcdString(string);
    Delay(300);
  }while((DataOut.latitude == 0.0f) && (DataOut.longitude == 0.0f));
  CurrentLoc.latitude = DataOut.latitude;
  CurrentLoc.longitude = DataOut.longitude;
  */

  for(; ;) {
    do
  {
    
    do
    {
        Delay(1010);
        size = 100;
        GPSGetSentence(string, &size);
        i = 0;
        free(Temp);
        lcdClear();
        lcdSetRowCol(0, 0);
        lcdString("Searching");
        Temp = FindGPSString(string, &i);
        if(Temp!= NULL)
        {
        lcdSetRowCol(1, 0);
        lcdString(Temp);
        ParseGPGGA(Temp, &DataOut);
        }
    }while(BoolSuccess == 0 && Temp[1] != '\0');
    lcdSetRowCol(2, 0);
    (void)sprintf(string, "Lat: %+f", DataOut.latitude);
    lcdString(string);
    lcdSetRowCol(3, 0);
    (void)sprintf(string, "Lon: %+f", DataOut.longitude);
    lcdString(string);
    Delay(300);
  }while((DataOut.latitude != 0.0f) && (DataOut.longitude != 0.0f));
  CurrentLoc.latitude = DataOut.latitude;
  CurrentLoc.longitude = DataOut.longitude;
    FindDirection(&Direction, &CurrentLoc, &TargetData);

  
    switch(State) 
    {
      case UserInput:
         ButtonCheck();
       break;
      case ActiveSearch:
       lcdClear();
       lcdSetRowCol(0, 0);
       lcdString("Location:");
       lcdSetRowCol(1, 0);
       (void)sprintf(string, "Lat: %+f", CurrentLoc.latitude);  
       lcdString(string);
       lcdSetRowCol(2, 0);
       (void)sprintf(string, "Lon: %+f", CurrentLoc.longitude); 
       lcdString(string);
       for(i=0; i < 10; i++)
       {
         ButtonCheck();
         Delay(400);
       }
       
       lcdClear();
       lcdSetRowCol(0, 0);
       lcdString("Target:");
       lcdSetRowCol(1, 0);
       (void)sprintf(string, "Lat: %+f",TargetData.latitude);  
       lcdString(string);
       lcdSetRowCol(2, 0);
       (void)sprintf(string, "Lon: %+f",TargetData.longitude);  
       lcdString(string);
       for(i=0; i < 10; i++)
       {
         ButtonCheck();
         Delay(400);
       }
       
       lcdClear();
       lcdSetRowCol(0, 0);
       lcdString("Direction:");
       lcdSetRowCol(1, 0);
       (void)sprintf(string, "Dis: %d Km",Direction.Distance);  
       lcdString(string);
       lcdSetRowCol(2, 0);
       (void)sprintf(string, "Bar: %d",Direction.Barring);  
       lcdString(string);
       for(i=0; i < 10; i++)
       {
         ButtonCheck();
         Delay(400);
       }
       break;
    }

  //SendString("Print this");
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
}
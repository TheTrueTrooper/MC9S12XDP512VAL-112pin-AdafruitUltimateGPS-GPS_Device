/*
  Author: Angelo Sanches
  Board:  mc9s12xdp512(nait)
  Perpous: SCI
  Created: 11/3/16 
                                 '
  -------------UseLog-------------
  ->last is template
  Modified:<version:Date>
  Reason:
  ----------Change Log------------
  ->last is template
  Log:<Reason/Modified> Optional log Optional log in case of compliations
*/
#include <hidef.h>
#include <stdlib.h>
#include "mc9s12xdp512.h"
#include "GPSParse.h"
#include "GPSData.h"
#include "MessageMaker.h"
#include "DirtyDelays.h"
#include "LED.h"

// A function to ready all ports for use with the GPS and configure GPS
void GPSInIt(void);
//Gets a Full GPS GPPA (lat & long GPS Protocol) sentence from the the serial port
void GPSGetSentence(char* SringOut, byte* outSize);
//Enables GPS by powering on at enable pin.
void GPSEnable(); 
//Disables GPS by Powering off at enable pin
void GPSDisable();
//Sends a Command to GPS
void GPSSendCommand(char* String);

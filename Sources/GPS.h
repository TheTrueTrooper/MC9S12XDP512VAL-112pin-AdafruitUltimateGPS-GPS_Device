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

void GPSInIt(void);

void GPSGetSentence(char* SringOut, byte* outSize);

void GPSEnable(); 

void GPSDisable();

void GPSSendCommand(char* String);
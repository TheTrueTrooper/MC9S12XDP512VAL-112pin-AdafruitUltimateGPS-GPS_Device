#include <hidef.h>     
#include "mc9s12xdp512.h"
#include <stdio.h>
#include <stdlib.h>
#include "GPSData.h"

char* FindGPSString(char* Data, byte* OutStart); 

char* ReadSection(char* Data, byte* OutStart, char Spliter);

//Pares out data from string
//-1 is for Unknown Data type or not accounted for on perpous          tryur
//-2 is for bad check sum or bad data
int GPSParse(char* Data, GPSDataType* DataOutr);

int ParseGPGGA(char* data, GPSDataType* DataOut); 

                         
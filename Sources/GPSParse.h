#include <hidef.h>     
#include "mc9s12xdp512.h"
#include <stdio.h>
#include <stdlib.h>
#include "GPSData.h"
//Will find the where the GPS string actually starts
char* FindGPSString(char* Data, byte* OutStart); 
//Will read a section of a char seperated stiring and will return a new sub sting of it starting at the OutStart
char* ReadSection(char* Data, byte* OutStart, char Spliter);

//Pares will fully parse out data from string will be able to parse all GPS data types however it only supports GPGGA data for now
//-1 is for Unknown Data type or not accounted (Only GPPA at this time)
//-2 is for bad check sum or bad data
// else if positive will return data type
int GPSParse(char* Data, GPSDataType* DataOutr);

//Will Fully parse a GPGGA string
int ParseGPGGA(char* data, GPSDataType* DataOut); 

                         

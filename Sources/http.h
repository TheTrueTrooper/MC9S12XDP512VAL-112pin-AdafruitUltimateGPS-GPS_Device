#include <hidef.h>     
#include "mc9s12xdp512.h"
#include <stdio.h>
#include <stdlib.h>
#include "GPSParse.h"
#include <string.h>



char* ReadSectionLong(char* Data, int* OutStart, char Spliter);

void FindURL(char* Data, char* OutURL);

void ParseJson(char *jsonData, GPSDataType* DataOutr); 
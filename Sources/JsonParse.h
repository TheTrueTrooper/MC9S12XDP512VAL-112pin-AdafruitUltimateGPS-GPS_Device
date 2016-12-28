#include <hidef.h>     
#include "mc9s12xdp512.h"
#include <stdio.h>
#include <stdlib.h>
#include "GPSData.h"


char * TrimSpace(char * Data);

void ReplaceChar(char * Data, char Find, char replace);

char* JReadSection(char* Data, unsigned int* OutStart, char Spliter);

void JasonParseGPGGA(char* Data, GPSDataType* DataOut);
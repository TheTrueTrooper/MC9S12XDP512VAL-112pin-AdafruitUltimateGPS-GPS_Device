#include <hidef.h>   
#include "mc9s12xdp512.h"
#include "enum.h"
#include <stdio.h>


//#pragma align on  //for xgate aligning

//#pragma options align=2 

struct GPSData;

#ifndef __GPSData
#define __GPSData
typedef struct GPSData {
  
   byte type;
   
   float TimeStamp;
   /// use sign for N/S  ect
   float latitude;
   /// use sign for N/S ect
   float longitude;
   
   byte Quality;
   byte NSatellite;
   ///all will be in M if in feet convert plz
   float HDP;
   float  Alt;
   ///all will be in M if in feet convert plz
   float GeoidalS;
   
   float ADGD;
   ///if given?
   int StationID;
   
} GPSDataType;

#endif

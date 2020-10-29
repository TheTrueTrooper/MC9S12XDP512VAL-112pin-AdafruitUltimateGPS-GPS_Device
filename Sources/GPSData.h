#include <hidef.h>   
#include "mc9s12xdp512.h"
#include "enum.h"
#include <stdio.h>
#include <math.h>


//#pragma align on  //for xgate aligning

//#pragma options align=2 
//There is a little extra compiler specific platform work to do with defining to step on mulitple refing
//let compiler know about types
struct GPSData;
struct GPSDirection;

//if type has not been defined 
#ifndef __GPSData
#define __GPSData
//Deserialized data from the GPS GPPA strings
typedef struct GPSData {
   // The DATA TYPE GPPA = 0
   byte type;
   // The time stamp
   float TimeStamp;
   /// use sign for N/S  ect
   // The current location as per the latitude
   float latitude;
   /// use sign for N/S ect
   // The current location as per the longitude
   float longitude;
   //The quality of the data recived (does it look trustable) -> GPS Quality indicator (0=no fix, 1=GPS fix, 2=Dif. GPS fix) (is there a ground fix to double ref against)
   byte Quality;
   //The number of satalites involved in the location fix (Should always be for as that is min for a Alt fix)
   byte NSatellite;
   //horizontal dilution of precision used to check accracy Should be accurate enough to ignore
   float HDP;
   //Antenna altitude above mean-sea-level (Auto converted to meters)
   float  Alt;
   //Geoidal separation (Auto converted to meters)
   float GeoidalS;
   //Age of Differential GPS data (seconds) 
   float ADGD;
   ///if given?
   // the ID of the ground station used int the fix.
   int StationID;
   
} GPSDataType;
// ref http://aprs.gids.nl/nmea/
#endif


#ifndef __GPSDirection
#define __GPSDirection
//The Calcuation for one point to another
typedef struct GPSDirection {
  //The distance in meters
   float Distance;
   // the Barring in degrees
   float Barring;
   
} GPSDirectionType;

#endif

#include <hidef.h>           
#include "mc9s12xdp512.h"

enum GPSDataType;
enum SatQuality;

#ifndef __GPSDataType
#define __GPSDataType
enum GPSDataType{
  DataTypeNone,
  GPGGA,
}; 
#endif

#ifndef __SatQuality
#define __SatQuality
enum SatQuality{
   Unknown,
   Uncorrelated,
   DifferentiallyCorrected,
   RTKFix,
   RTKFloat
};  
#endif
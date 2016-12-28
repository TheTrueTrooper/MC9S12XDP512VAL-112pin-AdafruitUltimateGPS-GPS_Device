#include "GPSDirectFind.h"

#define M_PI acos(-1.0)


//Distance Barring
void FindDirection(GPSDirectionType *Out, GPSDataType* Start, GPSDataType* End)
{
     float Lat1;
     float Lat2;
     float DLat;
     float DLon;
     float a;
     float b;
     Lat1 = (*Start).latitude /100 * M_PI /180;
     Lat2 = (*End).latitude /100 * M_PI /180;
     DLat = ((*End).latitude /100 - (*Start).latitude /100) * M_PI /180;
     DLon = ((*End).longitude /100 - (*Start).longitude /100) * M_PI /180;
     
     a = sin(DLat / 2) * sin(DLat) + cos(Lat1) * cos(Lat2) * sin(DLon /2) * sin(DLon /2);
     b = 2* atan2(sqrt(a), sqrt(1-a));
     
     (*Out).Distance = 6371e3 * b;
     
     a = atan2(cos(Lat1) * sin(Lat2) - sin(Lat1) * cos(Lat2) * cos(DLon), sin(DLon) * cos(Lat2)) * 180 / M_PI;
     
     (*Out).Barring = fmod(((int)a + 180 ), 360);
     
}


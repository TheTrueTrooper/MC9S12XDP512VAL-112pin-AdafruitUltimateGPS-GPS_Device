#include <hidef.h>
#include <stdlib.h>
#include "mc9s12xdp512.h"
#include "SCI.h"
#include "GPSParse.h"
#include "GPSData.h"
#include "MessageMaker.h"
#include "DirtyDelays.h"


void CELLInIt(void);

void CELLSendCommand(char* String);

void CELLToggleOnOff();        

void CELLGetHTTP(char* URL, int URLsize, char** Params, int* ParamSize, char** Value, int* ValueSize, char* Response, int ResponseSize, byte ParamsNum);
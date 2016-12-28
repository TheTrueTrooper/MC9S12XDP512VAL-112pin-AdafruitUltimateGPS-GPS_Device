/*
  Author: Angelo Sanches
  Board:  mc9s12xdp512(nait)
  Perpous: Inerupt Clock Header
  Created: 3/11/16 
  
  -------------UseLog-------------
  ->last is template
  Modified:<version:Date>
  Reason:
  ----------Change Log------------
  ->last is template
  Log:<Reason/Modified> Optional log Optional log in case of compliations
*/

#include <hidef.h>
#include "mc9s12xdp512.h"

void CLockInIt(byte preScaler);

void SetInOutVtimer0(byte* inValueInOut);

void Vtimer0InIt(double TargetTime, void(*FunctionIn)(byte* ValueInOuts));

interrupt VectorNumber_Vtimch0 void TimerInterval(void);
/*
  Author: Angelo Sanches
  Board:  mc9s12xdp512(nait)
  Perpous: DirtyDelays C (asm)
  Created: 3/11/16 
  
  -------------UseLog-------------
  ->last is template
  Modified:<version:Date>
  Reason:
  ----------Change Log------------
  ->last is template
  Log:<Reason/Modified> Optional log Optional log in case of compliations
*/
#include "DirtyDelays.h"

// an asm delay
void Delay(word mSec)
{
   asm ldx mSec
   
   asm SafeDelayLoop: 
   asm ldy #2665
   asm SafedelayIn:    
   asm dbne y, SafedelayIn
   asm dbne x, SafeDelayLoop
}

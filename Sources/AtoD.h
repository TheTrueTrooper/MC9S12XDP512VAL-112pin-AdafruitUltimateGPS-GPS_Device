/*
  Author: Angelo Sanches
  Board:  mc9s12xdp512(nait)
  Perpous: AtoD Header
  Created: 3/31/16  
  
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
#include "DirtyDelays.h"

//Opens Anolog to Digital Port 0 
void ATD0InIt(void);

//Samples from open Anolog to Digital Port 0 
unsigned int ATD0_Sample(void);

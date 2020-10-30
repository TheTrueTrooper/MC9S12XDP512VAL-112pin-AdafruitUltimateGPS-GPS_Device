/*
  Author: Angelo Sanches
  Board:  mc9s12xdp512(nait)
  Perpous: AtoD C
  Created: 3/31/16 
  
  -------------UseLog-------------
  ->last is template
  Modified:<version:Date>
  Reason:
  ----------Change Log------------
  ->last is template
  Log:<Reason/Modified> Optional log Optional log in case of compliations
*/


#include "AtoD.h"

//opens Anolog to Digital Port 0 for use
void ATD0InIt(void)
{
  //set up turn it on
  ATD0CTL2 = 0xE0;  // turn it on still needs 50us
  //set it for single read polls
  ATD0CTL3 = 0x0A;  //set up for single sample
  //Set it for 4 sample average
  ATD0CTL4 = 0x26;  //set for four cycle sampletimes
  //wait to use
  Delay(1000);
}

//samples from open Anolog to Digital Port 0 
unsigned int ATD0_Sample(void)
{  
   //tell it to sample
   ATD0CTL5 = 0x80;
   //Check for value and hold untill a successfull poll
   while ((ATD0STAT0 & 0x80)==0);
   //return that value
   return ATD0DR0;
}

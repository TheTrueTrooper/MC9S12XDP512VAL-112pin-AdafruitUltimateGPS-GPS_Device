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

void ATD0InIt(void)
{
  ATD0CTL2 = 0xE0;  // turn it on still needs 50us
  
  ATD0CTL3 = 0x0A;  //set up for single sample
  ATD0CTL4 = 0x26;  //set for four cycle sampletimes
  
  Delay(1000);
}

unsigned int ATD0_Sample(void)
{                             
   ATD0CTL5 = 0x80;
   
   while ((ATD0STAT0 & 0x80)==0);
   
   return ATD0DR0;
}
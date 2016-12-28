/*
  Author: Angelo Sanches
  Board:  mc9s12xdp512(nait)
  Perpous: RYGLeds C
  Created: 3/11/16 
  
  -------------UseLog-------------
  ->last is template
  Modified:<version:Date>
  Reason:
  ----------Change Log------------
  ->last is template
  Log:<Reason/Modified> Optional log Optional log in case of compliations
*/
#include "RYGLeds.h"


// sets the ports needed to proper outs and enables
void LedRYGInIt()
{
  PT1AD1 &= 0x1F; // clear the bits
  DDR1AD1 |= 0xE0;//sets the first 3 to outs
}

void RedLedOn(void)
{
  PT1AD1 |= 0x80;
}

void RedLedOff(void)
{
  PT1AD1 &= 0x7F;
}

void RedLedToggle(void)
{
  PT1AD1 ^= 0x80;
}

void YelLedOn(void)
{
  PT1AD1 |= 0x40;
}

void YelLedOff(void)
{
  PT1AD1 &= 0xBF;
}

void YelLedToggle(void)
{
  PT1AD1 ^= 0x40;
}

void GreLedOn(void)
{
  PT1AD1 |= 0x20;
}

void GreLedOff(void)
{
  PT1AD1 &= 0xDF;
}

void GreLedToggle(void)
{
  PT1AD1 ^= 0x20;
}
/*
  Author: Angelo Sanches
  Board:  mc9s12xdp512(nait)
  Perpous: Inerupt Clock C
  Created: 3/11/16 
  
  -------------UseLog-------------
  ->last is template
  Modified:<version:Date>
  Reason:
  ----------Change Log------------
  ->last is template
  Log:<Reason/Modified> Optional log Optional log in case of compliations
*/

#include "Clock.h"

// for clock
byte PreScaler;
// for Intrupt
void(*Vtimer0Fun)(byte* ValueInOuts);
word Vtimer0SmallTick;
word Vtimer0BigTick;
word Vtimer0BigTickCount;
byte* ValueInOut;

void CLockInIt(byte preScaler)
{
  TSCR1 = 0x80;
  if ( 1 <=preScaler)
  {
    TSCR2 = 0;
    PreScaler=1;
  }
  else if ( 2 <=preScaler)
  {
    TSCR2 = 1;
    PreScaler=2;
  }
  else if ( 4 <=preScaler)
  {
    TSCR2 = 2;
    PreScaler=4;
  }
  else if ( 8 <=preScaler)
  {
    TSCR2 = 3;
    PreScaler=8;
  }
  else if ( 16 <=preScaler)
  {
    TSCR2 = 4;
    PreScaler=16;
  }
  else if ( 32 <=preScaler)
  {
    TSCR2 = 5;
    PreScaler=32;
  }
  else if ( 64 <=preScaler)
  {
    TSCR2 = 6;
    PreScaler=64;
  }
  else
  {
    TSCR2 = 7;
    PreScaler=128;
  }
  TIOS = 0; // set to output compares to non on will be set in channels in
  TCTL2 =0; // set channels toggle styles to deffualt will se in its init
  TIE = 0; // set no channel interup will turn on as needed
  TFLG1 = 0xFF; // clear all flags with the od mex

}

void SetInOutVtimer0(byte* inValueInOut)
{
  ValueInOut = inValueInOut;
}


void Vtimer0InIt(double TargetTime, void(*FunctionIn)(byte* ValueInOuts))
{
   long int RawTicks;
   long double Getit;
   Vtimer0Fun = FunctionIn;
   
   Getit = 8000000 / PreScaler * TargetTime ;
   RawTicks = (long int)Getit;
   Vtimer0SmallTick = (word)(RawTicks % 0xFFFF);
   Vtimer0BigTick = (word)(RawTicks / 0xFFFF);
   Vtimer0BigTickCount =0;
   
   TIOS |= 0x01; // set to output compares to non on will be set in channels in
   TCTL2 |=0x01; // set channels toggle styles to deffualt will se in its init
   TIE = 0;
   TC0 = TCNT + Vtimer0SmallTick;
}

interrupt VectorNumber_Vtimch0 void TimerInterval(void)
{
 TFLG1 = 0x01;
 Vtimer0BigTickCount++;
 if (Vtimer0BigTickCount >= Vtimer0BigTick+1)
 {
 TC0 += Vtimer0SmallTick;
 Vtimer0BigTickCount = 0;
 (*Vtimer0Fun)(ValueInOut);
 }

}


















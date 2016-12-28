/*
  Author: Angelo Sanches
  Board:  mc9s12xdp512(nait)
  Perpous: Switches C
  Created: 3/11/16 
  
  -------------UseLog-------------
  Modified: Created new pointer vs 
  this allows for main to hold the 
  real workers ** note old vs 
  commented out
  Reason: 03/31/2016
  Modified:
  Reason: mm/dd/yyyy
*/

#include "Switches.h"

word AngButtonTickDelay;
word AngButtonTickTimer;

// this vers will allow for funtions to hide in main
void (*PointerDoDowns)(byte Debounce);
void (*PointerDoHeld)(byte Debounce);
void (*PointerDoUp)(byte Debounce);

void InItSwitch(void(*inPointerDoDowns)(byte Debounce), void(*inPointerDoHeld)(byte Debounce), void(*inPointerDoUp)(byte Debounce)) 
{
     PT1AD1 &= 0xE0;
     DDR1AD1 &= 0xE0; // set outs
     ATD1DIEN1 |= 0x1F;
     AngButtonTickDelay = 300;
     AngButtonTickTimer = 200;
     PointerDoDowns = inPointerDoDowns;
     PointerDoHeld = inPointerDoHeld;
     PointerDoUp = inPointerDoUp;
}

void ChangeButtonDelays(word nButtonTickDelay,word nButtonTickTimer)
{
     AngButtonTickDelay =  nButtonTickDelay;
     AngButtonTickTimer =  nButtonTickTimer;
}


// the switch checker
void ButtonCheck(void) 
{
     byte Debounce;  
     if ((PT1AD1 & 0x1F) > 0) 
     {
      
        Debounce = PT1AD1 & 0x1F;

         if ((PT1AD1 & 0x1F) == Debounce)
         {
             Delay(AngButtonTickDelay);
             (*PointerDoDowns)(Debounce);
             Delay(AngButtonTickTimer);
             while(Debounce == (PT1AD1 & 0x1F))
             {
                (*PointerDoHeld)(Debounce);
                Delay(AngButtonTickTimer); 
             }
             (*PointerDoUp)(Debounce);
         }
     } 
}





/*  old safe vers
void InItSwitch(void(*inPointerDoDowns)(byte Debounce), void(*inPointerDoHeld)(byte Debounce), void(*inPointerDoUp)(byte Debounce)) 
{
     PT1AD1 &= 0xE0;
     DDR1AD1 &= 0xE0; // set outs
     ATD1DIEN1 |= 0x1F;
     AngButtonTickDelay = 200;
     AngButtonTickTimer = 300;
}


void ChangeButtonDelay(byte nButtonTickDelay,byte nButtonTickTimer)
{
     AngButtonTickDelay =  nButtonTickDelay;
     AngButtonTickTimer =  nButtonTickTimer;
}

void ButtonCheck(void) 
{
     byte Debounce;  
     if ((PT1AD1 & 0x1F) > 0) 
     {
      
        Debounce = PT1AD1 & 0x1F;

         if ((PT1AD1 & 0x1F) == Debounce)
         {
             Delay(AngButtonTickDelay);
             DoDowns(Debounce);
             Delay(AngButtonTickTimer);
             while(Debounce == (PT1AD1 & 0x1F))
             {
                DoHeld(Debounce);
                Delay(AngButtonTickTimer); 
             }
             DoUp(Debounce);
         }
     } 
}


void DoDowns(byte DebounceResult) 
{
    switch(DebounceResult) 
    {
      case Center:
      break;
      case Right:
      break;
      case Bottom:
      break;
      case Left:
      break;
      case Top:
      break;
    }
}

void DoHeld(byte HeldResults) 
{                                           
     switch(HeldResults) 
    {
      case Center:
      break;
      case Right:
      break;
      case Bottom:
      break;
      case Left:
      break;
      case Top:
      break;
    }  
}


void DoUp(byte UpResults) 
{
      switch(UpResults) 
    {
      case Center:
      break;
      case Right:
      break;
      case Bottom:
      break;
      case Left:
      break;
      case Top:
      break; 
    }
}

*/
 





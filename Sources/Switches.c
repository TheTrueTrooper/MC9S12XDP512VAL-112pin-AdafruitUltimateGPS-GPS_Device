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

//The time on a debounce
word AngButtonTickDelay;
//the Time on another hold command.
word AngButtonTickTimer;

// this vers will allow for funtions to hide in main
//A pointer function for if a button is pressed down with its down time showen
void (*PointerDoDowns)(byte ButtonState);
//A pointer function for if a button is held down with its down time showen
void (*PointerDoHeld)(byte ButtonState);
//A pointer function for if a button is let rise from the down postion with its down time showen
void (*PointerDoUp)(byte ButtonState);

//Creates a set of switches on the pins connected to buttons and attaches some pointer functions to them
//inPointerDoDowns - Is a function to connect to the down of a button.
//inPointerDoHeld - Is a function to connect to the holding down of a button.
//inPointerDoUp - Is a function to connect to the down of a button.
void InItSwitch(void(*inPointerDoDowns)(byte ButtonState), void(*inPointerDoHeld)(byte ButtonState), void(*inPointerDoUp)(byte ButtonState)) 
{
     // set the GPIOs for the buttons to be off
     PT1AD1 &= 0xE0;
     // set the GPIOs for the buttons to be ins open
     DDR1AD1 &= 0xE0; // set outs
     // set the GPIOs for the buttons on
     ATD1DIEN1 |= 0x1F;
      //sett a button to delay a tick on a debounce to this many seconds
     AngButtonTickDelay = 300;
     // set other following ticks on a held down to the following
     AngButtonTickTimer = 200;
     //Bind the buttons
     PointerDoDowns = inPointerDoDowns;
     PointerDoHeld = inPointerDoHeld;
     PointerDoUp = inPointerDoUp;
}

//Changes a delays on buttons
void ChangeButtonDelays(word nButtonTickDelay,word nButtonTickTimer)
{
     AngButtonTickDelay =  nButtonTickDelay;
     AngButtonTickTimer =  nButtonTickTimer;
}


// polls button states for changes and calls pointer functions for changes
void ButtonCheck(void) 
{
     //The current debounce time
     byte Debounce;  
     //If a button has been pressed then
     if ((PT1AD1 & 0x1F) > 0) 
     {
        //Check for debounce with getting state
        DebounceButtonState = PT1AD1 & 0x1F;
        //wait for debounce time and then check to make sure it was debounced
        Delay(AngButtonTickDelay);
         if ((PT1AD1 & 0x1F) == DebounceButtonState)
         {
             //If successed do button down event as a pointer function call
             (*PointerDoDowns)(DebounceButtonState);
             //Wait for hold timer then begin hold check
             Delay(AngButtonTickTimer);
             while(DebounceButtonState == (PT1AD1 & 0x1F))
             {
                //do Event Button for held down if held down and repeate
                (*PointerDoHeld)(DebounceButtonState);
                Delay(AngButtonTickTimer); 
             }
            //on up do up event at end
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
 





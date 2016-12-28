/*
  Author: Angelo Sanches
  Perpous: Switches Header
  Created: 3/11/16 
  
    -------------UseLog-------------
  Modified: Created new pointer vs 
  this allows for main to hold the 
  real workers
  Reason: 03/31/2016
  Modified:
  Reason: mm/dd/yyyy
*/

#include <hidef.h>
#include "mc9s12xdp512.h"
#include "DirtyDelays.h"



// Button Enums add as needed for combos
enum DownCombos{
    swCenter = 1,
    swRight = 2,
    swBottom = 4,
    swLeft = 8,
    swTop = 16
};


//Sets up the swithches for use
//void InItSwitch(void);
void InItSwitch(void(*inPointerDoDowns)(byte Debounce), void(*inPointerDoHeld)(byte Debounce), void(*inPointerDoUp)(byte Debounce));

//Checks the buttons once
void ButtonCheck(void);

void ChangeButtonDelays(word nButtonTickDelay,word nButtonTickTimer);

//void DoDowns(byte DebounceResult);

//void DoHeld(byte HeldResults);

//void DoUp(byte UpResults);





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
  //For the center switch 
  // -
  //-.-
  // -
    swCenter = 1,
  //For the center switch 
  // -
  //--.
  // -
    swRight = 2,
  //For the center switch 
  // -
  //---
  // .
    swBottom = 4,
  //For the center switch 
  // -
  //.--
  // -
    swLeft = 8,
  //For the center switch 
  // .
  //---
  // -
    swTop = 16
};


//Creates a set of switches on the pins connected to buttons and attaches some pointer functions to them
//inPointerDoDowns - Is a function to connect to the down of a button.
//inPointerDoHeld - Is a function to connect to the holding down of a button.
//inPointerDoUp - Is a function to connect to the down of a button.
void InItSwitch(void(*inPointerDoDowns)(byte ButtonState), void(*inPointerDoHeld)(byte ButtonState), void(*inPointerDoUp)(byte ButtonState));


// polls button states for changes and calls pointer functions for changes
void ButtonCheck(void);

// changes debounce delay and Hold down delay
//nButtonTickDelay - is the delay on debounce
//nButtonTickTimer - is the delay between hold down calls (Note debounce delay happens befor first) and button up calls
void ChangeButtonDelays(word nButtonTickDelay,word nButtonTickTimer);

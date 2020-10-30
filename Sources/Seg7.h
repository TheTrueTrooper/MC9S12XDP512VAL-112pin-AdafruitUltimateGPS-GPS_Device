/*
  Author: Angelo Sanches
  Board:  mc9s12xdp512(nait)
  Perpous: Seg7 Header
  Created: 3/11/16 
  
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

//the initializer
void Seg7InIt(void);


//the Clears a position 
//takes a positional byte how ever only 0-7 ar valid other bits will be tuncated
// also clears sll positions for a clean set
void Seg7Clear(byte position);


//Sets a number out to location
//takes a positional byte how ever only 0-7 ar valid other bits will be tuncated
//takes a value to put out from 0 - F again truncates
//takes a bool to put a decimal or not
void Char7Seg(byte position, byte Value, byte decimal);

//Sets a byte out to last 2 locations on top or bottom
//takes byte value
//takes bool true: bottom false: Bottom
void Byte7Seg(byte Value, byte BottomVsTop);

//Sets a word on top or bottom
//takes byte value
//takes bool true: bottom false: Bottom
void Word7Seg(word Value, byte BottomVsTop);


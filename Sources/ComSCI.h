/*
  Author: Angelo Sanches
  Board:  mc9s12xdp512(nait)
  Perpous: SCI (Com) Header
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
#include "DirtyDelays.h"


void SCI0_InIt(void);

byte SCI0_Key_Hit(void);

// Waits to Read a byte out of the the out if
// fail time outs are output in byte return 
byte WaitReadByte(byte* Out);
// makes a quick pass(single Pass) at the byte
byte ReadByte(void);
// Waits to Send a byte out of the the out if
// fail time outs are output in byte return 
byte WaitSendByte(byte SendOut);
// makes a quick attempt(single Pass) at sending the byte fails refect in return
byte SendByte(byte SendOut);
// outs a string with the size of string on the out after you give it an array as a buffer
byte ReadString(char* String, byte* OutSize);
// outs a string without the size of string on the out after you give it an array as a buffer use for sending more compl
byte ReadBytes(byte* Out, byte Size);
// sends a string with the size of string on the out after you give it an array as a buffer
byte SendString(char* String);
// sends a string with the size of string on the out after you give it an array as a buffer
byte SendBytes(byte* String, byte Number);

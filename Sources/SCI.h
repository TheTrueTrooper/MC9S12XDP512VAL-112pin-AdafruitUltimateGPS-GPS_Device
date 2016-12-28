/*
  Author: Angelo Sanches
  Board:  mc9s12xdp512(nait)
  Perpous: SCI H
  Created: 11/3/16 
  
  -------------UseLog-------------
  ->last is template
  Modified:<version:Date>
  Reason:
  ----------Change Log------------
  ->last is template
  Log:<Reason/Modified> Optional log Optional log in case of compliations
*/

#include <hidef.h>
#include <stdlib.h>
#include "mc9s12xdp512.h"

//byte[] (*SIC0PointerFCallBack)(byte[] Buffer, byte *Pos);
/*  Example and Rules for the call back
--Aways free if data is being wiped 
--Aways resset Pos = 0 if data is being wiped 
--Aways (byte*)malloc(size) if Pos data is being wiped 
--the order is important 
--if No Wipe aways just return Buffer
--Data Must be copied out to a new buff and wiped for use if message is complete
    byte[] SIC0PointerFCallBack(byte[] Buffer, byte *Pos, int size)
    {
     if (//some check to see we have a Full Message)
     {
     // do stuff with the Buffer
      ?  ex
      ?  int ExampleIndexer = 0;
      ?  while(string != \0)
      ?  {
      ?     free(ExampleGlobleArrayWhereCreated)
      ?     ExampleGlobleArrayWhereCreated =  (byte*)malloc(size)
      ?     ExampleGlobleArrayWhereCreated[ExampleIndexer] = Buffer[ExampleIndexer]
      ?  }
     free(Buffer)//let Go of old buffer
     *Pos = 0; //reset buffer
     return =  (byte*)malloc(size)
     }
     return = Buffer;
    }
    usefull notes 
    -int n = sizeof(a) / sizeof(int); //n will be arrays size
    -int n = sizeof(a); //number of bytes in array
*/
//byte[] (*SIC1PointerFCallBack)(byte[] Buffer, byte *Pos);
/*
   -- same as above
*/

void SIC0InIt9600(void); 

void SIC1InIt9600(void);
                                
byte SCI0ByteReady(void);

void SCI0WaitReadByte(byte* Out);

byte SCI0ReadByte(void);

byte SCI0BusySendByte(void);

void SCI0WaitReadChar(char* Out);

void SCI0WaitSendByte(byte SendOut);

void SCI0ReadString(char* String, int* OutSize);

void SCI0SendString(char* String);

byte SCI1ByteReady(void);

void SCI1WaitReadChar(char* Out);

void SCI1WaitReadByte(byte* Out);

byte SCI1ReadByte(void);

byte SCI1BusySendByte(void);

void SCI1WaitSendByte(byte SendOut);

void SCI1ReadString(char* String, int* OutSize);

void SCI1SendString(char* String);
 

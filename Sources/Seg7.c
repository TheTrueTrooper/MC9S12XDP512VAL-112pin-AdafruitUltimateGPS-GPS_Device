/*
  Author: Angelo Sanches
  Board:  mc9s12xdp512(nait)
  Perpous: Switches C
  Created: 3/11/16 
  -------------UseLog-------------
  ->last is template
  Modified:<version:Date>
  Reason:
  ----------Change Log------------
  ->last is template
  Log:<Reason/Modified> Optional log in case of compliations
*/
#include "Seg7.h"


          

void Seg7InIt() 
{
// byte to count through all positions
   byte Segs = 0;// for loop
   
   // set the data direction needed on last 2 ports
   DDRA |= 0x03;
   // set the data direction needed on all b ports doe the info
   DDRB |= 0xFF;
   // set it up for first print may cut it 
   PORTA = 0x03;
   
   
   
   for (Segs = 0; Segs< 8; Segs++)
   {
         Seg7Clear(Segs);
   }
   return;
   
}




void Seg7Clear(byte position)
{
   // sets port b as needed for a position
   position |= 0x70;
   PORTB = position;
  
  // clears $03 of Portas last 2 bits   
   PORTA &= 0xFC;
   // loads it in as position by 
   //leaving first bit on for position
   PORTA |= 0x02;
   // and turning second high to send out
   PORTA |= 0x03;
   
   // set b to set to set a decimaless blank
   PORTB = 0x80;
   
   // clears 02 bits (0011 on back of byte)
   // 
   PORTA &= 0xFC;
   // sendes it out last bit
   PORTA |= 0x01;
   return;   
}


void Char7Seg(byte position, byte Value, byte decimal)
{
   // sets port b as needed for a position
   position |= 0x50;
   PORTB = position;
  
   //clears $03 of Portas last 2 bits   
   PORTA &= 0xFC;
   // loads it in as position by 
   //leaving first bit on for position
   PORTA |= 0x02;
   // and turning second high to send out
   PORTA |= 0x03;
   
   //grabs value
   Value &= 0x5F;
   PORTB = Value;
   
   // set b to set to set a decimaless blank
   // if non-required
   if (!decimal)
   PORTB |= 0x80;
   
   // clears 02 bits (0011 on back of byte) 
   PORTA &= 0xFC;
   // sendes it out last bit
   PORTA |= 0x01;

}


void Byte7Seg(byte Value, byte BottomVsTop)
{
  byte PositionValue1 = Value;
  byte PositionValue2;
  
  // do all bit shifts at one by 
  //one to allow for time effie lost on this one but its cool
  PositionValue2 = PositionValue1;
  PositionValue2 = PositionValue2 >> 4;
  
  // now drop front of each
  PositionValue1 &= 0x0F;
  PositionValue2 &= 0x0F;
  
  // now print all
  if(BottomVsTop)
  {
  Seg7Clear(0);
  Seg7Clear(1);// clears/ prints;
  Char7Seg(2, PositionValue2, 0);
  Char7Seg(3, PositionValue1, 0);
  return;
  }
  else
  {
  Seg7Clear(4);
  Seg7Clear(5);
  Char7Seg(6, PositionValue2, 0);
  Char7Seg(7, PositionValue1, 0);
  return;
  }
  

}



void Word7Seg(word Value, byte BottomVsTop)
{
  byte PositionValue1 = (byte)Value;
  byte PositionValue2;
  byte PositionValue3 = (byte)(Value>>8);
  byte PositionValue4;
  
  
  // do all bit shifts at one by 
  //one to allow for time effie lost on this one but its cool
  PositionValue2 = PositionValue1;
  PositionValue2 = PositionValue2 >> 4;
  PositionValue4 = PositionValue3;
  PositionValue4 = PositionValue4 >> 4;
  
  // now drop front of each
  PositionValue1 &= 0x0F;
  PositionValue2 &= 0x0F;
  PositionValue3 &= 0x0F;
  PositionValue4 &= 0x0F;
  
  // now print all
  if(BottomVsTop)
  {
  Char7Seg(0, PositionValue4, 0);
  Char7Seg(1, PositionValue3, 0);
  Char7Seg(2, PositionValue2, 0);
  Char7Seg(3, PositionValue1, 0);
  return;
  }
  else
  {
  Char7Seg(4, PositionValue4, 0);
  Char7Seg(5, PositionValue3, 0);
  Char7Seg(6, PositionValue2, 0);
  Char7Seg(7, PositionValue1, 0);
  return;
  }

}




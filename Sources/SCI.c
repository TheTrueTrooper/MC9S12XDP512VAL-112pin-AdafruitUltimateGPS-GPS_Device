/*
  Author: Angelo Sanches
  Board:  mc9s12xdp512(nait)
  Perpous: SCI C
  Created: 3/11/16 
  
  -------------UseLog-------------
  ->last is template
  Modified:<version:Date>
  Reason:
  ----------Change Log------------
  ->last is template
  Log:<Reason/Modified> Optional log Optional log in case of compliations
*/
#include "SCI.h"

// _SCI0CR2; /* SCI 0 Control Register 2; 0x000000CB */
// _SCI0SR1; /* SCI 0 Status Register 1; 0x000000CC */
// _SCI0SR2; /* SCI 0 Status Register 2; 0x000000CD */
// _SCI0DRH; /* SCI 0 Data Register High; 0x000000CE */
// _SCI0DRL; /* SCI 0 Data Register Low; 0x000000CF */



//IF = Infa Red
//NPW = narow pulse width
void SIC0InIt9600(void) 
{
      // SCI0DRH B7 = 0 = no IF   
      // SCI0DRH B6,5 = 00 = 3/16 NPW
      // SCI0DRH, SCI0DRL {B4-0},{B7-1} = 0034 = 52 = 8Mhz /(9800hz * 16)
      SCI0BDH = 0x00; 
      SCI0BDL = 0x34;
      
      SCI0DRL = 0x00;
      SCI0DRH = 0x34;
      
      SCI0CR1 = 0;
      SCI0CR2 = 0x0C;


}

//IF = Infa Red
//NPW = narow pulse width
void SIC1InIt9600(void) 
{
      // SCI0DRH B7 = 0 = no IF
      // SCI0DRH B6,5 = 00 = 3/16 NPW
      // SCI0DRH, SCI0DRL {B4-0},{B7-1} = 0034 = 52 = 8Mhz /(9800hz * 16)
       
      SCI1BDH = 0x00; 
      SCI1BDL = 0x34;
      
      SCI1DRL = 0x00;
      SCI1DRH = 0x34;

      SCI1CR1 = 0;
      SCI1CR2 = 0x0C;


}






byte SCI0ByteReady(void)
{ 
  return SCI0SR1 & 0x20;
}

void SCI0WaitReadChar(char* Out)
{
   byte InnerOut;
   SCI1WaitReadByte(&InnerOut);
   *Out = (char)InnerOut;
}

void SCI0WaitReadByte(byte* Out)
{
  while(SCI0ByteReady() == 0);

  *Out = SCI0DRL;  

}


byte SCI0ReadByte(void)
{
  if (SCI0ByteReady() == 0)
    return SCI0DRL;

  return 0xFF;
}

byte SCI0BusySendByte(void)
{
  return SCI0SR1 & 0x80;
}

void SCI0WaitSendByte(byte SendOut)
{

  while(SCI0BusySendByte() == 0);
  SCI0DRL = SendOut;
}

byte SCI0SendByte(byte SendOut)
{
  if(SCI0BusySendByte()==0)
  return 0xFF;
  SCI0DRL = SendOut;
  return 0;
}


void SCI0ReadString(char* String, int* OutSize)
{
  char readOut;
  *OutSize = 0;
  
  while(String[*OutSize] != 0x00 && String[*OutSize] != '\0')
  {
    SCI0WaitReadChar(&readOut);
    String[*OutSize] = readOut;
    OutSize++; 
  }
}




void SCI0SendString(char* String)
{
  byte i =0;
  while(String[i] != (char)0x00 && String[i] != '\0')
  {
    SCI0WaitSendByte(String[i]);
    i++; 
  }
}

byte SCI1ByteReady(void)
{ 
  return SCI1SR1 & 0x20;
}

void SCI1WaitReadChar(char* Out)
{
   byte InnerOut;
   SCI1WaitReadByte(&InnerOut);
   *Out = (char)InnerOut;
}

void SCI1WaitReadByte(byte* Out)
{
  byte Count = 0;
  while(SCI1ByteReady() == 0);

  *Out = SCI1DRL;
   

}


byte SCI1ReadByte(void)
{
  if (SCI1ByteReady() == 0)
    return SCI1DRL;

  return 0xFF;
}

byte SCI1BusySendByte(void)
{
  return SCI1SR1 & 0x80;
}

void SCI1WaitSendByte(byte SendOut)
{
  while(SCI1BusySendByte() == 0);

  SCI1DRL = SendOut;

}

byte SCI1SendByte(byte SendOut)
{
  if(SCI1BusySendByte()==0)
  return 0xFF;
  SCI1DRL = SendOut;
  return 0;
}


void SCI1ReadString(char* String, int* OutSize)
{
  char readOut;
  *OutSize = 0;
  while(String[*OutSize] != 0x00 && String[*OutSize] != '\0')
  {
    SCI1WaitReadChar(&readOut);
    String[*OutSize] = readOut;
    OutSize++; 
  }

}




void SCI1SendString(char* String)
{
  byte i =0;
  while(String[i] != 0x00 && String[i] != '\0')
  {
    SCI1WaitSendByte(String[i]);
    i++; 
    
  }
}

 

  








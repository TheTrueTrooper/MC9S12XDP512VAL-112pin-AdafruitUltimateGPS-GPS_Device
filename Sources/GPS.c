/*
  Author: Angelo Sanches
  Board:  mc9s12xdp512(nait)
  Perpous: SCI
  Created: 11/3/16 
                                         etry
  -------------UseLog-------------
  ->last is template
  Modified:<version:Date>
  Reason:
  ----------Change Log------------
  ->last is template
  Log:<Reason/Modified> Optional log Optional log in case of compliations
*/
#include "GPS.h"


void GPSInIt(void)
{
   SCI1BDH = 0x00; 
   SCI1BDL = 0x34;
      
   SCI1DRL = 0x00;
   SCI1DRH = 0x34;

   SCI1CR1 = 0;
   SCI1CR2 = 0x0C;
       
   DDRA &= 0xFB; //set direction to out
   PORTA |= 0x04; // set pin high for on
   
   //set buad and out result
   lcdClear();
   lcdSetRowCol(0, 0);
   lcdString("Setting up GPS");
   GPSSendCommand("PMTK251,9600"); //set buad to 9600
   Delay(400);
   
   // set thresh hold
   /*lcdClear();
   lcdSetRowCol(0, 0);
   lcdString("Settting thresh hold");
   GPSSendCommand("PMTK397,2"); // set thresh
   Delay(1000);*/  

   //turn off anten stat
   GPSSendCommand("PGCMD,33,0"); //turn off anten status
   Delay(200);
   
   //set GPS data grab hz
   GPSSendCommand("PMTK220,100"); //set hrz
   Delay(200);
   
   //set sentence types
   GPSSendCommand("PMTK314,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0"); //set son only gppa and 4 sats
   Delay(200);
   
   
   /*//set Response rate
   lcdClear();
   for (OutSize = 0; OutSize < 20;OutSize++)
    SringOut[OutSize] = '\0';
   lcdSetRowCol(0, 0);
   lcdString("Response rate");
   GPSSendCommand("PMTK220,1000"); // set to out at a hert
   (void)SCI1ReadString(SringOut, &OutSize);
   lcdSetRowCol(1, 0);
   lcdString(SringOut);
   Delay(1000);*/
}

void GPSEnable()
{
    PORTA |= 0x04; // pin high is enabled
}

void GPSDisable()
{
    PORTA &= 0xFB; // pin low is disabled
}

void GPSSendCommand(char* String)
{
byte i =0;
   char* message = NULL;
   message = MakeNMEAMessage(String);
    while(message[i] != 0x00 && message[i] != '\0')
    {
      while((SCI1SR1 & 0x80) == 0);
      SCI1DRL = message[i]; 
      i++; 
    
    }
   free(message);
}




void GPSGetSentence(char* SringOut, byte* OutSize)
{
     //SCI1SR1 &= 0x20;
     byte i;
     for (i = 0; i < *OutSize - 1;i++)
     {
      
      //SringOut[i] = '\0';
      while((SCI1SR1 & 0x20) == 0);
      SringOut[i] = SCI1DRL;
     }
     SringOut[i] = '\0';
     //SCI1ReadString(SringOut, outSize);
     
     ///*
     /*i = 0;
     
     while(SringOut[i] != '$')
     {
      while((SCI1SR1 & 0x20) == 0);
      SringOut[i] = SCI1DRL;
     }
     do
     {
      i++;
      while((SCI1SR1 & 0x20) == 0);
      SringOut[i] = SCI1DRL; 
     }while(SringOut[i] != 0x00 && SringOut[i] != '\0');
     i++;
     SringOut[i] = '\0';
     *OutSize = i;
     */
     
     
}







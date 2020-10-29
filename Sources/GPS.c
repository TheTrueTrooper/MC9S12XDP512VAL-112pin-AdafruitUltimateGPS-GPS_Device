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

//Sets up every thing needed for the GPS device
void GPSInIt(void)
{
   // set the register for data recived from SCI Serial interface 1 for 9600 baud
   SCI1BDH = 0x00; 
   SCI1BDL = 0x34;
   // set the register for data recived from SCI Serial interface 1 for 9600 baud
   SCI1DRL = 0x00;
   SCI1DRH = 0x34;
   // set the register for data recived from SCI Serial interface 1 for 9600 baud
   SCI1CR1 = 0;
   SCI1CR2 = 0x0C;
       
   DDRA &= 0xFB; //set direction to out
   PORTA |= 0x04; // set pin high for on
   
   //set buad and out result
   lcdClear();
   lcdSetRowCol(0, 0);
   lcdString("Setting up GPS");
   //set buad to 9600
   GPSSendCommand("PMTK251,9600");
   Delay(400);

   //turn off the anten status on strings
   GPSSendCommand("PGCMD,33,0");
   Delay(200); // delay a little between every command to allow GPS rec modual to cary out command.
   
   //set GPS data grab at speed
   GPSSendCommand("PMTK220,100"); //set hrz
   Delay(200);
   
   //set sentence types for GPPA Data (Lat & Long) and to only listen to for satalites on a mininum data
   GPSSendCommand("PMTK314,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0");
   Delay(200);
   
   
}
//Turns off GPS With GPIO pin attached at by rasing high
void GPSEnable()
{
    PORTA |= 0x04; // pin high is enabled
}
//Turns off GPS With GPIO pin attached at by cutting low
void GPSDisable()
{
    PORTA &= 0xFB; // pin low is disabled
}
//Sends a command for the GPS
void GPSSendCommand(char* String)
{
  //start at start
   byte i =0;
  //ready a message memory location
   char* message = NULL;
  //make a meessage from the string for the NMEA Protocol
   message = MakeNMEAMessage(String);
  //while you still have values in a sting and not null terminated
    while(message[i] != 0x00 && message[i] != '\0')
    {
      //wait while charater is still being sent
      while((SCI1SR1 & 0x80) == 0);
      // after message is sent load next
      SCI1DRL = message[i]; 
      //cont iterate
      i++; 
    }
    // after done free memory used internally while sending.
   free(message);
}




void GPSGetSentence(char* SringOut, byte* OutSize)
{
     //Set location to start of buffer
     byte i;
     for (i = 0; i < *OutSize - 1;i++)
     {  
      //check to see if data has been recieved yet on register
      while((SCI1SR1 & 0x20) == 0);
      //Load data when there
      SringOut[i] = SCI1DRL;
     }
     //end string just in case
     SringOut[i] = '\0';    
     
}







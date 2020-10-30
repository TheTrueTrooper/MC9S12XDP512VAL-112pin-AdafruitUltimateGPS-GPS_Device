#include "CELL.h"
//Opens the cellphone models serial port and sets up for use.
void CELLInIt(void)
{
   //Open SCI1 and set for a baud rate of 9600
   SCI1BDH = 0x00; 
   SCI1BDL = 0x34;
      
   SCI1DRL = 0x00;
   SCI1DRH = 0x34;

   SCI1CR1 = 0;
   SCI1CR2 = 0x0C;
   
   //Open direction for enable GPIO pin 60 for enabling cell model
   DDRA &= 0xF7; //set direction to out for pin 60
   DDRA |= 0xF0; //set direction in for 60 - 64

}

//Sends a Basic Command to the Cellphone
void CELLSendCommand(char* String)
{
   (void)SCI1SendString(String);
}

void CELLToggleOnOff()
{
   PORTA |= 0x08; // set pin high to start on toggle  
   Delay(2002);   // set for 2 sec
   PORTA &= 0xF7; // set pin low to finish toggle
}

void CELLGetHTTP(char* URL, int URLsize, char** Params, int* ParamSize, char** Value, int* ValueSize, char* Response, int ResponseSize, byte ParamsNum)
{
//Huge string building exert
    char* Command = "AT+HTTPPARA=\"URL\",\"";
    char* FullURL = NULL;
    int i;
    //capture the sizes to alot mem
    int ParamsSIZES = URLsize;
    for (i = 0; i < ParamsNum; i ++)
    {
        ParamsSIZES += ParamSize[i];
        ParamsSIZES += ValueSize[i];
        ParamsSIZES++; //for &
    }
    //alot mem    
    FullURL = (char*)malloc(ParamsSIZES + 3 + 20);  // for (& + \0 + \r ) + 18 for Command
    (void)strcat(FullURL, Command);// set command ith open dting for use
    (void)strcat(FullURL, URL);  //add url
    (void)strcat(FullURL, "&"); //add param sep 
    //add all params & values as stuff
    for (i = 0; i < ParamsNum; i ++)    //\r
    {
      (void)strcat(FullURL, Params[i]);
      (void)strcat(FullURL, "=");
      (void)strcat(FullURL, Value[i]);
    }
    (void)strcat(FullURL, "\""); //close string
    (void)strcat(FullURL, "\r"); //carage return for our thing
    (void)strcat(FullURL, "\0"); //end of string for us
    CELLSendCommand("AT+HTTPINIT\r"); //start sesh
    CELLSendCommand("AT+HTTPPARA=\"CID\",1\r");//confing cell for http 
    CELLSendCommand(FullURL); // set url param
    CELLSendCommand("AT+HTTPACTION=0\r");  //Send it
    CELLSendCommand("AT+HTTPREAD\r");   //GetResponse
    SCI1ReadString(Response, &ResponseSize); //listen to response
    CELLSendCommand("AT+HTTPTERM\r"); // clean up cell
    free(FullURL); // clean up func
}



/*
  Author: Angelo Sanches
  Board:  mc9s12xdp512(nait)
  Perpous: To Create and maintain a connection with the cellphone model
  Created: ?  
  Notes: Port is shared with the old Comport so they can not be used together. 
  -------------UseLog-------------
  ->last is template
  Modified:<version:Date>
  Reason:
  ----------Change Log------------
  ->last is template
  Log:<Reason/Modified> Optional log Optional log in case of compliations
*/
#include "CELL.h"
//Opens the cellphone models serial port and sets up for use.
void CELLInIt(void)
{
   //Open SCI1 and set for a baud rate of 9600
   SCI0BDH = 0x00; 
   SCI0BDL = 0x34;
      
   SCI0DRL = 0x00;
   SCI0DRH = 0x34;

   SCI0CR1 = 0;
   SCI0CR2 = 0x0C;
   
   //Open direction for enable GPIO pin 60 for enabling cell model
   DDRA &= 0xF7; //set direction to out for pin 60
   DDRA |= 0xF0; //set direction in for 60 - 64

}

//Sends a Basic Command to the Cellphone
void CELLSendCommand(char* String)
{
   (void)SCI0SendString(String);
}

//Turns off and on cellphone model
void CELLToggleOnOff()
{
   PORTA |= 0x08; // set pin high to start on toggle  
   Delay(2002);   // Pulse activated for 2 seconds. so hold high for 2 seconds.
   PORTA &= 0xF7; // set pin low to finish toggle
}

//This Gets a the cellphone to make a http reqest.
//URL - is a string of the loction to make the request.
//Param - is a array of strings for the params that will be added to a http get request
//ParamSize - is an array of the chars in all the params in the array of strings (low level programming he)
//Value - is a array of strings for the params values that will be added to a http get request
//ValueSize - is an array of the chars in all the params values in the array of strings (low level programming hehe)
//ParamsNum - The nunmber of paramerters
//Response - if for your reponse buffer to fill
//ResponseSize - The size of the response
void CELLGetHTTP(char* URL, int URLsize, char** Params, int* ParamSize, char** Value, int* ValueSize, byte ParamsNum, char* Response, int* ResponseSize)
{
    //Huge string building exert
    //Set the set HTTP request target string start
    char* Command = "AT+HTTPPARA=\"URL\",\"";
    //Create a space to create the full Set url string
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
    //alot memory for tha  
    FullURL = (char*)malloc(ParamsSIZES + 3 + 22);  // for (& + \0 + \r ) + 18 for Command
    // set the start of the string to be used
    (void)strcat(FullURL, Command);// set command ith open dting for use
    //Add the root URL
    (void)strcat(FullURL, URL);  //add url
    //Add the url Params seperation marker as ?
    (void)strcat(FullURL, "?"); //add param sep 
    //add all params & values as to the get string from here
    for (i = 0; i < ParamsNum; i ++)    //\r
    {
       //if we are on a another param add another param seperation marker as &
      if(i > 0)
         (void)strcat(FullURL, "&");
      (void)strcat(FullURL, Params[i]);
      (void)strcat(FullURL, "=");
      (void)strcat(FullURL, Value[i]);
    }
    (void)strcat(FullURL, "\""); //close string
    (void)strcat(FullURL, "\r"); //carage return for our thing
    (void)strcat(FullURL, "\0"); //end of string for us
    CELLSendCommand("AT+HTTPINIT\r"); //start sesh
    CELLSendCommand("AT+HTTPPARA=\"CID\",1\r");//confing cell for http 
    //Send the full url for the request with params
    CELLSendCommand(FullURL); // set url param
    CELLSendCommand("AT+HTTPACTION=0\r");  //Send it
    CELLSendCommand("AT+HTTPREAD\r");   //GetResponse
    SCI0ReadString(Response, &ResponseSize); //listen to response
    //Clean up the string
    CELLSendCommand("AT+HTTPTERM\r"); // clean up cell
    // null termate the string
    FullURL[ParamsSIZES + 3 + 21] = '\0';
    free(FullURL); // clean up func
}



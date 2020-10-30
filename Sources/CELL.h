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
#include <hidef.h>
#include <stdlib.h>
#include "mc9s12xdp512.h"
#include "SCI.h"
#include "GPSParse.h"
#include "GPSData.h"
#include "MessageMaker.h"
#include "DirtyDelays.h"

//Opens the com ports and sets up a Serial port for use.
void CELLInIt(void);

//Sends a string to the Cellphone for custom commands
void CELLSendCommand(char* String);

//Toggles the Cellphone modual on and off using the GPIO with a pulse
void CELLToggleOnOff();    

//This Gets a the cellphone to make a http reqest.
//URL - is a string of the loction to make the request.
//Param - is a array of strings for the params that will be added to a http get request
//ParamSize - is an array of the chars in all the params in the array of strings (low level programming he)
//Value - is a array of strings for the params values that will be added to a http get request
//ValueSize - is an array of the chars in all the params values in the array of strings (low level programming hehe)
//ParamsNum - The nunmber of paramerters
//Response - if for your reponse buffer to fill
//ResponseSize - The size of the response
void CELLGetHTTP(char* URL, int URLsize, char** Params, int* ParamSize, char** Value, int* ValueSize, char* Response, int ResponseSize, byte ParamsNum);

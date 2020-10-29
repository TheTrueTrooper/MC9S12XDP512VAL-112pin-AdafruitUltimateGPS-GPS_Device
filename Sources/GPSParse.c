#include "GPSParse.h"

//TESTED AND WORKS DO NOT ALTER AT ALL
//Data : a string to parse will split from the string or data with out altering 
//OutStart : The Position in the data to parse at the value will be 
//modified by the function so can be used for next parse
//Spliter : the single char (uses '' not "") to split on
char* ReadSection(char* Data, byte* OutStart, char Spliter) 
{ 
      // looks for fist start space
      int i = 0;
      //start a string
      char* StringOut = NULL;
      // Gets size of the data
      while (Data[*OutStart + i]!= 0x00 && Data[*OutStart + i]!= '\0' && Data[*OutStart + i] != Spliter)
      {
         i++;
      }
      
      //alocate a new string with a extra spot for null termator
      StringOut = (char*)malloc(i + 1); // thanks to herb for showing me aloting data
      i = 0;
      //load all data into the new string
      while (Data[*OutStart + i]!= 0x00 && Data[*OutStart + i]!= '\0' && Data[*OutStart + i] != Spliter) 
      {
         StringOut[i] = Data[*OutStart + i]; 
         i++;
      }
      //null terminate the string
      StringOut[i] = '\0';    
      //set us ready for the read on the next section by moving one
      *OutStart += i + 1;
      return StringOut; 
}

//Gets the actuall GPPA string from the full data string removing all unessarry bits
char* FindGPSString(char* Data, byte* OutStart) 
{ 
      
      int i = 0;
      int j = 0;
      char* StringOut = NULL;
      //find the start of the string
      while (Data[*OutStart + j] != '$' && Data[*OutStart + j + 1] != 'G')
      {
         j++;
            //if for some reason we have a null we failled on aqquiring a string so kill it and wait for next data
         if (Data[*OutStart + j] == '\0')
          return NULL;
      }
      //look for the end of the data from the beinging of the string.
      i = j;
      while (Data[*OutStart + i] != '\r')
      {
         i++;
         if (Data[*OutStart + i] == '\0')
          return NULL;
      }
      
      //allocate some space for a string and give it one extra spot for a end of the string on a null termator
      StringOut = (char*)malloc(i - j + 1); 
      i = 0;
      //copy the data
      while(Data[*OutStart + i + j] != '\r') 
      {
         StringOut[i] = Data[*OutStart + i + j]; 
         i++;
         if (Data[*OutStart + i] == '\0')
          return NULL;
      }
      //null termiate
      StringOut[i] = '\0';       
      *OutStart += i;
      return StringOut; 
}

//Pares out data from string        wert
//-1 is for Unknown Data type or not accounted for on perpous
//-2 is for bad check sum or bad data
//so here right a parser selector
int GPSParse (char* Data, GPSDataType* DataOutr)
{
      //check the data type to find if it is the correct data type
  if((Data[0]=='$')&& (Data[1]=='G')&& (Data[2]=='P') && (Data[3]=='G') && (Data[4]== 'G') && (Data[5]=='A')) 
  {
      (*DataOutr).type = GPGGA;//GPGGA;
  }
  ///as many as we want for types
  // check for GPGGA
  switch((*DataOutr).type)
  { 
    default:
      return -1; // unknown type
    case GPGGA:
      return ParseGPGGA(Data, DataOutr);
      

  } 

}
//Gets hex values from data
byte ParseHex(char* IN) 
{
      int Out = 0;
      char Parse[2];
      Parse[0] =  IN[0];
      Parse[1] =  '\0';
      Out = atoi(Parse);
      Parse[0] =  IN[1];
      Parse[1] =  '\0';
      return 16 * Out +  atoi(Parse);
}

//Data: The String To use
int ParseGPGGA(char* Data, GPSDataType* DataOut)
{


  // check for GPGGAPrior
  
  byte i;
  int bytedata =0;
  
  char* ParsedData;
  char Check = (char)0;
      
  //get check sum on all of the data
  i = 1;
  while(Data[i] != '*')
  {
       Check ^= Data[i];
       i++;
  }
  
  
  i = 8;
  // check hhmmss.ss
  // check time stamp;
  ParsedData = ReadSection(Data , &i, ',');
  (*DataOut).TimeStamp = atof(ParsedData);
  free(ParsedData);   // thanks to herb for showing me free data
  // check for latitude
  ParsedData = ReadSection(Data, &i, ',');
  (*DataOut).latitude = atof(ParsedData);
  free(ParsedData);
  //check for N or S
  ParsedData = ReadSection(Data, &i, ',');
  if(*ParsedData == 'S') {
    (*DataOut).latitude *= -1;
  }
  free(ParsedData);
  //check for longitude
  ParsedData = ReadSection(Data, &i, ',');
  (*DataOut).longitude = atof(ParsedData);
  free(ParsedData);
  //check for W or E
  ParsedData = ReadSection(Data, &i, ',');
  if(*ParsedData == 'W') {
    (*DataOut).longitude *= -1;
  }
  free(ParsedData);
  // check to see the quality of indicator
  ParsedData = ReadSection(Data, &i, ',');
  bytedata = atoi(ParsedData);
  free(ParsedData);
  if(bytedata == 1)
    (*DataOut).Quality = Uncorrelated;
  else if(bytedata ==2)
    (*DataOut).Quality= DifferentiallyCorrected;
  else if(bytedata ==3)
    (*DataOut).Quality = RTKFix;
  else if(bytedata ==4)
    (*DataOut).Quality = RTKFloat;
  else
    (*DataOut).Quality = Unknown;     
  
  //denotes number of satellites used in the coordinate   
  ParsedData = ReadSection(Data, &i, ',');
  free(ParsedData);
  
  // check for HDP
  ParsedData = ReadSection(Data, &i, ',');
  (*DataOut).HDP = atof(ParsedData);
  free(ParsedData);
  
  // check for altitude
  ParsedData = ReadSection(Data, &i, ',');
  (*DataOut).Alt = atof(ParsedData);
  free(ParsedData);
  
  // check for unit
  ParsedData = ReadSection(Data, &i, ',');
  //come back Meters Mesurements Feet vs Meters convert<--------
  if(*ParsedData == 'F') // convert to Meter
  {
        //if in feet auto convert
  (*DataOut).Alt *= 3.28084;
  }
  free(ParsedData);
  
  //check for geoidal separation
  ParsedData = ReadSection(Data, &i, ',');
  (*DataOut).GeoidalS = atof(ParsedData);
  free(ParsedData);
  // check for unit
  ParsedData = ReadSection(Data, &i, ',');
  //come back Alt Mesurements Feet vs Meters convert<--------
  if(*ParsedData == 'F') // convert to Meter
  {
        //if in feet auto convert
  (*DataOut).GeoidalS *= 3.28084;
  }
  free(ParsedData);
  // age of the correction
  ParsedData = ReadSection(Data, &i, ',');
  (*DataOut).ADGD = atof(ParsedData);
  free(ParsedData);
  //station ID
  ParsedData = ReadSection(Data, &i, '*');
  (*DataOut).StationID = atoi(ParsedData);
  free(ParsedData);
  
  //get check sum and check
  ParsedData = ReadSection(Data, &i, '*');
  i = ParseHex(ParsedData);
  free(ParsedData);
  if(i == (int)Check)
    return -2;           //bad data
                
  return GPGGA;


}







   





















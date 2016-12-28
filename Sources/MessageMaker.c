#include "MessageMaker.h"


void StrCheckSum(char* Data, char* CheckSum)
{
  int i = 0;
  char Check = (char)0;
  
  while(Data[i] != '\0')
  {
       Check ^= Data[i];
       i++;
  }
  
  CheckSum[0] = (char)((byte)Check / 16 + 48); 
  CheckSum[1] = (char)((byte)Check % 16 + 48);
 
}

char* MakeNMEAMessage(char* String)
{
  int i = 0;      //              \r\n
  char Check[2]; 
  char* StringOut = NULL; //(char*)malloc(i + 1);
  
  StrCheckSum(String, Check);
  
  while(String[i] != '\0')
  {
     i++;
  }
  
  StringOut = (char*)malloc(i + 8);
  StringOut[0] = '$';
  i = 0;
  do {
     StringOut[i + 1] = String[i];
     i++;
  } while(String[i] != '\0');
  i++;
  StringOut[i] = '*';
  i++;
  StringOut[i] = Check[0];
  i++;
  StringOut[i] = Check[1];
  i++;
  StringOut[i] = '\r';
  i++;
  StringOut[i] = '\n';
  i++;
  StringOut[i] = '\0';
  return StringOut;
}
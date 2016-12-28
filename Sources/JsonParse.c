#include "JsonParse.h"

char* JReadSection(char* Data, unsigned int* OutStart, char Spliter) 
{ 
      
      int i = 0;
      char* StringOut = NULL;
      while (Data[*OutStart + i]!= '\0' && Data[*OutStart + i] != Spliter)
      {
         i++;
      }
      
     
      StringOut = (char*)malloc(i + 1); // thanks to herb for showing me aloting data
      i = 0;
      while (Data[*OutStart + i]!= '\0' && Data[*OutStart + i] != Spliter) 
      {
         StringOut[i] = Data[*OutStart + i]; 
         i++;
      }
      StringOut[i] = '\0';       
      *OutStart += i + 1;
      return StringOut; 
}

void ReplaceChar(char * Data, char Find, char replace)
{
     int i = 0;
     while (Data[i]!= '\0')
     {
         if(Data[i] == Find)
           Data[i] = replace;
         i++;
     }
}


char * TrimSpace(char * Data)
{
     
     int i = 0;
     unsigned int start = 0;
     unsigned int end = 0;
     unsigned int Total = 0;
     char* StringOut = NULL;
     //mov to end
     while (Data[i]!= '\0')
     {
        if(start == 0 && Data[0] == ' ' && Data[i] != ' ')
          start = i;
        i++;
     }
     i -=1;
     i = Total = i;
     //move back after pan
     while (i > start)
     {
        if(Data[Total] != ' ' || Data[i] != ' ' )
        {
          end = i;
          break;
        }
        i--;
     }
      
     
     StringOut = (char*)malloc(end - start + 1); // thanks to herb for showing me aloting data
     for (i = start; i < end + 1; i++)
     {
         StringOut[i - start] = Data[i]; 
     }
     StringOut[i] = '\0';       
     return StringOut; 
}



void JasonParseGPGGA(char* Data, GPSDataType* DataOut)
{
   unsigned int i = 0;
   char* ParsedData = NULL;
   ParsedData = JReadSection(Data , &i, ':');
   free(ParsedData);
   ParsedData = JReadSection(Data , &i, ':');
   free(ParsedData);
   ParsedData = JReadSection(Data , &i, ':');
   free(ParsedData);
   ParsedData = JReadSection(Data , &i, ':');
   free(ParsedData);
   ParsedData = JReadSection(Data , &i, ':');
   free(ParsedData);
   ParsedData = JReadSection(Data , &i, ',');
   (*DataOut).latitude = atof(ParsedData);
   free(ParsedData);
   ParsedData = JReadSection(Data , &i, ':');
   free(ParsedData);
   ParsedData = JReadSection(Data , &i, '}');
   (*DataOut).longitude = atof(ParsedData);
   free(ParsedData);
   
}


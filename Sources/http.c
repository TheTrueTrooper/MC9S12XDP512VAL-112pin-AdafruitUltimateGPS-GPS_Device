//https://www.googleapis.com/geolocation/v1/geolocate?key=YOUR_API_KEY
 // https://maps.googleapis.com/maps/api/place/nearbysearch/output?parameters
//required parameters
//char location = DataOutr.latitude +"," DataOutr.longitude; // latitude and longitude
char* radius = "5000"; // within the range of 5000
char* type = "";// the place or name you wanna go to 
char* keyword="oewifs";// keyword to insert
char* latitude = "80.9";
char* longitude = "-1093.84";
 
#include "http.h"
 
 
//TESTED AND WORKS DO NOT ALTER AT ALL
//Data : a string to parse will split from the string or data with out altering 
//OutStart : The Position in the data to parse at the value will be 
//modified by the function so can be used for next parse
//Spliter : the single char (uses '' not "") to split on
char* ReadSectionLong(char* Data, int* OutStart, char Spliter) 
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
 
void FindURL(char* data, char* OutURL) {  
  char* urladdress ="https://maps.googleapis.com/maps/api/place/radarsearch/json?";
  char* lo ="location=";    
  char* la = "";
  //Lat strcpy(la, "2390.8");
  char* co = ",";
  char* lon ="";
  //lon strcpy(lon, "-23984.0");
  char* ra = "&radius=5000&keyword=";
  char* ke = "";
  //strcpy(ke, "museum");
  char* ap= "&key=api_key";
  
  (void)strcpy(la, "2390.8");
  (void)strcpy(lon, "-23984.0");
  (void)strcpy(ke, "museum");
  
  (void)strcat(urladdress, lo);
  (void)strcat(urladdress, la);
  (void)strcat(urladdress, co);
  (void)strcat(urladdress, lon);
  (void)strcat(urladdress, ra);
  (void)strcat(urladdress, ke);
  (void)strcat(urladdress, ap);
    
  (void)strcpy(OutURL,urladdress);
}

void ParseJson(char *jsonData, GPSDataType* DataOutr) {

  int i =0;
  char* ParseData = NULL; 
  ParseData = ReadSectionLong(jsonData, &i, '{');
  free(ParseData);
  ParseData = ReadSectionLong(jsonData, &i,'{');
  free(ParseData);
  ParseData = ReadSectionLong(jsonData, &i, '{');
  free(ParseData);
  ParseData = ReadSectionLong(jsonData, &i, '{');
  free(ParseData);
  ParseData = ReadSectionLong(jsonData, &i, ':');
  free(ParseData);
  ParseData = ReadSectionLong(jsonData, &i, ',');
  (*DataOutr).latitude = atof(ParseData);
  free(ParseData);
  ParseData = ReadSectionLong(jsonData, &i, ':');
  free(ParseData);
  ParseData = ReadSectionLong(jsonData, &i, '}');
  (*DataOutr).longitude = atof(ParseData);
  free(ParseData);
  
}
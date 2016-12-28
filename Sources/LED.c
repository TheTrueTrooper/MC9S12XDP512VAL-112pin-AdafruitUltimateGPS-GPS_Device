/*
  Author: Angelo Sanches
  Board:  mc9s12xdp512(nait)
  Perpous: LED c
  Created: 3/31/16 
  
  -------------UseLog-------------
  ->last is template
  Modified:<version:Date>
  Reason:
  ----------Change Log------------
  ->last is template
  Log:<Reason/Modified> Optional log Optional log in case of compliations
*/
#include "LED.h"



void lcdRWup(void)
{
  PORTK |= 0x02;
}


void lcdRWdown()
{
  PORTK &= 0xFD;
}

void lcdEup()
{
  PORTK |= 0x01;
}

void lcdEdown()
{
  PORTK &= 0xFE;
}

void lcdRSup()
{
  PORTK |= 0x04;
}

void lcdRSdown()
{
  PORTK &= 0xFB;
}

void lcdSDelay()
{
  asm ldy #10;
  asm dbne y,*;
}

void lcdLDelay()
{
  asm ldy #0;
  asm dbne y,*;
}

void lcdInIt()
{
  PTH = 0x00;
  DDRH = 0xFF;
  
  PORTK &= 0xF8;
  DDRK |= 0x07;
  
  lcdLDelay();
  lcdLDelay();
  lcdLDelay();
  
  PTH = 0x38;
  lcdEup();
  lcdEdown();
  lcdLDelay();
  
  lcdEup();
  lcdEdown();
  lcdLDelay();
  
  lcdEup();
  lcdEdown();
  lcdLDelay();
  
  lcdEup();
  lcdEdown();
  lcdLDelay();
  
  PTH = 0x0C;
  lcdEup();     //Disp control = on, no cursor, no blink
  lcdEdown();
  lcdLDelay();
  
  PTH = 0x01;
  lcdEup();
  lcdEdown();   //clear
  lcdLDelay();
  
  PTH = 0x06;
  lcdEup();
  lcdEdown();   //Entry Mode = inc no disp shift
  lcdLDelay();
}

void lcdBusy()
{
  char lcd_Busy = 0x00;
  DDRH = 0x00;
  
  lcdRSdown();
  lcdRWup();
  do
  {
    lcdSDelay();
    lcdEup();
    lcdSDelay();
    lcd_Busy = PTH;
    lcd_Busy &= 0x80;
    lcdEdown();
    
  } while (lcd_Busy != 0);
}

//send data to control
void lcdInst(char cIn)
{
  lcdBusy();
  
  PORTK &= 0xF8;     // premark all down
  
  PTH = cIn;
  DDRH = 0xFF;
  
  lcdSDelay();
  
  lcdEup();        // send it out
  lcdEdown();

}

// sends data t current cursor
void lcdData(char cIn)
{
  lcdBusy();
  
  PORTK &= 0xF8;    // pre mark all down
  
  PTH = cIn;
  DDRH = 0xFF;
  
  lcdSDelay();
  
  lcdRSup();     //data
  lcdEup();
  lcdEdown();   //out with it

}


// sets addr in A to LCD
void lcdAddr(char cAddress)
{
  lcdBusy();
  lcdInst(0x80|cAddress);
}

void lcdCGAddr(char cAddress)
{
  lcdBusy();
  lcdInst(0x40|(0x3F & cAddress));
}

void lcdString(char* InputString)
{
  char cLetter = '0';
  int iIndex = 0;
  while (InputString[iIndex] != '\0' && iIndex < 20)
  {
    cLetter = InputString[iIndex];
    lcdData(cLetter);
    iIndex++;
  }
}

void lcdStringFromBack(char* InputString)
{
  char cLetter = '0';
  int iIndex = 0;
  while (InputString[iIndex] != '\0' && iIndex < 20)
  {
    cLetter = InputString[iIndex];
    iIndex++;
  }
  while (iIndex > 0)
  {
    iIndex--;
    cLetter = InputString[iIndex];
    lcdData(cLetter);
  }
  
}      

void lcdClear()
{
  lcdBusy();
  lcdInst(1);
}

void lcdSetRowCol(char row, char col)
{
  char cAddr = 0;
  if(col >= 0 && col < 20)
  {
    switch (row)
    {
      case 0:
      cAddr = col;
      lcdAddr(cAddr);
      break;
      case 1:
      cAddr = 0x40 + col;
      lcdAddr(cAddr);
      break;
      case 2:
      cAddr = 0x14 + col;
      lcdAddr(cAddr);
      break;
      case 3:
      cAddr = 0x54 + col;
      lcdAddr(cAddr);
      break;
      default:
      cAddr = col;
      lcdAddr(cAddr);
      break;
    }
  }
    else
    {
    lcdAddr(cAddr);
    }
}

void lcdQuickLables(char* Lb0, char* Lb1,char* Lb2, char* Lb3)
{
 lcdSetRowCol(0,0);
 lcdString(Lb0);
 lcdSetRowCol(1,0);
 lcdString(Lb1);
 lcdSetRowCol(2,0);
 lcdString(Lb2);
 lcdSetRowCol(3,0);
 lcdString(Lb3);
}


void lcdLablesPro(char PosOnRow, char* Lb0, char* Lb1,char* Lb2, char* Lb3)
{
 lcdSetRowCol(0,PosOnRow);
 lcdString(Lb0);
 lcdSetRowCol(1,PosOnRow);
 lcdString(Lb1);
 lcdSetRowCol(2,PosOnRow);
 lcdString(Lb2);
 lcdSetRowCol(3,PosOnRow);
 lcdString(Lb3);
}

void lcdQuickLablesFB(char* Lb0, char* Lb1,char* Lb2, char* Lb3)
{
 lcdSetRowCol(0,0);
 lcdStringFromBack(Lb0);
 lcdSetRowCol(1,0);
 lcdStringFromBack(Lb1);
 lcdSetRowCol(2,0);
 lcdStringFromBack(Lb2);
 lcdSetRowCol(3,0);
 lcdStringFromBack(Lb3);
}


void lcdLablesProFB(char PosOnRow, char* Lb0, char* Lb1,char* Lb2, char* Lb3)
{
 lcdSetRowCol(0,PosOnRow);
 lcdStringFromBack(Lb0);
 lcdSetRowCol(1,PosOnRow);
 lcdStringFromBack(Lb1);
 lcdSetRowCol(2,PosOnRow);
 lcdStringFromBack(Lb2);
 lcdSetRowCol(3,PosOnRow);
 lcdStringFromBack(Lb3);
}







/*
  Author: Angelo Sanches
  Board:  mc9s12xdp512(nait)
  Perpous: LED Header
  Created: 3/31/16 
  
  -------------UseLog-------------
  ->last is template
  Modified:<version:Date>
  Reason:
  ----------Change Log------------
  ->last is template
  Log:<Reason/Modified> Optional log Optional log in case of compliations
*/
#include <hidef.h>
#include "mc9s12xdp512.h"

void lcdRWup(void);
void lcdRWdown(void);

void lcdEup(void);
void lcdEdown(void);

void lcdRSup(void);
void lcdRSdown(void);

void lcdSDelay(void);
void lcdLDelay(void);

void lcdInIt(void);

void lcdInst(char cIn);

void lcdData(char cIn);

void lcdAddr(char cAddress);

void lcdCGAddr(char cAddress);

void lcdString(char* InputString);

void lcdStringFromBack(char* InputString);

void lcdClear(void);

void lcdSetRowCol(char row, char col);

void lcdQuickLables(char* Lb0, char* Lb1,char* Lb2, char* Lb3);

void lcdLablesPro(char PosOnRow, char* Lb0, char* Lb1,char* Lb2, char* Lb3);

void lcdQuickLablesFB(char* Lb0, char* Lb1,char* Lb2, char* Lb3);

void lcdLablesProFB(char PosOnRow, char* Lb0, char* Lb1,char* Lb2, char* Lb3);

//use sprintf(char *Targetstr, const char *format, var)
/*
format %[flags][width][.Precision][length][specifier]
-flags
- = left justify
+ = Forces sign in front
# = forces decimal
0 = pad with 0s
-width
number = min number of chars to print
*      = place holder ie does nothing
-.Precision
.number = Digits
.*      = For float Number of digits to print
-length
h = short
l = long
L = double long
-specifier
c    = char
d ,i = sint
e    = Expo using e
e    = Expo using E
g    = uses the shortner of %e or %f.
g    = uses the shortner of %E or %f
o    = soct
s    = string of char
u    = us dec int
x    = us hex int
X    = us hex int caped
p    = Pointer add
n    = nothing
%    = Char
*/






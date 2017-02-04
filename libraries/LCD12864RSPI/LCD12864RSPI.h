//Demo LCD12864 spi
//www.dfrobot.com
#include <Arduino.h>
#ifndef LCD12864RSPI_h
#define LCD12864RSPI_h
#include <avr/pgmspace.h>
#include <inttypes.h>


class LCD12864RSPI {
typedef unsigned char uchar;


public:

LCD12864RSPI();

void Initialise(int _latchPin,int _dataPin,int _clockPin);
void delayns(void);

void WriteByte(int dat);
void WriteCommand(int CMD);
void WriteData(int CMD);


void CLEAR(void);
void DisplayString(int X,int Y,uchar *ptr,int dat);
void DisplaySig(int M,int N,int sig);
void DrawFullScreen(uchar *p);

int delaytime;
int DEFAULTTIME;


int latchPin = 8;  
int dataPin = 9; 
int clockPin = 3;  

//static const int latchPin = _latchPin;  
//static const int dataPin = _dataPin; 
//static const int clockPin = _clockPin; 

};
extern LCD12864RSPI LCDA;    
#endif

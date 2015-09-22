#include <NewSoftSerial.h>
//-------------------------------------------------------------------------
#include <LCD5110_Graph.h>
LCD5110 myGLCD(3,4,5,6,7);
//-------------------------------------------------------------------------
extern uint8_t SmallFont[];
extern unsigned char TinyFont[];
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
#include "BBKGPS.h"
BBKGPS myGPS;
NewSoftSerial mySerial(10, 11); // RX, TX
//-------------------------------------------------------------------------

void setup() 
{
  //-------------------------------------------------------------------------
  myGLCD.InitLCD(50);
  //-------------------------------------------------------------------------
  myGLCD.clrScr();
  myGLCD.setFont(SmallFont);
  myGLCD.print("GPS Read Start", CENTER, 14); 
  myGLCD.setFont(TinyFont);
  myGLCD.print("(C)2013 by", CENTER, 36);
  myGLCD.print("BOBOKing.COM", CENTER, 42);
  myGLCD.update();
  //-------------------------------------------------------------------------
  delay(500); 
  //-------------------------------------------------------------------------
  myGLCD.clrScr();
  myGLCD.setFont(SmallFont);
  myGLCD.print("HardwareSerial", CENTER, 10); 
  myGLCD.print("Read Start", CENTER, 24); 
  myGLCD.update();
  delay(500); 
  //-------------------------------------------------------------------------
  myGPS.InitGPS(Serial,mySerial,0,9600,8);
  //-------------------------------------------------------------------------
}
//-------------------------------------------------------------------------
unsigned long NoowTime = 0;
unsigned long ShowTime = 0;
int ShowTimeKey = 1000;//5s
//-------------------------------------------------------------------------
void loop() 
{
  //-------------------------------------------------------------------------
  NoowTime = millis();
  //-------------------------------------------------------------------------
  myGPS.Read(0);
  //-------------------------------------------------------------------------
  if( NoowTime - ShowTime > ShowTimeKey){ 
    ShowTime = NoowTime;
    GpsLCDShow();
    //Serial.println(NoowTime); 
  }
  //-------------------------------------------------------------------------
}

char str[20];
void GpsLCDShow(){
  //-------------------------------------------------------------------------
  myGPS.toStr(0);
  //-------------------------------------------------------------------------
  myGLCD.clrScr();
  myGLCD.setFont(SmallFont);
  //-------------------------------------------------------------------------
  myGLCD.print(myGPS.tDate, 0,  0);  
  myGLCD.print(myGPS.sTime, 36,  0);
  //------------------------------------------------
  myGLCD.print("W",  0,  9);  
  myGLCD.print(myGPS.sLats, 18,  9);
  myGLCD.print("J",  0, 18);  
  myGLCD.print(myGPS.sLons, 12, 18);
  //------------------------------------------------
  myGLCD.print(myGPS.cLock, 0, 27);  
  myGLCD.print(myGPS.cType, 8, 27);  
  myGLCD.print("-", 16, 27);    
  myGLCD.print(myGPS.sGpsn, 24, 27);     
  myGLCD.print("R", 46, 27); 
  myGLCD.print(myGPS.sRads, 54, 27);   
  //------------------------------------------------
  myGLCD.print("S",  0, 36); 
  myGLCD.print(myGPS.sSped,  8, 36); 
  myGLCD.print("F",  46, 36); 
  myGLCD.print(myGPS.sFans, 54, 36);
  //-------------------------------------------------------------------------
  //myGLCD.print(myGPS.charGPRMC,  0, 36);  
  //-------------------------------------------------------------------------
  myGLCD.update();
  //-------------------------------------------------------------------------
}


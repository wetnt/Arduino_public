//-------------------------------------------------------------------------
#include <LCD5110_Graph.h>
LCD5110 myGLCD(3,4,5,6,7);
//-------------------------------------------------------------------------
extern uint8_t SmallFont[];
extern unsigned char TinyFont[];
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
unsigned long NoowTime = 0;
//-------------------------------------------------------------------------
unsigned long ShowTime = 0;
int ShowTimeKey = 1000;//5s
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
#include "BBKGPS.h"
BBKGPS myGPS();
//-------------------------------------------------------------------------

void setup() 
{
  //-------------------------------------------------------------------------
  myGLCD.InitLCD(50);
  //-------------------------------------------------------------------------
  myGLCD.setFont(SmallFont);
  myGLCD.clrScr();
  myGLCD.print("GPS Read Start", CENTER, 14); 
  myGLCD.setFont(TinyFont);
  myGLCD.print("(C)2013 by", CENTER, 36);
  myGLCD.print("BOBOKing.COM", CENTER, 42);
  myGLCD.update();
  //-------------------------------------------------------------------------
  //Serial.begin(9600);
  delay(500); 
  //-------------------------------------------------------------------------
  InitGPS(&Serial,9600,8);
  //-------------------------------------------------------------------------
  myGLCD.setFont(SmallFont);
  myGLCD.clrScr();
  myGLCD.print("HardwareSerial", CENTER, 10); 
  myGLCD.print("Read Start", CENTER, 24); 
  myGLCD.update();
  delay(500); 
  //-------------------------------------------------------------------------
}

void loop() 
{
  //-------------------------------------------------------------------------
  NoowTime = millis();
  //-------------------------------------------------------------------------
  myGPS.Read();
  //-------------------------------------------------------------------------
  if( NoowTime - ShowTime > ShowTimeKey){ 
    ShowTime = NoowTime;
    GpsLCDShow();
  }
  //-------------------------------------------------------------------------
}

char str[20];
void GpsLCDShow(){
  //-------------------------------------------------------------------------
  myGLCD.clrScr();
  myGLCD.setFont(SmallFont);
  //-------------------------------------------------------------------------
  String tDate = String( String(myGPS.YY,DEC) + "/" + String(myGPS.MT,DEC) + "/" + String(myGPS.DD,DEC) );
  tDate = String( String(myGPS.MT,DEC) + "/" + String(myGPS.DD,DEC) );
  String tTime = String( String(myGPS.HH,DEC) + ":" + String(myGPS.MM,DEC) + ":" + String(myGPS.SC,DEC) );
  dtostrf(myGPS.WW,3,6,str); 
  String tLats = str; 
  dtostrf(myGPS.JJ,3,6,str); 
  String tLons = str; 
  dtostrf(myGPS.VV,4,2,str); 
  String tVels = str; 
  dtostrf(myGPS.FF,4,2,str); 
  String tFans = str; 
  String tKeys = "V"; 
  if(myGPS.KK){ 
    tKeys = "A"; 
  }
  //-------------------------------------------------------------------------
  myGLCD.print(tDate, 0,  0);  
  myGLCD.print(tTime, 36,  0);
  myGLCD.print("W:",  0,  9);  
  myGLCD.print(tLats, 18,  9);
  myGLCD.print("J:",  0, 18);  
  myGLCD.print(tLons, 18, 18);
  myGLCD.print(tKeys+":",  0, 27);  
  myGLCD.print(tVels, 18, 27);
  myGLCD.print("F:",  0, 36);  
  myGLCD.print(tFans, 18, 36);
  //-------------------------------------------------------------------------
  //myGLCD.print(myGPS.charGPRMC,  0, 36);  
  //-------------------------------------------------------------------------
  myGLCD.update();
  //-------------------------------------------------------------------------
}

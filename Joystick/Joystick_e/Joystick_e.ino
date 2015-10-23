//====================================
#include <SoftwareSerial.h>
SoftwareSerial myCmds(10, 11); // RX, TX
//====================================
#include "Timer.h"
Timer t;
int tickEvent = 0;
int timeEvent = 200;
//====================================
int PinAX = A0,PinAY = A1,PinAK = 12;
int PinBX = A2,PinBY = A3,PinBK = 13;
int PinCX = A6,PinCY = A7,PinCK = A4;
//====================================
int IntAX = 0,IntAY = 0,IntAK = 0;
int IntBX = 0,IntBY = 0,IntBK = 0;
int IntCX = 0,IntCY = 0,IntCK = 0;
//====================================
String strCMD = String("$JML,CAR,SAN,A,B,C,4,5,6,7,8,9,10,11,12;");
//====================================
void setup()
{
  //-------------------------------------------- 
  Serial.begin(9600);
  myCmds.begin(9600);
  //-------------------------------------------- 
  pinMode(PinAX, INPUT);
  pinMode(PinAY, INPUT);
  pinMode(PinAK, INPUT);
  pinMode(PinBX, INPUT);
  pinMode(PinBY, INPUT);
  pinMode(PinBK, INPUT);
  //pinMode(PinCX, INPUT);
  //pinMode(PinCY, INPUT);
  //pinMode(PinCK, INPUT);
  //-------------------------------------------- 
  tickEvent = t.every(timeEvent, CmdShow);
  //-------------------------------------------- 
  CmdShow();
  //-------------------------------------------- 
}

void loop(){
  readRun();
  //readShow();
  //CmdShow();
  t.update();
}

void readRun(){
  //-------------------------------------------- 
  IntAX = readAxis(PinAX);
  IntAY = readAxis(PinAY);
  IntAK = readDigital(PinAK);
  //-------------------------------------------- 
  IntBX = readAxis(PinBX);
  IntBY = readAxis(PinBY);
  IntBK = readDigital(PinBK);
  //-------------------------------------------- 
  //IntCX = readAxis(PinCX);
  //IntCY = readAxis(PinCY);
  //IntCK = readAxis(PinCK);
  //-------------------------------------------- 
}

void readShow(){
  //-------------------------------------------- 
  Serial.print(IntAX, DEC);  
  Serial.print(" "); 
  Serial.print(IntAY, DEC);  
  Serial.print(" "); 
  Serial.print(IntAK, DEC);  
  Serial.print(" "); 
  Serial.print(IntBX, DEC);  
  Serial.print(" "); 
  Serial.print(IntBY, DEC);  
  Serial.print(" "); 
  Serial.print(IntBK, DEC);  
  Serial.print(" "); 
  Serial.print(IntCX, DEC);  
  Serial.print(" "); 
  Serial.print(IntCY, DEC);  
  Serial.print(" "); 
  Serial.print(IntCK, DEC);  
  Serial.print(" "); 
  Serial.println(""); 
  //-------------------------------------------- 
}

void CmdShow(){
  //-------------------------------------------- 
  strCMD  = String("$JML,CAR,SAN,");
  strCMD += String(IntAX) + String(",");
  strCMD += String(IntAY) + String(",");
  strCMD += String(IntAK) + String(",");
  strCMD += String(IntBX) + String(",");
  strCMD += String(IntBY) + String(",");
  strCMD += String(IntBK) + String(",");
  strCMD += String(IntCX) + String(",");
  strCMD += String(IntCY) + String(",");
  strCMD += String(IntCK) + String(";");
  Serial.println(strCMD);
  myCmds.println(strCMD);
  //--------------------------------------------  
}





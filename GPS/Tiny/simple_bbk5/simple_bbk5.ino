#include <SoftwareSerial.h>
#include <TinyGPS++.h>
//-------------------------------------------------------------------------
#include <LCD5110_Graph.h>
LCD5110 myGLCD(3,4,5,6,7);
//-------------------------------------------------------------------------
extern uint8_t SmallFont[];
extern unsigned char TinyFont[];
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
TinyGPSPlus gps;
SoftwareSerial	GpsSerial(10, 13); // RX, TX
//-------------------------------------------------------------------------
SoftwareSerial	gsm(11, 12); // RX, TX
//-------------------------------------------------------------------------
static bool feedgps();
static void TinyGpsShow();
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
  Serial.begin(115200);
  GpsSerial.begin(4800);
  //-------------------------------------------------------------------------
  TinyGpsShow();
  //-------------------------------------------------------------------------
}
//-------------------------------------------------------------------------
unsigned long NoowTime = 0;
unsigned long ShowTime = 0;
int ShowTimeKey = 500;//5s
//-------------------------------------------------------------------------
void loop() 
{
  //-------------------------------------------------------------------------
  NoowTime = millis();
  //-------------------------------------------------------------------------
  feedgps();
  //-------------------------------------------------------------------------
  if( NoowTime - ShowTime > ShowTimeKey){ 
    ShowTime = NoowTime;
    //-------------------------------------------------------------------------
    GpsValueRun();
    GpsLCDShow();
    SerialShow();
    //-------------------------------------------------------------------------
  }
  //-------------------------------------------------------------------------
}


//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
int YY,MD,DD,HT,MT,ST;
float WW,JJ,HH,VV,FX;
int SN,SR;
bool KK;
char KT;
String sDate,tDate,sTime;//YMDHMS
String sLats,sLons,sHigh,sSped,sFans;//WJHVF
String cLock,cType,sGpsn,sRads,sSeal;//KK;KT;SN;SR;HZ;
//-------------------------------------------------------------------------
char sz[32];
char str[20];
void GpsValueRun(){
  //-------------------------------------------------------------------------
  KK = gps.fixhave;
  //-------------------------------------------------------------------------
  YY = gps.date.year();
  MD = gps.date.month();
  DD = gps.date.day();
  HT = gps.time.hour();
  MT = gps.time.minute();
  ST = gps.time.second();
  HT = HT + 8;
  if( HT > 23 ){
    HT = HT - 24;
    DD = DD + 1;
  }
  //-------------------------------------------------------------------------
  WW = gps.location.lat();
  JJ = gps.location.lng(); 
  //-------------------------------------------------------------------------
  HH = gps.altitude.meters();
  FX = gps.course.deg();
  VV = gps.speed.kmph();
  SN = gps.satellites.value();
  SR = gps.hdop.value();
  //-------------------------------------------------------------------------
  dtostrf(KK,1,0,str);   cLock = str;
  dtostrf(KT,2,0,str);   cType = str;
  //-------------------------------------------------------------------------
  sDate = String( String(MD,DEC) + "/" + String(DD,DEC) );
  sTime = String( String(HT,DEC) + ":" + String(MT,DEC) + ":" + String(ST,DEC) );
  tDate = String( String(YY,DEC) + "/" + sDate + " " + sTime );
  //-------------------------------------------------------------------------
  dtostrf(WW,3,6,str);  sLats = str;
  dtostrf(JJ,3,6,str);  sLons = str;
  dtostrf(HH,4,0,str);  sHigh = str;
  dtostrf(VV,3,1,str);  sSped = str;
  dtostrf(FX,3,1,str);  sFans = str;
  dtostrf(SN,2,0,str);  sGpsn = str;
  dtostrf(SR,3,0,str);  sRads = str;
  //-------------------------------------------------------------------------
}

void SerialShow(){
  //---------------------------------------------------
  Serial.println("----");
  //-------------------------
  Serial.println(tDate);
  Serial.println(sLats);
  Serial.println(sLons);
  //-------------------------
  Serial.print(sHigh);
  Serial.print(" ");
  Serial.print(sSped);
  Serial.print(" ");
  Serial.print(sFans);
  Serial.println();
  //-------------------------
  Serial.print(cLock);
  Serial.print(" ");
  Serial.print(cType);
  Serial.print(" ");
  Serial.print(sGpsn);
  Serial.print(" ");
  Serial.print(sRads);
  Serial.print(" ");
  Serial.print(sSeal);
  Serial.println();
  //---------------------------------------------------
}

void GpsLCDShow(){
  //-------------------------------------------------------------------------
  myGLCD.clrScr();
  myGLCD.setFont(SmallFont);
  //-------------------------------------------------------------------------
  myGLCD.print(sDate,0,  0);
  myGLCD.print(sTime,36,  0);
  //------------------------------------------------
  myGLCD.print("W",  0,  9);  
  myGLCD.print(sLats, 18,  9);  
  myGLCD.print("J",  0, 18);  
  myGLCD.print(sLons, 12, 18);
  //------------------------------------------------
  myGLCD.print("H", 0, 27);  
  myGLCD.print(sHigh, 8, 27);
  myGLCD.print("S", 46, 27); 
  myGLCD.print(sGpsn, 52, 27);  
  myGLCD.print(sRads, 66, 27);   
  ////------------------------------------------------
  myGLCD.print("V",  0, 36); 
  myGLCD.print(sSped,  8, 36); 
  myGLCD.print(cLock,  34, 36); 
  myGLCD.print(cType,  40, 36); 
  myGLCD.print("F",  46, 36); 
  myGLCD.print(sFans, 54, 36);
  //-------------------------------------------------------------------------
  //myGLCD.print(myGPS.charGPRMC,  0, 36);  
  //-------------------------------------------------------------------------
  myGLCD.update();
  //-------------------------------------------------------------------------
}


static bool feedgps()
{
  while (GpsSerial.available())
  {
    if (gps.encode(GpsSerial.read()))
      return true;
  }
  return false;
}

static void TinyGpsShow()
{
  //-------------------------------------------------------------------------
  Serial.print("Testing TinyGPSPlus library v. "); 
  Serial.println(TinyGPSPlus::libraryVersion());
  Serial.println("by Mikal Hart");
  Serial.println();
  //-------------------------------------------------------------------------
}

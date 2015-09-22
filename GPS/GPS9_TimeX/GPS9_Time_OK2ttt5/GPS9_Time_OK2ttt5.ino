//-------------------------------------------------------------------------
//#include <SoftwareSerial.h>
//SoftwareSerial mySerial(10, 11); // RX, TX
//-------------------------------------------------------------------------
#include <LCD5110_Graph.h>
LCD5110 myGLCD(3,4,5,6,7);
//-------------------------------------------------------------------------
extern uint8_t SmallFont[];
extern unsigned char TinyFont[];
//-------------------------------------------------------------------------



//-------------------------------------------------------------------------
int TimeZone = 8;
//-------------------------------------------------------------------------
class GPS{
public:
  int TimeZone;
  int YY,MT,DD,HH,MM,SC,MS;
  char key;
  float lat,lon,hit,vel,age;
};
//-------------------------------------------------------------------------
GPS myGps;
//-------------------------------------------------------------------------
long LoopTime;
long LoopTimeX;
int ledState = 0;
//-------------------------------------------------------------------------


//-------------------------------------------------------------------------
static unsigned char second,minute,hour;
unsigned long t = millis(); 
//-------------------------------------------------------------------------

void setup() 
{
  //-------------------------------------------------------------------------
  myGLCD.InitLCD(60);
  //-------------------------------------------------------------------------
  myGLCD.setFont(SmallFont);
  myGLCD.clrScr();
  myGLCD.print("GPS Read Start", CENTER, 14); 
  myGLCD.setFont(TinyFont);
  myGLCD.print("(C)2013 by", CENTER, 36);
  myGLCD.print("BOBOKing.COM", CENTER, 42);
  myGLCD.update();
  //-------------------------------------------------------------------------
  Serial.begin(9600);
  delay(500); 
  //-------------------------------------------------------------------------
  GpsInt(TimeZone,&Serial);
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
  GpsRead();  
  //-------------------------------------------------------------------------
  LoopTime++;
  if(LoopTime>12000){ 
    //GpsSerialShow();
    GpsLCDShow();
    LoopTime=0;
  }
  //-------------------------------------------------------------------------
}

char str[12];
void GpsLCDShow(){
  //-------------------------------------------------------------------------
  myGLCD.clrScr();
  myGLCD.setFont(SmallFont);
  //-------------------------------------------------------------------------
  String tDate = String( String(myGps.YY,DEC) + "/" + String(myGps.MT,DEC) + "/" + String(myGps.DD,DEC) );
  String tTime = String( String(myGps.HH,DEC) + ":" + String(myGps.MM,DEC) + ":" + String(myGps.SC,DEC) );
  dtostrf(myGps.lat,3,6,str); String tLats = str; 
  dtostrf(myGps.lon,3,6,str); String tLons = str; 
  //-------------------------------------------------------------------------
  String tKeys = String( myGps.key + String(" ") );
  dtostrf(myGps.vel,4,2,str); String tVels = str; 
  dtostrf(myGps.age,4,1,str); String tFans = str; 
  //-------------------------------------------------------------------------
  myGLCD.print(tDate, 0, 0);
  myGLCD.print(tTime, 0, 9);
  myGLCD.print(tLats, 0, 18); 
  myGLCD.print(tLons, 0, 27);
  myGLCD.print(tKeys, 0, 36);
  myGLCD.print(tVels, 10, 36);
  myGLCD.print(tFans, 40, 36);
  //-------------------------------------------------------------------------
  myGLCD.update();
  //-------------------------------------------------------------------------
}

void GpsSerialShow()
{
  //-------------------------------------------------------------------------
  Serial.print(myGps.YY); 
  Serial.print("/");
  Serial.print(myGps.MT); 
  Serial.print("/");
  Serial.print(myGps.DD); 
  Serial.print(" ");
  Serial.print(myGps.HH); 
  Serial.print(":");
  Serial.print(myGps.MM); 
  Serial.print(":");
  Serial.print(myGps.SC); 
  Serial.print(".");
  Serial.print(myGps.MS); 
  Serial.print(" ");
  //-------------------------------------------------------------------------
  Serial.print(myGps.key); 
  Serial.print(" ");
  //-------------------------------------------------------------------------
  Serial.print(myGps.lat,5); 
  Serial.print(","); 
  Serial.print(myGps.lon,5); 
  Serial.print(" ");
  //-------------------------------------------------------------------------
  Serial.print(myGps.vel); 
  Serial.print(",");
  Serial.print(myGps.age); 
  Serial.println();
  //-------------------------------------------------------------------------
}

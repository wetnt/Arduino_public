#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <LCD5110_Graph.h>
//-------------------------------------------
SoftwareSerial	GpsSerial(10,13); // RX, TX
SoftwareSerial	mySerial(11,12);
LCD5110 myGLCD(3,4,5,6,7);
TinyGPSPlus gps;
//-------------------------------------------
static bool feedgps();
static void TinyGpsShow();
extern uint8_t SmallFont[];
//-------------------------------------------
String myurl ="http://www.boboking.com/v/g.php?n=boboking&p=123xjp&g=38,112,50,46,80,99,1245678900000";
//-------------------------------------------

void setup() 
{
  //-----------------------------------------
  Serial.begin(115200);
  mySerial.begin(9600);
  GpsSerial.begin(4800);
  delay(1000);
  //-----------------------------------------
  Serial.println("BBK_GPS_GPRS");
  LcdIntShow();
  //-----------------------------------------
}
//-------------------------------------------
unsigned long NoowTime = 0;
unsigned long ShowTime = 0;
int ShowTimeKey = 1000;//5s
//-------------------------------------------
void loop() 
{
  //-----------------------------------------
  NoowTime = millis();
  //-----------------------------------------
  feedgps();
  //-----------------------------------------
  if( NoowTime - ShowTime > ShowTimeKey){ 
    ShowTime = NoowTime;
    //---------------------------------------
    Serial.println(NoowTime);
    GpsValueRun();
    //GpsLCDShow();
    //SerialShow();
    //SubmitHttpRequest(myurl,10);
    //---------------------------------------
  }
  //-----------------------------------------
}

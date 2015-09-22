#include <Time.h> 
#include <SoftwareSerial.h>
#include <LCD5110_Graph.h>
#include <TinyGPS++.h>
//-------------------------------------------------------------------------
LCD5110 myGLCD(3,4,5,6,7);
extern uint8_t SmallFont[];
//-------------------------------------------------------------------------
TinyGPSPlus gps;
time_t mytime = 0; 
SoftwareSerial	GpsSerial(10,13); // RX, TX(10, 13)
//-------------------------------------------------------------------------
char URL[120];
char UseH[] = "http://www.boboking.com/v/g.php?n=boboking&p=123xjp&g=";
//-------------------------------------------------------------------------

void setup() 
{
  //-------------------------------------------------------------------------
  myGLCD.InitLCD(50);  BBKLCDShow();  delay(500); 
  //-------------------------------------------------------------------------
  GpsSerial.begin(4800);  delay(500);  BBKLCDShowString("Gps Working!");
  //-------------------------------------------------------------------------
  Serial.begin(115200);    delay(500);  BBKLCDShowString("Serial Working!");
  BBKLCDShowString("HttpInt IsRun!");    delay(500);
  SubmitHttpInt(); 
  BBKLCDShowString("HttpInt IsOK!");  delay(500);
  //-------------------------------------------------------------------------
}

//-------------------------------------------------------------------------
void loop() 
{
  //-------------------------------------------------------------------------
  feedgps();
  GPSloop();
  //GSMloop();
  //-------------------------------------------------------------------------
}
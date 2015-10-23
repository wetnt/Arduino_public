//===================================================================
#include <SoftwareSerial.h>
//===================================================================
#include <Time.h>
#include <stdio.h>
#include <TinyGPS++.h>
//===================================================================
static const int GPSBaud = 9600;
//#define  gps  Serial2
SoftwareSerial gps(10, 11);//TX,RX
TinyGPSPlus gt;
//===================================================================
void GPS_setup() {
  gps.begin(GPSBaud);
  lgln(F("gps.Serial.start!"));
}
//===================================================================
void GPS_loop() {
  gpsFeed();
}
void GPS_work() {
  //GpsValueSet(gt, 8);
  //GpsStringSet();
  //GpsLineShow();
}
//===================================================================
static void gpsFeed()
{
  //-------------------------------
  gps.listen();
  while (gps.available()) {
    char c = gps.read();
    gt.encode(c);
    //lgs.write(c);
  }
  //-------------------------------
}
//===================================================================

//------------------------------------------
#include <Time.h>
#include <TinyGPS++.h>
#include <stdio.h>
//------------------------------------------
static const long LGSBaud = 115200;
static const int TSTBaud = 9600;
static const int GPSBaud = 9600;
static const int GSMBaud = 9600;
//------------------------------------------
TinyGPSPlus gt;
//------------------------------------------
#define PHONE_NUMBER  "13911969356"
//------------------------------------------
#define  lgs	Serial
#define  tst	Serial1
#define  gps	Serial2
#define  gsm	Serial3
//-------------------------------------------------------------------------


void setup() {
  //------------------------------------------
  lgln("--------------------------------");
  lgs.begin(LGSBaud); lgln(F("Log.Serial.start!"));
  tst.begin(TSTBaud); lgln(F("tst.Serial.start!"));
  gps.begin(GPSBaud); lgln(F("gps.Serial.start!"));
  gsm.begin(GSMBaud); lgln(F("gsm.Serial.start!"));
  //------------------------------------------
  GprsOpenTest();
  //------------------------------------------
}

void gsmStart() {
  //------------------------------------------
  lgln(F("GSM-Serial3.starting..."));
  pinMode(5, OUTPUT);  smartDelay(1000);
  digitalWrite(5, LOW);  smartDelay(4000);
  digitalWrite(5, HIGH); smartDelay(4000);
  lgln(F("GSM-Serial3.started!"));
  //------------------------------------------
}

void loop() {
  //------------------------------------------
  GpsSetValue();
  GpsLineShow();
  //------------------------------------------
  GprsRun();
  //------------------------------------------
  smartDelay(1000);
  //------------------------------------------
}


static void smartDelay(unsigned long ms)
{
  //------------------------------------------
  unsigned long start = millis();
  do {
    //-------------------------------
    gpsLoop();
    //-------------------------------
    while (lgs.available()) {
      gsm.write(lgs.read());
    }
    while (gsm.available()) {
      char c = gsm.read();
      //lgs.write(c);
      RingCheck(c);
    }
    //-------------------------------
  } while (millis() - start < ms);
  //------------------------------------------
}

static void gpsLoop()
{
  //-------------------------------
  while (gps.available()) {
    char c = gps.read();
    gt.encode(c);
    //lgs.write(c);
  }
  //-------------------------------
}

//------------------------------------------
#include <GPRS_Shield_Arduino.h>
#include <sim900_Suli.h>
#include <Suli.h>
//------------------------------------------
#include <Time.h>
#include <TinyGPS++.h>
//------------------------------------------
#include <SoftwareSerial.h>
static const int GPSBaud = 9600;
//static const int RXPin = 15, TXPin = 14;
//SoftwareSerial ss(RXPin, TXPin);
//------------------------------------------
TinyGPSPlus gt;
//------------------------------------------
#define PHONE_NUMBER  "13911969356"
//------------------------------------------
//#define PIN_TX    16
//#define PIN_RX    17
//#define BAUDRATE  9600
//GPRS gprsTest(PIN_TX, PIN_RX, BAUDRATE); //RX,TX,PWR,BaudRate
//------------------------------------------
#define  lgs	Serial
#define  tst	Serial1
#define  gps	Serial2
#define  gsm	Serial3
//-------------------------------------------------------------------------

void setup() {
  //------------------------------------------
  lgs.begin(115200); lgln(F("Log.Serial.start!"));
  //------------------------------------------
  tst.begin(GPSBaud);
  gps.begin(GPSBaud);
  gsm.begin(GPSBaud);
  //------------------------------------------
  gsmStart();
  SubmitHttpInt();
  //------------------------------------------
}

void gsmStart() {
  //------------------------------------------
  pinMode(5, OUTPUT);  delay(1000);
  digitalWrite(5, LOW);  delay(2000);
  digitalWrite(5, HIGH);
  lgln(F("GSM-Serial3.start!"));
  //------------------------------------------
}

void loop() {
  //------------------------------------------
  GpsSetValue();
  GpsLineShow();
  //------------------------------------------
  //SubmitHttpRequest(5);
  smartDelay(10000);
  //------------------------------------------
}


static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do {
    //-------------------------------
    while (gps.available()) {
      char c = gps.read();
      gt.encode(c);
      //lgs.write(c);
    }
    //-------------------------------
    while (lgs.available()) {
      gsm.write(lgs.read());
    }
    while (gsm.available()) {
      lgs.write(gsm.read());
    }
    //-------------------------------
  } while (millis() - start < ms);
}

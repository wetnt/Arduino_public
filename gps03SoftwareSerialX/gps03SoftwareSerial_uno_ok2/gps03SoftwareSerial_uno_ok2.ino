#include <Time.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

TinyGPSPlus gps;
SoftwareSerial myGps(10, 11);//RX,TX

void setup()
{
  Serial.begin(4800);
  while (!Serial) {}
  myGps.begin(9600);
  //Serial.println("gps03SoftwareSerial_uno_ok");
}




//-------------------------------------------------------------------------
void loop() 
{
  //-------------------------------------------------------------------------
  SerialRead();
  GpsRead();
  GpsShow();
  GetShow2();
  //-------------------------------------------------------------------------
}

static bool SerialRead()
{
  //-------------------------------------------------------------------------
  while (myGps.available()>0)
  {
    char c = myGps.read();
    SerialExp(c);    
  }
  return true;
  //-------------------------------------------------------------------------
}

static bool GpsRead()
{
  //-------------------------------------------------------------------------
  while (Serial.available())
  {
    if (gps.encode(Serial.read()))
      return true;
  }
  return false;
  //-------------------------------------------------------------------------
}

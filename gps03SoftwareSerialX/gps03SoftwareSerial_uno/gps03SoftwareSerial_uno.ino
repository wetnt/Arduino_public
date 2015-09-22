#include <Time.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;
SoftwareSerial myGps(10, 11); // RX, TX

void setup()
{
  Serial.begin(GPSBaud);
  while (!Serial) {}
  myGps.begin(4800);
  Serial.println("gps02");
  Serial.println();
}




//-------------------------------------------------------------------------
void loop() 
{
  //-------------------------------------------------------------------------
  SerialRead();
  GpsRead();
  GpsShow();
  //GSMloop();
  //StrReport();
  GetShow2();
  //-------------------------------------------------------------------------
}

static bool SerialRead()
{
  //-------------------------------------------------------------------------
  while (Serial.available())
  {
    char inChar = Serial.read();
    SerialExp(inChar);
  }
  //-------------------------------------------------------------------------
}

static bool GpsRead()
{
  //-------------------------------------------------------------------------
  while (myGps.available())
  {
    if (gps.encode(myGps.read()))
      return true;
  }
  return false;
  //-------------------------------------------------------------------------
}

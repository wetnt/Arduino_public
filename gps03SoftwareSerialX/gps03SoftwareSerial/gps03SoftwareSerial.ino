#include <Time.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;
SoftwareSerial myGps(10, 11); // RX, TX

void setup()
{
  Serial.begin(115200);
  Serial1.begin(GPSBaud);
  myGps.begin(GPSBaud);
  Serial.println(F("gps02"));
  Serial.println();
}




//-------------------------------------------------------------------------
void loop() 
{
  //-------------------------------------------------------------------------
  GpsRead();
  GpsShow();
  //GSMloop();
  //StrReport();
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

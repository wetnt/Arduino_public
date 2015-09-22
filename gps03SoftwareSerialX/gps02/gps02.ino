#include <Time.h>
#include <TinyGPS++.h>

static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;


void setup()
{
  Serial.begin(115200);
  Serial1.begin(GPSBaud);
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
  while (Serial1.available())
  {
    if (gps.encode(Serial1.read()))
      return true;
  }
  return false;
  //-------------------------------------------------------------------------
}

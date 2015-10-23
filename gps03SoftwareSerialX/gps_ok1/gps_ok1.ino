#include <Time.h>
#include <TinyGPS++.h>
#include <dht.h>

TinyGPSPlus gps;

void setup()
{
  Serial.begin(9600);
  while (!Serial) {}
  Serial.println("gps_mini_ok");
}




//-------------------------------------------------------------------------
void loop() 
{
  //-------------------------------------------------------------------------
  GpsRead();
  GpsSetValue();
  //-------------------------------------------------------------------------
  GpsCheck();
  GpsReport();
  //-------------------------------------------------------------------------
}


void GpsRead()
{
  //-------------------------------------------------------------------------
  while (Serial.available())
  {
    gps.encode(Serial.read());
  }
  //-------------------------------------------------------------------------
}

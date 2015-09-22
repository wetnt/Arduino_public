#include <Time.h>
#include <TinyGPS++.h>

TinyGPSPlus gps;

void setup()
{
  Serial.begin(115200);
  Serial1.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(9600);
  while (!Serial) {}
  while (!Serial1) {}
  while (!Serial2) {}
  Serial.println("gps03SoftwareSerial_uno_ok3");
}




//-------------------------------------------------------------------------
void loop() 
{
  //-------------------------------------------------------------------------
  SerialRead();
  GpsRead();
  GpsSetValue();
  //-------------------------------------------------------------------------
  GpsSetValue();
  GpsReport();
  //-------------------------------------------------------------------------
}

void SerialRead()
{
  //-------------------------------------------------------------------------
  while (Serial3.available()>0)
  {
    SerialExp(Serial3.read());    
  }
  //-------------------------------------------------------------------------
}

void GpsRead()
{
  //-------------------------------------------------------------------------
  while (Serial2.available())
  {
    gps.encode(Serial2.read());
  }
  //-------------------------------------------------------------------------
}

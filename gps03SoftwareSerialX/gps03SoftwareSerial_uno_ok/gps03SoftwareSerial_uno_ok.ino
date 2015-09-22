#include <Time.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

TinyGPSPlus gps;
SoftwareSerial myGps(10, 11);//RX,TX
static const uint32_t GPSBaud = 9600;

void setup()
{
  Serial.begin(GPSBaud);
  while (!Serial) {}
  myGps.begin(4800);
  Serial.println("gps03SoftwareSerial_uno_ok");
}




//-------------------------------------------------------------------------
void loop() 
{
  //-------------------------------------------------------------------------
  SerialRead();
  //GpsRead();
  //GpsShow();
  GetShow2();
  //-------------------------------------------------------------------------
}

static bool SerialRead()
{
  //-------------------------------------------------------------------------
  while (Serial.available())
  {
    char cc = Serial.read();
    SerialExp(cc);
    Serial.print(cc);
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

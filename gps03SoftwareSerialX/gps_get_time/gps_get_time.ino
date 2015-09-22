#include <Time.h>
#include <SoftwareSerial.h>

static const uint32_t GPSBaud = 9600;
SoftwareSerial myGps(10, 11); // RX, TX

void setup()
{
  Serial.begin(GPSBaud);
  while (!Serial) {
  }
  myGps.begin(GPSBaud);
  TubeSetup();
}

//-------------------------------------------------------------------------
void loop() 
{
  //-------------------------------------------------------------------------
  SerialRead();
  TubeLoop();
  //-------------------------------------------------------------------------
}
static bool SerialRead()
{
  //-------------------------------------------------------------------------
  while (myGps.available())
  {
    char inChar = myGps.read();
    Serial.print(inChar);
    SerialExp(inChar);
  }
  //-------------------------------------------------------------------------
}

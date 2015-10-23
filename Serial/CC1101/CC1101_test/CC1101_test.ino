static const uint32_t GPSBaud = 9600;
#include <SoftwareSerial.h>
SoftwareSerial myGps(10, 11); // RX, TX

void setup()
{
  Serial.begin(GPSBaud);
  while (!Serial) {
  }
  myGps.begin(GPSBaud);
}

//-------------------------------------------------------------------------
void loop() 
{
  //-------------------------------------------------------------------------
  SerialRead();
  //-------------------------------------------------------------------------
}
static bool SerialRead()
{
  //-------------------------------------------------------------------------
  while (myGps.available())
  {
    char inChar = myGps.read();
    Serial.print(inChar);
  }
  //-------------------------------------------------------------------------
}

#include <Time.h>
static const uint32_t GPSBaud = 9600;

void setup()
{
  Serial.begin(GPSBaud);
  while (!Serial) {
  }
  Serial1.begin(GPSBaud);
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
  while (Serial1.available())
  {
    char inChar = Serial1.read();
    Serial.print(inChar);
    SerialExp(inChar);
  }
  //-------------------------------------------------------------------------
}

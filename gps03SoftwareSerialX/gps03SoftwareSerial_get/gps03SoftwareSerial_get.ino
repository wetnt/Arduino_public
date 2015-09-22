#include <Time.h>

static const uint32_t GPSBaud = 9600;

void setup()
{
  Serial.begin(GPSBaud);
  while (!Serial) {
  }
  Serial.println("gps_exp");
  Serial.println();
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
  while (Serial.available())
  {
    int inChar = Serial.read();
    SerialExp(inChar);
  }
  //-------------------------------------------------------------------------
}

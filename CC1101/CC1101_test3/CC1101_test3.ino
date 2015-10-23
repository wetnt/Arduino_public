#include <SoftwareSerial.h>
SoftwareSerial myGps(10, 11); // RX, TX

void setup()
{
  Serial.begin(9600);
  while (!Serial) {}
  myGps.begin(9600);
  Serial.println("gps03SoftwareSerial_uno_ok");
}




//-------------------------------------------------------------------------
void loop() 
{
  //-------------------------------------------------------------------------
  SerialRead();
  GetShow2();
  //-------------------------------------------------------------------------
}

static bool SerialRead()
{
  //-------------------------------------------------------------------------
  while (myGps.available())
  {
    char cc = myGps.read();
    Serial.print(cc);
    SerialExp(cc);
  }
  //-------------------------------------------------------------------------
}

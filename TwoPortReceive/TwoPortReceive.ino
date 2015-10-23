/*
 The circuit:
 * First serial device's TX attached to digital pin 2, RX to pin 3
 * Second serial device's TX attached to digital pin 4, RX to pin 5

 Note: so only the following can be used for RX:
 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69
 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).
 */

#include <SoftwareSerial.h>
SoftwareSerial portOne(10, 11);//TXd10/RXd11
SoftwareSerial portTwo(8, 9);

void setup()
{
  Serial.begin(9600);
  while (!Serial) {;}
  portOne.begin(9600);
  portTwo.begin(9600);
}

void loop()
{
  portOne.listen();
  Serial.println("Data from port one:");
  while (portOne.available() > 0) {
    char inByte = portOne.read();
    Serial.write(inByte);
  }
  Serial.println();

  portTwo.listen();
  Serial.println("Data from port two:");
  while (portTwo.available() > 0) {
    char inByte = portTwo.read();
    Serial.write(inByte);
  }
  Serial.println();
}







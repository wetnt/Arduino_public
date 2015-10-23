#include <SoftwareSerial.h>
SoftwareSerial gpsTR(11, 10); //TX,RX
static const int GPSBaud = 9600;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(GPSBaud);
  gpsTR.begin(GPSBaud);
}

void loop() {
  //-------------------------------
  gpsTR.listen();
  while (gpsTR.available()) {
    char c = gpsTR.read();
    Serial.write(c);
  }
  //-------------------------------

}

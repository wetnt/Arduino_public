#include <SoftwareSerial.h>
SoftwareSerial gpsTR(10, 11); //RX,TX
void setup() {
  Serial.begin(9600);
  gpsTR.begin(9600);
  Serial.println("abcde");
}

void loop() {
  //Serial.println("abcde");
  //-------------------------------
  //gpsTR.listen();
  while (gpsTR.available()) {
    char c = gpsTR.read();
    Serial.write(c);
  }
  //-------------------------------

}

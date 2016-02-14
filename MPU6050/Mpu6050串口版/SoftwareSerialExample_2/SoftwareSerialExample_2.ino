#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX
void setup()
{
  
  pinMode(13, INPUT);
  pinMode(A0, INPUT);
  pinMode(12, INPUT);
  pinMode(9, INPUT);
  
  Serial.begin(115200);
  while (!Serial) {; }
  Serial.println("Goodnight moon!");
  mySerial.begin(115200);
  //mySerial.println("Hello, world?");
}

void loop() // run over and over
{
  if (mySerial.available())
    Serial.write(mySerial.read());
  if (Serial.available())
    mySerial.write(Serial.read());
}


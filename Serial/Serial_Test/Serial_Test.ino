#include <Wire.h>
#include <I2Cdev.h>
#include <SoftwareSerial.h>
#include <MPU6050.h>

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  digitalWrite(13, HIGH);  Serial.println("HIGH");  delay(1000);
  digitalWrite(13, LOW);   Serial.println("LOW");   delay(1000);
}

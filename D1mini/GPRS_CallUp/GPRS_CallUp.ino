#include <GPRS_Shield_Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <Suli.h>

#define PIN_TX    D4
#define PIN_RX    D3
#define BAUDRATE  9600
#define PHONE_NUMBER  "13911969356"

GPRS gprsTest(PIN_TX,PIN_RX,BAUDRATE);//RX,TX,PWR,BaudRate

void setup() {
  Serial.begin(9600);
  while(0 != gprsTest.init()) { //gprs init
      delay(1000);
      Serial.print("init error\r\n");
  }
  Serial.println("gprs init success");
  Serial.println("start to call ...");
  gprsTest.callUp(PHONE_NUMBER);
}

void loop() {
  //nothing to do
}

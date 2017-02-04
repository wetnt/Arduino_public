#include "ESP8266WiFi.h"

void setup() {
  lgsetup(F("WIFI SCAN 1001"));
  ss8266_init(F("SIM808"), 9600, true);
  smartDelay(100);
  Serial.println("Setup done");
}

void loop() {
  ss_feed();
  ss_write();
  //lgWrite();
  smartDelay(1000);
}
static void smartDelay(unsigned long ms) {
  unsigned long start = millis(); do {
    //------------------------------------------
    lgFeed();
    ss_feed();
    //------------------------------------------
  } while (millis() - start < ms);
}

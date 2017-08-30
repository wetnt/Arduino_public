#include <Arduino.h>
#include <ESP8266WiFi.h>

void setup() {
  lgsetup(F("WIFI SCAN 1001"));
  wifi_setup();
  tLoop_Setup();
}

void loop() {
  //------------------------------------------
  if (ts_loop(1)) {
  }
  //------------------------------------------
  if (ts_loop(10)) {
    lewei_post();
  }
  //------------------------------------------
}





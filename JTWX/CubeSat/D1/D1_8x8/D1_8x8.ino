#include <Arduino.h>
#include <ESP8266WiFi.h>

void setup() {
  lgsetup(F("WIFI SCAN 1001"));
  ws8x8_setup();
  tLoop_Setup();
}

void loop() {
  //------------------------------------------
  if (ts_loop(100)) {
    lgln("100");
    ws8x8_loop();
  }
  //------------------------------------------
  if (ts_loop(60)) {
    lgln("60");
  }
  //------------------------------------------
}



#include <Arduino.h>
#include <ESP8266WiFi.h>

void setup() {
  lgsetup(F("WIFI SCAN 1001"));
  wifi_setup();
  microduino_8x8_setup();
  tLoop_Setup();
}

void loop() {
  //------------------------------------------
  if (ts_loop(100)) {
    weather_loop();
  }
  if (ts_loop(1)) {
    bmp_int_loop();
  }
  //------------------------------------------
  if (ts_loop(60)) {
    wifi_loop();
    http_get();
    http_exp();
  }
  //------------------------------------------
}

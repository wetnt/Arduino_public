//https://wiki.wemos.cc/products:d1:d1_mini
//https://blog.csdn.net/happyjoey217/article/details/82786032
//http://arduino.esp8266.com/stable/package_esp8266com_index.json
//https://item.taobao.com/item.htm?spm=a1z09.2.0.0.6eee2e8dqomJFZ&id=531755241333&_u=rkdpei64d4


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

#include <Arduino.h>
#include <ESP8266WiFi.h>
static const String codeName = "PlanTowerG5_x_1!";
void setup() {
  //------------------------------------------------
  lgsetup(codeName);
  //------------------------------------------------
  ss_init(F("G5"),7,8,9600,true); //String name, int rx, int tx, long btl, boolean lgKey
  //------------------------------------------------
  //oled_setup();
  tLoop_Setup();
}
void loop() {
  ss_feed();
  if (ts_loop(100)) {
    //ws8x8_txt_loop();
  }
}
static void smartDelay(unsigned long ms) {
  unsigned long start = millis(); do {
    //------------------------------------------
    lgFeed(); ss_feed();
    //------------------------------------------
  } while (millis() - start < ms);
}

#include <Arduino.h>
#include <ESP8266WiFi.h>
static const String codeName = "PlanTowerG5_x_1!";
void setup() {
  //------------------------------------------------
  lgsetup(codeName);
  ss_init(F("G5"),7,8,9600,true); //String name, int rx, int tx, long btl, boolean lgKey
  tLoop_Setup();
}
void loop() {
  ss_feed();
}
static void smartDelay(unsigned long ms) {
  unsigned long start = millis(); do {
    //------------------------------------------
    lgFeed(); ss_feed();
    //------------------------------------------
  } while (millis() - start < ms);
}

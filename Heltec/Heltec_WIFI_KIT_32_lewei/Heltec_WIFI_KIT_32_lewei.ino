//--------------------------------------------------
#include <WiFi.h>
#include "BBK_TIME.h"
//--------------------------------------------------
void setup() {
  //--------------------------------------------------
  lgsetup("Heltec_WIFI_KIT_32") ;
  lgln("-----------------------------------");
  //--------------------------------------------------
  oled_setup();
  wifi_setup();
  BT_setup();
  tLoop_Setup();
  //--------------------------------------------------
}
void loop() {
  if (ts_loop(1)) {
    dt.addTimeSecond();
    WIFI_TIME_SHOW();
  }
  if (ts_loop(30)) {
    WIFI_Lewei_Report();
  }
  //smartDelay(20 * 1000);
}
//===============================================
static void smartDelay(unsigned long ms) {
  unsigned long start = millis(); do {
    //------------------------------------------
    //lgFeed(); wfs_loop(); Dog_Loop();
    //------------------------------------------
  } while (millis() - start < ms);
}
//===============================================

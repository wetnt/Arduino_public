//--------------------------------------------------
#include <WiFi.h>
//--------------------------------------------------
void setup() {
  //--------------------------------------------------
  lgsetup("Heltec_WIFI_KIT_32") ;
  lgln("-----------------------------------");
  //--------------------------------------------------
  oled_setup();
  wifi_setup();
  //--------------------------------------------------
}
void loop() {
  sdf();
  smartDelay(20 * 1000);
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
//===================================================================
#include "bIMU.h"
//===================================================================
static const String codeName = "bbk_gps_test!";
void setup() {
  //-------------------------------------
  Pin_setup();//必须首先执行，防止烧毁硬件
  //------------------------------------------------
  lgsetup(codeName);
  //------------------------------------------------
  MPU6050_setup();
  //------------------------------------------------
  //ss_init(String name, int rx, int tx, long btl, boolean lgKey);
  ss_init(F("GPS,170MHz"), 11, 10, 9600, false);
  //------------------------------------------------
}
void loop() {
  IMU_loop();
  smartDelay(20);
}
static void smartDelay(unsigned long ms) {
  unsigned long start = millis(); do {
    //------------------------------------------
    lgFeed(); ss_feed();
    //------------------------------------------
  } while (millis() - start < ms);
}


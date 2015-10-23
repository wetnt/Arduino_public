//===================================================================
#include <Time.h>//时间日期库
//===================================================================
void setup() {
  //-------------------------------------
  pinMode(13, OUTPUT);
  Log_setup();
  //-------------------------------------
  LCD5110_setup();
  GPS_setup();
  //-------------------------------------
  Timer_setup();
  //-------------------------------------
}
void loop() {
  //-------------------------------------
  GPS_Feed();
  Timer_loop();
  //-------------------------------------
}
//===================================================================

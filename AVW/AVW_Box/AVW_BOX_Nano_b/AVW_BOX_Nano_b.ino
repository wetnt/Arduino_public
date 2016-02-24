/*===================================================================
1.电量测量盒子
2.AcMeter_60A
3.
4.
5.
//=================================================================*/
//===================================================================
#include "Timer.h"//时间操作系统头文件 
Timer t;
//===================================================================
//#include <SoftwareSerial.h>
//SoftwareSerial gas(10, 11); // RX, TX
//static const long GasBaud = 9600;
//SoftwareSerial wfs(9, 8); // RX, TX
//static const long WfsBaud = 9600;
//===================================================================
void setup() {
  //------------------------------------------------
  lgsetup("AVW_BOX_Nano_b ...");
  //------------------------------------------------
  //------------------------------------------------
  LCD1602_setup(); LCD1602_Clear(); LCD1602_Show(0, 0, F("AVW_Nano_Start!"));
  //------------------------------------------------
  int tickEvent1 = t.every(500, LCD1602_loop_test);
  //int tickEvent5 = t.every(10000, Car_loop);//50ms
  //------------------------------------------------
  //int tickEvent2 = t.every(50, MPU6050_show);
  //int tickEvent9 = t.every(500, rc_info_send);
  //------------------------------------------------
}
void loop() {
  //---------------------------------
  t.update();
  lgFeed(); //rcFeed();
  //wfsLoop();
  //lgsLoop();
  //---------------------------------
}
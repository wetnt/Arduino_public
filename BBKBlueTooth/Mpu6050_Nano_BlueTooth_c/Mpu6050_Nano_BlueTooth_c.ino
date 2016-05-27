//===================================================================
#include "bIMU.h"
//===================================================================
#include "Timer.h"
Timer t;//时间类
float timeKey = 20; //滤波法采样时间间隔毫秒
//===================================================================
static const String codeName = "Mpu6050_Nano_BlueTooth_c";
//===================================================================
void setup() {
  //-------------------------------------
  Pin_setup();//必须首先执行，防止烧毁硬件
  //-------------------------------------
  lg_setup(codeName, "1.0", false, '{', '}');
  MPU6050_setup();
  ss_init("BlueTooth", true, '{', '}');
  Gets_Now_Address();
  //-------------------------------------
  int tickEvent1 = t.every(10, IMU_loop) ;
  int tickEvent2 = t.every(20, IMU_work) ;
  int tickEvent3 = t.every(2000, IMU_BlueTooth_Out) ;
  //-------------------------------------
}
void loop() {
  t.update();
  lg_loop();
  ss_loop();
}
//===================================================================
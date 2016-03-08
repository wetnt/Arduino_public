//===================================================================
#include "bIMU.h"
//===================================================================
#include "Timer.h"
Timer t;//时间类
float timeKey = 20; //滤波法采样时间间隔毫秒
//===================================================================
int Pinx[6] = {A0, A1, A2, A3, A6, A7};
//===================================================================
void setup() {
  //-------------------------------------
  for (int i = 0; i < 6; i++)pinMode(Pinx[i], INPUT);
  //-------------------------------------
  lgsetup(F("MPU6050_IMU"));
  MPU6050_setup();
  //-------------------------------------
  int tickEvent1 = t.every(10, IMU_loop) ; //本语句执行以后50毫秒执行回调函数printout，串口输出
  int tickEvent2 = t.every(20, IMU_show) ; //本语句执行以后50毫秒执行回调函数printout，串口输出
  //-------------------------------------
}
void loop() {
  t.update();//时间操作系统运行
}
//===================================================================

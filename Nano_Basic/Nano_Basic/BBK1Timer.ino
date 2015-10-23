//===================================================================
#include "Timer.h"//时间操作系统头文件
Timer timerLoop;//时间类
//===================================================================
void Timer_setup() {
  //-------------------------------------
  int timerEvent1 = timerLoop.every(timeChange, getangle); //本语句执行以后timeChange毫秒执行回调函数getangle
  //int timerEvent2 = timerLoop.every(100, MPU6050_show) ; //本语句执行以后50毫秒执行回调函数printout，串口输出
  //int timerEvent3 = timerLoop.every(1000, WorkRunA) ; 
  //-------------------------------------
}
void Timer_loop() {
  timerLoop.update();//时间操作系统运行
}
//===================================================================

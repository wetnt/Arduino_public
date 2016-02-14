//===================================================================
//http://www.geek-workshop.com/forum.php?mod=viewthread&tid=10172&highlight=mpu6050
//===================================================================
#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
//===================================================================
MPU6050 accelgyro;//陀螺仪类
int16_t accx, accy, accz, gyrox, gyroy, gyroz;//陀螺仪原始3个加速度,3个角速度
//===================================================================
void MPU6050_setup() {
  Wire.begin();//初始化
  accelgyro.initialize();//初始化
  accelgyro.setFullScaleGyroRange(MPU6050_GYRO_FS_2000);
  accelgyro.setFullScaleAccelRange(MPU6050_ACCEL_FS_8);
}
void MPU6050_read() {
  accelgyro.getMotion6(&accx, &accy, &accz, &gyrox, &gyroy, &gyroz);//读取原始6个数据
}
void MPU6050_show() {
   lg(accx); lg(','); lg(accy); lg(','); lg(accz); lg(','); 
   lg(gyrox); lg(','); lg(gyroy); lg(','); lg(gyroz); lg(','); 
   lg();
}
//===================================================================

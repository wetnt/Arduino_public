//===================================================================
//http://www.geek-workshop.com/forum.php?mod=viewthread&tid=10172&highlight=mpu6050
//===================================================================
#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
//===================================================================
// 把原始数据转换为G
//accelgyro.setFullScaleAccelRange(MPU6050_ACCEL_FS_2);//16384
//#define  RAW_TO_G  16384.0f  //MPU6050_ACCEL_FS_2  = 32768/2
//#define  RAW_TO_G  8192.0f //MPU6050_ACCEL_FS_4  = 32768/4
//#define  RAW_TO_G  4096.0f //MPU6050_ACCEL_FS_8  = 32768/8
//#define  RAW_TO_G  2048.0f //MPU6050_ACCEL_FS_16 = 32768/16
// 把原始数据转换为"度/秒"
//MPU6050_setFullScaleGyroRange(MPU6050_GYRO_FS_2000);
//#define  RAW_TO_DS  131.0f  //MPU6050_GYRO_FS_250  = 32768/250 = 131  
//#define  RAW_TO_DS  65.5f     //MPU6050_GYRO_FS_500  = 65.5
//#define  RAW_TO_DS  32.8f   //MPU6050_GYRO_FS_1000 = 32.8
//#define  RAW_TO_DS  16.4f   //MPU6050_GYRO_FS_2000 = 16.4
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

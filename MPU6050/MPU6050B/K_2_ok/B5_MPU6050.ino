//===================================================================
//http://www.geek-workshop.com/forum.php?mod=viewthread&tid=10172&highlight=mpu6050
//===================================================================
#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
//===================================================================
MPU6050 accelgyro;//陀螺仪类
float angleRawX, gyroRawGy; //计算后的角度（与x轴夹角）和角速度
int16_t accx, accy, accz, gyrox, gyroy, gyroz;//陀螺仪原始数据 3个加速度+3个角速度
//===================================================================
void MPU6050_setup() {
  //----------------------------------------------------
  lgln(F("Initializing I2C devices..."));
  Wire.begin();
  //----------------------------------------------------
  lgln(F("Initializing MPU6050 devices..."));
  accelgyro.initialize();
  accelgyro.setFullScaleAccelRange(MPU6050_ACCEL_FS_2);
  accelgyro.setFullScaleGyroRange(MPU6050_GYRO_FS_250);
  //核实 verify connection
  lg(F("Testing MPU6050 connections..."));
  lgln(accelgyro.testConnection() ? F("successful") : F("failed"));
  //----------------------------------------------------
}
void MPU6050_read() {
  accelgyro.getMotion6(&accx, &accy, &accz, &gyrox, &gyroy, &gyroz);//读取原始6个数据
}
void MPU6050_show() {
  //for (int i = 0; i < 10; i++) {
  //-------------------------------------
  lg(accx); lg(','); lg(accy); lg(','); lg(accz); lg(',');
  lg(gyrox); lg(','); lg(gyroy); lg(','); lg(gyroz); lg(','); lg(); //lg(',');
  //-------------------------------------
  //}
}
//===================================================================

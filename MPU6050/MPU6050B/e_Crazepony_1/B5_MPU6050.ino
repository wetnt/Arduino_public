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
//CFilterOne f1; float angleOne;  //一阶滤波角度输出
//CFilterTwo f2; float angleTwo;  //={0.0, 0.2, 20}; ////2阶滤波角度输出
//CKalman    f3; float angleKlm;  //卡尔曼滤波
//===================================================================
void MPU6050_setup() {
  Wire.begin();//初始化
  accelgyro.initialize();//初始化
  accelgyro.setFullScaleGyroRange(MPU6050_GYRO_FS_2000);
  accelgyro.setFullScaleAccelRange(MPU6050_ACCEL_FS_8);
}
void MPU6050_loop() {
}
void MPU6050_read() {
  accelgyro.getMotion6(&accx, &accy, &accz, &gyrox, &gyroy, &gyroz);//读取原始6个数据
}
void MPU6050_show() {
   lg(accx); lg(','); lg(accy); lg(','); lg(accz); lg(','); 
   lg(gyrox); lg(','); lg(gyroy); lg(','); lg(gyroz); lg(','); lg(); //lg(',');
  //for (int i = 0; i < 10; i++) {
    //-------------------------------------
    //    Serial.print(angleRawX); Serial.print(',');
    //    Serial.print(angleOne);   Serial.print(',');
    //    Serial.print(angleTwo);   Serial.print(',');
    //    Serial.print(angleKlm);   Serial.print(',');
    //Serial.println("");
    //Serial.print(gx/131.00);Serial.print(',');
    //Serial.println(Output);
    //-------------------------------------
  //}
}
//===================================================================
void getAngle() {
  //--------------------------------------------------------
  accelgyro.getMotion6(&accx, &accy, &accz, &gyrox, &gyroy, &gyroz);//读取原始6个数据
  angleRawX = atan2(accx, accz) * 180 / PI; //计算与x轴夹角
  gyroRawGy = -gyroy / 131.00; //计算角速度
  //--------------------------------------------------------
  //  angleOne = f1.lvbo(angleRawX, gyroRawGy); //一阶滤波
  //  angleTwo = f2.lvbo(angleRawX, gyroRawGy); //二阶滤波
  //  angleKlm = f3.lvbo(angleRawX, gyroRawGy); //卡尔曼滤波
  //--------------------------------------------------------
}
//===================================================================

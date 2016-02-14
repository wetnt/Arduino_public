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
  //-32768.00,32767.00
  accelgyro.setFullScaleGyroRange(MPU6050_GYRO_FS_2000);
  accelgyro.setFullScaleAccelRange(MPU6050_ACCEL_FS_16);
  //-11748.00,14140.00

}
float axmin, aymin, azmin, gxmin, gymin, gzmin;
float axmax, aymax, azmax, gxmax, gymax, gzmax;
void MPU6050_loop() {
  accelgyro.getMotion6(&accx, &accy, &accz, &gyrox, &gyroy, &gyroz);

//  axmin = axmin > accx ? accx : axmin;
//  axmax = axmax < accx ? accx : axmax;
gxmin = gxmin>gyrox?gyrox:gxmin;
gxmax = gxmax<gyrox?gyrox:gxmax;

  lg(gxmin); lg(','); lg(gxmax); lg();
}

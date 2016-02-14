//===================================================================
//http://www.geek-workshop.com/forum.php?mod=viewthread&tid=10172&highlight=mpu6050
//===================================================================
#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
//===================================================================
MPU6050 accelgyro;//陀螺仪类
float angleRawX, gyroRawGy; //计算后的角度（与x轴夹角）和角速度
int16_t ax, ay, az, gx, gy, gz;//陀螺仪原始数据 3个加速度+3个角速度
//===================================================================
CFilterOne f1; float angleOne;  //一阶滤波角度输出
CFilterTwo f2; float angleTwo;  //={0.0, 0.2, 20}; ////2阶滤波角度输出
CKalman    f3; float angleKlm;  //卡尔曼滤波
//========================================================================
// 把原始数据转换为G
//accelgyro.setFullScaleAccelRange(MPU6050_ACCEL_FS_2);//16384
#define  RAW_TO_G  16384.0f  //MPU6050_ACCEL_FS_2  = 32768/2
//#define  RAW_TO_G  8192.0f //MPU6050_ACCEL_FS_4  = 32768/4
//#define  RAW_TO_G  4096.0f //MPU6050_ACCEL_FS_8  = 32768/8
//#define  RAW_TO_G  2048.0f //MPU6050_ACCEL_FS_16 = 32768/16
// 把原始数据转换为"度/秒"
//MPU6050_setFullScaleGyroRange(MPU6050_GYRO_FS_2000);
#define  RAW_TO_DS  131.0f  //MPU6050_GYRO_FS_250  = 32768/250 = 131  
//#define  RAW_TO_DS  65.5f     //MPU6050_GYRO_FS_500  = 65.5
//#define  RAW_TO_DS  32.8f   //MPU6050_GYRO_FS_1000 = 32.8
//#define  RAW_TO_DS  16.4f   //MPU6050_GYRO_FS_2000 = 16.4
//========================================================================
//===================================================================
void MPU6050_setup() {
  Wire.begin();//初始化
  accelgyro.initialize();//初始化  
  accelgyro.setFullScaleAccelRange(MPU6050_ACCEL_FS_2);
  accelgyro.setFullScaleGyroRange(MPU6050_GYRO_FS_250);
}
void MPU6050_loop() {
}
void MPU6050_show() {
  for (int i = 0; i < 10; i++) {
    //-------------------------------------
    Serial.print(angleRawX); Serial.print(',');
    Serial.print(angleOne);   Serial.print(',');
    Serial.print(angleTwo);   Serial.print(',');
    Serial.print(angleKlm);   Serial.print(',');
    Serial.println("");
    //Serial.print(gx/131.00);Serial.print(',');
    //Serial.println(Output);
    //-------------------------------------
  }
}
//===================================================================
void getAngle() {
  //--------------------------------------------------------
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);//读取原始6个数据
  angleRawX = atan2(ax, az) * 180 / PI; //计算与x轴夹角
  gyroRawGy = -gy / 131.00; //计算角速度
  //--------------------------------------------------------
  angleOne = f1.lvbo(angleRawX, gyroRawGy); //一阶滤波
  angleTwo = f2.lvbo(angleRawX, gyroRawGy); //二阶滤波
  angleKlm = f3.lvbo(angleRawX, gyroRawGy); //卡尔曼滤波
  //--------------------------------------------------------
}
//===================================================================

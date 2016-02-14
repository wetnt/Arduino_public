//===================================================================
//http://www.geek-workshop.com/forum.php?mod=viewthread&tid=10172&highlight=mpu6050
//===================================================================
#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
//===================================================================
// 陀螺仪
float angleRawX, gyroGy; //计算后的角度（与x轴夹角）和角速度
MPU6050 accelgyro;//陀螺仪类
int16_t ax, ay, az, gx, gy, gz;//陀螺仪原始数据 3个加速度+3个角速度
//===================================================================
float timeChange = 20;//ms滤波法采样时间间隔毫秒
float dt = timeChange * 0.001; //注意：dt的取值为滤波器采样时间
//===================================================================
//一阶滤波
float K1 = 0.05; // 对加速度计取值的权重
float angle1;//一阶滤波角度输出
//二阶滤波
float K2 = 0.2; // 对加速度计取值的权重
float x1, x2, y1; //运算中间变量
float angle2;//er阶滤波角度输出
//卡尔曼滤波参数与函数
float angleK, angleK_dot;//角度和角速度
float angle_0, angle_dot_0;//采集来的角度和角速度
//===================================================================
//运算中间变量
float P[2][2] = {{ 1, 0 }, { 0, 1 }};
float Pdot[4] = { 0, 0, 0, 0};
float Q_angle = 0.001, Q_gyro = 0.005; //角度数据置信度,角速度数据置信度
float R_angle = 0.5 , C_0 = 1;
//float q_bias, angle_err, PCt_0, PCt_1, E, K_0, K_1, t_0, t_1;
//===================================================================
void MPU6050_setup() {
  Wire.begin();//初始化
  accelgyro.initialize();//初始化
}
void MPU6050_show() {
  for (int i = 0; i < 5; i++) {
    //-------------------------------------
    lg(angleK);   lg(',');
    //lg(angleRawX); lg(',');
    //lg(angle1 );   lg(',');
    //lg(angle2 );   lg(',');
    lg();
    //-------------------------------------
  }
}
float MPU6050_GetX(){
  return angleK;
}
//===================================================================
//===================================================================
//===================================================================
void MPU6050_loop() { //getAngle() {
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);//读取原始6个数据
  angleRawX = atan2(ax, az) * 180 / PI; //计算与x轴夹角
  gyroGy = -gy / 131.00; //计算角速度
  Yijielvbo(angleRawX, gyroGy); //一阶滤波
  //Erjielvbo(angleRawX, gyroGy); //二阶滤波
  //Kalman_Filter(angleRawX, gyroGy);  //卡尔曼滤波
}
//===================================================================
void Yijielvbo(float angle_m, float gyro_m) { //一阶滤波
  angle1 = K1 * angle_m + (1 - K1) * (angle1 + gyro_m * dt);
}
void Erjielvbo(float angle_m, float gyro_m) { //二阶滤波
  x1 = (angle_m - angle2) * (1 - K2) * (1 - K2);
  y1 = y1 + x1 * dt;
  x2 = y1 + 2 * (1 - K2) * (angle_m - angle2) + gyro_m;
  angle2 = angle2 + x2 * dt;
}
//===================================================================

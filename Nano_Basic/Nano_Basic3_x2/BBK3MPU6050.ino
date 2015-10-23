//===================================================================
//http://www.geek-workshop.com/forum.php?mod=viewthread&tid=10172&highlight=mpu6050
//===================================================================
#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
//===================================================================
// 陀螺仪
float angleAx, gyroGy; //计算后的角度（与x轴夹角）和角速度
MPU6050 accelgyro;//陀螺仪类
int16_t ax, ay, az, gx, gy, gz;//陀螺仪原始数据 3个加速度+3个角速度
//===================================================================
float timeChange = 20; //滤波法采样时间间隔毫秒
//===================================================================
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
float angle, angle_dot;//角度和角速度
float angle_0, angle_dot_0;//采集来的角度和角速度
//===================================================================
//运算中间变量
float P[2][2] = {{ 1, 0 }, { 0, 1 }};
float Pdot[4] = { 0, 0, 0, 0};
float Q_angle = 0.001, Q_gyro = 0.005; //角度数据置信度,角速度数据置信度
float R_angle = 0.5 , C_0 = 1;
float q_bias, angle_err, PCt_0, PCt_1, E, K_0, K_1, t_0, t_1;
//===================================================================
void MPU6050_setup() {
  Wire.begin();//初始化
  accelgyro.initialize();//初始化
}
void MPU6050_loop() {
}
void MPU6050_show() {
  //-------------------------------------
  Serial.print(angleAx); Serial.print(',');
  Serial.print(angle1); Serial.print(',');
  Serial.print(angle2); Serial.print(',');
  Serial.println(angle);//Serial.print(',');
  // Serial.print(gx/131.00);Serial.print(',');
  //   Serial.println(Output);
  //-------------------------------------
}
//===================================================================
void getangle()
{
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);//读取原始6个数据
  angleAx = atan2(ax, az) * 180 / PI; //计算与x轴夹角
  gyroGy = -gy / 131.00; //计算角速度
  Yijielvbo(angleAx, gyroGy); //一阶滤波
  Erjielvbo(angleAx, gyroGy); //二阶滤波
  Kalman_Filter(angleAx, gyroGy);  //卡尔曼滤波
}
//===================================================================
void Yijielvbo(float angle_m, float gyro_m)//一阶滤波
{
  angle1 = K1 * angle_m + (1 - K1) * (angle1 + gyro_m * dt);
}

void Erjielvbo(float angle_m, float gyro_m)//二阶滤波
{
  x1 = (angle_m - angle2) * (1 - K2) * (1 - K2);
  y1 = y1 + x1 * dt;
  x2 = y1 + 2 * (1 - K2) * (angle_m - angle2) + gyro_m;
  angle2 = angle2 + x2 * dt;
}

void Kalman_Filter(double angle_m, double gyro_m)//卡尔曼滤波
{
  angle += (gyro_m - q_bias) * dt;
  angle_err = angle_m - angle;
  Pdot[0] = Q_angle - P[0][1] - P[1][0];
  Pdot[1] = - P[1][1];
  Pdot[2] = - P[1][1];
  Pdot[3] = Q_gyro;
  P[0][0] += Pdot[0] * dt;
  P[0][1] += Pdot[1] * dt;
  P[1][0] += Pdot[2] * dt;
  P[1][1] += Pdot[3] * dt;
  PCt_0 = C_0 * P[0][0];
  PCt_1 = C_0 * P[1][0];
  E = R_angle + C_0 * PCt_0;
  K_0 = PCt_0 / E;
  K_1 = PCt_1 / E;
  t_0 = PCt_0;
  t_1 = C_0 * P[0][1];
  P[0][0] -= K_0 * t_0;
  P[0][1] -= K_0 * t_1;
  P[1][0] -= K_1 * t_0;
  P[1][1] -= K_1 * t_1;
  angle += K_0 * angle_err; //最优角度
  q_bias += K_1 * angle_err;
  angle_dot = gyro_m - q_bias; //最优角速度
}
//===================================================================

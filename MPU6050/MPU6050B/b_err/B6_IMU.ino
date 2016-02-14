//---------------------------------------------------------------------------------------------------
// 变量定义
#define   f       1
#define   Kp      2.0f      // 比例增益支配率收敛到加速度计/磁强计
#define   Ki      0.005f    // 积分增益支配率的陀螺仪偏见的衔接
#define   halfT   0.5f      // 采样周期的一半
//---------------------------------------------------------------------------------------------------
float q0 = 1, q1 = 0, q2 = 0, q3 = 0;          // 四元数的元素，代表估计方向
float exInt = 0, eyInt = 0, ezInt = 0;        // 按比例缩小积分误差
//---------------------------------------------------------------------------------------------------
//互补滤波
#define        kfa   0.98f
#define        kfan  1.0f-kfa
#define        kfg   0.80f
#define        kfgn  1.0f-kfg
//---------------------------------------------------------------------------------------------------
float Yaw, Pitch, Rool; //偏航角，俯仰角，翻滚角
//====================================================================================================
void IMU_loop() {
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  float rax, ray, raz, rgx, rgy, rgz;

  rgx = gx / RAW_TO_DS;
  rgy = gy / RAW_TO_DS;
  rgz = gz / RAW_TO_DS;
  rax = ax / RAW_TO_G;// * 9.80;
  ray = ay / RAW_TO_G;//* 9.80;
  raz = az / RAW_TO_G;//* 9.80;

  //IMUupdate(rax, ray, raz, rgx, rgy, rgz);
  IMUupdate(ax, ay, az, gx, gy, gz);
}
void IMUupdate(float gxi, float gyi, float gzi, float axi, float ayi, float azi) {
  //------------------------------------------------------------------
  float norm; float vx, vy, vz; float ex, ey, ez;
  //------------------------------------------------------------------
  //增加互补滤波
  ax = ax * kfa + kfan * axi;
  ay = ay * kfa + kfan * ayi;
  az = az * kfa + kfan * azi;
  gx = gx * kfg + kfgn * gxi;
  gy = gy * kfg + kfgn * gyi;
  gz = gz * kfg + kfgn * gzi;
  //------------------------------------------------------------------
  // 测量正常化
  norm = sqrt(ax * ax + ay * ay + az * az);
  ax = ax / norm; ay = ay / norm; az = az / norm;
  //------------------------------------------------------------------
  // 估计方向的重力
  vx = 2 * (q1 * q3 - q0 * q2);
  vy = 2 * (q0 * q1 + q2 * q3);
  vz = q0 * q0 - q1 * q1 - q2 * q2 + q3 * q3;
  //------------------------------------------------------------------
  // 错误的领域和方向传感器测量参考方向之间的交叉乘积的总和
  ex = (ay * vz - az * vy);
  ey = (az * vx - ax * vz);
  ez = (ax * vy - ay * vx);
  //------------------------------------------------------------------
  // 积分误差比例积分增益
  exInt = exInt + ex * Ki;
  eyInt = eyInt + ey * Ki;
  ezInt = ezInt + ez * Ki;
  //------------------------------------------------------------------
  // 调整后的陀螺仪测量
  gx = gx + Kp * ex + exInt;
  gy = gy + Kp * ey + eyInt;
  gz = gz + Kp * ez + ezInt;
  //------------------------------------------------------------------
  // 整合四元数率和正常化
  q0 = q0 + (-q1 * gx - q2 * gy - q3 * gz) * halfT;
  q1 = q1 + (q0 * gx + q2 * gz - q3 * gy) * halfT;
  q2 = q2 + (q0 * gy - q1 * gz + q3 * gx) * halfT;
  q3 = q3 + (q0 * gz + q1 * gy - q2 * gx) * halfT;
  //------------------------------------------------------------------
  // 正常化四元
  norm = sqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
  q0 = q0 / norm; q1 = q1 / norm;
  q2 = q2 / norm; q3 = q3 / norm;
  //------------------------------------------------------------------
  Pitch  = asin(-2 * q1 * q3 + 2 * q0 * q2) * 57.3f; // pitch
  Rool = atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2 * q2 + 1) * 57.3f; // rollv
  //------------------------------------------------------------------
  for (int i = 0; i < 1; i++) {
    //-------------------------------------
    //    Serial.print(gxi);   Serial.print(',');
    //    Serial.print(gyi);   Serial.print(',');
    //    Serial.print(gzi);   Serial.print(',');
    Serial.print(Pitch); Serial.print(',');
    Serial.print(Rool);   Serial.print(',');
    Serial.println("");
    //Serial.print(gx/131.00);Serial.print(',');
    //Serial.println(Output);
    //-------------------------------------
  }
  //------------------------------------------------------------------
}

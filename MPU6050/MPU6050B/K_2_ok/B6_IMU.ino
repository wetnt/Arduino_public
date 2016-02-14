//http://tieba.baidu.com/p/3183760992?pid=54333210165&see_lz=1
//========================================================================
double t1, t0, dt;
int16_t ax, ay, az, gx, gy, gz;
int axoffs, ayoffs, azoffs, gxoffs, gyoffs, gzoffs;
double rgx, rgy, rgz, rax, ray, raz;
double ax0, ay0, az0, ax1, ay1, az1;
double wx0, wy0, wz0, wx1, wy1, wz1, dwx, dwy, dwz, dw;
double q0, q1, q2, q3, p0, p1, p2, p3, qc0, qc1, qc2, qc3;
double roll, pitch, yaw;
//========================================================================
CEulerAngle fx;
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
void IMU_setup() {
  q0 = 1; q1 = 0; q2 = 0; q3 = 0;
  IMU_offs();
}
void IMU_offs() {
  //----------------------------------------------------
  float n = 2000.0f;//两千次校准值
  //int16_t ax, ay, az, gx, gy, gz;
  long int axsum = 0, aysum = 0, azsum = 0;
  long int gxsum = 0, gysum = 0, gzsum = 0;
  lg(F("IMU_offs..."));
  //----------------------------------------------------
  for (int i = 1; i <= n; i++) {
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    axsum = ax + axsum; aysum = ay + aysum; azsum = az + azsum - RAW_TO_G; //去除重力方向?
    gxsum = gx + gxsum; gysum = gy + gysum; gzsum = gz + gzsum;
  }
  //----------------------------------------------------
  axoffs = -axsum / n; ayoffs = -aysum / n; azoffs = -azsum / n;
  gxoffs = -gxsum / n; gyoffs = -gysum / n; gzoffs = -gzsum / n;
  //----------------------------------------------------
  lgln(F("n = 2000.0f"));
  //----------------------------------------------------
}
void IMU_loop() {
  //----------------------------------------------------
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  //----------------------------------------------------
  t0 = t1; t1 = micros(); dt = (t1 - t0) / 1000000.0f;
  //----------------------------------------------------
  //消除初始姿态差
  rax = ax + axoffs; ray = ay + ayoffs; raz = az + azoffs;
  rgx = gx + gxoffs; rgy = gy + gyoffs; rgz = gz + gzoffs;
  //----------------------------------------------------
  //实际值转换
  wx0 = wx1; wy0 = wy1; wz0 = wz1;
  wx1 = rgx / RAW_TO_DS;
  wy1 = rgy / RAW_TO_DS;
  wz1 = rgz / RAW_TO_DS;
  ax1 = (rax / RAW_TO_G) * 9.80f;
  ay1 = (ray / RAW_TO_G) * 9.80f;
  az1 = (raz / RAW_TO_G) * 9.80f;
  //----------------------------------------------------
  //滤波
  dwx = ((wx1 + wx0) / 2.0f) * dt * 0.01745f;
  dwy = ((wy1 + wy0) / 2.0f) * dt * 0.01745f;
  dwz = ((wz1 + wz0) / 2.0f) * dt * 0.01745f;
  //----------------------------------------------------
  //欧拉角转四元数
  dw = sqrt(dwx * dwx + dwy * dwy + dwz * dwz);
  qc0 = cos(dw / 2.0);
  qc1 = (dwx / dw) * sin(dw / 2.0);
  qc2 = (dwy / dw) * sin(dw / 2.0);
  qc3 = (dwz / dw) * sin(dw / 2.0);
  //----------------------------------------------------
  p0 = q0; p1 = q1; p2 = q2; p3 = q3;
  q0 = qc0 * p0 - qc1 * p1 - qc2 * p2 - qc3 * p3;
  q1 = qc1 * p0 + qc0 * p1 + qc3 * p2 - qc2 * p3;
  q2 = qc2 * p0 - qc3 * p1 + qc0 * p2 + qc1 * p3;
  q3 = qc3 * p0 + qc2 * p1 - qc1 * p2 + qc0 * p3;
  //----------------------------------------------------
  //四元数转欧拉角
  roll = atan2(2 * (q0 * q1 + q2 * q3), 1 - 2 * (q1 * q1 + q2 * q2)) * 57.25977;
  pitch = -asin(2 * (q0 * q2 - q3 * q1)) * 57.25977;
  yaw = -atan2(2 * (q0 * q3 + q1 * q2), 1 - 2 * (q2 * q2 + q3 * q3)) * 57.25977;
  if (yaw < 0) yaw = 360 + yaw;
  //----------------------------------------------------
  //fx =  GetEulerAngle(q0,q1,q2,q3);
  //----------------------------------------------------
}
void IMU_show() {
  //----------------------------------------------------
  //lg(ax1);lg(",");lg(ay1);lg(",");lg(az1);lg(",");
  //lg(roll); lg(","); lg(pitch); lg(","); lg(yaw); lg();
  lg(roll - fx.x); lg(","); lg(pitch - fx.y); lg(","); lg(yaw - fx.z); lg();
  //lg(fx.x); lg(","); lg(fx.y); lg(","); lg(fx.z); lg();
  //lg(dwx); lg(","); lg(dwy); lg(","); lg(dwz); lg();
  //----------------------------------------------------
}

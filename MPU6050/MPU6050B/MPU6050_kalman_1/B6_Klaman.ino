#include <Kalman.h>
Kalman kalmanX, kalmanY;

/* IMU Data */
int16_t accX, accY, accZ, gyroX, gyroY, gyroZ;
int16_t tempRaw;
double temperature;

double gyroXangle, gyroYangle; // Angle calculate using the gyro only//只使用陀螺角计算
double compAngleX, compAngleY; // Calculated angle using a complementary filter//使用互补滤波器计算角度
double kalAngleX, kalAngleY; // Calculated angle using a Kalman filter//使用卡尔曼滤波计算角度

double roll, pitch;
uint32_t timer;
void Kalman_setup() {
  //------------------------------------------------
  accelgyro.getMotion6(&accX, &accY, &accZ, &gyroX, &gyroY, &gyroZ);//读取原始6个数据
  //------------------------------------------------
  double roll  = atan(accY / sqrt(accX * accX + accZ * accZ)) * RAD_TO_DEG;
  double pitch = atan2(-accX, accZ) * RAD_TO_DEG;
  //------------------------------------------------
  kalmanX.setAngle(roll);
  kalmanY.setAngle(pitch);
  //------------------------------------------------
  gyroXangle = roll; gyroYangle = pitch;
  compAngleX = roll; compAngleY = pitch;
  //------------------------------------------------
  timer = micros();
  //------------------------------------------------
}
void Kalman_loop() {
  //------------------------------------------------------------------------------
  accelgyro.getMotion6(&accX, &accY, &accZ, &gyroX, &gyroY, &gyroZ);
  temperature = (double)tempRaw / 340.0 + 36.53;
  //------------------------------------------------------------------------------
  double dt = (double)(micros() - timer) / 1000000; timer = micros();
  //------------------------------------------------------------------------------
  double roll  = atan(accY / sqrt(accX * accX + accZ * accZ)) * RAD_TO_DEG;
  double pitch = atan2(-accX, accZ) * RAD_TO_DEG;
  //------------------------------------------------------------------------------
  double gyroXrate = gyroX / 131.0;
  double gyroYrate = gyroY / 131.0;
  //------------------------------------------------------------------------------
  if ((pitch < -90 && kalAngleY > 90) || (pitch > 90 && kalAngleY < -90)) {
    kalmanY.setAngle(pitch);
    compAngleY = pitch; kalAngleY = pitch; gyroYangle = pitch;
  } else
    kalAngleY = kalmanY.getAngle(pitch, gyroYrate, dt); // Calculate the angle using a Kalman filter
  //------------------------------------------------------------------------------
  if (abs(kalAngleY) > 90) gyroXrate = -gyroXrate; // Invert rate, so it fits the restriced accelerometer reading
  //------------------------------------------------------------------------------
  kalAngleX = kalmanX.getAngle(roll, gyroXrate, dt); // Calculate the angle using a Kalman filter
  //------------------------------------------------------------------------------
  gyroXangle += gyroXrate * dt;
  gyroYangle += gyroYrate * dt;
  compAngleX = 0.93 * (compAngleX + gyroXrate * dt) + 0.07 * roll;
  compAngleY = 0.93 * (compAngleY + gyroYrate * dt) + 0.07 * pitch;
  if (gyroXangle < -180 || gyroXangle > 180) gyroXangle = kalAngleX;
  if (gyroYangle < -180 || gyroYangle > 180) gyroYangle = kalAngleY;
  //------------------------------------------------
}
void Kalman_show() {
  //------------------------------------------------
  for (int i = 0; i < 5; i++) {
    //lg(accX); lg(","); lg(accY); lg(","); lg(accZ); lg(",");lg(gyroX); lg(","); lg(gyroY); lg(","); lg(gyroZ); lg(",");
    lg(roll); lg(","); lg(gyroXangle); lg(","); lg(compAngleX); lg(","); lg(kalAngleX); lg(",");
    lg(pitch); lg(","); lg(gyroYangle); lg(","); lg(compAngleY); lg(","); lg(kalAngleY); lg(",");
    lg(temperature); lg(","); lg();
  }
  //------------------------------------------------
}

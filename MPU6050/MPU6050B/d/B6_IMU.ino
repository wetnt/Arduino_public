
//const int nCalibTimes = 1000;         //校准时读数的次数
int calibData[6];                     //校准数据

#include <Kalman.h>
Kalman kalmanRoll;                    //Roll角滤波器
Kalman kalmanPitch;                   //Pitch角滤波器

int16_t ax, ay, az, gx, gy, gz;
float fRad2Deg = 57.295779513f;       //将弧度转为角度的乘数
unsigned long nLastTime = 0;          //上一次读数的时间
/***********四元数参数***********/
#define KP 0.025f//10.0f
#define KI 0.0f//0.008f
#define halfT 0.001f
float q0 = 1, q1 = 0, q2 = 0, q3 = 0;
float exInt = 0, eyInt = 0, ezInt = 0;
float Angle_roll, Angle_pitch, Angle_yaw;

void IMU_loop() {
  int16_t readouts[6];
  ReadAccGyr(readouts); //读出测量值

  float realVals[6];
  Rectify(readouts, realVals); //根据校准的偏移量进行纠正

  //四元数解析出欧拉角
  AngleUpdate(realVals);

  //计算加速度向量的模长，均以g为单位
  float fRoll = GetRoll(realVals); //计算Roll角
  float fPitch = GetPitch(realVals); //计算Pitch角

  //计算两次测量的时间间隔dt，以秒为单位
  unsigned long nCurTime = micros();
  float dt = (double)(nCurTime - nLastTime) / 1000000.0;
  //对Roll角和Pitch角进行卡尔曼滤波
  float fNewRoll = kalmanRoll.getAngle(fRoll, realVals[4], dt);
  float fNewPitch = kalmanPitch.getAngle(fPitch, realVals[5], dt);
  nLastTime = nCurTime;//更新本次测的时间

  //lg(fNewRoll); lg(','); lg(fNewPitch); lg(','); lg(); //lg("");
}
void ReadAccGyr(int16_t *pVals) {
  accelgyro.getMotion6(&pVals[0], &pVals[1], &pVals[2], &pVals[3], &pVals[4], &pVals[5]);
}
void Rectify(int *pReadout, float *pRealVals) {
  for (int i = 0; i < 3; ++i) {
    pRealVals[i] = (float)(pReadout[i] - calibData[i]) / 16384.0f;
  }
  for (int i = 3; i < 6; ++i) {
    pRealVals[i] = (float)(pReadout[i] - calibData[i]) / 131.0f;
  }
}
float GetRoll(float *pRealVals) {
  float fNorm = sqrt(pRealVals[0] * pRealVals[0] + pRealVals[1] * pRealVals[1] + pRealVals[2] * pRealVals[2]);
  float fNormXZ = sqrt(pRealVals[0] * pRealVals[0] + pRealVals[2] * pRealVals[2]);
  float fCos = fNormXZ / fNorm;
  if (pRealVals[1] > 0)
    return -acos(fCos) * fRad2Deg;
  else
    return acos(fCos) * fRad2Deg;
}
float GetPitch(float *pRealVals) {
  float fNorm = sqrt(pRealVals[0] * pRealVals[0] + pRealVals[1] * pRealVals[1] + pRealVals[2] * pRealVals[2]);
  float fNormYZ = sqrt(pRealVals[1] * pRealVals[1] + pRealVals[2] * pRealVals[2]);
  float fCos = fNormYZ / fNorm;
  if (pRealVals[0] < 0)
    return -acos(fCos) * fRad2Deg;
  else
    return acos(fCos) * fRad2Deg;
}
void AngleUpdate(float *pRealVals) {
  float norm,vx, vy, vz,ex, ey, ez;
  if (pRealVals[0]*pRealVals[1]*pRealVals[2] == 0) return;

  norm = sqrt(pRealVals[0] * pRealVals[0] + pRealVals[1] * pRealVals[1] + pRealVals[2] * pRealVals[2]);

  vx = 2 * (q1 * q3 - q0 * q2);
  vy = 2 * (q0 * q1 - q3 * q2);
  vz = q0 * q0 - q1 * q1 - q2 * q2 + q3 * q3;

  ex = pRealVals[1]* vz / norm  - pRealVals[2]* vy / norm ;
  ey = pRealVals[2] * vx / norm - pRealVals[0]* vz / norm ;
  ez = pRealVals[0]* vy / norm  - pRealVals[1] * vx / norm;

  exInt = exInt + ex * KI;
  eyInt = eyInt + ey * KI;
  ezInt = ezInt + ez * KI;

  q0 = q0 + (-q1 * pRealVals[3] + KP * ex + exInt - q2 * pRealVals[4] + KP * ey + eyInt - q3 * pRealVals[5] + KP * ez + ezInt) * halfT;
  q1 = q1 + (q0 * pRealVals[3] + KP * ex + exInt + q2 * pRealVals[5] + KP * ez + ezInt - q3 * pRealVals[4] + KP * ey + eyInt) * halfT;
  q2 = q2 + (q0 * pRealVals[4] + KP * ey + eyInt - q1 * pRealVals[5] + KP * ez + ezInt + q3 * pRealVals[3] + KP * ex + exInt) * halfT;
  q3 = q3 + (q0 * pRealVals[5] + KP * ez + ezInt + q1 * pRealVals[4] + KP * ey + eyInt - q2 * pRealVals[3] + KP * ex + exInt) * halfT;

  norm = sqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
  q0 = q0 / norm;
  q1 = q1 / norm;
  q2 = q2 / norm;
  q3 = q3 / norm;

  Angle_roll = atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2 * q2 + 1) * fRad2Deg;
  Angle_pitch = asin(-2 * q1 * q3 + 2 * q0 * q2) * fRad2Deg;
  Angle_yaw = atan2(2 * q1 * q2 + 2 * q0 * q3, -2 * q2 * q2 - 2 * q3 * q3 + 1) * fRad2Deg;

  lg(Angle_roll); lg(','); lg(Angle_pitch); lg(','); lg(Angle_yaw); lg(','); lg(); //lg("");
}

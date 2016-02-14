
//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
//! Auxiliary variables to reduce number of repeated operations
static float q0 = 1.0f, q1 = 0.0f, q2 = 0.0f, q3 = 0.0f;  /** quaternion of sensor frame relative to auxiliary frame */
static float dq0 = 0.0f, dq1 = 0.0f, dq2 = 0.0f, dq3 = 0.0f;  /** quaternion of sensor frame relative to auxiliary frame */
static float gyro_bias[3] = {0.0f, 0.0f, 0.0f}; /** bias estimation */
static float q0q0, q0q1, q0q2, q0q3;
static float q1q1, q1q2, q1q3;
static float q2q2, q2q3;
static float q3q3;
static uint8_t bFilterInit = 0;
//---------------------------------------------------------------------------------------------------
float invSqrt(float number) {
  volatile long i;
  volatile float x, y;
  volatile const float f = 1.5F;

  x = number * 0.5F;
  y = number;
  i = * (( long * ) &y);
  i = 0x5f375a86 - ( i >> 1 );
  y = * (( float * ) &i);
  y = y * ( f - ( x * y * y ) );
  return y;
}
//---------------------------------------------------------------------------------------------------
imu_t imu;
//---------------------------------------------------------------------------------------------------
#define SENSOR_MAX_G 8.0f    //constant g    // tobe fixed to 8g. but IMU need to  correct at the same time
#define SENSOR_MAX_W 2000.0f  //deg/s
#define ACC_SCALE  (SENSOR_MAX_G/32768.0f)
#define GYRO_SCALE  (SENSOR_MAX_W/32768.0f)
void ReadIMUSensorHandle(void) {
  //---------------------------------------------------------------------------------------------------
  imu.accADC[0] = accx; imu.accADC[0] = accy; imu.accADC[0] = accz;
  imu.gyroADC[0] = gyrox; imu.gyroADC[0] = gyroy; imu.gyroADC[0] = gyroz;
  //---------------------------------------------------------------------------------------------------
  //tutn to physical
  for (int i = 0; i < 3; i++)  {
    imu.accRaw[i] = (float)imu.accADC[i] * ACC_SCALE * CONSTANTS_ONE_G ;
    imu.gyroRaw[i] = (float)imu.gyroADC[i] * GYRO_SCALE * M_PI_F / 180.f; //deg/s
  }
  //---------------------------------------------------------------------------------------------------
  imu.accb[0] = imu.accRaw[0];
  imu.accb[1] = imu.accRaw[1];
  imu.accb[2] = imu.accRaw[2];
  imu.gyro[0] = imu.gyroRaw[0];
  imu.gyro[1] = imu.gyroRaw[1];
  imu.gyro[2] = imu.gyroRaw[2];

  //  imu.accb[0] = LPF2pApply_1(imu.accRaw[0] - imu.accOffset[0]);
  //  imu.accb[1] = LPF2pApply_2(imu.accRaw[1] - imu.accOffset[1]);
  //  imu.accb[2] = LPF2pApply_3(imu.accRaw[2] - imu.accOffset[2]);
  //  imu.gyro[0] = LPF2pApply_4(imu.gyroRaw[0]);
  //  imu.gyro[1] = LPF2pApply_5(imu.gyroRaw[1]);
  //  imu.gyro[2] = LPF2pApply_6(imu.gyroRaw[2]);
  //  //  imu.gyro[0] = LPF2pApply_4(imu.gyroRaw[0] - imu.gyroOffset[0]);
  //  //  imu.gyro[1] = LPF2pApply_5(imu.gyroRaw[1] - imu.gyroOffset[1]);
  //  //  imu.gyro[2] = LPF2pApply_6(imu.gyroRaw[2] - imu.gyroOffset[2]);
  //---------------------------------------------------------------------------------------------------
  //low pass filter.  inertial or digital . tobe tested=低通滤波器。惯性或数字。托比测试
  /*
  for(int i=0;i<2;i++)  //tobe fixed to digital filter{
      accFilted[i] = accFilted[i] * (1.0f - (1.0f / ACC_XY_LPF_FACTOR)) + accRaw[i] * (1.0f /ACC_XY_LPF_FACTOR);
      gyroFilted[i] = gyroFilted[i] * (1.0f - (1.0f / GYRO_XY_LPF_FACTOR)) + gyroRaw[i] * (1.0f/GYRO_XY_LPF_FACTOR);
  }
  accFilted[2]=LPF2pApply_3(accRaw[2]);     // need to set cutoff freq and sample rate before
  gyroFilted[2] = gyroFilted[2] * (1.0f - (1.0f / GYRO_Z_LPF_FACTOR)) + gyroRaw[2] * (1.0f/GYRO_Z_LPF_FACTOR);
  */
  //---------------------------------------------------------------------------------------------------
}
//---------------------------------------------------------------------------------------------------
//! Using accelerometer, sense the gravity vector.
//! Using magnetometer, sense yaw.
void NonlinearSO3AHRSinit(float ax, float ay, float az, float mx, float my, float mz) {
  //---------------------------------------------------------------------------------------------------
  float initialRoll, initialPitch;
  float cosRoll, sinRoll, cosPitch, sinPitch;
  float magX, magY;
  float initialHdg, cosHeading, sinHeading;
  //---------------------------------------------------------------------------------------------------
  initialRoll = atan2(-ay, -az);
  initialPitch = atan2(ax, -az);
  cosRoll = cosf(initialRoll); sinRoll = sinf(initialRoll);
  cosPitch = cosf(initialPitch); sinPitch = sinf(initialPitch);
  //---------------------------------------------------------------------------------------------------
  magX = mx * cosPitch + my * sinRoll * sinPitch + mz * cosRoll * sinPitch;
  magY = my * cosRoll - mz * sinRoll;
  //---------------------------------------------------------------------------------------------------
  initialHdg = atan2f(-magY, magX);
  //---------------------------------------------------------------------------------------------------
  cosRoll = cosf(initialRoll * 0.5f);
  sinRoll = sinf(initialRoll * 0.5f);
  cosPitch = cosf(initialPitch * 0.5f);
  sinPitch = sinf(initialPitch * 0.5f);
  cosHeading = cosf(initialHdg * 0.5f);
  sinHeading = sinf(initialHdg * 0.5f);
  //---------------------------------------------------------------------------------------------------
  q0 = cosRoll * cosPitch * cosHeading + sinRoll * sinPitch * sinHeading;
  q1 = sinRoll * cosPitch * cosHeading - cosRoll * sinPitch * sinHeading;
  q2 = cosRoll * sinPitch * cosHeading + sinRoll * cosPitch * sinHeading;
  q3 = cosRoll * cosPitch * sinHeading - sinRoll * sinPitch * cosHeading;
  //---------------------------------------------------------------------------------------------------
  // auxillary variables to reduce number of repeated operations, for 1st pass
  q0q0 = q0 * q0; q0q1 = q0 * q1; q0q2 = q0 * q2; q0q3 = q0 * q3;
  q1q1 = q1 * q1; q1q2 = q1 * q2; q1q3 = q1 * q3;
  q2q2 = q2 * q2; q2q3 = q2 * q3;
  q3q3 = q3 * q3;
  //---------------------------------------------------------------------------------------------------
}
void NonlinearSO3AHRSupdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz, float twoKp, float twoKi, float dt) {
  float recipNorm;
  float halfex = 0.0f, halfey = 0.0f, halfez = 0.0f;

  // Make filter converge to initial solution faster
  // This function assumes you are in static position.
  // WARNING : in case air reboot, this can cause problem. But this is very unlikely happen.
  if (bFilterInit == 0) {
    NonlinearSO3AHRSinit(ax, ay, az, mx, my, mz);
    bFilterInit = 1;
  }
  //---------------------------------------------------------------------------------------------------
  //! If magnetometer measurement is available, use it.
  if (!((mx == 0.0f) && (my == 0.0f) && (mz == 0.0f))) {
    float hx, hy, hz, bx, bz;
    float halfwx, halfwy, halfwz;

    // Normalise magnetometer measurement
    // Will sqrt work better? PX4 system is powerful enough?
    recipNorm = invSqrt(mx * mx + my * my + mz * mz);
    mx *= recipNorm;
    my *= recipNorm;
    mz *= recipNorm;

    // Reference direction of Earth's magnetic field
    hx = 2.0f * (mx * (0.5f - q2q2 - q3q3) + my * (q1q2 - q0q3) + mz * (q1q3 + q0q2));
    hy = 2.0f * (mx * (q1q2 + q0q3) + my * (0.5f - q1q1 - q3q3) + mz * (q2q3 - q0q1));
    hz = 2.0f * mx * (q1q3 - q0q2) + 2.0f * my * (q2q3 + q0q1) + 2.0f * mz * (0.5f - q1q1 - q2q2);
    bx = sqrt(hx * hx + hy * hy);
    bz = hz;

    // Estimated direction of magnetic field
    halfwx = bx * (0.5f - q2q2 - q3q3) + bz * (q1q3 - q0q2);
    halfwy = bx * (q1q2 - q0q3) + bz * (q0q1 + q2q3);
    halfwz = bx * (q0q2 + q1q3) + bz * (0.5f - q1q1 - q2q2);

    // Error is sum of cross product between estimated direction and measured direction of field vectors
    halfex += (my * halfwz - mz * halfwy);
    halfey += (mz * halfwx - mx * halfwz);
    halfez += (mx * halfwy - my * halfwx);
  }

  //增加一个条件：  加速度的模量与G相差不远时。 0.75*G < normAcc < 1.25*G
  // Compute feedback only if accelerometer measurement valid (avoids NaN in accelerometer normalisation)
  if (!((ax == 0.0f) && (ay == 0.0f) && (az == 0.0f)))
  {
    float halfvx, halfvy, halfvz;
    float accNorm = 0;

    // Normalise accelerometer measurement
    recipNorm = invSqrt(ax * ax + ay * ay + az * az);
    //--added!!!
    //    accNorm=1.0f/recipNorm;
    //    if(accNorm > 0.75 * CONSTANTS_ONE_G && accNorm < 1.25 * CONSTANTS_ONE_G )  //加速度过大时
    //    {
    ax *= recipNorm;
    ay *= recipNorm;
    az *= recipNorm;

    // Estimated direction of gravity and magnetic field
    halfvx = q1q3 - q0q2;
    halfvy = q0q1 + q2q3;
    halfvz = q0q0 - 0.5f + q3q3;

    // Error is sum of cross product between estimated direction and measured direction of field vectors
    halfex += ay * halfvz - az * halfvy;
    halfey += az * halfvx - ax * halfvz;
    halfez += ax * halfvy - ay * halfvx;
    //    }
  }

  // Apply feedback only when valid data has been gathered from the accelerometer or magnetometer
  if (halfex != 0.0f && halfey != 0.0f && halfez != 0.0f) {
    // Compute and apply integral feedback if enabled
    if (twoKi > 0.0f) {
      gyro_bias[0] += twoKi * halfex * dt;  // integral error scaled by Ki
      gyro_bias[1] += twoKi * halfey * dt;
      gyro_bias[2] += twoKi * halfez * dt;

      // apply integral feedback
      gx += gyro_bias[0];
      gy += gyro_bias[1];
      gz += gyro_bias[2];
    }
    else {
      gyro_bias[0] = 0.0f;  // prevent integral windup
      gyro_bias[1] = 0.0f;
      gyro_bias[2] = 0.0f;
    }

    // Apply proportional feedback
    gx += twoKp * halfex;
    gy += twoKp * halfey;
    gz += twoKp * halfez;
  }

  //! Integrate rate of change of quaternion
#if 0
  gx *= (0.5f * dt);    // pre-multiply common factors
  gy *= (0.5f * dt);
  gz *= (0.5f * dt);
#endif

  // Time derivative of quaternion. q_dot = 0.5*q\otimes omega.
  //! q_k = q_{k-1} + dt*\dot{q}
  //! \dot{q} = 0.5*q \otimes P(\omega)
  dq0 = 0.5f * (-q1 * gx - q2 * gy - q3 * gz);
  dq1 = 0.5f * (q0 * gx + q2 * gz - q3 * gy);
  dq2 = 0.5f * (q0 * gy - q1 * gz + q3 * gx);
  dq3 = 0.5f * (q0 * gz + q1 * gy - q2 * gx);

  q0 += dt * dq0;
  q1 += dt * dq1;
  q2 += dt * dq2;
  q3 += dt * dq3;

  // Normalise quaternion
  recipNorm = invSqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
  q0 *= recipNorm;
  q1 *= recipNorm;
  q2 *= recipNorm;
  q3 *= recipNorm;

  // Auxiliary variables to avoid repeated arithmetic
  q0q0 = q0 * q0;
  q0q1 = q0 * q1;
  q0q2 = q0 * q2;
  q0q3 = q0 * q3;
  q1q1 = q1 * q1;
  q1q2 = q1 * q2;
  q1q3 = q1 * q3;
  q2q2 = q2 * q2;
  q2q3 = q2 * q3;
  q3q3 = q3 * q3;
}

#define so3_comp_params_Kp 1.0f
#define so3_comp_params_Ki  0.05f



void IMUSO3Thread(void) {
  //---------------------------------------------------------------------------------------------------
  //! Time constant
  float dt = 0.01f;   //s
  static uint32_t tPrev = 0, startTime = 0; //us
  unsigned long nows;
  //---------------------------------------------------------------------------------------------------
  float euler[3] = {0.0f, 0.0f, 0.0f};  //rad
  //---------------------------------------------------------------------------------------------------
  /* Initialization */
  float Rot_matrix[9] = {1.f,  0.0f,  0.0f, 0.0f,  1.f,  0.0f, 0.0f,  0.0f,  1.f };   /**< init: identity matrix */
  float acc[3] = {0.0f, 0.0f, 0.0f};    //m/s^2
  float gyro[3] = {0.0f, 0.0f, 0.0f};   //rad/s
  float mag[3] = {0.0f, 0.0f, 0.0f};
  //need to calc gyro offset before imu start working
  static float gyro_offsets_sum[3] = { 0.0f, 0.0f, 0.0f }; // gyro_offsets[3] = { 0.0f, 0.0f, 0.0f },
  static uint16_t offset_count = 0;
  //---------------------------------------------------------------------------------------------------
  nows = micros(); dt = (tPrev > 0) ? (nows - tPrev) / 1000000.0f : 0; tPrev = nows;
  //---------------------------------------------------------------------------------------------------
  ReadIMUSensorHandle();
  //---------------------------------------------------------------------------------------------------
  if (!imu.readys) {
    if (startTime == 0) startTime = nows;

    gyro_offsets_sum[0] += imu.gyroRaw[0];
    gyro_offsets_sum[1] += imu.gyroRaw[1];
    gyro_offsets_sum[2] += imu.gyroRaw[2];
    offset_count++;

    if (nows > startTime + GYRO_CALC_TIME) {
      imu.gyroOffset[0] = gyro_offsets_sum[0] / offset_count;
      imu.gyroOffset[1] = gyro_offsets_sum[1] / offset_count;
      imu.gyroOffset[2] = gyro_offsets_sum[2] / offset_count;     
       
      gyro_offsets_sum[0] = 0; 
      gyro_offsets_sum[1] = 0; 
      gyro_offsets_sum[2] = 0;
      startTime = 0;
      offset_count = 0;
      
      imu.readys = 1;
    }
    return;
  }
  //---------------------------------------------------------------------------------------------------
  gyro[0] = imu.gyro[0] - imu.gyroOffset[0];
  gyro[1] = imu.gyro[1] - imu.gyroOffset[1];
  gyro[2] = imu.gyro[2] - imu.gyroOffset[2];

  acc[0] = -imu.accb[0];
  acc[1] = -imu.accb[1];
  acc[2] = -imu.accb[2];

  // NOTE : Accelerometer is reversed.
  // Because proper mount of PX4 will give you a reversed accelerometer readings.
  NonlinearSO3AHRSupdate(gyro[0], gyro[1], gyro[2],
                         -acc[0], -acc[1], -acc[2],
                         mag[0], mag[1], mag[2],
                         so3_comp_params_Kp,
                         so3_comp_params_Ki,
                         dt);

  //---------------------------------------------------------------------------------------------------
  // Convert q->R, This R converts inertial frame to body frame.
  Rot_matrix[0] = q0q0 + q1q1 - q2q2 - q3q3;// 11
  Rot_matrix[1] = 2.f * (q1 * q2 + q0 * q3); // 12
  Rot_matrix[2] = 2.f * (q1 * q3 - q0 * q2); // 13
  Rot_matrix[3] = 2.f * (q1 * q2 - q0 * q3); // 21
  Rot_matrix[4] = q0q0 - q1q1 + q2q2 - q3q3;// 22
  Rot_matrix[5] = 2.f * (q2 * q3 + q0 * q1); // 23
  Rot_matrix[6] = 2.f * (q1 * q3 + q0 * q2); // 31
  Rot_matrix[7] = 2.f * (q2 * q3 - q0 * q1); // 32
  Rot_matrix[8] = q0q0 - q1q1 - q2q2 + q3q3;// 33
  //---------------------------------------------------------------------------------------------------
  //1-2-3 Representation.
  //Equation (290)
  //Representing Attitude: Euler Angles, Unit Quaternions, and Rotation Vectors, James Diebel.
  // Existing PX4 EKF code was generated by MATLAB which uses coloum major order matrix.
  euler[0] = atan2f(Rot_matrix[5], Rot_matrix[8]);  //! Roll
  euler[1] = -asinf(Rot_matrix[2]);                 //! Pitch
  euler[2] = atan2f(Rot_matrix[1], Rot_matrix[0]);
  //---------------------------------------------------------------------------------------------------
  //DCM . ground to body
  for (int i = 0; i < 9; i++) {
    *(&(imu.DCMgb[0][0]) + i) = Rot_matrix[i];
  }
  //---------------------------------------------------------------------------------------------------
  imu.rollRad = euler[0];
  imu.pitchRad = euler[1];
  imu.yawRad = euler[2];
  imu.roll = euler[0] * 180.0f / M_PI_F;
  imu.pitch = euler[1] * 180.0f / M_PI_F;
  imu.yaw = euler[2] * 180.0f / M_PI_F;
  //---------------------------------------------------------------------------------------------------
}
void IMU_show() {
  lg(imu.roll); lg(','); lg(imu.pitch); lg(','); lg(imu.yaw); lg(','); lg(); //lg(',');
}
void IMU_loop() {
  MPU6050_read();//MPU6050_show();
  IMUSO3Thread();
  IMU_show();
}


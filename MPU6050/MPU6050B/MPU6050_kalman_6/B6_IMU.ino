#define  RAW_TO_G  16384.0f// 把原始数据转换为G
#define  RAW_TO_DS  131.0f// 把原始数据转换为"度/秒"
//---------------------------------------------------------------------------------------
float  RwAcc[3];    //(G) 通过加速度传感器把重力加速度投影在x/y/z三轴上
float  Gyro[3];     //(°/s) 陀螺仪读取
float  RwGyro[3];   //(°/s) 重新读取陀螺仪
float  Awz[2];      //(°) XZ/ YZ平面和Z轴（度）R的投影之间的角度
float  RwEst[3];    //欧拉角
//---------------------------------------------------------------------------------------
unsigned long currentTime = 0;
unsigned long lastTime = 0;
unsigned long interval = 0;
//---------------------------------------------------------------------------------------
float wGyro = 10.0;
boolean firstSample = true;
//---------------------------------------------------------------------------------------
void sensorsToPhysics(float ax, float ay, float az, float gx, float gy, float gz) {
  // 把原始数据转换为G
  RwAcc[0] = float(ax) / RAW_TO_G;
  RwAcc[1] = float(ay) / RAW_TO_G;
  RwAcc[2] = float(az) / RAW_TO_G;
  // 把原始数据转换为"度/秒"
  Gyro[0] = float(gx) / RAW_TO_DS;
  Gyro[1] = float(gy) / RAW_TO_DS;
  Gyro[2] = float(gz) / RAW_TO_DS;
}
void IMU_loop() {
  int w = 0;
  float tmpf = 0.0f;
  float rwTemp;
  int signRzGyro;
  //------------------------------------------------
  sensorsToPhysics(ax, ay, az, gx, gy, gz);
  // normalize3DVec(RwAcc);
  rwTemp = fastInvSqrt(RwAcc[0] * RwAcc[0] + RwAcc[1] * RwAcc[1] + RwAcc[2] * RwAcc[2]);
  RwAcc[0] *= rwTemp; RwAcc[1] *= rwTemp; RwAcc[2] *= rwTemp;
  //------------------------------------------------
  currentTime = millis();
  interval = (lastTime > 0) ? currentTime - lastTime : 0;
  lastTime = currentTime;
  //------------------------------------------------
  if (firstSample) { // || float.isNaN(RwEst[0])) { //NaN用来等待检查从arduino过来的数据
    for (w = 0; w <= 2; w++) RwEst[w] = RwAcc[w]; //初始化加速度传感器读数
  } else {
    // 对RwGyro进行评估
    if (abs(RwEst[2]) < 0.1) {
      // Rz值非常的小，它的作用是作为Axz与Ayz的计算参照值，防止放大的波动产生错误的结果。
      // 这种情况下就跳过当前的陀螺仪数据，使用以前的。
      for (w = 0; w <= 2; w++) RwGyro[w] = RwEst[w];
    } else {
      // ZX/ZY平面和Z轴R的投影之间的角度，基于最近一次的RwEst值
      for (w = 0; w <= 1; w++) {
        tmpf = Gyro[w];                             //获取当前陀螺仪的deg/s
        tmpf *= interval / 1000.0f;                     // 得到角度变化值
        Awz[w] = atan2(RwEst[w], RwEst[2]) * 180 / PI;  // 得到角度并转换为度
        Awz[w] += tmpf;             // 根据陀螺仪的运动得到更新后的角度
      }

      // 判断RzGyro是多少，主要看Axz的弧度是多少
      // 当Axz在-90 ..90 => cos(Awz) >= 0这个范围内的时候RzGyro是准确的
      signRzGyro = (cos(Awz[0] * PI / 180) >= 0) ? 1 : -1;

      //从Awz的角度值反向计算RwGyro的公式请查看网页
      //http://starlino.com/imu_guide.html
      for (w = 0; w <= 1; w++) {
        RwGyro[0] = sin(Awz[0] * PI / 180);
        RwGyro[0] /= sqrt( 1 + squared(cos(Awz[0] * PI / 180)) * squared(tan(Awz[1] * PI / 180)) );
        RwGyro[1] = sin(Awz[1] * PI / 180);
        RwGyro[1] /= sqrt( 1 + squared(cos(Awz[1] * PI / 180)) * squared(tan(Awz[0] * PI / 180)) );
      }
      RwGyro[2] = signRzGyro * sqrt(1 - squared(RwGyro[0]) - squared(RwGyro[1]));
    }

    // 把陀螺仪与加速度传感器的值进行结合
    for (w = 0; w <= 2; w++) RwEst[w] = (RwAcc[w] + wGyro * RwGyro[w]) / (1 + wGyro);

    //normalize3DVec(&RwEst[0], &RwEst[1], &RwEst[2]);
    rwTemp = fastInvSqrt(RwEst[0] * RwEst[0] + RwEst[1] * RwEst[1] + RwEst[2] * RwEst[2]);
    RwEst[0] *= rwTemp; RwEst[1] *= rwTemp; RwEst[2] *= rwTemp;
  }

  firstSample = false;
}
//---------------------------------------------------------------------------------------
void IMU_show() {
  lg(RwEst[0]); lg(", "); lg(RwEst[1]); lg(", "); lg(RwEst[2]); lg(", ");  lg();
}
//---------------------------------------------------------------------------------------
//void normalize3DVec(float* v0, float* v1, float* v2) {
//  float R;
//  R = sqrt(*v0 * *v0 + *v1 * *v1 + *v2 * *v2);
//  *v0 /= R; *v1 /= R; *v2 /= R;
//}
//void normalize3DVec(float vector[]) {
//  float R;
//  R = sqrt(vector[0] * vector[0] + vector[1] * vector[1] + vector[2] * vector[2]);
//  vector[0] /= R; vector[1] /= R; vector[2] /= R;
//}
float squared(float x) {
  return x * x;
}
float fastInvSqrt(float x) {//快速倒置开方
  float halfx = 0.5f * x;
  float y = x;
  long i = *(long*)&y;
  i = 0x5f3759df - (i >> 1);
  y = *(float*)&i;
  y = y * (1.5f - (halfx * y * y));
  return y;
}
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------

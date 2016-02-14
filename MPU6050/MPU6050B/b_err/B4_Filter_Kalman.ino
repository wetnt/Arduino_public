typedef struct CFilterOne {//一阶滤波
  //--------------------------------------------------------
  float angle;//一阶滤波角度输出
  float K = 0.05; // 对加速度计取值的权重
  float dt = 20 * 0.001; //注意：dt的取值为滤波器采样时间
  //--------------------------------------------------------
  float lvbo(float angle_m, float gyro_m) { //一阶滤波
    angle = K * angle_m + (1 - K) * (angle + gyro_m * dt);
    return angle;
  }
  //--------------------------------------------------------
} CFilterOne;
typedef struct CFilterTwo {//二阶滤波
    //--------------------------------------------------------
  public :
    float angle;//er阶滤波角度输出
    float K = 0.2; // 对加速度计取值的权重
    float dt = 20 * 0.001; //注意：dt的取值为滤波器采样时间
    //--------------------------------------------------------
    //    CFilterTwo CFilterTwoInit(float K_ = 0.2, float t_ = 20) {
    //      K = K_; dt = t_ * 0.001;
    //      return me;
    //    }
    //--------------------------------------------------------
  private : float x1, x2, y1; //运算中间变量
    //--------------------------------------------------------
  public :
    float lvbo(float angle_m, float gyro_m) { //二阶滤波
      //--------------------------------------------------------
      x1 = (angle_m - angle) * (1 - K) * (1 - K);
      y1 = y1 + x1 * dt;
      x2 = y1 + 2 * (1 - K) * (angle_m - angle) + gyro_m;
      angle = angle + x2 * dt ;
      //--------------------------------------------------------
      return angle;
      //--------------------------------------------------------
    }
} CFilterTwo;
typedef struct CKalman { //卡尔曼滤波
    //--------------------------------------------------------
    //卡尔曼滤波参数与函数
    float angleK, angleK_dot;//角度和角速度
    float angle_0, angle_dot_0;//采集来的角度和角速度
    float dt = 20 * 0.001; //注意：dt的取值为滤波器采样时间
    //--------------------------------------------------------
  private:
    //运算中间变量
    float P[2][2] = {{ 1, 0 }, { 0, 1 }};
    float Pdot[4] = { 0, 0, 0, 0};
    float Q_angle = 0.001, Q_gyro = 0.005; //角度数据置信度,角速度数据置信度
    float R_angle = 0.5 , C_0 = 1;
    float q_bias, angle_err, PCt_0, PCt_1, E, K_0, K_1, t_0, t_1;
  public:
    float lvbo(double angle_m, double gyro_m) { //卡尔曼滤波
      angleK += (gyro_m - q_bias) * dt;
      angle_err = angle_m - angleK;
      Pdot[0] = Q_angle - P[0][1] - P[1][0];
      Pdot[1] = - P[1][1]; Pdot[2] = - P[1][1]; Pdot[3] = Q_gyro;
      P[0][0] += Pdot[0] * dt; P[0][1] += Pdot[1] * dt;
      P[1][0] += Pdot[2] * dt; P[1][1] += Pdot[3] * dt;
      PCt_0 = C_0 * P[0][0]; PCt_1 = C_0 * P[1][0];
      E = R_angle + C_0 * PCt_0;
      K_0 = PCt_0 / E; K_1 = PCt_1 / E;
      t_0 = PCt_0; t_1 = C_0 * P[0][1];
      P[0][0] -= K_0 * t_0; P[0][1] -= K_0 * t_1;
      P[1][0] -= K_1 * t_0; P[1][1] -= K_1 * t_1;
      angleK += K_0 * angle_err; //最优角度
      q_bias += K_1 * angle_err;
      angleK_dot = gyro_m - q_bias; //最优角速度
      return angleK;
    }
    //--------------------------------------------------------
} CKalman;

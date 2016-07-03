void computeIMU() {
  uint8_t axis;
  static int16_t gyroADCprevious[3] = {0,0,0};
  int16_t gyroADCp[3];
  int16_t gyroADCinter[3];
  static uint32_t timeInterleave = 0;

  ACC_getADC();            //获取加速度计的ADC值
  getEstimatedAttitude();  //姿态估计
  Gyro_getADC();           //获取陀螺仪的ADC值

  for (axis = 0; axis < 3; axis++)
    gyroADCp[axis] =  gyroADC[axis];  //保存传感器的数据
  timeInterleave=micros();
  annexCode();  //通过串口向GUI发送MWC的实时数据
  if ((micros()-timeInterleave)>650) {  //通过实测,如果没有这个等待,整个运行周期有可能小于2ms,这样就不能满足输出给电调最大信号的要求了
     annex650_overrun_count++;  //运行时间超时,并进行计数
  } else {
     while((micros()-timeInterleave)<650) ; //直到时间超过650us
  }
  Gyro_getADC();  //获取陀螺仪的ADC值
  for (axis = 0; axis < 3; axis++) {  //陀螺仪的值求平均
    gyroADCinter[axis] =  gyroADC[axis]+gyroADCp[axis];
    //通过试验获得前面的值和当前值的权重
    gyroData[axis] = (gyroADCinter[axis]+gyroADCprevious[axis])/3;  //对最近三次的Gyro数据求平均值
    gyroADCprevious[axis] = gyroADCinter[axis]>>1;  //除2
    //gyroData=［ADC+ADCp+（ADC+ADCp）/2］/3,化简 gyroData=1/2（ADC+ADCp）,最终得到：gyroData=1/2ADC+（1-1/2）ADCp
    //其中：gyroData为本次滤波输出值,ADC为本次陀螺仪测量值，ADCp为上一次的滤波输出值,很明显它符合公式一,说明它就是采用的一阶滞后滤波
    //实际物理意义：公式中输出等于本次采样值乘以置信度与上一次滤波输出值乘以1与置信度的差的和。即对本次采样值和上次的输出值的信任度都为50%,在后面的算法中置信度一般都很小,即对本次的采样的信任度很小
  }
}

#define ACC_LPF_FACTOR 4       //加速度计的低通滤波因子
#define GYR_CMPF_FACTOR 600    //设置陀螺仪权重在加速度计值与加速度互补滤波值的权重因子

#define INV_GYR_CMPF_FACTOR   (1.0f / (GYR_CMPF_FACTOR  + 1.0f))

#define GYRO_SCALE ((2279 * PI)/((32767.0f / 4.0f ) * 180.0f * 1000000.0f))   //0.0049 e-6
//+-2000度/秒, 不考虑修正系数，此处的理论值应为：(2000/8192)*(PI/180)
//8192即为32767/4,参见“Gyro_getADC ()”中的rawADC>>2
//经验值应该是 #define GYRO_SCALE (1.0f/200e6f)

typedef struct fp_vector {		
  float X,Y,Z;		
} t_fp_vector_def;

typedef union {	  //共用体
  float A[3];		
  t_fp_vector_def V;		
} t_fp_vector;

int16_t _atan2(float y, float x){  //坐标(x,y)与x轴形成的角度
  float z = y / x;
  int16_t a;
  if ( abs(y) < abs(x) ){
     a = 573 * z / (1.0f + 0.28f * z * z);    //180°/pi = 57.3
   if (x<0) {
     if (y<0) a -= 1800;    //-180°
     else a += 1800;        //+180°
   }
  } else {
   a = 900 - 573 * z / (z * z + 0.28f);
   if (y<0) a -= 1800;      //-180°
  }
  return a;
}

//根据陀螺仪的角度值使用旋转矩阵的小角度近似算法
void rotateV(struct fp_vector *v,float* delta) {
  fp_vector v_tmp = *v;
  v->Z -= delta[ROLL]  * v_tmp.X + delta[PITCH] * v_tmp.Y;
  v->X += delta[ROLL]  * v_tmp.Z - delta[YAW]   * v_tmp.Y;
  v->Y += delta[PITCH] * v_tmp.Z + delta[YAW]   * v_tmp.X;
}

static int32_t accLPF32[3]    = {0, 0, 1};
static float invG; // 1/|G|

static t_fp_vector EstG;         //共用体

void getEstimatedAttitude(){     //姿态估计
  uint8_t axis;
  int32_t accMag = 0;
  float scale, deltaGyroAngle[3];
  static uint16_t previousT;
  uint16_t currentT = micros();

  scale = (currentT - previousT) * GYRO_SCALE;
  previousT = currentT;

  //初始化
  for (axis = 0; axis < 3; axis++) {
    deltaGyroAngle[axis] = gyroADC[axis]  * scale;        //陀螺仪角度: 角速度*两次间隔时间

    accLPF32[axis]    -= accLPF32[axis]>>ACC_LPF_FACTOR;
    accLPF32[axis]    += accADC[axis];
    accSmooth[axis]    = accLPF32[axis]>>ACC_LPF_FACTOR;  //等效于：0.9375*accSmooth +0.0625*accADC
    accMag += (int32_t)accSmooth[axis]*accSmooth[axis] ;  //加速度模的平方
  }
  accMag = accMag*100/((int32_t)acc_1G*acc_1G);           //加速度模的平方扩大100倍，再标准化处理
  rotateV(&EstG.V,deltaGyroAngle);                        //旋转计算
  if ( abs(accSmooth[ROLL])<acc_25deg && abs(accSmooth[PITCH])<acc_25deg && accSmooth[YAW]>0) {
    f.SMALL_ANGLES_25 = 1;
  } else {
    f.SMALL_ANGLES_25 = 0;
  }
  //互补滤波(陀螺漂移修正)
  //如果ACC>1.15g或<0.85g(|a|-1<0.15),ACC向量超出限制范围,我们使加速度计在角度估算中的作用无效。
  //为实现这个约束条件,超出范围部分我们直接跳过过滤器,EstV已经陀螺旋转修正
  if (  72 < accMag && accMag < 133 )    //0.85的平方*100 = 72, 1.15的平方*100 = 132
    for (axis = 0; axis < 3; axis++) {
      EstG.A[axis] = (EstG.A[axis] * GYR_CMPF_FACTOR + accSmooth[axis]) * INV_GYR_CMPF_FACTOR;
      //EstG.A = 0.99833 * EstG.A + 0.00166 * accSmooth. EstG.A和EstG.V为共用体,EstG.V为这次的角度,在上面已经使用旋转矩阵法将陀螺仪积分进去了
    }
  //姿态估计向量
  angle[ROLL]  =  _atan2(EstG.V.X , EstG.V.Z) ;
  angle[PITCH] =  _atan2(EstG.V.Y , EstG.V.Z) ;
}


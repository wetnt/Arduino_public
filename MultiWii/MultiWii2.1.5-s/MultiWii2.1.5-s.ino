/*****  MultiWiiCopter V2.1.5简化版  *****/

#include "config.h"    //MWC的配置头文件
#include "def.h"       //MWC的定义头文件
#define  VERSION  215  //版本号，2.1.5精简版

/*****  RC 指令名称  *****/

enum rc {    //遥控枚举类型变量定义
  ROLL,      //0
  PITCH,     //1
  YAW,       //2
  THROTTLE,  //3
  AUX1,      //4
  AUX2,      //5
  AUX3,      //6
  AUX4       //7
};

enum pid {    //PID枚举类型变量定义
  PIDROLL,    //0
  PIDPITCH,   //1
  PIDYAW,     //2
  PIDALT,     //3
  PIDPOS,     //4
  PIDPOSR,    //5
  PIDNAVR,    //6
  PIDLEVEL,   //7, PID外环控制系数
  PIDMAG,     //8
  PIDVEL,     //9, 当前未使用
  PIDITEMS    //10
};

enum box {  //功能枚举类型变量定义
  BOXARM,
  BOXANGLE,
  BOXHORIZON,
  BOXBARO,
  CHECKBOXITEMS
};

const char boxnames[] PROGMEM = //动态生成GUI的配置名称,把这个静态数组放在MCU的FLASHROM中
  "ARM;"
  "ANGLE;"
  "HORIZON;"
  "BARO;"
;

const uint8_t boxids[] PROGMEM = {//功能的ID号
  0, //"ARM;"
  1, //"ANGLE;"
  2, //"HORIZON;"
  3, //"BARO;"
};

static uint32_t currentTime = 0;   //当前时间
static uint16_t previousTime = 0;  //前次时间
static uint16_t cycleTime = 0;     //循环周期时间
static uint16_t calibratingA = 0;  //加速度校准
static uint16_t calibratingG;      //陀螺仪校准
static uint16_t acc_1G;            //1G加速度值
static uint16_t acc_25deg;         //25°的加速度值
static int16_t  gyroADC[3],accADC[3],accSmooth[3];  //陀螺仪AD采集值，加速度AD采集值，加速度滤波值
static uint8_t  rcOptions[CHECKBOXITEMS];  //遥控选择工作模式
/*********************/
static int32_t  EstAlt;            //估计高度
static int16_t  sonarAlt;          //超声波高度
static uint32_t Sonar_endTime = 0; //上次超声测量可靠结束时间
/*********************/

struct flags_struct {          //标志结构变量
  uint8_t OK_TO_ARM :1 ;       //锁定状态标识
  uint8_t ARMED :1 ;           //解锁状态标识
  uint8_t ACC_CALIBRATED :1 ;  //加速度校准
  uint8_t ANGLE_MODE :1 ;      //ANGLE模式
  uint8_t HORIZON_MODE :1 ;    //HORIZON模式
  uint8_t BARO_MODE :1 ;
  uint8_t SMALL_ANGLES_25 :1 ; //倾斜角小于25度
} f;

static int16_t  i2c_errors_count = 0;  //I2C错误计数
static int16_t  annex650_overrun_count = 0;  //650微妙超时次数计数

/***** 遥控 *****/
#define MINCHECK 1150  //遥控器动态范围最小设定值
#define MAXCHECK 1850  //遥控器动态范围最大设定值

#define ROL_LO  (1<<(2*ROLL))      //0000 0001
#define ROL_CE  (3<<(2*ROLL))      //0000 0011
#define ROL_HI  (2<<(2*ROLL))      //0000 0010
#define PIT_LO  (1<<(2*PITCH))     //0000 0100
#define PIT_CE  (3<<(2*PITCH))     //0000 1100
#define PIT_HI  (2<<(2*PITCH))     //0000 1000
#define YAW_LO  (1<<(2*YAW))       //0001 0000
#define YAW_CE  (3<<(2*YAW))       //0011 0000
#define YAW_HI  (2<<(2*YAW))       //0010 0000
#define THR_LO  (1<<(2*THROTTLE))  //0100 0000
#define THR_CE  (3<<(2*THROTTLE))  //1100 0000
#define THR_HI  (2<<(2*THROTTLE))  //1000 0000

static int16_t rcData[RC_CHANS];    //遥控接收数据,范围[1000;2000]
static int16_t rcCommand[4];        //遥控命令: THROTTLE - [1000;2000], ROLL/PITCH/YAW - [-500;+500]  
static int16_t lookupPitchRollRC[6];//查找表: PITCH+ROLL, RATE & EXPO 
static int16_t lookupThrottleRC[11];//查找表: THROTTLE, MID & EXPO   

/***** gyro+acc IMU *****/
static int16_t gyroData[3] = {0,0,0};  //陀螺仪数据
static int16_t gyroZero[3] = {0,0,0};  //陀螺仪零点
static int16_t angle[2]    = {0,0};    //姿态角度, 180度 = 1800

/***** 电机 *****/
static int16_t axisPID[3];    //三个轴的PID值
static int16_t motor[4];      //电机的PWM输出值

/***** EEPROM布局定义 *****/
static uint8_t dynP8[3], dynD8[3];

static struct { 
  uint8_t currentSet;    //当前设置
  int16_t accZero[3];    //加速度零点
  int16_t magZero[3];    //罗盘零点,此处不用
  uint8_t checksum;      //校验和 
} global_conf;           //全局配置

static struct {
  uint8_t checkNewConf;    //检查新配置
  uint8_t P8[PIDITEMS], I8[PIDITEMS], D8[PIDITEMS];  //PID
  uint8_t rcRate8;         //遥控 RATE
  uint8_t rcExpo8;         //遥控 EXPO
  uint8_t rollPitchRate;   //横滚、俯仰比率
  uint8_t yawRate;         //偏航比率
  uint8_t dynThrPID;       //动态油门PID
  uint8_t thrMid8;         //油门 MID
  uint8_t thrExpo8;        //油门 EXPO
  int16_t angleTrim[2];    //角度矫正
  uint16_t activate[CHECKBOXITEMS];  //功能激活
  uint8_t powerTrigger1;   //未使用
  int16_t minthrottle;     //最小油门
  uint8_t  checksum;       //校验和 
} conf;                    //配置参数

  // default POSHOLD control gains
  #define POSHOLD_P              .11
  #define POSHOLD_I              0.0
  #define POSHOLD_IMAX           20        // degrees

  #define POSHOLD_RATE_P         2.0
  #define POSHOLD_RATE_I         0.08      // Wind control
  #define POSHOLD_RATE_D         0.045     // try 2 or 3 for POSHOLD_RATE 1
  #define POSHOLD_RATE_IMAX      20        // degrees

  // default Navigation PID gains
  #define NAV_P                  1.4
  #define NAV_I                  0.20      // Wind control
  #define NAV_D                  0.08      //
  #define NAV_IMAX               20        // degrees

//油门映射
void annexCode() { //每个循环都会执行，若执行时间少于650MS则不会影响主循环的执行
  static uint32_t calibratedAccTime;  //加速度校准时间
  uint16_t tmp,tmp2;
  uint8_t axis,prop1,prop2;

  #define BREAKPOINT 1500
  // PITCH俯仰 & ROLL横滚 根据油门值动态PID调整
  if (rcData[THROTTLE]<BREAKPOINT) {  //油门小于1500
    prop2 = 100;
  } else {  //油门大于1500
    if (rcData[THROTTLE]<2000) {  //油门小于2000
      prop2 = 100 - (uint16_t)conf.dynThrPID*(rcData[THROTTLE]-BREAKPOINT)/(2000-BREAKPOINT);
      //dynThrPID 四轴默认0 可以GUI设置   TPA参数              PROP 与动态pid有关。dynThrPIDprop 越小 即油门大小对于PID影响越大。
    } else {  //油门大于2000
      prop2 = 100 - conf.dynThrPID;
    }
  }

  for(axis=0;axis<3;axis++) {
    tmp = min(abs(rcData[axis]-MIDRC),500);
    if(axis!=2) { //ROLL横滚 & PITCH俯仰
      tmp2 = tmp/100;  //偏移量除以100
      rcCommand[axis] = lookupPitchRollRC[tmp2] + (tmp-tmp2*100) * (lookupPitchRollRC[tmp2+1]-lookupPitchRollRC[tmp2]) / 100;
      //差值法求用于控制的rc信号，取决于roll pitch 曲线
      prop1 = 100-(uint16_t)conf.rollPitchRate*tmp/500;  //tmp=rc数据与中立值差的绝对值,rate[0 100];
      prop1 = (uint16_t)prop1*prop2/100;  //根据prop2 修改 prop1
    } else {  // YAW航向
      rcCommand[axis] = tmp;
      prop1 = 100-(uint16_t)conf.yawRate*tmp/500;  //tmp=RC距离中点值,yawRate[0 100],默认为0
    }
    dynP8[axis] = (uint16_t)conf.P8[axis]*prop1/100;  //动态YAW PID参数
    dynD8[axis] = (uint16_t)conf.D8[axis]*prop1/100;
    if (rcData[axis]<MIDRC) rcCommand[axis] = -rcCommand[axis];
  }
  tmp = constrain(rcData[THROTTLE],MINCHECK,2000);  //令tmp=rcData[THROTTLE]
  tmp = (uint32_t)(tmp-MINCHECK)*1000/(2000-MINCHECK); //把油门控制[MINCHECK;2000]转化为[0;1000]
  tmp2 = tmp/100;  //通过油门曲线对油门控制量进行换算
  rcCommand[THROTTLE] = lookupThrottleRC[tmp2] + (tmp-tmp2*100) * (lookupThrottleRC[tmp2+1]-lookupThrottleRC[tmp2]) / 100; // [0;1000] -> expo -> [conf.minthrottle;MAXTHROTTLE]

  if ( (calibratingA>0) || (calibratingG>0) ) { //校准期间
    LEDPIN_TOGGLE;
  } else {
    if (f.ACC_CALIBRATED) {LEDPIN_OFF;}  //ACC校准结束,灯灭
    if (f.ARMED) {LEDPIN_ON;}  //解锁灯亮
  }

  if ( currentTime > calibratedAccTime ) {  //每100S检测一次
    if (! f.SMALL_ANGLES_25) {  //倾斜太大或者未校准ACC
      f.ACC_CALIBRATED = 0;  //校准标志位清0
      LEDPIN_TOGGLE;
      calibratedAccTime = currentTime + 100000;
    } else {
      f.ACC_CALIBRATED = 1;
    }
  }
  serialCom();
}

/***** 解锁 *****/
void go_arm() {
  if(calibratingG == 0 && f.ACC_CALIBRATED) {
    if(!f.ARMED) { //若未解锁
      f.ARMED = 1;  //解锁标志位置1
    }
  } else if(!f.ARMED) { 
    blinkLED(2,255,1);  //灯闪烁
  }
}
/***** 加锁 *****/
void go_disarm() {
  if (f.ARMED) {
    f.ARMED = 0;  //解锁标志位清0
  }
}

void setup() {              //初始化
  SerialOpen(115200);        //打开串口，波特率115200
  LEDPIN_PINMODE;            //设置LED引脚状态
  initOutput();              //使能所有PWM引脚
  global_conf.currentSet=0;  //当前设置置0
  readEEPROM();              //读EEPROM
  readGlobalSet();           //读全局设置
  readEEPROM();              //加载当前设定数据
  blinkLED(2,40,global_conf.currentSet+1);  //状态灯启动闪烁
  configureReceiver();       //设置RC接收引脚状态，如aux2
  initSensors();             //初始化传感器芯片
  previousTime = micros();   //读取当前时间值
  calibratingG = 512;        //校正采集次数512
  ADCSRA |= _BV(ADPS2) ; ADCSRA &= ~_BV(ADPS1); ADCSRA &= ~_BV(ADPS0); //这种设置的AD读取速度使得分辨率损失小
  //_BV(ADPS2)实际上就是把ADPS2位置1
  f.SMALL_ANGLES_25=1;       //倾斜角小于25度
}

// ******** 主循环 *********
void loop () {
  static uint8_t rcDelayCommand;           //20ms周期整倍数计数
  static uint8_t rcSticks;                 //摇杆位置
  uint8_t axis,i;                          //轴, i
  int16_t error,errorAngle;                //误差，角度误差
  int16_t delta,deltaSum;                  //δ,δ和
  int16_t PTerm,ITerm,DTerm;               //P, I, D
  int16_t PTermACC = 0 , ITermACC = 0 , PTermGYRO = 0 , ITermGYRO = 0;
  static int16_t lastGyro[3] = {0,0,0};    //
  static int16_t delta1[3],delta2[3];      //
  static int16_t errorGyroI[3] = {0,0,0};  //
  static int16_t errorAngleI[2] = {0,0};   //
  static uint32_t rcTime  = 0;             //
  static int16_t initialThrottleHold;      //
  static uint32_t timestamp_fixated = 0;   //

  if (currentTime > rcTime ) {             //大于20ms执行一次
    rcTime = currentTime + 20000;          //设定下个周期时间值
    computeRC();                           //对接收的遥控信号进行循环滤波，取4组数据，80MS，算平均值，大于平均值的减小2，小于平均值的增大2
    //检测摇杆组合位置
    uint8_t stTmp = 0;
    for(i=0;i<4;i++) {
      stTmp >>= 2;  //stTmp除以4
      if(rcData[i] > MINCHECK) stTmp |= 0x80;      //MINCHECK=1150, 1000 0000B
      if(rcData[i] < MAXCHECK) stTmp |= 0x40;      //MAXCHECK=1850, 0100 0000B
    }
    if(stTmp == rcSticks) {
      if(rcDelayCommand<250) rcDelayCommand++;  //若摇杆在最大最小位置外的状态保持周期数小于250,则rcDelayCommand+1
    } else rcDelayCommand = 0;  //否则清0
    rcSticks = stTmp;  //保存stTmp
    
    //执行动作    
    if (rcData[THROTTLE] <= MINCHECK) {  //油门在最低位置
      errorGyroI[ROLL] = 0; errorGyroI[PITCH] = 0; errorGyroI[YAW] = 0;  //roll,pitch,yaw陀螺仪误差置0
      errorAngleI[ROLL] = 0; errorAngleI[PITCH] = 0;  //roll,pitch角度误差置0
      if (conf.activate[BOXARM] > 0) {    //通过 ARM BOX 解锁/加锁
        if ( rcOptions[BOXARM] && f.OK_TO_ARM ) go_arm(); else if (f.ARMED) go_disarm();  //解锁,否则加锁
      }
    }
    if(rcDelayCommand == 20) {  //若摇杆在最大最小位置外的状态保持周期数 = 20 (20*20 = 400ms)
      if(f.ARMED) {  //处于解锁时
        if (conf.activate[BOXARM] == 0 && rcSticks == THR_LO + YAW_LO + PIT_CE + ROL_CE) go_disarm();    //通过YAW加锁
      } else {  //处于加锁时
        i=0;
        if (rcSticks == THR_LO + YAW_LO + PIT_LO + ROL_CE) {    //GYRO（陀螺仪）校准
          calibratingG=512;
        }
        if (conf.activate[BOXARM] == 0 && rcSticks == THR_LO + YAW_HI + PIT_CE + ROL_CE) go_arm();  //通过YAW解锁
        else if (rcSticks == THR_HI + YAW_LO + PIT_LO + ROL_CE) calibratingA=512;   //油门throttle=最大, 航向yaw=左, 俯仰pitch=最小, 横滚roll=中位, 加速度校准
        i=0;
        if      (rcSticks == THR_HI + YAW_CE + PIT_HI + ROL_CE) {conf.angleTrim[PITCH]+=2; i=1;}  //角度矫正, 计算PID时有用
        else if (rcSticks == THR_HI + YAW_CE + PIT_LO + ROL_CE) {conf.angleTrim[PITCH]-=2; i=1;}
        else if (rcSticks == THR_HI + YAW_CE + PIT_CE + ROL_HI) {conf.angleTrim[ROLL] +=2; i=1;}
        else if (rcSticks == THR_HI + YAW_CE + PIT_CE + ROL_LO) {conf.angleTrim[ROLL] -=2; i=1;}
        if (i) {
          writeParams(1);
          rcDelayCommand = 0;    //周期整倍数计数置0
        }
      }
    }
    
    uint16_t auxState = 0;  //测量辅助通道位置, 小于1300, 1300到1700, 大于1700
    for(i=0;i<4;i++)
      auxState |= (rcData[AUX1+i]<1300)<<(3*i) | (1300<rcData[AUX1+i] && rcData[AUX1+i]<1700)<<(3*i+1) | (rcData[AUX1+i]>1700)<<(3*i+2);
    for(i=0;i<CHECKBOXITEMS;i++)
      rcOptions[i] = (auxState & conf.activate[i])>0;  //将辅助通道位置与选择的开启方式比较，保存开启的模式
    if ( rcOptions[BOXANGLE]) {  //开启自稳ANGLE模式
      if (!f.ANGLE_MODE) {
        errorAngleI[ROLL] = 0; errorAngleI[PITCH] = 0;
        f.ANGLE_MODE = 1;
      }  
    } else {
       f.ANGLE_MODE = 0;
    }
    if ( rcOptions[BOXHORIZON] ) {  //开启HORIZON模式
      f.ANGLE_MODE = 0;  //关闭自稳ANGLE模式
      if (!f.HORIZON_MODE) {  //若HORIZON模式未开启
        errorAngleI[ROLL] = 0; errorAngleI[PITCH] = 0;
        f.HORIZON_MODE = 1;  //开启HORIZON模式
      }
    } else {
      f.HORIZON_MODE = 0;  //关闭HORIZON模式
    }

    if (rcOptions[BOXARM] == 0) f.OK_TO_ARM = 1;
 
  }  //RC循环结束
  
  if(micros() > Sonar_endTime) {
    Sonar_update();  //读取超声测距
    EstAlt = (int32_t)sonarAlt;
  }
  
  computeIMU();  //计算IMU
  currentTime = micros();  //读取当前时间
  cycleTime = currentTime - previousTime;  //计算循环周期时间
  previousTime = currentTime;  //保存当前时间

  /**** PITCH俯仰 & ROLL横滚 & YAW航向 PID ****/
  int16_t prop;
  prop = min(max(abs(rcCommand[PITCH]),abs(rcCommand[ROLL])),500); //限定控制量的范围 [0;500]

  for(axis=0;axis<3;axis++) {  //循环3次分别对俯仰，横滚，和航向三个轴计算PID
    if ((f.ANGLE_MODE || f.HORIZON_MODE) && axis<2 ) { //是否在自稳的模式，如果是，执行自稳的PID计算
      //计算PID的第一项（偏差 * P）
      errorAngle = constrain((rcCommand[axis]<<1),-500,+500) - angle[axis] + conf.angleTrim[axis]; //求出传感器数据和遥控数据算的偏差
      PTermACC = ((int32_t)errorAngle*conf.P8[PIDLEVEL])>>7;  //偏差乘上P，再除以128
      PTermACC = constrain(PTermACC,-conf.D8[PIDLEVEL]*5,+conf.D8[PIDLEVEL]*5);  //算出来的数和我们设置的D值的5倍作比较,不能大于D的五倍
      //计算PID的第二项（偏差积分 *  I）
      errorAngleI[axis]     = constrain(errorAngleI[axis]+errorAngle,-10000,+10000);    //把之前算出来的errorAngle加到errorAngleI[axis]存起来，完成“偏差积分”
      ITermACC              = ((int32_t)errorAngleI[axis]*conf.I8[PIDLEVEL])>>12;       //“偏差积分”乘 I，再除以4096
    }
    
    if ( !f.ANGLE_MODE || f.HORIZON_MODE || axis == 2 ) { //第三个轴(航向,YAW)和特技HORIZON模式的PID部分(特技模式即纯手动模式)
      //之所以方向和特技是用一个算法，是因为这两个都不需要自稳（推杆持续动作，松杆后不恢复）
      if (abs(rcCommand[axis])<500) error =          (rcCommand[axis]<<6)/conf.P8[axis] ; //根据数据大小选择计算方式,节省内存
                               else error = ((int32_t)rcCommand[axis]<<6)/conf.P8[axis] ; //
                               //和之前自稳的最大的区别就是，这里不再用传感器回传的angle来计算偏差，而是用遥控指令
      error -= gyroData[axis];  //用陀螺仪数据对error做一个修正
      PTermGYRO = rcCommand[axis];  //特技模式PID中,PID第一项简单的用rcCommand[axis]来计算,没有乘一个系数
      errorGyroI[axis]  = constrain(errorGyroI[axis]+error,-16000,+16000);   //PID第二项,errorGyroI[axis]+error把每次的偏差都加在一起,同时把偏差控制在(-16000,+16000)之间,防止过大
      
      if (abs(gyroData[axis])>640) errorGyroI[axis] = 0;  //如果陀螺仪的数据过大,那么就把偏差人为地设定为0,防止偏差不断累积出现问题
      ITermGYRO = ((errorGyroI[axis]>>7)*conf.I8[axis])>>6;  //偏差*I再除以系数,得出PID公式第二项
    }
    
    if ( f.HORIZON_MODE && axis<2) {  //特技模式,还需要一点微调
      PTerm = ((int32_t)PTermACC*(512-prop) + (int32_t)PTermGYRO*prop)>>9;  //微调用到prop,这个prop是利用遥控信号算出来的
      ITerm = ((int32_t)ITermACC*(512-prop) + (int32_t)ITermGYRO*prop)>>9;
    } else {  //如果是自稳模式,那么就不用微调,直接赋值
      if ( f.ANGLE_MODE && axis<2) {  //开启自稳: 使用PTermACC,ITermACC
        PTerm = PTermACC;
        ITerm = ITermACC;
      } else {  //如果是第三个轴(方向,YAW),也不需要微调,直接赋值
        PTerm = PTermGYRO;
        ITerm = ITermGYRO;
      }
    }
    //动态P,根据油门大小对P进行微调,油门比较大的时候,P会略小一点
    PTerm -= ((int32_t)gyroData[axis]*dynP8[axis])>>6; 
    //PID公式第三项: 偏差微分 * I
    delta          = gyroData[axis] - lastGyro[axis];  //微分等于陀螺仪数据减去上一次的陀螺仪数据
    lastGyro[axis] = gyroData[axis];   //把前三次测得的陀螺仪数据依次存储在delta,delta1,delta2里
    deltaSum       = delta1[axis]+delta2[axis]+delta;
    delta2[axis]   = delta1[axis];
    delta1[axis]   = delta;
    DTerm = ((int32_t)deltaSum*dynD8[axis])>>5;  //偏差微分
    axisPID[axis] =  PTerm + ITerm - DTerm;  //最终结果等于:偏差*P+偏差积分*I+偏差微分*D
  }
  //参见"浅析MWC飞控PID算法" http://blog.csdn.net/do335maomao/article/details/43899003
  mixTable();      //设置各个电机的输出
  writeMotors();   //电机输出
}

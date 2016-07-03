#define MPU6050_ADDRESS     0x68 //MPU6050地址
#define ACC_ORIENTATION(X, Y, Z)  {accADC[ROLL]  = X; accADC[PITCH]  = -Y; accADC[YAW]  =  Z;}  //板载加速度传感器取向
#define GYRO_ORIENTATION(X, Y, Z) {gyroADC[ROLL] = -Y; gyroADC[PITCH] = -X; gyroADC[YAW] = -Z;}  //板载陀螺仪传感器取向

//MPU6050陀螺滤波器设置
#if defined(MPU6050_LPF_256HZ) || defined(MPU6050_LPF_188HZ) || defined(MPU6050_LPF_98HZ) || defined(MPU6050_LPF_42HZ) || defined(MPU6050_LPF_20HZ) || defined(MPU6050_LPF_10HZ) || defined(MPU6050_LPF_5HZ)
  #if defined(MPU6050_LPF_256HZ)
    #define MPU6050_DLPF_CFG   0
  #endif
  #if defined(MPU6050_LPF_188HZ)
    #define MPU6050_DLPF_CFG   1
  #endif
  #if defined(MPU6050_LPF_98HZ)
    #define MPU6050_DLPF_CFG   2
  #endif
  #if defined(MPU6050_LPF_42HZ)
    #define MPU6050_DLPF_CFG   3
  #endif
  #if defined(MPU6050_LPF_20HZ)
    #define MPU6050_DLPF_CFG   4
  #endif
  #if defined(MPU6050_LPF_10HZ)
    #define MPU6050_DLPF_CFG   5
  #endif
  #if defined(MPU6050_LPF_5HZ)
    #define MPU6050_DLPF_CFG   6
  #endif
#else
    #define MPU6050_DLPF_CFG   0
#endif

uint8_t rawADC[6];                             //加速度,陀螺仪的6个原始AD采集数据
  
/*****  I2C 通用函数  *****/
void i2c_init(void) {                          //I2C初始化
  PORTC &= ~(1<<4); PORTC &= ~(1<<5);          //I2C上拉禁止
  TWSR = 0;                                    //I2C状态寄存器,控制比特率预分频因子(1),参见ATmega168中文手册（P194）
  TWBR = ((F_CPU / I2C_SPEED) - 16) / 2;       //I2C比特率寄存器,参见ATmega168中文手册（P192）
  TWCR = 1<<TWEN;                              //I2C控制寄存器,使能TWI,参见ATmega168中文手册（P193）
}

void i2c_rep_start(uint8_t address) {          //I2C发送重复起始信号
  TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN) ; //TWI中断标志,TWI START状态位,TWI使能,发送重复起始信号
  waitTransmissionI2C();                       //等待传输完成
  TWDR = address;                              //发送设备地址
  TWCR = (1<<TWINT) | (1<<TWEN);               //TWI中断标志,TWI使能
  waitTransmissionI2C();                       //等待传输完成
}

void i2c_stop(void) {                          //I2C停止
  TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);  //TWI中断标志,TWI使能,TWI STOP状态位,发送停止信号
}

void i2c_write(uint8_t data ) {                //I2C写数据
  TWDR = data;                                 //发送数据
  TWCR = (1<<TWINT) | (1<<TWEN);               //TWI中断标志,TWI使能,
  waitTransmissionI2C();                       //等待传输完成
}

uint8_t i2c_read(uint8_t ack) {                //I2C读数据
  TWCR = (1<<TWINT) | (1<<TWEN) | (ack? (1<<TWEA) : 0);  //TWI中断标志,TWI使能,使能TWI应答
  waitTransmissionI2C();                       //等待传输完成
  uint8_t r = TWDR;                            //读数据
  if (!ack) i2c_stop();                        //等待应答，发送STOP信号
  return r;                                    //返回读取的数据
}

void waitTransmissionI2C() {                   //等待传输完成
  uint16_t count = 255;
  while (!(TWCR & (1<<TWINT))) {               //
    count--;
    if (count==0) {                            //判断是否超时
      TWCR = 0;                                //超时强制重置TWINT寄存器
      i2c_errors_count++;                      //超时I2C错误计数加1
      break;
    }
  }
}

size_t i2c_read_to_buf(uint8_t add, void *buf, size_t size) {  //读到缓冲区
  i2c_rep_start((add<<1) | 1);              //I2C读方向
  size_t bytes_read = 0;                    //读字节数置0
  uint8_t *b = (uint8_t*)buf;               //缓冲指针变量
  while (size--) {
    *b++ = i2c_read(size > 0);              //收到除最后一个字节外的所有字节存入缓冲区
    bytes_read++;                           //读字节数加1
  }
  return bytes_read;                        //返回读到的字节数
}

size_t i2c_read_reg_to_buf(uint8_t add, uint8_t reg, void *buf, size_t size) {
  i2c_rep_start(add<<1);                    //I2C写方向
  i2c_write(reg);                           //选择MPU6050的寄存器
  return i2c_read_to_buf(add, buf, size);   //读到缓冲区
}

void i2c_getSixRawADC(uint8_t add, uint8_t reg) {  //通过I2C获取6个原始的AD值
  i2c_read_reg_to_buf(add, reg, &rawADC, 6);       //
}

void i2c_writeReg(uint8_t add, uint8_t reg, uint8_t val) {
  i2c_rep_start(add<<1);                    //I2C写方向
  i2c_write(reg);                           //选择MPU6050的寄存器
  i2c_write(val);                           //val写入寄存器
  i2c_stop();                               //发送I2C停止位
}

/*****  GYRO公用部分  *****/
void GYRO_Common() {    //
  static int16_t previousGyroADC[3] = {0,0,0};
  static int32_t g[3];
  uint8_t axis, tilt=0;

  if (calibratingG>0) {  //校准GYRO
    for (axis = 0; axis < 3; axis++) {
      // Reset g[axis] at start of calibration
      if (calibratingG == 512) {
        g[axis]=0;                          //校准开始,清零g[axis]
      }
      g[axis] +=gyroADC[axis];              //读取512次求和
      gyroADC[axis]=0;                      //清除全局变量准备读下一个值
      gyroZero[axis]=0;                     //
      if (calibratingG == 1) {              //
        gyroZero[axis]=g[axis]>>9;          //除以512,修正校准值
        blinkLED(10,15,1); //the delay causes to beep the buzzer really long 
      }
    }
    calibratingG--;                         //每个主函数执行2次,-2,512次主循环校准结束,512*3ms/2=0.64S
  }
  for (axis = 0; axis < 3; axis++) {
    gyroADC[axis]  -= gyroZero[axis];       //修正校准值
    //anti gyro glitch, limit the variation between two consecutive readings
    gyroADC[axis] = constrain(gyroADC[axis],previousGyroADC[axis]-800,previousGyroADC[axis]+800);
    previousGyroADC[axis] = gyroADC[axis];
  }
}

/*****  ACC公用部分  *****/
void ACC_Common() {
  static int32_t a[3];
  if (calibratingA>0) {                     //校准ACC
    for (uint8_t axis = 0; axis < 3; axis++) {
      if (calibratingA == 512) a[axis]=0;   //校准开始,清零a[axis]
      a[axis] +=accADC[axis];               //读取512次求和
      accADC[axis]=0;
      global_conf.accZero[axis]=0;          //清零全局变量
    }
    //求平均值, Calculate average,Z = acc_1G,存储到EEPROM
    if (calibratingA == 1) {
      global_conf.accZero[ROLL]  = a[ROLL]>>9;  //除以512
      global_conf.accZero[PITCH] = a[PITCH]>>9; //除以512
      global_conf.accZero[YAW]   = (a[YAW]>>9)-acc_1G; //除以512 -1G
      conf.angleTrim[ROLL]   = 0;
      conf.angleTrim[PITCH]  = 0;
      writeGlobalSet(1);                        //写零点信息到EEPROM
    }
    calibratingA--;                             //每个主函数执行1次,-1,512次主循环校准结束,512*2.5ms=1.28S
  }
  accADC[ROLL]  -=  global_conf.accZero[ROLL] ; //修正校准值
  accADC[PITCH] -=  global_conf.accZero[PITCH]; //修正校准值
  accADC[YAW]   -=  global_conf.accZero[YAW] ;  //修正校准值
}

/*****  I2C 陀螺仪和加速度计MPU6050  *****/
void Gyro_init() {                                       //陀螺仪初始化
  TWBR = ((F_CPU / 400000L) - 16) / 2;                   //I2C时钟频率更改为400kHz
  i2c_writeReg(MPU6050_ADDRESS, 0x6B, 0x80);             //PWR_MGMT_1: DEVICE_RESET置1,所有的寄存器复位,随后DEVICE_RESET自动置0
  delay(5);
  i2c_writeReg(MPU6050_ADDRESS, 0x6B, 0x03);             //PWR_MGMT_1: SLEEP 0; CYCLE 0; TEMP_DIS 0; CLKSEL 3 (内部Z轴陀螺仪PLL输出)
  i2c_writeReg(MPU6050_ADDRESS, 0x1A, MPU6050_DLPF_CFG); //CONFIG: 禁用帧同步引脚的采样; 配置数字低通滤波器
  i2c_writeReg(MPU6050_ADDRESS, 0x1B, 0x18);             //GYRO_CONFIG: FS_SEL = 3: 陀螺仪量程 2000度/秒
}

void Gyro_getADC () {                                    //获取陀螺仪的AD值
  i2c_getSixRawADC(MPU6050_ADDRESS, 0x43);
  GYRO_ORIENTATION( ((rawADC[0]<<8) | rawADC[1])>>2 ,    //范围: +/- 8192; +/- 2000 deg/sec
                    ((rawADC[2]<<8) | rawADC[3])>>2 ,    //32768/4 = 8192
                    ((rawADC[4]<<8) | rawADC[5])>>2 );
  GYRO_Common();    //获取校准修正后的陀螺仪值
}

void ACC_init () {
  i2c_writeReg(MPU6050_ADDRESS, 0x1C, 0x10);  //ACCEL_CONFIG: 加速度传感器量程+/-8G
  acc_1G = 512;  //加速度的精度, 1g时候对应的数值,8G时，应为32767/8=4096,但“ACC_getADC ()”函数中rawADC>>3,所以acc_1G=4096/8=512
}

void ACC_getADC () {                                     //获取加速度计的AD值
  i2c_getSixRawADC(MPU6050_ADDRESS, 0x3B);  //
  ACC_ORIENTATION( ((rawADC[0]<<8) | rawADC[1])>>3 ,     //
                   ((rawADC[2]<<8) | rawADC[3])>>3 ,
                   ((rawADC[4]<<8) | rawADC[5])>>3 );
  ACC_Common();    //获取校准修正后的加速度计值
}

void initSensors() {    //传感器初始化
  delay(200);
  delay(100);
  i2c_init();           //I2C初始化
  delay(100);
  Gyro_init();          //陀螺仪初始化
  ACC_init();           //加速度计初始化
  delay(100);
  Sonar_init();
  acc_25deg = acc_1G * 0.423;  //sin(25) = 0.423
}

/*****   超声波测距   *****/
volatile static uint32_t Sonar_starTime = 0;      //超声回波起始时间
volatile static uint32_t Sonar_echoTime = 0;      //超声回波时间
volatile static uint16_t Sonar_waiting_echo = 0;  //等待回波状态

void Sonar_init()          //超声测距初始化
{
  PCICR  |= (1<<PCIE1);    //引脚(Port C)变化中断控制寄存器,使能中断向量 
  PCMSK1 |= (1<<PCINT10);  //A2(PC2)作为回波输入,引脚变化屏蔽寄存器,决定哪些引脚触发中断
  DDRC |= 0x08;            //A3(PC3)作为超声波触发输出
  Sonar_update();          //发送超声测距触发脉冲
}

ISR(PCINT1_vect) {         //中断测量超声距离
    if (PINC & 1<<PCINT10) {     //indicates if the bit 0 of the arduino port [B0-B7] is at a high state
      Sonar_starTime = micros();                  //记录测距回波起始时间
      Sonar_endTime = Sonar_starTime + 60000;     //设定下次测距触发时间大于60ms
    }
    else {
      Sonar_echoTime = micros() - Sonar_starTime; //回波时间(微秒)
      if (Sonar_echoTime <= 700*58) {             //有效距离对应时间
        sonarAlt = Sonar_echoTime / 58;           //超声距离cm
      }
      else
      {
        sonarAlt = -1;                            //没有有效的数据
      }
      Sonar_waiting_echo = 0;                     //回波结束
    }
}

void Sonar_update()             //发送超声测距触发脉冲
{
  if (Sonar_waiting_echo == 0)  //判断回波是否结束
  {
    PORTC &= ~(0x08);           //发送2微秒低电平(PC3),以确保我们得到一个可靠的脉冲    
    delayMicroseconds(2);
    PORTC |= (0x08);            //发送10微妙的脉冲(PC3高)
    delayMicroseconds(10);      //等待10微秒
    PORTC &= ~(0x08);           //脉冲结束,PC3低电平
    Sonar_waiting_echo = 1;     //等待回波
  }
}


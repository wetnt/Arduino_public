/*****   参数配置   *****/
#define MINTHROTTLE 1150     //马达油门最小值
#define MAXTHROTTLE 1850     //马达油门最大值
#define MINCOMMAND  1000     //电机锁最小值
#define I2C_SPEED 400000L    //I2c接口速度, 400kHz

/*****   陀螺仪滤波   *****/
//#define MPU6050_LPF_256HZ
//#define MPU6050_LPF_188HZ
//#define MPU6050_LPF_98HZ
#define MPU6050_LPF_42HZ      //我的四轴滤波配置
//#define MPU6050_LPF_20HZ
//#define MPU6050_LPF_10HZ
//#define MPU6050_LPF_5HZ     //宁可换电机,换桨,也最好不要用这个选项

#define MOTOR_STOP    //油门低位时马达停转
#define MIDRC 1500    //遥控设备的中点设定

#define ESC_CALIB_LOW  MINCOMMAND  //电调最低值
#define ESC_CALIB_HIGH 2000        //电调最高值
//#define ESC_CALIB_CANNOT_FLY     //电调行程校准


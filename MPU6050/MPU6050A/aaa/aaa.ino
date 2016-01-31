#include <I2Cdev.h>
#include <MPU6050.h>
#include <Wire.h>//添加必须的库文件
//====一下三个定义了陀螺仪的偏差===========
#define Gx_offset -3.06
#define Gy_offset 1.01
#define Gz_offset -0.88
//====================
MPU6050 accelgyro;
int16_t ax,ay,az;
int16_t gx,gy,gz;//存储原始数据
float aax,aay,aaz,ggx,ggy,ggz;//存储量化后的数据
float Ax,Ay,Az;//单位 g(9.8m/s^2)
float Gx,Gy,Gz;//单位 °/s

float Angel_accX,Angel_accY,Angel_accZ;//存储加速度计算出的角度

long LastTime,NowTime,TimeSpan;//用来对角速度积分的

#define LED_PIN 13

bool blinkState=false;

void setup()//MPU6050的设置都采用了默认值，请参看库文件
{
  Wire.begin();
  Serial.begin(9600);
  Serial.println("Initializing I2C device.....");
  accelgyro.initialize();
  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful":"MPU6050 connection failure");
  pinMode(LED_PIN,OUTPUT);
}

void loop()
{
  accelgyro.getMotion6(&ax,&ay,&az,&gx,&gy,&gz);//获取三个轴的加速度和角速度
  //======下三行是对加速度进行量化，得出单位为g的加速度值
  Ax=ax/16384.00;
  Ay=ay/16384.00;
  Az=az/16384.00;
  //==========以下三行是用加速度计算三个轴和水平面坐标系之间的夹角
  Angel_accX=atan(Ax/sqrt(Az*Az+Ay*Ay))*180/3.14;
  Angel_accY=atan(Ay/sqrt(Ax*Ax+Az*Az))*180/3.14;
  Angel_accZ=atan(Az/sqrt(Ax*Ax+Ay*Ay))*180/3.14;
  //==========以下三行是对角速度做量化==========
  ggx=gx/131.00;
  ggy=gy/131.00;
  ggz=gz/131.00;

  //===============以下是对角度进行积分处理================
  NowTime=millis();//获取当前程序运行的毫秒数
  TimeSpan=NowTime-LastTime;//积分时间这样算不是很严谨
  //下面三行就是通过对角速度积分实现各个轴的角度测量，当然假设各轴的起始角度都是0
  Gx=Gx+(ggx-Gx_offset)*TimeSpan/1000;
  Gy=Gy+(ggy-Gy_offset)*TimeSpan/1000;
  Gz=Gz+(ggz-Gz_offset)*TimeSpan/1000;

  LastTime=NowTime;

  //==============================
  Serial.print(Ax);
  Serial.print(",");
  Serial.print(Ay);
  Serial.print(",");
  Serial.print(Az);
  Serial.print(",");
  Serial.print(Gx);
  Serial.print(",");
  Serial.print(Gy);
  Serial.print(",");
  Serial.println(Gz);

  blinkState=!blinkState;
  digitalWrite(LED_PIN,blinkState);
  delay(10);//这个用来控制采样速度
}



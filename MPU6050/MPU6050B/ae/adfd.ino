#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
 
MPU6050 accelgyro; 
 
int16_t ax, ay, az;
int16_t gx, gy, gz;
float accx,accy,accz;
float gyrox,gyroy,gyroz;
float axo=0,ayo=0,azo=0;  //加速度计偏移量
float gxo=0,gyo=0,gzo=0;  //陀螺仪偏移量
float pi=3.1415926;
float AcceRatio=16384.0;
float GyroRatio=131.0;
float Rad=180.0/pi;

#define Kp 0.025f//10.0f
#define Ki 0.0f//0.008f
#define halfT 0.001f
 
float q0=1,q1=0,q2=0,q3=0;
float exInt=0,eyInt=0,ezInt=0;
 
float Angle_roll,Angle_pitch,Angle_yaw;
 
void AngleUpdate(float ax,float ay,float az,float gx,float gy,float gz)
{
    float norm;
    float vx,vy,vz;
    float ex,ey,ez;
 
    if (ax*ay*az==0)
        return;
 
    norm=sqrt(ax*ax+ay*ay+az*az);
    ax=ax/norm;
    ay=ay/norm;
    az=az/norm;
 
    vx=2*(q1*q3-q0*q2);
    vy=2*(q0*q1-q3*q2);
    vz=q0*q0-q1*q1-q2*q2+q3*q3;
 
    ex=ay*vz-az*vy;
    ey=az*vx-ax*vz;
    ez=ax*vy-ay*vx;
 
    exInt=exInt+ex*Ki;
    eyInt=eyInt+ey*Ki;
    ezInt=ezInt+ez*Ki;
 
    gx=gx+Kp*ex+exInt;
    gy=gy+Kp*ey+eyInt;
    gz=gz+Kp*ez+ezInt;
 
    q0=q0+(-q1*gx-q2*gy-q3*gz)*halfT;
    q1=q1+(q0*gx+q2*gz-q3*gy)*halfT;
    q2=q2+(q0*gy-q1*gz+q3*gx)*halfT;
    q3=q3+(q0*gz+q1*gy-q2*gx)*halfT;
 
    norm=sqrt(q0*q0+q1*q1+q2*q2+q3*q3);
    q0=q0/norm;
    q1=q1/norm;
    q2=q2/norm;
    q3=q3/norm;
 
    Angle_roll=atan2(2*q2*q3+2*q0*q1,-2*q1*q1-2*q2*q2+1)*Rad;
    Angle_pitch=asin(-2*q1*q3+2*q0*q2)*Rad;
    Angle_yaw=atan2(2*q1*q2+2*q0*q3,-2*q2*q2-2*q3*q3+1)*Rad;
}
 
void imu_setup()
{
    Wire.begin(); 
    accelgyro.initialize();
  accelgyro.setFullScaleAccelRange(MPU6050_ACCEL_FS_2);
  accelgyro.setFullScaleGyroRange(MPU6050_GYRO_FS_250);
 
    unsigned short times=400;
    for(int i=0;i<times;i++) {
        accelgyro.getMotion6(&ax,&ay,&az,&gx,&gy,&gz);
        axo += ax; ayo += ay; azo += az;      //采样和
        gxo += gx; gyo += gy; gzo += gz;
    }
    axo /= times; ayo /= times; azo /= times; //计算加速度计偏移
    gxo /= times; gyo /= times; gzo /= times; //计算陀螺仪偏移
 
   Serial.println("Angle_roll   ,   Angle_pitch   ,   Angle_yaw");
   Serial.print(axo);Serial.print("  ,   ");Serial.print(gxo);
}
 
void imu_loop()
{
    accelgyro.getMotion6(&ax,&ay,&az,&gx,&gy,&gz);

    accx=ax/AcceRatio;
    accy=ay/AcceRatio;
    accz=az/AcceRatio;
    gyrox=gx/GyroRatio;
    gyroy=gy/GyroRatio;
    gyroz=gz/GyroRatio;
    
//    accx=(ax-axo)/AcceRatio;
//    accy=(ay-ayo)/AcceRatio;
//    accz=(az-azo)/AcceRatio;
//    gyrox=(gx-gxo)/GyroRatio;
//    gyroy=(gy-gyo)/GyroRatio;
//    gyroz=(gz-gzo)/GyroRatio;
    //Serial.print(accx);Serial.print(",");Serial.print(accy);Serial.print(",");Serial.println(accz);
    AngleUpdate(accx,accy,accz,gyrox,gyroy,gyroz);
    //Kalman_Filter(Angle_roll,gyrox);
    Serial.print(Angle_roll);Serial.print(",");Serial.print(Angle_pitch);Serial.print(",");Serial.println(Angle_yaw);
    //delay(20);
}


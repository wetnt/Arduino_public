//http://tieba.baidu.com/p/3183760992?pid=54333210165&see_lz=1
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"


// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 accelgyro;
//MPU6050 accelgyro(0x69); // <-- use for AD0 high
int16_t ax, ay, az;
int16_t gx, gy, gz;
int axoffs, ayoffs, azoffs;
int gxoffs, gyoffs, gzoffs;
double rgx, rgy, rgz;
double rax, ray, raz;
double ax0, ay0, az0;
double ax1, ay1, az1;
double wx0, wy0, wz0;
double wx1, wy1, wz1;
double dwx, dwy, dwz;
double q0, q1, q2, q3;
double p0, p1, p2, p3;
double qc0, qc1, qc2, qc3;
double roll, pitch, yaw;
double t1;
double t0;
double t;
double dw;
// uncomment "OUTPUT_READABLE_ACCELGYRO" if you want to see a tab-separated
// list of the accel X/Y/Z and then gyro X/Y/Z values in decimal. Easy to read,
// not so easy to parse, and slow(er) over UART.
#define OUTPUT_READABLE_ACCELGYRO


// uncomment "OUTPUT_BINARY_ACCELGYRO" to send all 6 axes of data as 16-bit
// binary, one right after the other. This is very fast (as fast as possible
// without compression or data loss), and easy to parse, but impossible to read
// for a human.
//#define OUTPUT_BINARY_ACCELGYRO




#define LED_PIN 13
bool blinkState = false;
//----------------------------------------------------
// Accel scale 8g (4096 LSB/g)
//MPU6050_setFullScaleGyroRange(MPU6050_GYRO_FS_2000);
//#define MPU6050_GYRO_FS_250         0x00  //131
//#define MPU6050_GYRO_FS_500         0x01  //65.5
//#define MPU6050_GYRO_FS_1000        0x02  //32.8
//#define MPU6050_GYRO_FS_2000        0x03  //16.4
//----------------------------------------------------
//#define MPU6050_ACCEL_FS_2          0x00  //16384
//#define MPU6050_ACCEL_FS_4          0x01  //8192
//#define MPU6050_ACCEL_FS_8          0x02  //4096
//#define MPU6050_ACCEL_FS_16         0x03  //2048
//----------------------------------------------------
void setup() {
  Wire.begin();
  // initialize serial communication
  // (38400 chosen because it works as well at 8MHz as it does at 16MHz, but
  // it*s really up to you depending on your project)
  Serial.begin(115200);


  // initialize device
  Serial.println("Initializing I2C devices...");
  accelgyro.initialize();
  accelgyro.setFullScaleGyroRange(MPU6050_GYRO_FS_500);//65.5
  accelgyro.setFullScaleAccelRange(MPU6050_ACCEL_FS_2);//16384


  // verify connection
  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");


  // use the code below to change accel/gyro offset values

  q0 = 1;
  q1 = 0;
  q2 = 0;
  q3 = 0;

  getoffs();


  // configure Arduino LED for
  pinMode(LED_PIN, OUTPUT);
}


void loop() {
  // read raw accel/gyro measurements from device
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  t0 = t1;t1 = micros();t = (t1 - t0) / 1000000;


  // these methods (and a few others) are also available
  //accelgyro.getAcceleration(&ax, &ay, &az);
  //accelgyro.getRotation(&gx, &gy, &gz);
  ax = ax + axoffs;
  ay = ay + ayoffs;
  az = az + azoffs;
  gx = gx + gxoffs;
  gy = gy + gyoffs;
  gz = gz + gzoffs;
  //calibration error

  rgx = gx;
  rgy = gy;
  rgz = gz;
  rax = ax;
  ray = ay;
  raz = az;

  wx0 = wx1;
  wy0 = wy1;
  wz0 = wz1;
  //

  p0 = q0;
  p1 = q1;
  p2 = q2;
  p3 = q3;
  //

  wx1 = rgx / 65.5;
  wy1 = rgy / 65.5;
  wz1 = rgz / 65.5;
  ax1 = (rax / 16384) * 9.80;
  ay1 = (ray / 16384) * 9.80;
  az1 = (raz / 16384) * 9.80;
  //

  dwx = ((wx1 + wx0) / 2) * t * 0.01745;
  dwy = ((wy1 + wy0) / 2) * t * 0.01745;
  dwz = ((wz1 + wz0) / 2) * t * 0.01745;
  //

  dw = sqrt(dwx * dwx + dwy * dwy + dwz * dwz);
  qc0 = cos(dw / 2);
  qc1 = (dwx / dw) * sin(dw / 2);
  qc2 = (dwy / dw) * sin(dw / 2);
  qc3 = (dwz / dw) * sin(dw / 2);


  q0 = qc0 * p0 - qc1 * p1 - qc2 * p2 - qc3 * p3;
  q1 = qc1 * p0 + qc0 * p1 + qc3 * p2 - qc2 * p3;
  q2 = qc2 * p0 - qc3 * p1 + qc0 * p2 + qc1 * p3;
  q3 = qc3 * p0 + qc2 * p1 - qc1 * p2 + qc0 * p3;


  //

  roll = atan2(2 * (q0 * q1 + q2 * q3), 1 - 2 * (q1 * q1 + q2 * q2)) * 57.25977;
  pitch = -asin(2 * (q0 * q2 - q3 * q1)) * 57.25977;
  yaw = -atan2(2 * (q0 * q3 + q1 * q2), 1 - 2 * (q2 * q2 + q3 * q3)) * 57.25977;
  //

  if (yaw < 0){yaw = 360 + yaw;}

  Serial.print(roll); Serial.print(",");
  Serial.print(pitch); Serial.print(",");
  Serial.print(yaw); Serial.print(",");
  //Serial.print(ax1); Serial.print(",");
  //Serial.print(ay1); Serial.print(",");
  //Serial.println(az1);

Serial.println();


}
void getoffs()
{
  int16_t ax, ay, az;
  int16_t gx, gy, gz;
  long int axsum = 0;
  long int aysum = 0;
  long int azsum = 0;
  long int gxsum = 0;
  long int gysum = 0;
  long int gzsum = 0;
  int i;
  for (i = 1; i <= 2000; i++)
  {
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    axsum = ax + axsum;
    aysum = ay + aysum;
    azsum = az + azsum - 16384;
    gxsum = gx + gxsum;
    gysum = gy + gysum;
    gzsum = gz + gzsum;
  }
  axoffs = -axsum / 2000;
  ayoffs = -aysum / 2000;
  azoffs = -azsum / 2000;
  gxoffs = -gxsum / 2000;
  gyoffs = -gysum / 2000;
  gzoffs = -gzsum / 2000;
}

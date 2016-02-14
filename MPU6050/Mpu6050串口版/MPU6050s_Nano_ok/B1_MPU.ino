//-------------------------------------------------------------------------
#include <SoftwareSerial.h>
SoftwareSerial mpu(10, 11); //RX,TX
static const long MpuBaud = 115200;
//static const long MpuBaud = 9600;
//-------------------------------------------------------------------------
float a[3], w[3], angle[3], T;
unsigned char sign = 0;
unsigned char Re_buf[11], counter = 0;
//-------------------------------------------------------------------------
void mpu_setup() {
  //--------------------------------------------------
  //!!!必须不然硬件烧毁!!!
  pinMode(9, INPUT);  pinMode(12, INPUT);
  pinMode(13, INPUT); pinMode(A0, INPUT);
  //--------------------------------------------------
  mpu.begin(MpuBaud); lg(F("MPU.Serial.start! = ")); lg(MpuBaud); lg();
  //--------------------------------------------------
}
void mpu_loop() {//伪终端，loop()里不能有有delay
  while (mpu.available()) {
    //---------------------------while---------------------------------
    Re_buf[counter] = (unsigned char)mpu.read();
    //lgs.write(Re_buf[counter]);
    if (counter == 0 && Re_buf[0] != 0x55) return; //第0号数据不是帧头
    counter++;
    if (counter == 11) {      //接收到11个数据
      counter = 0; sign = 1;  //重新赋值，准备下一帧数据的接收
    }
    //---------------------------while---------------------------------
  }
}
void mpu_show() {
  lg("angle:"); lg(angle[0]); lg(','); lg(angle[1]); lg(','); lg(angle[2]); lg(','); lg(',');
  lg("a:"); lg(a[0]); lg(','); lg(a[1]); lg(','); lg(a[2]); lg(','); lg(',');
  lg("w:"); lg(w[0]); lg(','); lg(w[1]); lg(','); lg(w[2]); lg(','); lg(',');
  lg("T:"); lg(T); lg(','); lg();
}
void mpu_show2() {
  lg(angle[0]); lg(','); lg(angle[1]); lg(','); lg(angle[2]); lg();
}
//-------------------------------------------------------------------------
void mathSensors() {
  if (sign) {
    sign = 0;
    if (Re_buf[0] == 0x55) {  //检查帧头
      switch (Re_buf [1]) {
        case 0x51:
          a[0] = (short(Re_buf [3] << 8 | Re_buf [2])) / 32768.0 * 16;
          a[1] = (short(Re_buf [5] << 8 | Re_buf [4])) / 32768.0 * 16;
          a[2] = (short(Re_buf [7] << 8 | Re_buf [6])) / 32768.0 * 16;
          T = (short(Re_buf [9] << 8 | Re_buf [8])) / 340.0 + 36.25;
          break;
        case 0x52:
          w[0] = (short(Re_buf [3] << 8 | Re_buf [2])) / 32768.0 * 2000;
          w[1] = (short(Re_buf [5] << 8 | Re_buf [4])) / 32768.0 * 2000;
          w[2] = (short(Re_buf [7] << 8 | Re_buf [6])) / 32768.0 * 2000;
          T = (short(Re_buf [9] << 8 | Re_buf [8])) / 340.0 + 36.25;
          break;
        case 0x53:
          angle[0] = (short(Re_buf [3] << 8 | Re_buf [2])) / 32768.0 * 180;
          angle[1] = (short(Re_buf [5] << 8 | Re_buf [4])) / 32768.0 * 180;
          angle[2] = (short(Re_buf [7] << 8 | Re_buf [6])) / 32768.0 * 180;
          T = (short(Re_buf [9] << 8 | Re_buf [8])) / 340.0 + 36.25;
          break;
      }
    }
  }
}
//-------------------------------------------------------------------------

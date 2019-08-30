//https://tools.clz.me/ 点阵转换
//http://www.docin.com/p-1011581730.html
//https://www.arduino.cn/thread-41158-1-1.html
#include <U8g2lib.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, 2);
void oled_setup(void) {
  u8g2.begin();
}

int state = 0;
void oled_loop(void) {
  //  u8g2.clearBuffer();
  //  u8g2.drawXBMP( 0 , 0 , 63 , 32 , col );
  //  u8g2.sendBuffer();
  //  smartDelay(1000);

  switch (state)  {
    case 0: eye_mids(); break;
    case 1: eye_rigt(); break;
    case 2: eye_left(); break;
    default: eye_mids(); break;
  }
  state++; if (state > 2)state = 0;
}

void eye_mids() {
  u8g2.clearBuffer();
  u8g2.drawCircle(64, 32, 31);
  u8g2.drawFilledEllipse(64, 32, 14, 20);
  u8g2.sendBuffer();
}
void eye_left() {
  u8g2.clearBuffer();
  u8g2.drawCircle(64, 32, 31);
  u8g2.drawFilledEllipse(48, 32, 14, 20);
  u8g2.sendBuffer();
}
void eye_rigt() {
  u8g2.clearBuffer();
  u8g2.drawCircle(64, 32, 31);
  u8g2.drawFilledEllipse(80, 32, 14, 20);
  u8g2.sendBuffer();
}


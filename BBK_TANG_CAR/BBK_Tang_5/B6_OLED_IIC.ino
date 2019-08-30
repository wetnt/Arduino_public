//https://tools.clz.me/ 点阵转换
//http://www.docin.com/p-1011581730.html
//https://www.arduino.cn/thread-41158-1-1.html
#include <U8g2lib.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, 2);
void oled_setup(void) {
  u8g2.begin();
}

//width:63,height:32
//const unsigned char col[] U8X8_PROGMEM = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x03, 0x20, 0x00, 0xb8, 0x01, 0xc0, 0x01, 0xe0, 0x03, 0xc0, 0x00, 0x60, 0x01, 0x80, 0x03, 0xc0, 0x00, 0xc0, 0x00, 0x70, 0x02, 0xc0, 0x07, 0x40, 0x00, 0x90, 0x0f, 0x7e, 0x02, 0xf0, 0x06, 0xc0, 0x07, 0xfc, 0x01, 0xf6, 0x02, 0xf8, 0x02, 0xe0, 0x00, 0xce, 0x00, 0xf2, 0x02, 0x60, 0x03, 0xf8, 0x00, 0xe0, 0x03, 0x3a, 0x02, 0x30, 0x11, 0x40, 0x03, 0x20, 0x03, 0x6a, 0x02, 0x34, 0x31, 0x60, 0x06, 0x10, 0x03, 0xf2, 0x03, 0x18, 0x3f, 0x30, 0x1c, 0xa8, 0x01, 0x8a, 0x03, 0x00, 0x1e, 0x18, 0x38, 0xe4, 0x00, 0xf4, 0x01, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x50, 0x55, 0xa9, 0x50, 0x45, 0xaa, 0x02, 0x00, 0xd0, 0x31, 0xc9, 0xc8, 0x01, 0xb2, 0x00, 0x00, 0x50, 0x51, 0xa9, 0x50, 0x51, 0xaa, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
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


//https://tools.clz.me/ 点阵转换
//http://www.docin.com/p-1011581730.html
#include <Arduino.h>
#include <U8g2lib.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, 2);
void oled_setup(void) {
  u8g2.begin();
}

//width:126,height:65 
const unsigned char col[] U8X8_PROGMEM= {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xfe,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x0f,0x00,0x00,0x18,0x00,0x00,0x80,0x9f,0x03,0x00,0x00,0xe0,0x00,0x00,0x00,0xe0,0x0f,0x00,0x00,0x78,0x00,0x00,0x80,0x33,0x07,0x00,0x00,0xe0,0x03,0x00,0x00,0xf8,0x0f,0x00,0x00,0xf0,0x00,0x00,0x00,0x7c,0x06,0x00,0x00,0xc0,0x03,0x00,0x00,0xf0,0x03,0x00,0x00,0xf0,0x01,0x00,0x00,0x7f,0x0e,0x00,0x00,0xc0,0x1f,0x00,0x00,0xe0,0x01,0x00,0x00,0xf0,0x01,0x00,0x10,0x7f,0x0c,0x00,0x00,0xc0,0x7f,0x00,0x00,0xe0,0x00,0x00,0x00,0x3c,0x00,0x00,0x30,0x3f,0x0c,0x00,0x00,0xf0,0x7f,0x00,0x00,0x60,0x00,0x00,0x00,0x87,0xff,0x00,0xb8,0x3f,0x0c,0x00,0x00,0xfc,0x7f,0x00,0x00,0x70,0x1e,0x00,0x00,0xfe,0xfc,0x00,0x38,0x1f,0x0c,0x00,0x00,0xff,0x39,0x00,0x00,0xe0,0x3f,0x00,0xe0,0xff,0x07,0x00,0x38,0xff,0x0c,0x00,0xe0,0xff,0x3c,0x00,0x00,0xe0,0x07,0x00,0xfe,0xe3,0x01,0x00,0x18,0xfc,0x0c,0x00,0xc0,0xff,0x1c,0x00,0x00,0xf8,0x01,0x00,0xfc,0xe0,0x00,0x00,0x18,0xfe,0x0c,0x00,0x00,0x79,0x1e,0x00,0x00,0x7f,0x00,0x00,0x3c,0xf0,0x03,0x00,0x1c,0xcf,0x0c,0x00,0x00,0x78,0x0e,0x00,0x80,0xff,0x01,0x00,0x00,0xf8,0x0f,0x00,0x8c,0x5f,0x0c,0x00,0x00,0x3c,0x07,0x01,0x00,0xff,0x03,0x00,0x00,0x38,0x1c,0x00,0x8c,0x7b,0x0c,0x00,0x00,0x1e,0x07,0x02,0x00,0x30,0x0e,0x00,0x00,0x1c,0x1e,0x00,0x8c,0x3d,0x1c,0x00,0x00,0x1e,0x07,0x06,0x00,0x38,0x1c,0x00,0x00,0x0e,0x0e,0x00,0x0c,0x1e,0x1c,0x00,0x20,0x0f,0x07,0x0e,0x00,0x38,0x3c,0x00,0x00,0x07,0x0e,0x00,0x0c,0xff,0x0e,0x00,0xe0,0x07,0x07,0x1f,0x00,0x1c,0xf8,0x00,0x80,0x09,0x07,0x00,0x8c,0xe3,0x0e,0x00,0xc0,0x03,0xff,0x1f,0x00,0x1e,0xf0,0x03,0xc0,0x88,0x03,0x00,0xdc,0x81,0x0f,0x00,0xc0,0x01,0xfe,0x1f,0x00,0x0f,0xe0,0x0f,0x70,0x98,0x03,0x00,0x38,0x07,0x0f,0x00,0x00,0x00,0xf8,0x07,0xc0,0x03,0xc0,0x1f,0x30,0xf8,0x01,0x00,0x70,0xfe,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3f,0x00,0xf0,0x00,0x00,0xe0,0xff,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0xf0,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00,0x10,0x00,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00,0x10,0x00,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xcf,0xd1,0xe1,0x13,0x0f,0x4f,0xcc,0xf1,0xe0,0xf1,0xf8,0x0e,0x00,0x00,0x00,0x00,0x23,0x32,0x33,0x93,0x99,0x41,0x62,0x32,0x30,0x98,0x99,0x19,0x00,0x00,0x00,0x00,0x03,0x32,0x12,0x92,0x90,0xc0,0x23,0x36,0x10,0x08,0x89,0x11,0x00,0x00,0x00,0x00,0xe3,0x13,0x1a,0xd2,0xb0,0xc0,0xf1,0x17,0x10,0x0c,0x8b,0x11,0x00,0x00,0x00,0x00,0x23,0x12,0x12,0x92,0x90,0x40,0x23,0x10,0x10,0x08,0x89,0x11,0x00,0x00,0x00,0x00,0x22,0x13,0x32,0x93,0x99,0x41,0x66,0x12,0x32,0x98,0x89,0x11,0x00,0x00,0x00,0x00,0xee,0x13,0xe2,0x13,0x0f,0x4f,0xcc,0x11,0xe2,0xf1,0x88,0x11,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xe0,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

void drawLogo(void) {
  u8g2.setFontMode(1);

  u8g2.setFontDirection(0);  u8g2.setFont(u8g2_font_inb24_mf);  u8g2.drawStr(0, 30, "U");
  u8g2.setFontDirection(1);  u8g2.setFont(u8g2_font_inb30_mn);  u8g2.drawStr(21, 8, "8");
  u8g2.setFontDirection(0);  u8g2.setFont(u8g2_font_inb24_mf);
  u8g2.drawStr(51, 30, "g");  u8g2.drawStr(67, 30, "\xb2");

  u8g2.drawHLine(2, 35, 47);  u8g2.drawHLine(3, 36, 47);
  u8g2.drawVLine(45, 32, 12); u8g2.drawVLine(46, 33, 12);
}
void drawURL(void) {
  u8g2.setFont(u8g2_font_4x6_tr);
  u8g2.drawStr(60, 50, "WWW.TANGLOCKER.COM");
  u8g2.drawStr(60, 60, "a九天方圆b");
}
void oled_loop(void) {
  u8g2.clearBuffer();
  drawLogo(); drawURL();
  u8g2.sendBuffer();
  delay(1000);

  u8g2.clearBuffer();
  u8g2.drawXBMP( 0 , 0 , 126 , 65 , col );
  u8g2.sendBuffer();
  delay(1000);
}

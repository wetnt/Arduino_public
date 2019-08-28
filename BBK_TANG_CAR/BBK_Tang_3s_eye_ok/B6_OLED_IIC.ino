//https://tools.clz.me/ 点阵转换
//http://www.docin.com/p-1011581730.html
//https://www.arduino.cn/thread-41158-1-1.html
#include "U8glib.h"
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE | U8G_I2C_OPT_DEV_0); //I2C/TWI
uint8_t draw_state = 0;
void oled_setup(void) {
  //----------------------------------------------------------------------------------
  // u8g.setRot180();//屏幕方向
  //----------------------------------------------------------------------------------
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) u8g.setColorIndex(255);       // white
  else if ( u8g.getMode() == U8G_MODE_BW ) u8g.setColorIndex(1);        // pixel on
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) u8g.setColorIndex(3);  // max intensity
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) u8g.setHiColorByRGB(255, 255, 255);
  //----------------------------------------------------------------------------------
  u8g.firstPage();
  do {
    u8g.setFont(u8g_font_unifont);
    u8g.drawStr(0, 22, " TangLocker.Com");
  } while ( u8g.nextPage() );
  //----------------------------------------------------------------------------------
}
void oled_loop(void) {
  u8g.firstPage();
  do {
    draw();
  } while ( u8g.nextPage() );
  draw_state++;
  if (draw_state >= 4)
    draw_state = 0;
}
void draw(void) {
  switch (draw_state) {
    case 0: eye_mids(); break;
    case 1: eye_left(); break;
    case 2: eye_rigt(); break;
    //case 3: HelloDraw(); break;
  }
}
//=======================================================
void eye_mids() {
  //u8g.drawFrame(5,5,118,54);
  u8g.drawCircle(64, 32, 31);
  u8g.drawFilledEllipse(64, 32, 14, 20);
}
void eye_left() {
  u8g.drawCircle(64, 32, 31);
  u8g.drawFilledEllipse(48, 32, 14, 20);
}
void eye_rigt() {
  u8g.drawCircle(64, 32, 31);
  u8g.drawFilledEllipse(80, 32, 14, 20);
}
void HelloDraw(void) {
  u8g.setFont(u8g_font_unifont);
  u8g.setFontPosTop();
  u8g.drawStr(0, 1, "Hello");
  u8g.drawHLine(0, 1 + 14, 40);
  u8g.setScale2x2();
  u8g.drawStr(0, 12, "Hello");
  u8g.drawHLine(0, 12 + 14, 40);
  u8g.undoScale();
}

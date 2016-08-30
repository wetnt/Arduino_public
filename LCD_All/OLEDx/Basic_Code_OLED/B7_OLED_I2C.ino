#include "U8glib.h"
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE | U8G_I2C_OPT_DEV_0); //I2C/TWI
char u8gTemp[25] ;
void oled_Init() {
  //----------------------------------------------------------------------------------
  //u8g.setRot180();//屏幕方向
  //----------------------------------------------------------------------------------
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) u8g.setColorIndex(255);       // white
  else if ( u8g.getMode() == U8G_MODE_BW ) u8g.setColorIndex(1);        // pixel on
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) u8g.setColorIndex(3);  // max intensity
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) u8g.setHiColorByRGB(255, 255, 255);
  //----------------------------------------------------------------------------------
  u8g.firstPage();
  do {
    u8g.setFont(u8g_font_unifont);
    u8g.drawStr(0, 22, "oled_Init!");
  } while ( u8g.nextPage() );
  delay(200);
  //----------------------------------------------------------------------------------
}
void oled_loop(void) {
  u8g.firstPage();
  do {
    draw();
  } while ( u8g.nextPage() );
}
void draw() {
  drawGraphics();
}
//================================================================
void drawLine(int x1, int y1, int x2, int y2) {
  u8g.drawLine(x1, y1, x2, y2);
}
void drawFrame() {
  int w = u8g.getWidth();
  int h = u8g.getHeight();
  u8g.drawFrame(0, 0, w, h);
  //lg(w); lg('x'); lg(h); lg();
}
void drawGraphics4() {
  drawFrame();
  u8g.setFont(u8g_font_unifont);
  u8g.drawStr(0, 10, "oled_Init!");
  //  u8g.drawLine(7 , 10, 40, 55);
  //  u8g.drawTriangle(14, 7, 45, 30, 10, 40);
}
void drawGraphics() {
  drawFrame();

  u8g.setFont(u8g_font_unifont);
  itostr(u8gTemp, accx); lg(u8gTemp); lg(); u8g.drawStr(10, 15, u8gTemp);
  itostr(u8gTemp, accy); lg(u8gTemp); lg(); u8g.drawStr(10, 30, u8gTemp);
  itostr(u8gTemp, accz); lg(u8gTemp); lg(); u8g.drawStr(10, 45, u8gTemp);

  //&accx, &accy, &accz, &gyrox, &gyroy, &gyroz
}
//================================================================
char* itostr(char *str, int i) {
  sprintf(str, "%d", i);
  return str;
}
char* dtostr(char *str, double d) {
  sprintf(str, "%f", d);
  return str;
}
//================================================================

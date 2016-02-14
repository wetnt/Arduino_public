#include "U8glib.h"
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE | U8G_I2C_OPT_DEV_0); //I2C/TWI
void oled_Init() {
  //----------------------------------------------------------------------------------
  u8g.setRot180();//屏幕方向
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
  delay(2000);
  //----------------------------------------------------------------------------------
}
int key = 0;
void oled_loop(void) {
  //----------------------------------------
  u8g.firstPage();
  do {
    draw();
  } while ( u8g.nextPage() );
  //----------------------------------------
  key++; if (key > 8) key = 0;
  //----------------------------------------
}
void draw() {
  switch (key) {
    case 7: drawGraphics4(); break;
  }
}
//================================================================
void drawLine(int x1, int y1, int x2, int y2) {
  u8g.drawLine(x1, y1, x2, y2);
}
void drawGraphics4() {
  u8g.drawLine(7 , 10, 40, 55);
  u8g.drawTriangle(14, 7, 45, 30, 10, 40);
}
//================================================================

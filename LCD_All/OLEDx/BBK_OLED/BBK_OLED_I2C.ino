#include "U8glib.h"
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE | U8G_I2C_OPT_DEV_0); //I2C/TWI
void oled_Init() {
  // u8g.setRot180();//屏幕方向
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) u8g.setColorIndex(255);       // white
  else if ( u8g.getMode() == U8G_MODE_BW ) u8g.setColorIndex(1);        // pixel on
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) u8g.setColorIndex(3);  // max intensity
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) u8g.setHiColorByRGB(255, 255, 255);
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
    case 0: drawCOM(); break;
    case 1: drawABC(); break;
    case 2: drawIco(); break;
    case 3: drawPic(); break;
    case 4: drawGraphics1(); break;
    case 5: drawGraphics2(); break;
    case 6: drawGraphics3(); break;
    case 7: drawGraphics4(); break;
    case 8: drawGraphics5(); break;
  }
}
//================================================================
void drawABC(void) {
  //  u8g.setFont(u8g_font_4x6);
  //  u8g.setFont(u8g_font_6x10);
  //  u8g.setFont(u8g_font_helvR24r);
  //u8g.setFont(u8g_font_osb21);
  u8g.setFont(u8g_font_unifont);
  u8g.drawStr(0, 22, "Hello World!");
}
void drawCOM(void) {
  drawLogo(0);
  drawURL();
  u8g.drawFrame(0, 0, u8g.getWidth(), u8g.getHeight());

  //  u8g.firstPage();
  //  u8g.setFont(u8g_font_helvR24r);
  //  u8g.setPrintPos(0, 100);
  //  u8g.print(u8g.getWidth(), DEC);
  //  u8g.print("x");
  //  u8g.print(u8g.getHeight(), DEC);

}
void drawLogo(uint8_t d) {
  u8g.setFont(u8g_font_gdr25r);
  u8g.drawStr(0 + d, 30 + d, "U");
  u8g.setFont(u8g_font_gdr30n);
  u8g.drawStr90(23 + d, 10 + d, "8");
  u8g.setFont(u8g_font_gdr25r);
  u8g.drawStr(53 + d, 30 + d, "g");

  u8g.drawHLine(2 + d, 35 + d, 47);
  u8g.drawVLine(45 + d, 32 + d, 12);
}
void drawURL(void) {
  u8g.setFont(u8g_font_4x6);
  if ( u8g.getHeight() < 59 ) {
    u8g.drawStr(53, 9, "code.google.com");
    u8g.drawStr(77, 18, "/p/u8glib");
  } else {
    u8g.drawStr(1, 54, "code.google.com/p/u8glib");
  }
}
//================================================================
const uint8_t rook_bitmap[] PROGMEM = {
  0x00,         // 00000000
  0x55,         // 01010101
  0x7f,         // 01111111
  0x3e,         // 00111110
  0x3e,         // 00111110
  0x3e,         // 00111110
  0x3e,         // 00111110
  0x7f          // 01111111
};
void drawIco(void) {
  u8g.drawBitmapP( 0, 0, 1, 8, rook_bitmap);
}
//================================================================
#define u8g_logo_width 38
#define u8g_logo_height 24
//static unsigned char u8g_logo_bits[] = {
static unsigned char u8g_logo_bits[] U8G_PROGMEM = {
  0xff, 0xff, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xe0, 0xe0,
  0xff, 0xff, 0x3f, 0xe3, 0xe1, 0xff, 0xff, 0x3f, 0xf3, 0xf1, 0xff, 0xff,
  0x3f, 0xf3, 0xf1, 0xfe, 0xbf, 0x37, 0xf3, 0x11, 0x1c, 0x1f, 0x30, 0xf3,
  0x01, 0x08, 0x8c, 0x20, 0xf3, 0x01, 0x00, 0xc0, 0x39, 0xf3, 0x81, 0xc7,
  0xc1, 0x39, 0xf3, 0xc1, 0xc7, 0xc9, 0x38, 0xf3, 0xc1, 0xc3, 0x19, 0x3c,
  0xe3, 0x89, 0x01, 0x98, 0x3f, 0xc7, 0x18, 0x00, 0x08, 0x3e, 0x0f, 0x3c,
  0x70, 0x1c, 0x30, 0x3f, 0xff, 0xfc, 0x87, 0x31, 0xff, 0xff, 0xbf, 0xc7,
  0x23, 0x01, 0x00, 0x00, 0xc6, 0x23, 0x03, 0x00, 0x00, 0x0e, 0x30, 0xff,
  0xff, 0x3f, 0x1f, 0x3c, 0xff, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0xff, 0x3f,
  0xff, 0x3f, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xff, 0xff, 0x3f
};
void drawPic(void) {
  u8g.drawXBMP( 0, 0, u8g_logo_width, u8g_logo_height, u8g_logo_bits);
}
//================================================================
void drawGraphics1() {
  int a = 0;
  u8g.drawStr(0, 0, "drawBox");
  u8g.drawStr(30 + a, 31, " 0");
  u8g.drawStr90(30, 31 + a, " 90");
  u8g.drawStr180(30 - a, 31, " 180");
  u8g.drawStr270(30, 31 - a, " 270");
}
void drawGraphics2() {
  u8g.drawBox(5, 10, 20, 10);
  u8g.drawDisc(10, 18, 9);
  u8g.drawCircle(10, 18 + 30, 9);
}
void drawGraphics3() {
  u8g.drawFrame(0, 0, u8g.getWidth(), u8g.getHeight());
  u8g.drawRFrame(5, 10, 40, 30, 3);
  u8g.drawRBox(50, 10, 25, 40, 3);
}
void drawGraphics4() {
  u8g.drawLine(7 , 10, 40, 55);
  u8g.drawTriangle(14, 7, 45, 30, 10, 40);
}
void drawGraphics5() {
  u8g.setRGB(255, 0, 0);
  u8g.drawStr( 66, 0, "Color Page");
}
//================================================================

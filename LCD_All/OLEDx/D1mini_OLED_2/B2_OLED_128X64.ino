#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

//#define OLED_CLK    D5//14
//#define OLED_MOSI   D6//12
//#define OLED_RESET  D2//4
//#define OLED_DC     D1//5
//#define OLED_CS     0//0


#define OLED_CLK    D6//14
#define OLED_MOSI   D5//12
#define OLED_RESET  D0//4
#define OLED_DC     D1//5
#define OLED_CS     D2//0
U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R0, OLED_CLK, OLED_MOSI, OLED_CS, OLED_DC, OLED_RESET);

void oled_setup() {
  u8g2.begin();
}

void oled_show() {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(0, 10, "Hello World!");
  //u8g2.drawStr180(20, 20, "a0000000000");
  //u8g2.drawStr(20, 30, s);
  u8g2.sendBuffer();
  delay(1000);
}

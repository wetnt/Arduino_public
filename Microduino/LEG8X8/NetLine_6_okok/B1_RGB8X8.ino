//---------------------------------------------------------------------------------
#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"
Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix();
//---------------------------------------------------------------------------------
uint8_t bmp1[10] = {0x00, 0x24, 0x7E, 0x7E, 0x3C, 0x18, 0x00, 0x00, 1, 5};
uint8_t bmp2[10] = {0x00, 0x66, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C, 0x18, 1, 5};
uint8_t bmp3[10] = {0x00, 0x24, 0x7E, 0x7E, 0x3C, 0x18, 0x00, 0x00, 2, 5};
uint8_t bmp4[10] = {0x00, 0x66, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C, 0x18, 2, 5};
uint8_t bmp5[10] = {0x00, 0x66, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C, 0x18, 1, 5};
uint8_t bmp6[10] = {0x00, 0x66, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C, 0x18, 1, 5};
String str0 = "I love you 1314,MaYuan!";
int colorKey = 3;
//---------------------------------------------------------------------------------
void RGB8X8_setup() {
  //--------------------------------------------
  matrix.begin(0x71);
  matrix.setRotation(0);
  matrix.setTextSize(1);
  //--------------------------------------------
}
//---------------------------------------------------------------------------------
void RGB8X8_loop() {
  //---------------------------------------------------------------------------------
  RGB8X8_bmp(bmp1); RGB8X8_bmp(bmp2); RGB8X8_bmp(bmp3); RGB8X8_bmp(bmp4); RGB8X8_bmp(bmp5);
  RGB8X8_text(str0, colorKey, 70); smartDelay(500);
  RGB8X8_bmp(bmp6);
  //---------------------------------------------------------------------------------
}
char output[9];
void outputTo2String(long number) {
  for (int i = 0; i < 8; i++) {
    output[i] = number & (1 << 7 - i);
    output[i] = output[i] >> 7 - i;
    output[i] = (output[i] == 0) ? '0' : '1';
  }
  output[8] = '\0';
}
void RGB8X8_bmp(uint8_t s[10]) {
  //--------------------------------------------
  int colork = s[8]; if (colork < 0 || colork > 3) colork = 0;
  int showtm = s[9]; if (showtm < 0 || colork > 1000) showtm = 0;
  //--------------------------------------------
  lg(F("RGB8X8_bmp = ")); lg(colork); lg(','); lg(showtm); lg();
  //for (int i = 0; i < 8; i++) lg(rgb8x8_bmp[i]);
  //--------------------------------------------
  matrix.clear();
  if (colork != 0) {
    //--------------------------------------------
    for (int h = 0; h < 8; h++) {
      outputTo2String(s[h]);
      for (int w = 0; w < 8; w++ ) {
        if (output[w] == '1') lg("##"); else lg("  ");
        if (output[w] == '1') matrix.drawPixel(w, h, colork);
      }
      lg();
    }
    lg();
    //--------------------------------------------
  }
  //--------------------------------------------
  matrix.writeDisplay();
  smartDelay(showtm * 100);
  //--------------------------------------------
}
void RGB8X8_text(String s, int colorKey, int delay_us) {
  //--------------------------------------------
  lg(F("RGB8X8_text = ")); lgln(s);
  //--------------------------------------------
  if (delay_us < 0)   delay_us = 100;
  int n = s.length() *  6;
  //--------------------------------------------
  matrix.setTextWrap(false);
  matrix.setTextColor(colorKey);
  //--------------------------------------------
  for (int i = 0; i < n; i++) {
    matrix.clear();
    matrix.setCursor(7 - i, 0);
    matrix.print(s);
    matrix.writeDisplay();
    smartDelay(delay_us);
  }
  //--------------------------------------------
}
//---------------------------------------------------------------------------------

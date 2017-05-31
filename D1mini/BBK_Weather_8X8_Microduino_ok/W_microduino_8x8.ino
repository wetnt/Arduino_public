//---------------------------------------------------------------------------------
#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"
Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix();
//---------------------------------------------------------------------------------
void microduino_8x8_setup() {
  Wire.begin(D4,D3); //定义I2C接口，并启动，ESP8266-12E的 2 和 14 口是原本定义为I2C接口，其他模块查看手册，用于读取BMP180的参数
  //--------------------------------------------
  matrix.begin(0x71);
  matrix.setRotation(0);
  matrix.setTextSize(1);
  //--------------------------------------------
  matrix.setTextWrap(false);
  matrix.setTextColor(1);
  //--------------------------------------------
  matrix.clear();
  matrix.setCursor(0, 0);
  matrix.print("M");
  matrix.writeDisplay();
  //--------------------------------------------
}
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
char output[9];
void outputTo2String(long number) {
  for (int i = 0; i < 8; i++) {
    output[i] = number & (1 << 7 - i);
    output[i] = output[i] >> 7 - i;
    output[i] = (output[i] == 0) ? '0' : '1';
  }
  //output[8] = '\0';
  output[8] = ' ';
}
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
void microduino_8x8_bmp(uint8_t *s,uint16_t color) {
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
  }
  //--------------------------------------------
}

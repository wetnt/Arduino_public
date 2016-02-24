//---------------------------------------------------------------------------------
#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"
Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix();
//---------------------------------------------------------------------------------
static const uint8_t PROGMEM  love_bmp[] = {0x66, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C, 0x18, 0x00};
//---------------------------------------------------------------------------------
int BMP_Color_Key = 1, STR_Color_Key = 1; int BMP_Time_Key = 1000;
uint8_t rgb8x8_bmp1[8] = {0x00, 0x66, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C, 0x18};
uint8_t rgb8x8_bmp2[8] = {0x00, 0x24, 0x7E, 0x7E, 0x3C, 0x18, 0x00, 0x00};
//uint8_t *rgb8x8_bmp;
String rgb_string = "I love you 1314,MaYuan!";//"I love You 1314 MaYuan!";
//---------------------------------------------------------------------------------
//$
//BMP1:1,2,...8,1,2,...8,..;//8X8
//BMP2:1,2,...8,1,2,...8,..;//8X8
//STR:ASDFASDFSAD;
//*
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
  if (BMP_Color_Key == 0) matrix.clear();
  else if (BMP_Color_Key == 1) RGB8X8_bmp(rgb8x8_bmp1, LED_RED, BMP_Time_Key);
  else if (BMP_Color_Key == 2) RGB8X8_bmp(rgb8x8_bmp1, LED_GREEN, BMP_Time_Key);
  else if (BMP_Color_Key == 3) RGB8X8_bmp(rgb8x8_bmp1, LED_YELLOW, BMP_Time_Key);
  if (BMP_Color_Key == 0) matrix.clear();
  else if (BMP_Color_Key == 1) RGB8X8_bmp(rgb8x8_bmp2, LED_RED, BMP_Time_Key);
  else if (BMP_Color_Key == 2) RGB8X8_bmp(rgb8x8_bmp2, LED_GREEN, BMP_Time_Key);
  else if (BMP_Color_Key == 3) RGB8X8_bmp(rgb8x8_bmp2, LED_YELLOW, BMP_Time_Key);
  //---------------------------------------------------------------------------------
  if (STR_Color_Key == 0) matrix.clear();
  else if (STR_Color_Key == 1) RGB8X8_text(rgb_string,  LED_RED, 70);
  else if (STR_Color_Key == 2) RGB8X8_text(rgb_string,  LED_GREEN, 70);
  else if (STR_Color_Key == 3) RGB8X8_text(rgb_string,  LED_YELLOW, 70);
  //---------------------------------------------------------------------------------
  matrix.clear(); matrix.writeDisplay(); smartDelay(300);
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
void RGB8X8_bmp(uint8_t s[8], int colorKey, int delay_us) {
  //--------------------------------------------
  lg(F("RGB8X8_bmp = ")); lg();
  //for (int i = 0; i < 8; i++) lg(rgb8x8_bmp[i]);
  //--------------------------------------------
  if (delay_us <= 0) delay_us = 100;
  //--------------------------------------------
  matrix.clear();
  //--------------------------------------------
  for (int h = 0; h < 8; h++) {
    outputTo2String(s[h]);
    for (int w = 0; w < 8; w++ ) {
      if (output[w] == '1') lg("##"); else lg("  ");
      if (output[w] == '1') matrix.drawPixel(w, h, colorKey);
    }
    lg();
  }
  lg();
  //--------------------------------------------
  matrix.writeDisplay();
  smartDelay(delay_us);
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

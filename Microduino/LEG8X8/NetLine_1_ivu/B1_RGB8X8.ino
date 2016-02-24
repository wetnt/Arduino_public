//---------------------------------------------------------------------------------
#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"
Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix();
//---------------------------------------------------------------------------------
static const uint8_t PROGMEM  love_bmp[] = {0x00, 0x66, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C, 0x18};
static const uint8_t PROGMEM  smile_bmp[] = { B00111100, B01000010, B10100101, B10000001, B10100101, B10011001, B01000010, B00111100};
static const uint8_t PROGMEM  neutral_bmp[] = { B00111100, B01000010, B10100101, B10000001, B10111101, B10000001, B01000010, B00111100};
static const uint8_t PROGMEM  frown_bmp[] = { B00111100, B01000010, B10100101, B10000001, B10011001, B10100101, B01000010, B00111100};
//---------------------------------------------------------------------------------
void RGB8X8_setup() {
  //--------------------------------------------
  matrix.begin(0x71);
  matrix.setRotation(0);
  matrix.setTextSize(1);
  //--------------------------------------------
}
//---------------------------------------------------------------------------------
int BMP_Color_Key = 1, STR_Color_Key = 1; int BMP_Time_Key = 1000;
uint8_t rgb8x8_bmp[] = {60, 66, 165, 129, 165, 153, 66, 60};
String rgb_string = "I love You 1314 MaYuan!";
//---------------------------------------------------------------------------------
//BMP:1,2,...8,1,2,...8,..;*//8X8
//STR:ASDFASDFSAD*
//---------------------------------------------------------------------------------
void RGB8X8_loop() {
  //---------------------------------------------------------------------------------
  if (BMP_Color_Key == 0) matrix.clear();
  else if (BMP_Color_Key == 1) RGB8X8_bmp(rgb8x8_bmp, LED_RED, BMP_Time_Key);
  else if (BMP_Color_Key == 2) RGB8X8_bmp(rgb8x8_bmp, LED_GREEN, BMP_Time_Key);
  else if (BMP_Color_Key == 3) RGB8X8_bmp(rgb8x8_bmp, LED_YELLOW, BMP_Time_Key);
  //---------------------------------------------------------------------------------
  if (STR_Color_Key == 0) matrix.clear();
  else if (STR_Color_Key == 1) RGB8X8_text(rgb_string,  LED_RED, 70);
  else if (STR_Color_Key == 2) RGB8X8_text(rgb_string,  LED_GREEN, 70);
  else if (STR_Color_Key == 3) RGB8X8_text(rgb_string,  LED_YELLOW, 70);
  //---------------------------------------------------------------------------------
  matrix.clear(); smartDelay(300);
  //---------------------------------------------------------------------------------
}
void RGB8X8_bmp(uint8_t s[8], int colorKey, int delay_us) {
  //--------------------------------------------
  lg(F("RGB8X8_bmp = "));
  for (int i = 0; i < 8; i++) lg(rgb8x8_bmp[i]); lg();
  //--------------------------------------------
  if (delay_us <= 0) delay_us = 100;
  //--------------------------------------------
  matrix.clear();
  matrix.drawBitmap(0, 0, s, 8, 8, colorKey);
  matrix.writeDisplay();
  //--------------------------------------------
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
  //matrix.setTextColor(LED_RED);
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
void r_love(int s) {
  matrix.clear();
  matrix.drawBitmap(0, 0, love_bmp, 8, 8, LED_RED);
  matrix.writeDisplay(); delay(s);
}
void r_n(int s) {
  matrix.clear();
  matrix.drawBitmap(0, 0, neutral_bmp, 8, 8, LED_YELLOW);
  matrix.writeDisplay(); delay(s);
}
void r_s(int s) {
  matrix.clear();
  matrix.drawBitmap(0, 0, smile_bmp, 8, 8, LED_YELLOW);
  matrix.writeDisplay(); delay(s);
}
void r_t() {
  rgb_string = "I love You 1314 MaYuan!";
  RGB8X8_text(rgb_string,  LED_GREEN, 70);
}
//---------------------------------------------------------------------------------
void RGB8X8_loop_basic() {

  matrix.clear();
  matrix.drawBitmap(0, 0, smile_bmp, 8, 8, LED_YELLOW);
  matrix.writeDisplay();
  delay(1500);

  matrix.clear();
  matrix.drawBitmap(0, 0, neutral_bmp, 8, 8, LED_GREEN);
  matrix.writeDisplay();
  delay(1500);

  matrix.clear();
  matrix.drawBitmap(0, 0, frown_bmp, 8, 8, LED_RED);
  matrix.writeDisplay();
  delay(1500);
  return;

  matrix.clear();      // clear display
  matrix.drawPixel(0, 0, LED_GREEN);
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(500);

  matrix.clear();
  matrix.drawLine(0, 0, 7, 7, LED_YELLOW);
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(500);

  matrix.clear();
  matrix.drawRect(0, 0, 8, 8, LED_RED);
  matrix.fillRect(2, 2, 4, 4, LED_GREEN);
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(500);

  matrix.clear();
  matrix.drawCircle(3, 3, 3, LED_YELLOW);
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(500);

  matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
  matrix.setTextSize(1);
  matrix.setTextColor(LED_GREEN);
  for (int8_t x = 7; x >= -36; x--) {
    matrix.clear();
    matrix.setCursor(x, 0);
    matrix.print("Hello");
    matrix.writeDisplay();
    delay(100);
  }
  matrix.setRotation(3);
  matrix.setTextColor(LED_RED);
  for (int8_t x = 7; x >= -36; x--) {
    matrix.clear();
    matrix.setCursor(x, 0);
    matrix.print("World");
    matrix.writeDisplay();
    delay(100);
  }
  matrix.setRotation(0);
}
//---------------------------------------------------------------------------------

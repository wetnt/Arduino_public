//---------------------------------------------------------------------------------
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
//---------------------------------------------------------------------------------
#define PIN D1

Adafruit_NeoMatrix matrix =
  Adafruit_NeoMatrix(8, 8, PIN,
                     NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
                     NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
                     NEO_GRB            + NEO_KHZ800);

const uint16_t colors[] = {
  matrix.Color(0, 0, 255),
  matrix.Color(0, 255, 0),
  matrix.Color(255, 255, 0)
};
//---------------------------------------------------------------------------------
void WS2812_8x8_setup() {
  //--------------------------------------------
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(40);
  matrix.setTextColor(colors[0]);
  //--------------------------------------------
  matrix.clear();
  matrix.setCursor(0, 0);
  matrix.print("M");
  matrix.show();
  //--------------------------------------------
  delay(1000);
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
void WS2812_8x8_bmp(uint8_t *s, uint16_t color) {
  //--------------------------------------------
  int colork = s[8]; if (colork < 0 || colork > 3) colork = 0;
  int showtm = s[9]; if (showtm < 0 || colork > 1000) showtm = 0;
  lg(F("RGB8X8_bmp = ")); lg(colork); lg(','); lg(showtm); lg();
  //--------------------------------------------
  if (colork != 0) {
    for (int h = 0; h < 8; h++) {
      outputTo2String(s[h]);
      for (int w = 0; w < 8; w++ ) {
        if (output[w] == '1') lg("##"); else lg("  ");
      }
      lg();
    }
    lg();
  }
  //--------------------------------------------
  matrix.clear();
  matrix.drawBitmap(0, 0, s, 8, 8, color);
  matrix.show();
  //--------------------------------------------
}
//---------------------------------------------------------------------------------
//void WS2812_8x8_bmp(uint8_t *s, uint16_t color) {
//  //--------------------------------------------
//  int colork = s[8]; if (colork < 0 || colork > 3) colork = 0;
//  int showtm = s[9]; if (showtm < 0 || colork > 1000) showtm = 0;
//  //--------------------------------------------
//  lg(F("RGB8X8_bmp = ")); lg(colork); lg(','); lg(showtm); lg();
//  //for (int i = 0; i < 8; i++) lg(rgb8x8_bmp[i]);
//  //--------------------------------------------
//  matrix.clear();
//  if (colork != 0) {
//    //--------------------------------------------
//    for (int h = 0; h < 8; h++) {
//      outputTo2String(s[h]);
//      for (int w = 0; w < 8; w++ ) {
//        if (output[w] == '1') lg("##"); else lg("  ");
//        if (output[w] == '1') matrix.drawPixel(w, h, colork);
//      }
//      lg();
//    }
//    lg();
//    //--------------------------------------------
//  }
//  //--------------------------------------------
//  matrix.show();
//  //--------------------------------------------
//}
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
    matrix.show();
  }
  //--------------------------------------------
}

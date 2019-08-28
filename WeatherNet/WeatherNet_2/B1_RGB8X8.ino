//---------------------------------------------------------------------------------
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
//---------------------------------------------------------------------------------
#define PIN 12
Adafruit_NeoMatrix matrix =
  Adafruit_NeoMatrix(8, 8, PIN,
                     NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
                     NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
                     NEO_GRB            + NEO_KHZ800);
//---------------------------------------------------------------------------------
const uint16_t colors[] = {
  matrix.Color(0, 0, 0),
  matrix.Color(255, 0, 0),
  matrix.Color(255, 255, 0),
  matrix.Color(0, 255, 255)
};
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
char output[9];
void outputTo2String(long number) {
  for (int i = 0; i < 8; i++) {
    output[i] = number & (1 << 7 - i);
    output[i] = output[i] >> 7 - i;
    output[i] = (output[i] == 0) ? '0' : '1';
  }
  output[8] = '\0';
}
//---------------------------------------------------------------------------------
void RGB8X8_setup() {
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(20);
  matrix.setTextColor(colors[2]);
}
//---------------------------------------------------------------------------------
void RGB8X8_loop() {
  //---------------------------------------------------------------------------------
  RGB8X8_bmp(bmp1); RGB8X8_bmp(bmp2); RGB8X8_bmp(bmp3);
  RGB8X8_bmp(bmp4); RGB8X8_bmp(bmp5);
  matrix.setTextColor(colors[1]);
  RGB8X8_falsh(str0, 70); smartDelay(500);
  RGB8X8_bmp(bmp6);
  //---------------------------------------------------------------------------------
}
void RGB8X8_bmp(uint8_t s[10]) {
  //--------------------------------------------
  int colork = s[8]; if (colork < 0 || colork > 3) colork = 0;
  int showtm = s[9]; if (showtm < 0 || colork > 1000) showtm = 0;
  //--------------------------------------------
  lg(F("RGB8X8_bmp = ")); lg(colork); lg(','); lg(showtm); lg();
  //--------------------------------------------
  matrix.clear();
  if (colork != 0) {
    //--------------------------------------------
    for (int h = 0; h < 8; h++) {
      outputTo2String(s[h]);
      for (int w = 0; w < 8; w++ ) {
        if (output[w] == '1') lg("##"); else lg("  ");
        if (output[w] == '1') matrix.drawPixel(w, h, colors[colork]);
      } lg();
    } lg();
    //--------------------------------------------
  }
  //--------------------------------------------
  matrix.show();
  smartDelay(showtm * 100);
  //--------------------------------------------
}
//---------------------------------------------------------------------------------
void RGB8X8_text(String txt) {  
  matrix.fillScreen(0);
  matrix.setCursor(0, 0);
  matrix.print(txt);
  matrix.show();
}
void RGB8X8_falsh(String txt, int delay_us) {
  //--------------------------------------------
  lg(F("RGB8X8_text = ")); lgln(txt);
  //--------------------------------------------
  if (delay_us < 0) delay_us = 100;
  int x = matrix.width();
  int n = (txt.length() + 1) * 6;
  //--------------------------------------------
  for (int i = 0; i < n; i++) {
    matrix.fillScreen(0);
    matrix.setCursor(x, 0);
    matrix.print(txt);
    matrix.show(); --x;
    smartDelay(delay_us);
  }
  //--------------------------------------------
  //matrix.fillScreen(0); 
  matrix.clear();matrix.show();
  //--------------------------------------------
}
//---------------------------------------------------------------------------------


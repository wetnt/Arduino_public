//===============================================
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
//===============================================
#define PIN D4
//===============================================
Adafruit_NeoMatrix matrix =
  Adafruit_NeoMatrix(24, 8, PIN,
                     NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
                     NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
                     NEO_GRB            + NEO_KHZ800);
//===============================================
const uint16_t colors[] = {
  matrix.Color(255, 0, 0),//RED
  matrix.Color(0, 255, 0),//GREEN
  matrix.Color(0, 0, 255),//BLUE
  matrix.Color(255, 255, 0)//RED
};
const uint16_t LED_RED = colors[0];
const uint16_t LED_GREEN = colors[1];
const uint16_t LED_BLUE = colors[2];
const uint16_t LED_YELLOW = colors[3];
//===============================================
String ws8x8_txt = "COMMSAT-12345-$#@$&*:)";
int ws8x8_n = (ws8x8_txt.length() + 1) * 6;
uint8_t bmp_box[10] = {0x00, 0x24, 0x7E, 0x7E, 0x3C, 0x18, 0x00, 0x00, 1, 5};
//===============================================
void ws8x8_setup() {
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(15);
  matrix.setTextColor(colors[0]);
}
void ws8x8_bmp(uint8_t *bmp,uint16_t color) {
  matrix.clear();
  matrix.drawBitmap(0, 0, bmp, 8, 8, color);
  matrix.show();
}
//===============================================
//===============================================
//===============================================
int ws8x8_x = matrix.width();
int ws8x8_c = 0;
void ws8x8_txt_loop() {
  //------------------------------------------
  matrix.fillScreen(0);
  matrix.setCursor(ws8x8_x, 0);
  matrix.print(ws8x8_txt);
  //------------------------------------------
  if (--ws8x8_x < -ws8x8_n) {
    ws8x8_x = matrix.width();
    if (++ws8x8_c >= 3) ws8x8_c = 0;
    matrix.setTextColor(colors[ws8x8_c]);
  }
  //------------------------------------------
  matrix.show();
  //------------------------------------------
}
void ws8x8_bmp_loop() {
  ws8x8_bmp(bmp_box, LED_RED);
}
//===============================================
//===============================================


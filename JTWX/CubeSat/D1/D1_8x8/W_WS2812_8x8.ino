//===============================================
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
//===============================================
#define WS2812_Widths 8;
#define WS2812_Height 8;
#define PIN D4
//===============================================
Adafruit_NeoMatrix matrix =
  Adafruit_NeoMatrix(8, 8, PIN,
                     NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
                     NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
                     NEO_GRB            + NEO_KHZ800);
//===============================================
const uint16_t colors[] = {
  matrix.Color(0, 0, 255),
  matrix.Color(0, 255, 0),
  matrix.Color(255, 255, 0)
};
//===============================================
void ws8x8_setup() {
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(5);
  matrix.setTextColor(colors[0]);
}
//===============================================
String txt = "COMMSAT-12345-$#@$&*:)";
int n = (txt.length() + 1) * 6;
//===============================================
int ws8x8_x = matrix.width();
int ws8x8_c = 0;
//===============================================
void ws8x8_loop() {
  //------------------------------------------
  matrix.fillScreen(0);
  matrix.setCursor(ws8x8_x, 0);
  matrix.print(txt);
  //------------------------------------------
  if (--ws8x8_x < -n) {
    ws8x8_x = matrix.width();
    if (++ws8x8_c >= 3) ws8x8_c = 0;
    matrix.setTextColor(colors[ws8x8_c]);
  }
  //------------------------------------------
  matrix.show();
  //------------------------------------------
}

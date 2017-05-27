#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#define PIN 39

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


String WS8X8_txt = " COMMSAT ";

void WS8X8_setup() {
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(40);
  matrix.setTextColor(colors[0]);
}

int x    = matrix.width();
int pass = 0;

void WS8X8_loop() {
  int n = (WS8X8_txt.length() + 1) * 6;
  matrix.fillScreen(0);
  matrix.setCursor(x, 0);
  matrix.print(WS8X8_txt);

  if (--x < -n) {
    x = matrix.width();
    if (++pass >= 3) pass = 0;
    //matrix.setTextColor(colors[pass]);
    matrix.setTextColor(colors[0]);
  }

  matrix.show();smartDelay2(100);
}

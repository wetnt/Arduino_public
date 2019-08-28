#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#define PIN 12

Adafruit_NeoMatrix matrix =
  Adafruit_NeoMatrix(8, 8, PIN,
                     NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
                     NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
                     NEO_GRB            + NEO_KHZ800);

const uint16_t colors[] = {
  matrix.Color(0, 0, 255),
  matrix.Color(0, 255, 0),
  matrix.Color(255,255, 0)
};

void setup() {
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(20);
  matrix.setTextColor(colors[0]);
}

int x    = matrix.width();
int pass = 0;

void loop() {
  String txt = "Welcome to TangBlock world - www.TangLock.com)";
  int n = (txt.length() + 1) * 6;

  matrix.fillScreen(0);
  matrix.setCursor(x, 0);
  matrix.print(txt);

  if (--x < -n) {
    x = matrix.width();
    if (++pass >= 3) pass = 0;
    matrix.setTextColor(colors[pass]);
  }

  matrix.show();
  delay(100);
}

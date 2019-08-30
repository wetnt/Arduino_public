#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#define PIN            A3
#define NUMPIXELS      64
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 500;

void setup() {
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  pixels.begin();
}

void loop() {
  for (int i = 1; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 10, 0));
    pixels.setPixelColor(i-1, pixels.Color(0, 0, 0));
    pixels.show();
    delay(delayval);
  }
}

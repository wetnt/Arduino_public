#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>

#define WS2812_Widths 8;
#define WS2812_Height 8;
#define PIN D4
//===============================================
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

void setup() {
  lgsetup(F("8x8 LED Matrix Test"));

  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(5);
  matrix.setTextColor(colors[0]);


  WeatherHttpExp();

  sss();


}

static const uint8_t PROGMEM
smile_bmp[] =
{ B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10100101,
  B10011001,
  B01000010,
  B00111100
},
neutral_bmp[] =
{ B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10111101,
  B10000001,
  B01000010,
  B00111100
},
frown_bmp[] =
{ B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10011001,
  B10100101,
  B01000010,
  B00111100
};

const uint16_t LED_GREEN = colors[0];
const uint16_t LED_YELLOW = colors[1];
const uint16_t LED_RED = colors[2];

uint8_t bmpx[] = {0x00, 0x24, 0x7E, 0x7E, 0x3C, 0x18, 0x00, 0x00};
//static const uint8_t PROGMEM bmpx[] = {B00111100,    B01000010,    B10100101,B10000001,    B10111101,    B10000001,    B01000010,    B00111100};

void loop() {
  //RGB8X8_loop();

  /*

    matrix.clear();
    matrix.drawBitmap(0, 0, bmpx, 8, 8, LED_GREEN);
    matrix.show();
    delay(500);


    matrix.clear();
    matrix.drawBitmap(0, 0, neutral_bmp, 8, 8, LED_YELLOW);
    matrix.writeDisplay();
    delay(500);

    matrix.clear();
    matrix.drawBitmap(0, 0, frown_bmp, 8, 8, LED_RED);
    matrix.writeDisplay();
    delay(500);

    matrix.clear();      // clear display
    matrix.drawPixel(0, 0, LED_GREEN);
    matrix.writeDisplay();  // write the changes we just made to the display
    delay(500);

    matrix.clear();
    matrix.drawLine(0,0, 7,7, LED_YELLOW);
    matrix.writeDisplay();  // write the changes we just made to the display
    delay(500);

    matrix.clear();
    matrix.drawRect(0,0, 8,8, LED_RED);
    matrix.fillRect(2,2, 4,4, LED_GREEN);
    matrix.writeDisplay();  // write the changes we just made to the display
    delay(500);

    matrix.clear();
    matrix.drawCircle(3,3, 3, LED_YELLOW);
    matrix.writeDisplay();  // write the changes we just made to the display
    delay(500);

    matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
    matrix.setTextSize(1);
    matrix.setTextColor(LED_GREEN);
    for (int8_t x=7; x>=-36; x--) {
      matrix.clear();
      matrix.setCursor(x,0);
      matrix.print("Hello");
      matrix.writeDisplay();
      delay(100);
    }
    matrix.setRotation(3);
    matrix.setTextColor(LED_RED);
    for (int8_t x=7; x>=-36; x--) {
      matrix.clear();
      matrix.setCursor(x,0);
      matrix.print("World");
      matrix.writeDisplay();
      delay(100);
    }
    matrix.setRotation(0);
  */
}
//===============================================
static void smartDelay(unsigned long ms) {
  unsigned long start = millis(); do {
    //------------------------------------------
    //lgFeed(); wfs_loop(); Dog_Loop();
    //------------------------------------------
  } while (millis() - start < ms);
}

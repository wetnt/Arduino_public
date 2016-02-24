#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix();

void setup() {
  //--------------------------------------------------
  //!!!必须不然硬件烧毁!!!
  pinMode(9, INPUT);  pinMode(12, INPUT);
  //--------------------------------------------
  lgsetup("8x8 LED Matrix Test!Net Line");
  wifi_Init(true, true, false); //lg,AP,test
  //--------------------------------------------
  matrix.begin(0x71);
}

static const uint8_t PROGMEM  smile_bmp[] = { 60, 66, 165, 129, 165, 153, 66, 60};
static const uint8_t PROGMEM  neutral_bmp[] = { B00111100, B01000010, B10100101, B10000001, B10111101, B10000001, B01000010, B00111100};
static const uint8_t PROGMEM  frown_bmp[] = { B00111100, B01000010, B10100101, B10000001, B10011001, B10100101, B01000010, B00111100};

//BMP:1,2,...8,1,2,...8,..;*//8X8
//STR:ASDFASDFSAD*

void loop() {

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
//===============================================
static void smartDelay(unsigned long ms) {
  unsigned long start = millis(); do {
    //------------------------------------------
    lgFeed(); wfs_loop();
    //------------------------------------------
  } while (millis() - start < ms);
}
//===============================================

#include <Arduino.h>
#include <TM1637Display.h>

#define CLK 2
#define DIO 3
#define TEST_DELAY   2000

TM1637Display tm(2, 3);//CLK, DIO

void setup() {
  tm.setBrightness(0x0f);
}

void loop() {
  tm.showNumberDec(1536);  delay(TEST_DELAY);
  tm.showNumberDec(22 , false, 4, 0);  delay(TEST_DELAY);
}

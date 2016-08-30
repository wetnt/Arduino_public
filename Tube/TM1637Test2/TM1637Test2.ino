#include <Arduino.h>
#include <TM1637Display.h>

// Module connection pins (Digital Pins)
#define CLK 3
#define DIO 2
#define TEST_DELAY   1000
TM1637Display display(CLK, DIO);

int k = 0;
void setup() {
  display.setBrightness(0x0f);
  k = 0;
}
void loop() {
  //  uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };
  //  display.setSegments(data);  delay(TEST_DELAY);// All segments on

  //参数：数字,是否补充0,变化位数,
  k++;
  display.showNumberDec(k, false, 4, 0);    delay(TEST_DELAY);
}

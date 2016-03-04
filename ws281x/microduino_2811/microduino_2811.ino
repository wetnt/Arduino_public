static const String codeName = "ws2811!";

#include <Adafruit_NeoPixel.h>
 
#define PIN 7   //led灯控制引脚
#define PIN_NUM 1 //允许接的led灯的个数
 
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIN_NUM, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  lgsetup(codeName);
  strip.begin();
}
 
void loop() {
  lgln("red");
  strip.setPixelColor(0, strip.Color(255, 0, 0));//红
  strip.show();
  delay(1000);
  lgln("green");
  strip.setPixelColor(0, strip.Color(0, 255, 0));//绿
  strip.show();
  delay(1000);
  lgln("blue");
  strip.setPixelColor(0, strip.Color(0, 0, 255));//蓝
  strip.show();
  delay(1000);
  lgln("close");
  strip.setPixelColor(0, strip.Color(0, 0, 0));//灭
  strip.show();
  delay(1000);
}

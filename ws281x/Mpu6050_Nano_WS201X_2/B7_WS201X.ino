//===================================================================
#include <Adafruit_NeoPixel.h>
//===================================================================
#define PIN 7   //led灯控制引脚
#define PIN_NUM 1 //允许接的led灯的个数 
//===================================================================
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIN_NUM, PIN, NEO_GRB + NEO_KHZ800);
//===================================================================
static const String WS_codeName = "ws2811_setup!";
void WS_setup() {
  lgsetup(WS_codeName);
  strip.begin();
}
void WS_start() {
  //strip.Color(255, 0, 0)//Red,Green,Blue
  strip.setPixelColor(0, strip.Color(255, 0, 0)); strip.show(); delay(1000); lgln("red");   //红
  strip.setPixelColor(0, strip.Color(0, 255, 0)); strip.show(); delay(1000); lgln("green"); //绿
  strip.setPixelColor(0, strip.Color(0, 0, 255)); strip.show(); delay(1000); lgln("blue");  //蓝
  strip.setPixelColor(0, strip.Color(0, 0, 0));   strip.show(); delay(1000); lgln("close"); //灭
}
void WS_show() {
  int r, g, b;
  r = abs(imu.roll);  r = r % 45; r = map(r, 0, 45, 0, 255);
  g = abs(imu.pitch); g = g % 45; g = map(g, 0, 45, 0, 255);
  b = abs(imu.yaw);   b = b % 45; b = map(b, 0, 45, 0, 255);
  strip.setPixelColor(0, strip.Color(r, g, b)); strip.show();
  lg(r); lg(','); lg(g); lg(','); lg(b); lg();
}

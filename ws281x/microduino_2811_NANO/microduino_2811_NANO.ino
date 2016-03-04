
http://my.oschina.net/u/241133/blog/143881
https://www.arduino.cc/en/Tutorial/MasterReader
http://todbot.com/blog/2010/09/25/softi2cmaster-add-i2c-to-any-arduino-pins/

static const uint8_t SS   = 10;
static const uint8_t MOSI = 11;
static const uint8_t MISO = 12;
static const uint8_t SCK  = 13;


static const uint8_t SDA = 18;
static const uint8_t SCL = 19;
static const uint8_t LED_BUILTIN = 13;


static const uint8_t A0 = 14;
static const uint8_t A1 = 15;
static const uint8_t A2 = 16;
static const uint8_t A3 = 17;
static const uint8_t A4 = 18;
static const uint8_t A5 = 19;
static const uint8_t A6 = 20;
static const uint8_t A7 = 21;


Arduino Board：I2C / TWI pins
Arduino Uno/Ethernet：A4 (SDA), A5 (SCL)
Arduino Mega2560：20 (SDA), 21 (SCL)
Arduino Leonardo：2 (SDA), 3 (SCL)
Arduino Due：20 (SDA), 21 (SCL), SDA1, SCL1




SDA = 18;
SCL = 19;

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

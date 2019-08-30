//--------------------------------------------------
#include <Wire.h>
#include "SSD1306.h"
SSD1306  oled(0x3c, 4, 15);
//--------------------------------------------------
//OLED pins to ESP32 GPIOs via this connecthin:
//OLED_SDA -- GPIO4
//OLED_SCL -- GPIO15
//OLED_RST -- GPIO16
//--------------------------------------------------
void oled_setup() {
  //--------------------------------------------------
  pinMode(16, OUTPUT);
  digitalWrite(16, LOW); delay(50); digitalWrite(16, HIGH);
  //while OLED is running, must set GPIO16 in high
  //--------------------------------------------------
  oled.init();
  oled.flipScreenVertically();//垂直翻转屏幕
  oled.setContrast(255);//对比度
  oled.setFont(ArialMT_Plain_10);
  //--------------------------------------------------
  oled.clear(); drawFontFaceDemo(); oled.display(); delay(1000);
  oled.clear(); drawTextFlowDemo(); oled.display(); delay(1000);
  //--------------------------------------------------
}
void oled_str(String s){
  oled.clear(); oled.drawStringMaxWidth(0, 0, 128, s); oled.display();
}
//============================================================================
void drawFontFaceDemo() {
  oled.setTextAlignment(TEXT_ALIGN_LEFT);
  oled.setFont(ArialMT_Plain_10); oled.drawString(0, 0, "Hello world");
  oled.setFont(ArialMT_Plain_16); oled.drawString(0, 10, "Hello world");
  oled.setFont(ArialMT_Plain_24); oled.drawString(0, 26, "Hello world");
  oled.display();
}
void drawTextFlowDemo() {
  oled.setFont(ArialMT_Plain_10); oled.setTextAlignment(TEXT_ALIGN_LEFT);
  oled.drawStringMaxWidth(0, 0, 128, "I love you Baby!!!" );
}
//============================================================================

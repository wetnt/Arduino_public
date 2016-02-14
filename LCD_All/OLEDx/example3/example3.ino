#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

void setup()   {
  Serial.begin(115200); delay(500);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  //I2C addr 0x3D (for the 128x64)
  display.display(); delay(1000);
  display.clearDisplay();


  // text display tests
  displayText("Hello, world!");

//  display.invertDisplay(true);  delay(1000);
//  display.invertDisplay(false); delay(1000);

//  display.clearDisplay();
//  display.drawBitmap2(30, 16,  logo16_glcd_bmp, 16, 16, 1);
//  display.display();
}

void displayDelay() {
  display.display(); delay(2000); display.clearDisplay();
}

void dText(int x,int y, String s) {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE, BLACK);//display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println(s);
  display.display();
  delay(2000);
  display.clearDisplay();
}



void loop() {

}


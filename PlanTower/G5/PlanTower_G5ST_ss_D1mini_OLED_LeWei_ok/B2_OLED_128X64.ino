#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_MOSI   12
#define OLED_CLK    14
#define OLED_DC     5
#define OLED_RESET  4
#define OLED_CS     0
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

void oled_setup() {
  display.begin(SSD1306_SWITCHCAPVCC);
  //display.invertDisplay(true);//反色
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);display.print("BOBOKing G5ST");
  display.setCursor(0,32);display.print("086 13911969356");
  display.display();
}

void oled_show() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  int xn = 6;
  int x1 = 0;
  int x2 = 97;
  int x3 = 35;
  int y1 = 0;
  int y2 = 16;
  int y3 = 32;
  int y4 = 48;

  display.setCursor(x1, y1 + xn); display.print("PM2.5"); display.setCursor(x2, y1 + xn); display.println("ug/m3");
  display.setCursor(x1, y2 + xn); display.print("HCHO"); display.setCursor(x2, y2 + xn); display.println("mg/m3");
  display.setCursor(x1, y3 + xn); display.print("TEMP"); display.setCursor(x2, y3 + xn); display.println("C");
  display.setCursor(x1, y4 + xn); display.print("HUMS"); display.setCursor(x2, y4 + xn); display.println("%");

  display.setTextSize(2);
  display.setCursor(x3, y1); display.print(g.pm25);
  display.setCursor(x3, y2); display.print(g.hcho, 3);
  display.setCursor(x3, y3); display.print(g.tmps, 1);
  display.setCursor(x3, y4); display.print(g.hums);
  display.display();
}

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//#define OLED_CLK    D5//14
//#define OLED_MOSI   D6//12
//#define OLED_RESET  D2//4
//#define OLED_DC     D1//5
//#define OLED_CS     0//0


#define OLED_CLK    D6//14
#define OLED_MOSI   D5//12
#define OLED_RESET  D0//4
#define OLED_DC     D1//5
#define OLED_CS     D2//0

Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

void oled_setup() {
  display.begin(SSD1306_SWITCHCAPVCC);
  //display.invertDisplay(true);//反色
  display.clearDisplay();

  display.setTextSize(0);
  display.setTextColor(WHITE);
  display.setCursor(0, 8);
  display.print("PM2.5");
  display.setCursor(97, 8);
  display.println("ug/m3");

  display.setCursor(3, 35);
  display.print("HCHO");
  display.setCursor(97, 35);
  display.println("mg/m3");

  display.setTextSize(2);
  display.setCursor(47, 4);
  display.print("000");

  display.setCursor(47, 32);
  display.print("000");

  display.display();
}

void oled_show() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(0, 8);  display.print("PM2.5");
  display.setCursor(95, 8); display.println("ug/m3");
  display.setCursor(0, 35);  display.print("HCHO");
  display.setCursor(95, 35); display.println("mg/m3");

  display.setTextSize(2);
  display.display();
}

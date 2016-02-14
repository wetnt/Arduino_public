#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup()   {
  Serial.begin(115200); delay(500);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  //I2C addr 0x3D (for the 128x64)
  display.display(); delay(1000);
  display.clearDisplay();

  displayText("Hello, world!");
}
void displayDelay() {
  display.display(); delay(2000); display.clearDisplay();
}
void displayText(String s) {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Hello, world!");

  display.setTextColor(BLACK, WHITE);
  
  display.println(3.141592);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.print("0x"); display.println(0xDEADBEEF, HEX);
  display.display();
  delay(2000);

}

void loop() {
}


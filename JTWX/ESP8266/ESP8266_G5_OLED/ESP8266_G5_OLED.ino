#include <Arduino.h>
//#include <ESP8266WiFi.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "G5_Drive.h"

#define OLED_MOSI   12
#define OLED_CLK   14
#define OLED_DC    5
#define OLED_CS    0
#define OLED_RESET 4

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif


Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

void setup()
{
	Serial.begin(9600);
	Serial.println();

	display.begin(SSD1306_SWITCHCAPVCC);

	display.clearDisplay();

	display.setTextSize(1);	display.setTextColor(WHITE);	
	display.setCursor(0,8);	display.print("PM2.5");	display.setCursor(97,8);	display.println("ug/m3");
	display.setCursor(0,35);	display.print("HCHO");	display.setCursor(97,35);	display.println("mg/m3");

	display.setTextSize(2);	
	display.setCursor(47,4);	display.print("000");
	display.setCursor(47,32);	display.print("000");
	
	display.display();
}

void loop()
{
	if (Serial.available()) {
		byte c = Serial.read();
		G5Feed(c);
	}

	display.clearDisplay();

	display.setTextSize(1);
	display.setTextColor(WHITE);
	display.setCursor(0,8);	display.print("PM2.5");	display.setCursor(97,8);	display.println("ug/m3");
	display.setCursor(3,35);	display.print("HCHO");	display.setCursor(97,35);	display.println("mg/m3");

	display.setTextSize(2);
	display.setCursor(35,4);
	if ((g.pm25/10000%10) == 0)
		display.print(" ");
	else display.print((byte)(g.pm25/10000%10), DEC);
	display.setCursor(47,4);
	if ((g.pm25/1000%10) == 0)
		display.print(" ");
	else display.print((byte)(g.pm25/1000%10), DEC);
	display.setCursor(59,4);
	if ((g.pm25/100%10) == 0)
		display.print(" ");
	else display.print((byte)(g.pm25/100%10), DEC);
	display.setCursor(71,4);
	if ((g.pm25/10%10) == 0)
		display.print(" ");
	else display.print((byte)(g.pm25/10%10), DEC);
	display.setCursor(83,4);
	display.print((byte)(g.pm25%10), DEC);

	display.setCursor(35,32);
	display.print((byte)(g.hcho/1000%10), DEC);
	display.setCursor(47,32);
	display.print(".");
	display.setCursor(59,32);
	display.print((byte)(g.hcho/100%10), DEC);
	display.setCursor(71,32);
	display.print((byte)(g.hcho/10%10), DEC);
	display.setCursor(83,32);
	display.print((byte)(g.hcho%10), DEC);

	display.display();
}



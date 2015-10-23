#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x20,16,2);  // set the LCD address to 0x20 for a 16 chars and 2 line display
long t0;//计时器

void setup()
{
  lcd.init(); // initialize the lcd 
  lcd.backlight();
  lcd.print("Hello, world!");
  Serial.begin(9600); // 定义串口
}

void loop()
{
  t0 = micros();
  Serial.println(t0);
  lcd.clear();
  lcd.print(t0,DEC);
  delay(500);
}


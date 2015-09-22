#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

long t0;	//计时器

void setup(void) {
  
  Serial.begin(9600);  
  Serial.println("hello!");
  
  nokia.init();
  nokia.setContrast(40);
  nokia.clear();
}

void loop(void) {
  
  t0 = micros();
    
  nokia.setPixel(10, 10, BLACK);// draw a single pixel
  nokia.setCursor(0, 17);
  
  nokia.print(t0);
  nokia.print(t0);
  nokia.print("/");
  
  nokia.display();
  delay(200);
  nokia.clear();
  
}

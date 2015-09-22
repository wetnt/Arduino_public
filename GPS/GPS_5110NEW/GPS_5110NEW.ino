#include "PCD8544.h"

// pin 7 - Serial clock out (SCLK) 3
// pin 6 - Serial data out (DIN) 4 
// pin 5 - Data/Command select (D/C) 5
// pin 4 - LCD chip select (CS) 7
// pin 3 - LCD reset (RST) 6
//PCD8544 nokia = PCD8544(7, 6, 5, 4, 3);

PCD8544 nokia = PCD8544(3,4,5,7,6); 
// 3 pin LCD control, SCLK, DN, D/C (CS, RST)

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

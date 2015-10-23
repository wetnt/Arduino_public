#include <PCD8544.h>

#include "PCD8544.h"

// pin 7 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
//PCD8544 nokia = PCD8544(7, 6, 5, 4, 3);

PCD8544 nokia = PCD8544(8,9,10,11,12); 
// 3 pin LCD control, SCLK, DN, D/C (CS, RST)

long t0;  //计时器

void setup(void) {
  
  Serial.begin(9600);  
  Serial.println("hello!");
  
  nokia.begin(84, 48);
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


#include "Image.h"

int pinLed = 13;
void setup() {
  Serial.begin(115200);
  oled_loop();
  moto_setup();
}

void loop() {
  //driveStepper();
  oled_loop(); delay(300);
}

void driveStepper() {
  moto_work();
}


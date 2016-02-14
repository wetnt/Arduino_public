
#include "xx.h"

void setup() {
  lgsetup("MPU6050_IMU");
  MPU6050_setup();
  IMU_setup();
}
void loop() {
  IMU_loop(); IMU_show();
  delay(10);
}

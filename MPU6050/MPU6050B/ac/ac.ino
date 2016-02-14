void setup() {
  //-------------------------------------
  lgsetup("MPU6050_IMU");
  MPU6050_setup();
  //-------------------------------------
}

void loop() {
  // put your main code here, to run repeatedly:
  MPU6050_loop();
  delay(20);
}

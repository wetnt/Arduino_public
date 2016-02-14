void setup() {
  //-------------------------------------
  lgsetup("MPU6050_IMU");
  imu_setup();
  //-------------------------------------
}

void loop() {
  // put your main code here, to run repeatedly:
  imu_loop();
  delay(20);
}

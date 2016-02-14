unsigned long t0, t1; //计时器
boolean RunTime(int tk) {
  boolean k = (micros() - t0) / 1000 > tk;
  if (!k)return false;
  t0 = micros(); return k;
}
void setup() {
  //-----------------------------------------------------------------------
  lgsetup(F("MPU6050_Nano_ok"));
  mpu_setup();
  //-----------------------------------------------------------------------
}
void loop() {
  if (RunTime(20)) {
    mathSensors();
    mpu_show2();
  }
  mpu_loop();
}





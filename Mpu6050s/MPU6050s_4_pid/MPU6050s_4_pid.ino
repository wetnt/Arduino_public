

//------------------------------------------------------------
long t0;//计时器
long RunTime()
{
  return ( micros() - t0 ) / 1000;
}
//------------------------------------------------------------


void setup() {
  //------------------------------------------------------------
  Serial.begin(115200);
  Serial3.begin(115200);//MPU6050_Read
  //------------------------------------------------------------
  mpu_init();
  achou_init();
  //------------------------------------------------------------
  Serial.println("Motor Go!");
  //------------------------------------------------------------
}

void loop() {
  //------------------------------------------------------------
  if (RunTime() > 20)
  {
    t0 = micros();
    mpu_show();
    achou_run();
  }
  // if (mpu_sign)
  //  {
  //   mpu_sign = false;
  // }

  //------------------------------------------------------------
  //------------------------------------------------------------
  //------------------------------------------------------------
  //------------------------------------------------------------
}
void serialEvent3() {//伪中断，loop()里不能有有delay
  //------------------------------------------------------------
  while (Serial3.available()) {
    mpu_read((unsigned char)Serial3.read());
  }
  //------------------------------------------------------------
}





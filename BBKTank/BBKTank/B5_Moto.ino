void moto_run_fast() {
  moto_run( 255, 1, 255, 1);
}
void moto_run_mid() {
  moto_run( 155, 1, 155, 1);
}
void moto_run_slow() {
  moto_run( 100, 1, 100, 1);
}
//------------------------------------------
void moto_run_step() {
  for (int i = 0; i < 255; i++) {
    moto_run( i, 1, i, 1);
    delay(50);
  }
  delay(5000);
  moto_stop(); delay(5000);
  for (int i = 0; i < 255; i++) {
    moto_run( i, -1, i, -1);  Serial.println(i);
    delay(50);
  }
  delay(5000);
  moto_stop(); delay(5000);
}
//------------------------------------------

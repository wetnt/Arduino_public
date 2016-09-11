//------------------------------------------
unsigned long car_cmd_start = millis();
void Car_stop() {
  if ( millis() - car_cmd_start > 1000) {
    Car_run(0, 0);
  }
}
void Car_run(int p, int y) {
  car_cmd_start = millis();
  int kr = p >= 0 ? 1 : -1;
  int kl = y >= 0 ? 1 : -1;
  int vr = abs(p);
  int vl = abs(y);
  moto_run(vr, kr, vl, kl);
}
//------------------------------------------
void moto_run_fast() {
  moto_run(255, 1, 255, 1);
}
void moto_run_mid() {
  moto_run(155, 1, 155, 1);
}
void moto_run_slow() {
  moto_run(100, 1, 100, 1);
}
//------------------------------------------
void moto_run_step() {
  for (int i = 0; i < 255; i++) {
    moto_run( i, 1, i, 1); lg(i); lg();
    delay(50);
  } delay(5000); moto_stop(); delay(5000);
  for (int i = 0; i < 255; i++) {
    moto_run( i, -1, i, -1); lg(i); lg();
    delay(50);
  } delay(5000); moto_stop(); delay(5000);
}
//------------------------------------------

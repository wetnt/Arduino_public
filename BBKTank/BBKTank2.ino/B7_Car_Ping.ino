void Car_Ping_Init() {
  PingSetup(A0, A1);
}
double Car_Head_length = 100;
void Car_Ping_Loop() {
  Car_Head_length = (double)PingLoop();
  if (Car_Head_length < 30) {
    rc_cmd_head_run_stop();
  }
}


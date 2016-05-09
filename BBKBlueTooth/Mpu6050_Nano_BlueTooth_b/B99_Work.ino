int n_r, n_g, n_b, n_x, l_r, l_g, l_b, l_x;
void IMU_work() {
  //------------------------------------------------------
  n_r = imu.roll; n_g = imu.pitch; n_b = imu.yaw;
  n_x = abs(n_r - l_r) + abs(n_g - l_g) + abs(n_b - l_b);
  l_r = imu.roll; l_g = imu.pitch; l_b = imu.yaw;
  //------------------------------------------------------
  //lg(n_r); lg(','); lg(n_g); lg(','); lg(n_b); lg(','); lg(n_x); lg();
  //------------------------------------------------------
  IMU_BlueTooth_Check();
  //------------------------------------------------------
}
long Time_Start, Time_Stops, Time_Runxx; boolean runKey = false;
int runnx = 0;
void IMU_BlueTooth_Check() {
  runnx += n_x;
}
void IMU_BlueTooth_Out() {
  //------------------------------------------------------
  boolean secondRun = runnx > 30; runnx = 0;
  //------------------------------------------------------
  if (secondRun && runKey == false) {
    Time_Start = millis(); runKey = true;
    Time_Stops = 0;
    State_BlueTooth_Runs_Out();
  }
  if (!secondRun && runKey == true) {
    Time_Stops = millis(); runKey = false;
    State_BlueTooth_Stop_Out();
  }
  //------------------------------------------------------
  lg(runKey); lg(' '); lg(Time_Start); lg(' '); lg(Time_Stops); lg(' '); lg(millis() / 1000); lg();
  //------------------------------------------------------
}
void State_BlueTooth_Runs_Out(){
    ss.print("Runs..."); ss.println(millis() / 1000);  
}
void State_BlueTooth_Stop_Out(){
    ss.print("Stop..."); ss.print(millis() / 1000); ss.print("="); ss.println((Time_Stops - Time_Start) / 1000);  
}


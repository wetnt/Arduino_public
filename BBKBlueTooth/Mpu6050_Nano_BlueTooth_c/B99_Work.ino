int n_r, n_g, n_b, n_x, l_r, l_g, l_b, l_x; unsigned long run_level = 0;
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
  run_level += runnx; boolean secondRun = runnx > 80; runnx = 0;
  //------------------------------------------------------
  if (secondRun && runKey == false) {
    Time_Start = millis(); runKey = true; Time_Stops = 0;
    run_level = 0; State_BlueTooth_Runs_Out();
  }
  if (!secondRun && runKey == true) {
    Time_Stops = millis(); runKey = false;
    int lv = run_level * 1000 / (Time_Stops - Time_Start);
    State_BlueTooth_Stop_Out(lv);
  }
  //------------------------------------------------------
  //lg(runKey); lg(' '); lg(Time_Start); lg(' '); lg(Time_Stops); lg(' '); lg(millis() / 1000); lg();
  //------------------------------------------------------
  if (bufferBack == "{BackData}") {
    sb_show(); sb_clear(); lg();
    lg("gjgjhgjgjhgjg");
    Get_All_Data();
  }
  //------------------------------------------------------
}
void State_BlueTooth_Runs_Out() {
  //ss.print("Runs..."); ss.println(millis() / 1000);
  Puts_New_Data('r', millis() / 1000, 0);
}
void State_BlueTooth_Stop_Out(int lv) {
  //ss.print("Stop..."); ss.print(millis() / 1000); ss.print("="); ss.println((Time_Stops - Time_Start) / 1000);
  Puts_New_Data('s', millis() / 1000, lv);
}

boolean lg_work(String s) {
  if (s.length() <= 0) { //lg("E");
  } else if (s.indexOf("AllData") > 0) {//{AllData}
    Get_All_Data(); return true;
  } else if (s.indexOf("ClearData") > 0) {//{ClearData}
    Set_New_Data(); return true;
  } else if (s.indexOf("ccc") > 0) {
    lg("c"); return true;
  }
  return false;
}

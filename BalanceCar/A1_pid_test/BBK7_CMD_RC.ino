//-------------------------------------
//0123456789012 3 4567 8 9012 3 4567 890
//$FF7F7F7F00FF P 0850 I 0200 D 0000 *
//-------------------------------------
int cmd_rolls = 127; //1滚转：机头尾连线轴运动
int cmd_pitch = 127; //2前后/俯仰：飞机、低头、抬头 Pitch
int cmd_power = 127; //3油门
int cmd_yawss = 127; //4左右/偏航：机首机尾左右旋转 Yaw
int cmd_5thss = 0; //5
int cmd_6thss = 0; //6
//-------------------------------------
int rc_cmd_len = 20;
char rc_cmd[20];
int rc_idx = -1;
//-------------------------------------
void rc_cmd_feed(char c) {
  //---------------------------------------------------------
  if (c == '*') {
    rc_cmd_loop();
    rc_info_send();
  }
  //---------------------------------------------------------
  if (c == '$') {
    rc_idx = -1; rc_cmd_clear();
  }
  //---------------------------------------------------------
  rc_idx++; rc_cmd[rc_idx] = c;
  //---------------------------------------------------------
  if ( rc_idx == 0 ) {}
  else if (rc_idx == 2 ) cmd_rolls = getV(rc_cmd[1], rc_cmd[2]);
  else if (rc_idx == 4 ) cmd_pitch = getV(rc_cmd[3], rc_cmd[4]);
  else if (rc_idx == 6 ) cmd_power = getV(rc_cmd[5], rc_cmd[6]);
  else if (rc_idx == 8 ) cmd_yawss = getV(rc_cmd[7], rc_cmd[8]);
  else if (rc_idx == 10) cmd_5thss = getV(rc_cmd[9], rc_cmd[10]);
  else if (rc_idx == 12) cmd_6thss = getV(rc_cmd[11], rc_cmd[12]);
  //---------------------------------------------------------
  else if (rc_idx == 17) Kp = getK(rc_cmd[14], rc_cmd[15], rc_cmd[16], rc_cmd[17]);
  else if (rc_idx == 22) Ki = getK(rc_cmd[19], rc_cmd[20], rc_cmd[21], rc_cmd[22]);
  else if (rc_idx == 27) Kd = getK(rc_cmd[24], rc_cmd[25], rc_cmd[26], rc_cmd[27]);
  //---------------------------------------------------------
  if (rc_idx == 28) rc_pid_run();
  //---------------------------------------------------------
}
void rc_cmd_clear() {
  for (int i = 0; i < rc_cmd_len; i++) rc_cmd[i] = '\0';
}
void rc_cmd_loop() {//解析执行命令
  int p = map(cmd_pitch, 0, 255, -255, 255); if (abs(p) < 10 )p = 0;
  int y = map(cmd_rolls, 0, 255, -255, 255); if (abs(y) < 10 )y = 0;
  PidCtR = (p * 4 - y ) / 5;
  PidCtL = (p * 4 + y ) / 5;
  //---------------------------------------------------------
  //Car_loop(r, l, 50);
  //---------------------------------------------------------
  //lg("rcCmd = "); lg(cmd_pitch); lg(","); lg(cmd_rolls); lg("  ");
  //lg("rcExp = "); lg(p); lg(","); lg(y); lg("  ");
  //lg("CarCt = "); lg(r); lg(","); lg(l); lg("  ");
  //lg("Speed = "); lg(wr.sNow); lg(" = "); lg(wl.sNow); lg(" ");
  //lg();
  //---------------------------------------------------------
}
void rc_cmd_head_run_stop() {
  if (PidCtR > 0 && PidCtL > 0) {
    PidCtR = 0; PidCtL = 0;
  }
}
void rc_cmd_back_run_stop() {
  if (cmd_pitch < 127)
    cmd_pitch = 127; //1滚转：机头尾连线轴运动
}
//-----------------------------------------------------------------------------
boolean pidKey = false;
void rc_pid_run() {
  pidKey = true;
  lg("pidKey = true;");lg();
}
void rc_pid_loop() {
  if (pidKey) Car_Pid_Test(20);
  pidKey = false;
}
//-----------------------------------------------------------------------------

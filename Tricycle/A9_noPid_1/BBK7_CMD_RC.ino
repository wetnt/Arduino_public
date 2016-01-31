//-------------------------------------
//012345678901234567890
//$FF7F7F7F00FF*
//-------------------------------------
int cmd_rolls = 127; //1滚转：机头尾连线轴运动 Roll
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
    //lg(rc_cmd);lg();
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
  //else if (rc_idx == 14) cmd_6thss = rc_cmd[13] + rc_cmd[14];
  //---------------------------------------------------------
}
void rc_cmd_clear() {
  for (int i = 0; i < rc_cmd_len; i++) rc_cmd[i] = '\0';
}
void rc_cmd_loop() {
  int p = map(cmd_pitch, 0, 255, -255, 255); if (abs(p) < 10 )p = 0;
  int y = map(cmd_rolls, 0, 255, -255, 255); if (abs(y) < 10 )y = 0;
  int r = p - y/3;
  int l = p + y/3;
  Car_loop(r, l);
  lg("rcCmd = "); lg(p); lg(","); lg(y); lg(","); lg(r); lg(","); lg(l); lg();
  //lg("cmd_rolls = "); lg(cmd_rolls); lg();
}
//-----------------------------------------------------------------------------
int getV(char a, char b) {
  return GetHexCharToInt(a) * 16 + GetHexCharToInt(b);
}
int GetHexCharToInt(char c) {
  if (1 == 0) {}
  else if (c == '0') return 0;
  else if (c == '1') return 1;
  else if (c == '2') return 2;
  else if (c == '3') return 3;
  else if (c == '4') return 4;
  else if (c == '5') return 5;
  else if (c == '6') return 6;
  else if (c == '7') return 7;
  else if (c == '8') return 8;
  else if (c == '9') return 9;
  else if (c == 'A') return 10;
  else if (c == 'B') return 11;
  else if (c == 'C') return 12;
  else if (c == 'D') return 13;
  else if (c == 'E') return 14;
  else if (c == 'F') return 15;
}


//-------------------------------------
//012345678901234567890
//$BMFF7F7F7F00FF*
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
    //rc_info_send();
  }
  //---------------------------------------------------------
  if (c == '$') {
    rc_idx = -1; rc_cmd_clear();
  }
  //---------------------------------------------------------
  rc_idx++; rc_cmd[rc_idx] = c;
  //---------------------------------------------------------
  if ( rc_idx == 0 ) {}
  else if (rc_idx == 4 ) cmd_rolls = rc_cmd[3]  + rc_cmd[4];
  else if (rc_idx == 6 ) cmd_pitch = rc_cmd[5]  + rc_cmd[6];
  else if (rc_idx == 8 ) cmd_power = rc_cmd[7]  + rc_cmd[8];
  else if (rc_idx == 10) cmd_yawss = rc_cmd[9]  + rc_cmd[10];
  else if (rc_idx == 12) cmd_5thss = rc_cmd[11] + rc_cmd[12];
  else if (rc_idx == 14) cmd_6thss = rc_cmd[13] + rc_cmd[14];
  //---------------------------------------------------------
}
void rc_cmd_clear() {
  for (int i = 0; i < rc_cmd_len; i++) rc_cmd[i] = '\0';
}
void rc_cmd_loop() {
  int p = map(cmd_pitch, 0, 255, -255, 255);
  int y = map(cmd_yawss, 0, 255, -255, 255);
  int r = p + y;
  int l = p - y;
  //Car_loop(r, l);
  lg("rcCmd = ");lg(p);lg(",");lg(y);lg(",");lg(r);lg(",");lg(l);lg();
}


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
char rc_cmd[40];
int rc_idx = -1;
//-------------------------------------
void rc_cmd_feed(char c) {
  //---------------------------------------------------------
  if (c == '*') {
    rc_cmd_loop();
    rc_cmd_clear();
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
}
void rc_cmd_clear() {
  for (int i = 0; i < rc_cmd_len; i++) rc_cmd[i] = '\0';
}
void rc_cmd_loop() {//解析执行命令
  int ca = map(cmd_rolls, 0, 255, -255, 255); if (abs(ca) < 10 )ca = 0;
  int cb = map(cmd_pitch, 0, 255, -255, 255); if (abs(cb) < 10 )cb = 0;
  int cc = map(cmd_power, 0, 255, -255, 255); if (abs(cc) < 10 )cc = 0;
  int cd = map(cmd_yawss, 0, 255, -255, 255); if (abs(cd) < 10 )cd = 0;
  int va = abs(ca);  int ka = ca > 0 ? -1 : 1; if (abs(ca) == 0 )ka = 0;
  int vb = abs(cb);  int kb = cb > 0 ? -1 : 1; if (abs(cb) == 0 )kb = 0;
  int vc = abs(cc);  int kc = cc > 0 ? -1 : 1; if (abs(cc) == 0 )kc = 0;
  int vd = abs(cd);  int kd = cd > 0 ? -1 : 1; if (abs(cd) == 0 )kd = 0;
  //---------------------------------------------------------
  car_cmd_start = millis();
  moto_run(va, ka, vb, kb, vc, kc, vd, kd);
  //---------------------------------------------------------
}
//-----------------------------------------------------------------------------

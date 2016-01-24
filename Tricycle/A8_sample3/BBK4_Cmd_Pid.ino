//-------------------------------------
int rc_cmd_len = 20;
char rc_cmd[20];
int rc_idx = -1;
//-------------------------------------
int Pp, Pi, Pd;
//-------------------------------------
void rc_cmd_loop(char c) {
  //---------------------------------------------------------
  if (c == '$') {
    rc_idx = -1;
    rc_cmd_clear();
  }
  //---------------------------------------------------------
  rc_idx++; rc_cmd[rc_idx] = c;
  //---------------------------------------------------------
  if (c == '*') rc_info_send();
  //---------------------------------------------------------
}
int getV(char a, char b, char c) {
  String s = "";
  s.concat(a);  s.concat(b);  s.concat(c);
  lg(s); lg();
  return s.toInt();
}
void rc_info_send() {
  lg(rc_cmd); lg();
  Pp = getV(rc_cmd[1], rc_cmd[2], rc_cmd[3]);
  Pi = getV(rc_cmd[4], rc_cmd[5], rc_cmd[6]);
  Pd = getV(rc_cmd[7], rc_cmd[8], rc_cmd[9]);
  Car_Kpi(Pp, Pi, Pd);
  Car_loop(100);
}
void rc_cmd_clear() {
  for (int i = 0; i < rc_cmd_len; i++) rc_cmd[i] = '\0';
}

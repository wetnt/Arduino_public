//-------------------------------------
//01234567890
//$Second:+1*
//$Second:-1*
//-------------------------------------
int tc_cmd_len = 12;
char tc_cmd[12];
int tc_idx = -1;
//-------------------------------------
void tc_cmd_feed(char c) {
  if (c == '$') tc_cmd_clear();
  tc_idx++; tc_cmd[tc_idx] = c;
  if (c == '*') tc_cmd_run();
}
void tc_cmd_clear() {
  tc_idx = -1;
  for (int i = 0; i < tc_cmd_len; i++) tc_cmd[i] = '\0';
}
void tc_cmd_run() {//解析执行命令
  //--------------------------------------
  //01234567890
  //$Second:+1*
  //$Second:-1*
  //--------------------------------------
  if ( tc_cmd[0] != '$' ) return;
  else if (tc_cmd[1] != 'S' ) return;
  else if (tc_cmd[2] != 'e' ) return;
  else if (tc_cmd[3] != 'c' ) return;
  else if (tc_cmd[4] != 'o' ) return;
  else if (tc_cmd[5] != 'n' ) return;
  else if (tc_cmd[6] != 'd' ) return;
  else if (tc_cmd[7] != ':' ) return;
  else if (tc_cmd[10] != '*' ) return;
  //--------------------------------------
  if (tc_cmd[8] == '+' ) secondAdjust(2);
  if (tc_cmd[8] == '-' ) secondAdjust(-1);
  //--------------------------------------
}


char CmdRc[20];
void rc_info_send() {
  sprintf(//
    CmdRc,//
    "$%02X%02X%02X%02X%02X%02X==%d,%d==%d,%d,%d*\0", //
    cmd_rolls, cmd_pitch, cmd_power, cmd_yawss, cmd_5thss, cmd_6thss,
    (int)(wr.sNow * 100), (int)(wl.sNow * 100), //
    (int)Kp, (int)Ki, (int)Kd //
  );
  rcSend(CmdRc, true);
  //lg(CmdRc);lg();
}

//String str;
//str = String("$B2") + cmd_rolls + "," + cmd_pitch + "," + cmd_power + "," + cmd_yawss + "," + cmd_5thss + "," + cmd_6thss + "*\r\n";

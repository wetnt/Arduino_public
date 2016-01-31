
char CmdRc[20];
void rc_info_send() {
  sprintf(//
    CmdRc,//
    "$%02X%02X%02X%02X%02X%02X\tvRL=%d,%d\tPID=%d,%d,%d\tAngle=%d\t*\0", //
    cmd_rolls, cmd_pitch, cmd_power, cmd_yawss, cmd_5thss, cmd_6thss,
    (int)(wr.sNow * 100), (int)(wl.sNow * 100), //
    (int)Kp, (int)Ki, (int)Kd,//
    (int)angleK
  );
  rcSend(CmdRc, true);
  lg(CmdRc);lg();
}
void car_info_log(){  
  //---------------------------------------------------------
  lg("rcCmd = "); lg(cmd_pitch); lg(","); lg(cmd_rolls); lg("  ");
  lg("rcPid = "); lg(PidCtR);    lg(","); lg(PidCtL);    lg("  ");
  lg("spPid = "); lg(rSetpoint); lg(","); lg(lSetpoint); lg("  ");
  lg("CarRL = "); lg(CarR);      lg(","); lg(CarL);      lg("  ");
  lg("Speed = "); lg(wr.sNow);   lg(","); lg(wl.sNow);   lg("  ");
  lg();
  //---------------------------------------------------------
}
//String str;
//str = String("$B2") + cmd_rolls + "," + cmd_pitch + "," + cmd_power + "," + cmd_yawss + "," + cmd_5thss + "," + cmd_6thss + "*\r\n";

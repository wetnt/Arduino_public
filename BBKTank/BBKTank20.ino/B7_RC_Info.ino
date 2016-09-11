char CmdRc[40];
//1、命令的1~6通道值
//2、传感器数据：姿态数据、碰撞数据、距离数据
//3、
void rc_info_send() {
  sprintf(//
    CmdRc,//
    "gets: $%02X%02X%02X%02X%02X%02X\t*\0", //
    cmd_rolls, cmd_pitch, cmd_power, cmd_yawss, cmd_5thss, cmd_6thss
  );
  rcSend(CmdRc, true);
  lg(CmdRc); lg();
}
void car_info_logSSS() {
  //---------------------------------------------------------
  //  lg("rcCmd = "); lg(cmd_pitch); lg(","); lg(cmd_rolls); lg("  ");
  //  lg("rcPid = "); lg(PidCtR);    lg(","); lg(PidCtL);    lg("  ");
  //  lg("spPid = "); lg(rSetpoint); lg(","); lg(lSetpoint); lg("  ");
  //  lg("CarRL = "); lg(CarR);      lg(","); lg(CarL);      lg("  ");
  //  lg("Speed = "); lg(wr.sNow);   lg(","); lg(wl.sNow);   lg("  ");
  //  lg();
  //---------------------------------------------------------
}
//String str;
//str = String("$B2") + cmd_rolls + "," + cmd_pitch + "," + cmd_power + "," + cmd_yawss + "," + cmd_5thss + "," + cmd_6thss + "*\r\n";

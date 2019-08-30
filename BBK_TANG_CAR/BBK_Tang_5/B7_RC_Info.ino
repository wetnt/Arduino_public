char CmdRc[40];
//1、命令的1~6通道值
//2、传感器数据：姿态数据、碰撞数据、距离数据
void rc_info_sendsss() {
  sprintf(//
    CmdRc,//
    "gets: $%02X%02X%02X%02X%02X%02X\t*\0", //
    cmd_rolls, cmd_pitch, cmd_power, cmd_yawss, cmd_5thss, cmd_6thss
  );
  rcSend(CmdRc, true);
  //lg(CmdRc); lg();
}

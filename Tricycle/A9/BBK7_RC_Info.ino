
char CmdRc[20];
void rc_info_send() {
  sprintf(CmdRc, "$B1%02X%02X%02X%02X%02X%02X*\0", cmd_rolls, cmd_pitch, cmd_power, cmd_yawss, cmd_5thss, cmd_6thss);
  rcSend(CmdRc, true);
}

//String str;
//str = String("$B2") + cmd_rolls + "," + cmd_pitch + "," + cmd_power + "," + cmd_yawss + "," + cmd_5thss + "," + cmd_6thss + "*\r\n";

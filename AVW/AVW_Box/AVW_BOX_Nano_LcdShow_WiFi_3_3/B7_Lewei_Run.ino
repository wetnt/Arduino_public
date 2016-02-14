//-------------------------------------------------------------------------
long LeweiTime = millis(), LeweiTimeKey = 10 * 1000;
void Lewei_Loop() {
  //-------------------------------------------------------------
  if ( millis() - LeweiTime < LeweiTimeKey) return;
  LeweiTime = millis();
  //-------------------------------------------------------------
  lgln("Lewei_Loop()");
  Lewei_Report();
  lewei_time_exp();//lewei_time_show();
  //-------------------------------------------------------------
}

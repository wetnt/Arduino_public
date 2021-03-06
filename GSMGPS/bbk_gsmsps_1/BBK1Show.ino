//===============================================================
void GpsLineShow() {
  //--------------------------------------------------------
  lg(gs.d); lg(" "); lg(gs.t); lg(" ");
  lg(gs.w); lg(","); lg(gs.j); lg(","); lg(gs.h); lg(",");
  lg(gs.v); lg(","); lg(gs.x); lg(","); lg(gs.n); lgln("");
  //--------------------------------------------------------
}
//===============================================================
char sDate[32], sTime[12];
void GpsTimeShow(int y, int m, int d, int h, int f, int s) {
  //--------------------------------------------------------
  sprintf(sDate, "%02d-%02d-%02d", y, m, d);
  sprintf(sTime, "%02d:%02d:%02d", h, f, s);
  lg(sDate); lg(" "); lg(sTime);
  //--------------------------------------------------------
}
void GpsTimeShow(time_t t) {
  //--------------------------------------------------------
  sprintf(sDate, "%02d-%02d-%02d", year(t), month(t), day(t));
  sprintf(sTime, "%02d:%02d:%02d", hour(t), minute(t), second(t));
  lg(sDate); lg(" "); lg(sTime);
  //--------------------------------------------------------
}
//===============================================================

void GpsLineShow() {
  //--------------------------------------------------------
  //printDateTime(gt.date, gt.time); lg("    ");
  //GpsTimeShow(g.dy,g.dm,g.dd,g.th,g.tm,g.ts);
  //GpsTimeShow(g.tl);lg(" ");
  //--------------------------------------------------------
  lg(gs.d);lg(" ");lg(gs.t);lg("    ");
  lg(gs.w);lg(",");lg(gs.j);lg(",");lg(gs.h);lg(",");
  lg(gs.v);lg(",");lg(gs.x);lg(",");lg(gs.n);lg("    ");
  //--------------------------------------------------------
  //printFloat(g.w, true, 11, 8); lg(",");
  //printFloat(g.j, true, 12, 8); lg(",");
  //printFloat(g.h, true,  6, 0); lg(",");
  //printFloat(g.v, true,  6, 2); lg("    ");
  //--------------------------------------------------------
  //lg("k="); lg(g.k); lg(",");
  //lg("p="); lg(g.p); lg(",");
  //lg("n="); printInt(g.n, true, 2); lg(",");
  //lg("r="); printInt(g.r, true, 4); lg("    ");
  //--------------------------------------------------------
  lgln("");
  //--------------------------------------------------------
}
char sDate[32], sTime[12];
void GpsTimeShow(int y,int m,int d,int h,int f,int s) {
  //--------------------------------------------------------
  sprintf(sDate,"%02d-%02d-%02d",y,m,d);
  sprintf(sTime,"%02d:%02d:%02d",h,f,s);
  lg(sDate);lg(" ");lg(sTime);
  //--------------------------------------------------------
}
void GpsTimeShow(time_t t) {
  //--------------------------------------------------------
  sprintf(sDate,"%02d-%02d-%02d",year(t),month(t),day(t));
  sprintf(sTime,"%02d:%02d:%02d",hour(t),minute(t),second(t));
  lg(sDate);lg(" ");lg(sTime);
  //--------------------------------------------------------
}

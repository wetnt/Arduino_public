//Date: Sat, 06 Feb 2016 05:53:55 GMT
int la = 0, lb = 0, lc = 0, ld = 0;
void lewei_time_exp() {
  //------------------------------------------
  String t = GetStringAB(wifiBack, "2016 ", "GMT"); 
  lg("t=");lgln(t);
  //------------------------------------------
  la = t[0] - 48; if (la < 0) la = 0;
  lb = t[1] - 48; if (lb < 0) lb = 0;
  lc = t[3] - 48; if (lc < 0) lc = 0;
  ld = t[4] - 48; if (ld < 0) ld = 0;
  //------------------------------------------
  la = la * 10 + lb; la = la + 8;
  if (la >= 24) la = la - 24;
  lb = la % 10; la = la / 10;
  //------------------------------------------
  if (la == 0) la = -1;
  //------------------------------------------
}
void lewei_time_show() {
  Tube4_set(la, lb, lc, ld, 2);
}


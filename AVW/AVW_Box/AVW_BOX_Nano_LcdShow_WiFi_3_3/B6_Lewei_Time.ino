//Date: Sat, 06 Feb 2016 05:53:55 GMT
int la = 0, lb = 0, lc = 0, ld = 0;
void lewei_time_init() {
  HttpBufferSet('+', '-');
}
void lewei_time_exp() {
  //------------------------------------------
  HttpBufferShow(); lg();
  String t = GetStringAB(bufferBack, "2016", "G");
  //------------------------------------------
  la = t[5] - 48; lb = t[6] - 48;
  lc = t[8] - 48; ld = t[9] - 48;
  //------------------------------------------
  //lg(la); lg(lb); lg(':'); lg(lc); lg(ld); lg();
  //------------------------------------------
  if (la < 0)la = 0;
  if (lb < 0)lb = 0;
  if (lc < 0)lc = 0;
  if (ld < 0)ld = 0;
  //------------------------------------------
  la = la * 10 + lb; la = la + 8;
  if (la >= 24) la = la - 24;
  lb = la % 10; la = la / 10;
  //------------------------------------------
  //lg(la); lg(lb); lg(':'); lg(lc); lg(ld); lg();
  //------------------------------------------
}
String Get_lewei_time() {
  String s = "";
  s.concat(la);  s.concat(lb);
  s.concat(":");
  s.concat(lc); s.concat(ld);
  return s;
}
void lewei_time_show() {
  //LCD1602_Clear();
  //LCD1602_Show(0, 0, Get_lewei_time());
}


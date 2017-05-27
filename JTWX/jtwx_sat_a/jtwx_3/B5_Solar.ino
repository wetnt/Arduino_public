B_analogRead s1, s2, s3, s4;
void Solar_Setup() {
  s1.init(A1, 5);
  s2.init(A2, 5);
  s3.init(A3, 5);//太阳能电池板
  s4.init(A4, 5);
}
void Solar_loop() {
  s1.loopRun();
  s2.loopRun();
  s3.loopRun();
  s4.loopRun();
}
void Solar_log() {
  lg(s1.vSum); lg(','); lg(s2.vSum); lg(','); lg(s3.vSum); lg(','); lg(s4.vSum); lg(','); lg();
}
void Solar_Lcd() {
  String s = "";
  s.concat(s1.vx);  s.concat(' ');
  s.concat(s2.vx);  s.concat(' ');
  s.concat(s3.vx);  s.concat(' ');
  //LCD1602_Show(0, 0, s);
}

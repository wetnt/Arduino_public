unsigned long RunTime = millis();
void RunTimeLoop() {
  RunTime = millis();
}
String RunTimeShow() {
  int t = RunTime / 1000;
  int h = t / 3600;
  int m = t / 60 - h * 60;
  int s = t - h * 3600 - m * 60;
  String f = ""; f.concat(h); f.concat(":"); f.concat(m); f.concat(":"); f.concat(s);
  return f;
}


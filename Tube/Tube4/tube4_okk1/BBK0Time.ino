//-------------------------------------------------------------
int time_hourss = 0;
int time_minute = 0;
int time_second = 0;
char time_time[10];
//-------------------------------------------------------------
void Time_Setup(int h, int m, int s) {
  Time_SetTime(h, m, s);
}
unsigned long time_last = millis();
void Time_Loop() {
  if (millis() - time_last > 1000) {
    time_AddSecond(); time_last = millis();
  }
}
void Time_SetTime(int h, int m, int s) {
  time_hourss = h; time_minute = m; time_second = s;
}
void Time_SetTimeAdd(int h, int m, int s) {
  time_hourss += h; time_minute = +m; time_second += s;
  time_AddSecond();
}
void Time_Show() {
  snprintf(time_time, sizeof(time_time), "%02d:%02d:%02d", time_hourss, time_minute, time_second);
  Serial.println(time_time);
}
void time_AddSecond() {
  time_second++;
  if (time_second >= 60) {
    time_second = 0; time_minute++;
  }
  if (time_minute >= 60) {
    time_minute = 0; time_hourss++;
  }
  if (time_hourss >= 24) {
    time_hourss = 0;
  }
}
int get_hourss() {
  return time_hourss;
}
int get_minute() {
  return time_minute;
}
int get_second() {
  return time_second;
}

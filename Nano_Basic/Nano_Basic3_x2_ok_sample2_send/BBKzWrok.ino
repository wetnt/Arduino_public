//===================================================================
void Timer_work() {
  //-------------------------------------
  int timerEvent1 = timerLoop.every(timeChange, getangle); //每timeChange毫秒执行回调函数getangle
  int timerEvent2 = timerLoop.every(100, MPU6050_work) ; //每50毫秒执行回调函数printout，串口输出
  int timerEvent20 = timerLoop.every(1000, MPU6050_clear);
  int timerEvent3 = timerLoop.every(1000, GPS_work) ; //GPS状态输出
  int timerEvent4 = timerLoop.every(1000, APC220_send) ; //APC串口发送
  //-------------------------------------
}
//===================================================================
int angleAbs = 0, angleMax = 0, angleLast = 0;
void MPU6050_clear() {
  //lg(angleAbs);   lgln("");
  angleMax = angleAbs, angleAbs = 0, angleLast = 0;
}
void MPU6050_work() {
  //-------------------------------------
  //lg(angleAx); lg(',');
  //lg(angle1);  lg(',');
  //lg(angle2);  lg(',');
  //lg(angle);   lgln("");
  //Serial.print(gx/131.00);Serial.print(',');
  //Serial.println(Output);
  //-------------------------------------
  angleAbs += abs(angle - angleLast);
  angleLast = angle;
  //-------------------------------------
}
//===================================================================
void GPS_work() {
  GpsValueSet();
  GpsStringSet();
  GpsToHome();
  //GpsLineShow();
}
//===================================================================
void APC220_send() {
  //------------------------------------------------------------------------------------------------
  String x = String(gs.d) + String(",") + String(gs.t) + String(",") +
             String(gs.w) + String(",") + String(gs.j) + String(",") + String(gs.h) + String(",") +
             String(gs.v) + String(",") + String(gs.x) + String(",") + String(gs.n) + String(",") +
             String(angleMax) + String(",") + String(homeL) + String(";");
   //x.replace(" ","");
   x.remove(' ');
  //------------------------------------------------------------------------------------------------
  apcTR.println(x);
  lgln(x);
  //------------------------------------------------------------------------------------------------
}
//===================================================================

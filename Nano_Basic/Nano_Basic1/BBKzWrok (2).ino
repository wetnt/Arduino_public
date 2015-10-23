//===================================================================
void Timer_work() {
  //-------------------------------------
  int timerEvent1 = timerLoop.every(timeChange, getangle); //每timeChange毫秒执行回调函数getangle
  int timerEvent2 = timerLoop.every(100, MPU6050_show) ; //每50毫秒执行回调函数printout，串口输出
  int timerEvent3 = timerLoop.every(1000, GPS_work) ; //GPS状态输出
  int timerEvent4 = timerLoop.every(1000, WorkRunA) ; //状态呼吸灯
  //-------------------------------------
}
//===================================================================
void GPS_work() {
  GpsValueSet();
  GpsStringSet();
  GpsLineShow();  
}
//===================================================================
bool LightKey = false;
void WorkRunA() {
  LightKey = !LightKey;
  if(LightKey){
    digitalWrite(13, HIGH);  lgs.println("HIGH");  //delay(1000);
  }else{
    digitalWrite(13, LOW);   lgs.println("LOW");   //delay(1000);
  }
}
//===================================================================

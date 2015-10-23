//-------------------------------------------------------------
int time_daywek = 1;
int time_yearss = 2014,time_months = 1,time_datess = 1;
int time_hourss = 0,time_minute = 0,time_second = 0;
char time_date[20], time_time[20];
//-------------------------------------------------------------
long TimeTime = millis(), TimeTimeKey = 1000;
//-------------------------------------------------------------
void Time_Setup(){
  Serial.print("Time_Setup......OK!");
}
void Time_Loop(bool showkey){
  //---------------------------------------
  if( millis() - TimeTime < TimeTimeKey) return; 
  TimeTime = millis();
  //---------------------------------------
  time_AddSecond();
  Tube_SetTime();  
  if(showkey) Time_Show();
  //---------------------------------------
}
void Time_SetDate(int y,int m,int d,int w){
  time_yearss = y;
  time_months = m;
  time_datess = d;
  time_daywek = w;
}
void Time_SetTime(int h,int m,int s){
  time_hourss = h;
  time_minute = m;
  time_second = s;
}
void Time_Show()
{
  //-------------------------------------------------------------
  //snprintf(time_date, 22, "Date: %4d-%02d-%02d",  time_yearss,time_months,time_datess);
  snprintf(time_time, 22, "Time: %02d:%02d:%02d", time_hourss,time_minute,time_second);
  //Serial.println(time_date);
  Serial.println(time_time);
  //-------------------------------------------------------------
}
//-------------------------------------------------------------
void time_AddSecond()
{
  //-------------------------------------------------------------------
  time_second++;
  //-------------------------------------------------------------------
  if(time_second==60){
    time_second=0;
    time_minute++;
    if(time_minute==60){
      time_minute=0;
      time_hourss++;
      if(time_hourss==24){
        time_hourss=0;
      }
    }
  }
  //-------------------------------------------------------------------
}

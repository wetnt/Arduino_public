//-------------------------------------------------------------
int tweek = 1;
int tyear = 1,tmont = 1,tdays = 1;
int thour = 10,tmint = 10,tsecd = 10;
//char t_date[20], t_time[20];
//-------------------------------------------------------------
long TimeTime = millis(), TimeTimeKey = 1000;
//-------------------------------------------------------------
void Time_Setup(){
  Serial.println("Time_Setup......OK!");
}
void Time_Loop(bool showkey){
  //---------------------------------------
  if( millis() - TimeTime < TimeTimeKey) return; 
  TimeTime = millis();
  //---------------------------------------
  t_AddSecond();
  Tube_SetTime(thour,tmint,tsecd);  
  if(showkey) Time_Show();
  //---------------------------------------
}
void Time_SetDate(int y,int m,int d,int w){
  tyear = y;
  tmont = m;
  tdays = d;
  tweek = w;
}
void Time_SetTime(int h,int m,int s){
  thour = h;
  tmint = m;
  tsecd = s;
}
void Time_Show()
{
  //-------------------------------------------------------------
  //snprintf(t_date, 22, "Date: %4d-%02d-%02d",  tyear,tmont,tdays);
  //snprintf(t_time, 22, "Time: %02d:%02d:%02d", thour,tmint,tsecd);
  //Serial.println(t_date);
  //Serial.println(t_time);
  //-------------------------------------------------------------
}
//-------------------------------------------------------------
void t_AddSecond()
{
  //-------------------------------------------------------------------
  tsecd++;
  //-------------------------------------------------------------------
  if(tsecd==60){
    tsecd=0;
    tmint++;
    if(tmint==60){
      tmint=0;
      thour++;
      if(thour==24){
        thour=0;
      }
    }
  }
  //-------------------------------------------------------------------
}

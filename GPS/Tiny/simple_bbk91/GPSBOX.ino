//-------------------------------------------------------------------------
unsigned long ShowTime = millis(), ShowTimeKey = 800;//1s
void GPSloop() 
{
  //-------------------------------------------------------------------------
  if( millis() - ShowTime < ShowTimeKey) return; 
  //-------------------------------------------------------------------------
  ShowTime = millis();
  //-------------------------------------------------------------------------
  GpsValueRun();
  GpsStringRun();
  //-------------------------------------------------------------------------
  GpsLCDShow();
  //-------------------------------------------------------------------------
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
typedef struct  { 
  //----------------------------------------------------------------
  int YY,MD,DD,HT,MT,ST;//year,month,day,hour,min,second
  float WW,JJ,HH,VV,FX;//lat,long,high,speed,fangxiang
  //----------------------------------------------------------------
  int SN,SR;//sat_number,sat_hdop
  bool KK;//GPS_Location_flag
  char KT;//GPS_Location_type
  //----------------------------------------------------------------
} 
GpsInfo;
//------------------------------------------------------------------
typedef struct  { 
  //----------------------------------------------------------------
  char sDate[12],tDate[32],sTime[12];//YMDHMS
  char sLats[12],sLons[12],sHigh[8],sSped[8],sFans[8];//WJHVF
  char cLock[4],cType[4],sGpsn[4],sRads[8],sSeal[8];//KK;KT;SN;SR;HZ;
  //----------------------------------------------------------------
} 
GpsInfoString;
//-------------------------------------------------------------------------
time_t loctime = 0,utctime = 0;
GpsInfo gi;
GpsInfoString gs;
//-------------------------------------------------------------------------
void GpsValueRun(){
  //-------------------------------------------------------------------------
  setTime( 
  gps.time.hour(),gps.time.minute(),gps.time.second(),
  gps.date.day(),gps.date.month(),gps.date.year()
    ); 
  utctime = now();  
  loctime = utctime + 8 * 3600;
  //-------------------------------------------------------------------------
  gi.YY = year(loctime);
  gi.MD = month(loctime);
  gi.DD = day(loctime);
  gi.HT = hour(loctime);
  gi.MT = minute(loctime);
  gi.ST = second(loctime);
  //-------------------------------------------------------------------------
  gi.KK = gps.fixhave;
  gi.KT = gps.fixtype-46;
  gi.WW = gps.location.lat();
  gi.JJ = gps.location.lng(); 
  //-------------------------------------------------------------------------
  gi.HH = gps.altitude.meters();
  gi.FX = gps.course.deg();
  gi.VV = gps.speed.kmph();
  gi.SN = gps.satellites.value();
  gi.SR = gps.hdop.value();
  //-------------------------------------------------------------------------
}
void GpsStringRun(){
  //-------------------------------------------------------------------------
  dtostrf(gi.KK,1,0,gs.cLock);
  dtostrf(gi.KT,1,0,gs.cType);
  //-------------------------------------------------------------------------
  //sprintf(gs.sDate,"%02d/%02d/%02d",gi.YY,gi.MD,gi.DD);  
  sprintf(gs.sDate,"%02d/%02d",gi.MD,gi.DD);
  sprintf(gs.sTime,"%02d:%02d:%02d",gi.HT,gi.MT,gi.ST);
  sprintf(gs.tDate,"%02d/%02d/%02d %02d:%02d:%02d",gi.YY,gi.MD,gi.DD,gi.HT,gi.MT,gi.ST);
  //-------------------------------------------------------------------------
  dtostrf(gi.WW,3,6,gs.sLats);
  dtostrf(gi.JJ,3,6,gs.sLons);
  dtostrf(gi.HH,3,1,gs.sHigh);
  dtostrf(gi.VV,3,1,gs.sSped);
  dtostrf(gi.FX,3,1,gs.sFans);
  dtostrf(gi.SN,2,0,gs.sGpsn);
  dtostrf(gi.SR,3,0,gs.sRads);
  //-------------------------------------------------------------------------
}

static bool feedgps()
{
  //-------------------------------------------------------------------------
  while (GpsSerial.available())
  {
    if (gps.encode(GpsSerial.read()))
      return true;
  }
  return false;
  //-------------------------------------------------------------------------
}

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
int YY,MD,DD,HT,MT,ST;//year,month,day,hour,min,second
float WW,JJ,HH,VV,FX;//lat,long,high,speed,fangxiang
int SN,SR;//sat_number,sat_hdop
bool KK;//GPS_Location_flag
char KT;//GPS_Location_type
char sDate[12],tDate[32],sTime[12];//YMDHMS
char sLats[12],sLons[12],sHigh[8],sSped[8],sFans[8];//WJHVF
char cLock[2],cType[2],sGpsn[4],sRads[8],sSeal[8];//KK;KT;SN;SR;HZ;
//-------------------------------------------------------------------------
void GpsValueRun(){
  //-------------------------------------------------------------------------
  KK = gps.fixhave;
  //-------------------------------------------------------------------------
  YY = gps.date.year();
  MD = gps.date.month();
  DD = gps.date.day();
  HT = gps.time.hour();
  MT = gps.time.minute();
  ST = gps.time.second();
  HT = HT + 8;
  if( HT > 23 ){
    HT = HT - 24;
    DD = DD + 1;
  }
  //-------------------------------------------------------------------------
  WW = gps.location.lat();
  JJ = gps.location.lng(); 
  //-------------------------------------------------------------------------
  HH = gps.altitude.meters();
  FX = gps.course.deg();
  VV = gps.speed.kmph();
  SN = gps.satellites.value();
  SR = gps.hdop.value();
  //-------------------------------------------------------------------------
  dtostrf(KK,1,0,cLock);
  dtostrf(KT,1,0,cType);
  //-------------------------------------------------------------------------
  //sDate = String( String(MD,DEC) + "/" + String(DD,DEC) );
  //sTime = String( String(HT,DEC) + ":" + String(MT,DEC) + ":" + String(ST,DEC) );
  //tDate = String( String(YY,DEC) + "/" + sDate + " " + sTime );
  sprintf(sDate,"%02d/%02d/%02d",YY,MD,DD);  
  sprintf(sDate,"%02d/%02d",MD,DD);
  sprintf(sTime,"%02d:%02d:%02d",HT,MT,ST);
  sprintf(tDate,"%02d/%02d/%02d %02d:%02d:%02d",YY,MD,DD,HT,MT,ST);
  //-------------------------------------------------------------------------
  dtostrf(WW,3,6,sLats);
  dtostrf(JJ,3,6,sLons);
  dtostrf(HH,4,0,sHigh);
  dtostrf(VV,3,1,sSped);
  dtostrf(FX,3,1,sFans);
  dtostrf(SN,2,0,sGpsn);
  dtostrf(SR,3,0,sRads);
  //-------------------------------------------------------------------------
}
void GpsTimeSet(){  
  //-------------------------------------------------------------------------
  setTime(HT,MT,ST,DD,MD,YY);
  mytime = now(); 
  //-------------------------------------------------------------------------
}

static bool feedgps()
{
  while (GpsSerial.available())
  {
    if (gps.encode(GpsSerial.read()))
      return true;
  }
  return false;
}

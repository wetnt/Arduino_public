//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
int YY,MD,DD,HT,MT,ST;
float WW,JJ,HH,VV,FX;
int SN,SR;
bool KK;
char KT;
String sDate,tDate,sTime;//YMDHMS
String sLats,sLons,sHigh,sSped,sFans;//WJHVF
String cLock,cType,sGpsn,sRads,sSeal;//KK;KT;SN;SR;HZ;
//-------------------------------------------------------------------------
char str[32];
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
  dtostrf(KK,1,0,str);   cLock = str;
  dtostrf(KT,2,0,str);   cType = str;
  //-------------------------------------------------------------------------
  sDate = String( String(MD,DEC) + "/" + String(DD,DEC) );
  sTime = String( String(HT,DEC) + ":" + String(MT,DEC) + ":" + String(ST,DEC) );
  tDate = String( String(YY,DEC) + "/" + sDate + " " + sTime );
  //-------------------------------------------------------------------------
  dtostrf(WW,3,6,str);  sLats = str;
  dtostrf(JJ,3,6,str);  sLons = str;
  dtostrf(HH,4,0,str);  sHigh = str;
  dtostrf(VV,3,1,str);  sSped = str;
  dtostrf(FX,3,1,str);  sFans = str;
  dtostrf(SN,2,0,str);  sGpsn = str;
  dtostrf(SR,3,0,str);  sRads = str;
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

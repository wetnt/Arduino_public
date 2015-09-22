//-------------------------------------------------------------------------
void GpsSetValue()
{
  //-------------------------------------------------------------------------
  GpsValueSet(gt,8);
  GpsStringSet();
  //-------------------------------------------------------------------------
}
//=========================================================================
//#########################################################################
//=========================================================================
typedef struct GpsInfo
{
  //----------------------------------------------------------------
  int tz = 8;//time_zone
  time_t tl = 0, tu = 0;//local_time,utc_time
  //----------------------------------------------------------------
  int dy, dm, dd, th, tm, ts; //year,month,day,hour,min,second
  float w, j, h, v, x; //lat,long,high,speed,fangxiang
  //----------------------------------------------------------------
  int n, r; //sat_number,sat_hdop
  bool k;//GPS_Location_flag
  char p;//GPS_Location_type
  //----------------------------------------------------------------
};
typedef struct GpsInfoString
{
  //----------------------------------------------------------------
  char d[32], t[12]; //YMDHMS
  char w[12], j[12],  h[8], v[8], x[8]; //WJHVF
  char k[4],  p[4],   n[4], r[8], z[8]; //KK;KT;SN;SR;HZ;
  //----------------------------------------------------------------
};
//=========================================================================
//#########################################################################
//=========================================================================
GpsInfo g;
GpsInfoString gs;
//=========================================================================
//#########################################################################
//=========================================================================
void GpsValueSet(TinyGPSPlus gps,int zone) {
  //-------------------------------------------------------------------------
  g.tz = zone;
  //-------------------------------------------------------------------------
  setTime(
    gps.time.hour(), gps.time.minute(), gps.time.second(),
    gps.date.day(), gps.date.month(), gps.date.year()
  );
  g.tu = now();
  setTime(
    gps.time.hour() + g.tz, gps.time.minute(), gps.time.second(),
    gps.date.day(), gps.date.month(), gps.date.year()
  );
  setTime(10,30,55,2,9,2015);
  g.tl = now();
  //-------------------------------------------------------------------------
  g.dy = year(g.tl); g.dm = month(g.tl); g.dd = day(g.tl);
  g.th = hour(g.tl); g.tm = minute(g.tl); g.ts = second(g.tl);
  //-------------------------------------------------------------------------
  g.k = true;//gps.gpsDataGood;//gps.sentencesWithFix()==2;
  g.p = 'l';//gps.sentenceHasFix - 46;
  //-------------------------------------------------------------------------
  g.w = 39.977;//gps.location.lat(); 
  g.j = 116.332;//gps.location.lng();
  g.h = 116.332;//gps.altitude.meters();
  g.x = 116.332;//gps.course.deg(); 
  g.v = 116.332;//gps.speed.kmph();
  //-------------------------------------------------------------------------
  g.n = 5;//gps.satellites.value(); 
  g.r = 100;//gps.hdop.value();
  //-------------------------------------------------------------------------
}
void GpsStringSet() {
  //-------------------------------------------------------------------------
  dtostrf(g.k, 1, 0, gs.k);  dtostrf(g.p, 1, 0, gs.p);
  //-------------------------------------------------------------------------
  sprintf(gs.d, "%02d-%02d-%02d", g.dy, g.dm, g.dd);
  sprintf(gs.t, "%02d:%02d:%02d", g.th, g.tm, g.ts);
  //-------------------------------------------------------------------------
  dtostrf(g.w, 3, 6, gs.w);  dtostrf(g.j, 3, 6, gs.j);  dtostrf(g.h, 3, 1, gs.h);
  dtostrf(g.v, 3, 1, gs.v);  dtostrf(g.x, 3, 1, gs.x);  dtostrf(g.n, 2, 0, gs.n);
  dtostrf(g.r, 3, 0, gs.r);
  //-------------------------------------------------------------------------
}
//=========================================================================
//#########################################################################
//=========================================================================


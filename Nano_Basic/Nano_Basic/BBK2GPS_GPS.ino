//=========================================================================
void GpsSetValue()
{
  //-------------------------------------------------------------------------
  GpsValueSet(gt, 8);
  GpsStringSet();
  //-------------------------------------------------------------------------
}
//=========================================================================
//#########################################################################
//#########################################################################
//=========================================================================
typedef struct GpsInfo
{
  //----------------------------------------------------------------
  int tz = 8;//time_zone
  time_t tl = 0, tu = 0;//local_time,utc_time
  //----------------------------------------------------------------
  int dy, dm, dd, th, tm, ts; //year,month,day,hour,min,second
  double w, j, h, v, x; //lat,long,high,speed,fangxiang
  //----------------------------------------------------------------
  int n, r; //sat_number,sat_hdop
  bool k;//GPS_Location_flag
  char p;//GPS_Location_type
  //----------------------------------------------------------------
};
typedef struct GpsInfoString
{
  //----------------------------------------------------------------
  char tl[15], tu[15]; //time_utc/local
  char d[32], t[12]; //YMDHMS
  char w[14], j[14], h[8], v[8], x[8]; //WJHVF
  char k[8],  p[8],  n[8], r[8], z[8]; //KK;KT;SN;SR;HZ;
  //----------------------------------------------------------------
};
//=========================================================================
//#########################################################################
//#########################################################################
//=========================================================================
GpsInfo g;
GpsInfoString gs;
//=========================================================================
//#########################################################################
//=========================================================================
static void GpsValueSet(TinyGPSPlus gps, int zone) {
  //-------------------------------------------------------------------------
  g.tz = zone;
  //-------------------------------------------------------------------------
  setTime(
    gps.time.hour(), gps.time.minute(), gps.time.second(),
    gps.date.day(), gps.date.month(), gps.date.year()
  );
  //setTime(10, 30, 38, 1, 10, 2015);
  g.tu = now();
  setTime(
    gps.time.hour() + g.tz, gps.time.minute(), gps.time.second(),
    gps.date.day(), gps.date.month(), gps.date.year()
  );
  //setTime(10, 30, 38, 1, 10, 2015);
  g.tl = now();
  //-------------------------------------------------------------------------
  g.dy = year(); g.dm = month(); g.dd = day();
  g.th = hour(); g.tm = minute(); g.ts = second();
  //-------------------------------------------------------------------------
  g.k = true;//gps.gpsDataGood;//gps.sentencesWithFix()==2;
  g.p = 'l';//gps.sentenceHasFix - 46;
  //-------------------------------------------------------------------------
  g.n = gps.satellites.value();
  g.r = gps.hdop.value();
  g.w = gps.location.lat();
  g.j = gps.location.lng();
  g.h = gps.altitude.meters();
  g.x = gps.course.deg();
  g.v = gps.speed.kmph();
  //-------------------------------------------------------------------------
  if (1) {
    g.w = 39.977123456; g.j = 116.332; g.h = 50;
    g.x = 180; g.v = 80; g.n = 4; g.r = 100;
  }
  //-------------------------------------------------------------------------
}
static void GpsStringSet() {
  //-------------------------------------------------------------------------
  dtostrf(g.k, 1, 0, gs.k);  dtostrf(g.p, 1, 0, gs.p);
  //-------------------------------------------------------------------------
  sprintf(gs.d, "%02d-%02d-%02d", g.dy, g.dm, g.dd);
  sprintf(gs.t, "%02d:%02d:%02d", g.th, g.tm, g.ts);
  //-------------------------------------------------------------------------
  dtostrf((uint32_t)g.tu, 10, 0, gs.tu);
  dtostrf((uint32_t)g.tl, 10, 0, gs.tl);
  //-------------------------------------------------------------------------
  dtostrf(g.w, 3, 7, gs.w);  dtostrf(g.j, 3, 7, gs.j);
  dtostrf(g.h, 4, 2, gs.h);  dtostrf(g.v, 3, 2, gs.v);
  dtostrf(g.x, 3, 2, gs.x);  dtostrf(g.n, 2, 2, gs.n);
  dtostrf(g.r, 3, 2, gs.r);
  //-------------------------------------------------------------------------
}
//=========================================================================
//#########################################################################
//=========================================================================
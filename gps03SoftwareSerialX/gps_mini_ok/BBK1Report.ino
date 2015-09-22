//----------------------------------------------------------------
String strVal = String("");
//----------------------------------------------------------------
void strBuild(){
  double w = gi.WW * 1000000;
  double j = gi.JJ * 1000000;
  double h = gi.HH * 100;
  double v = gi.VV * 100;
  //----------------------------------------------------------------
  strVal = String(gi.KK) + strRv;

  strVal += String(gi.YY) + strRv;
  strVal += String(gi.MD) + strRv;
  strVal += String(gi.DD) + strRv;
  strVal += String(gi.HT) + strRv;
  strVal += String(gi.MT) + strRv;
  strVal += String(gi.ST) + strRv;    

  strVal += String(w) + strRv;
  strVal += String(j) + strRv;
  strVal += String(h) + strRv;
  strVal += String(v) + strRv;

  strVal += String(gi.SN) + strRv;
  strVal += String(gi.SR) + strRv;
  
  strVal += String(DhtT) + strRv;
  strVal += String(DhtH) + strRv;
  //----------------------------------------------------------------
  strAll = "";
  strAll += strLoc + strRn;
  strAll += strDev + strRn;
  strAll += strIds + strRn;
  strAll += strVal + strRn;
  //----------------------------------------------------------------
  strAll += strRl;
  //----------------------------------------------------------------
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
bool ReportKey = false;
unsigned long StrTime = millis(), StrTimeKey = 5000;//5s
void GpsCheck(){  
  //----------------------------------------------------------------
  int k = gi.ST%10;
  if(k!=0)return;
  //----------------------------------------------------------------
  if( millis() - StrTime < StrTimeKey) return; 
  StrTime = millis();
  //----------------------------------------------------------------
  ReportKey = true;
  //----------------------------------------------------------------
}
void GpsReport(){
  //-------------------------------------------------------------------------
  if(!ReportKey)return;
  ReportKey = false;
  //-------------------------------------------------------------------------  
  strBuild();
  Serial.println(strAll);
  //-------------------------------------------------------------------------
}
//-------------------------------------------------------------------------

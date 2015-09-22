//-------------------------------------------------------------------------
//http://www.arduino.cc/en/Reference/String
//-------------------------------------------------------------------------
String strRl = String(';');
String strRn = String(':');
String strRv = String(',');
  //--------------------------------------
String strAll = String("");
String strLoc = String("JML");
String strDev = String("GPS");
String strIds = String("MAIN");
String strVal = String("");
//-------------------------------------------------------------------------
void strBuild(){
  //----------------------------------------------------------------
  strVal = String(gi.KK) + strRv;

  strVal += String(gi.YY) + strRv;
  strVal += String(gi.MD) + strRv;
  strVal += String(gi.DD) + strRv;
  strVal += String(gi.HT) + strRv;
  strVal += String(gi.MT) + strRv;
  strVal += String(gi.ST) + strRv;    

  strVal += String(gi.WW,DEC) + strRv;
  strVal += String(gi.JJ,DEC) + strRv;
  strVal += String(gi.HH) + strRv;
  strVal += String(gi.VV) + strRv;

  strVal += String(gi.SN) + strRv;
  strVal += String(gi.SR) + strRv;
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
unsigned long StrTime = millis(), StrTimeKey = 8000;//5s
void StrReport(){  
  //----------------------------------------------------------------
  int k = gi.ST%10;
  if(k!=0)return;
  //-------------------------------------------------------------------------
  if( millis() - StrTime < StrTimeKey) return; 
  StrTime = millis();
  //----------------------------------------------------------------
  strBuild();
  Serial.println(strAll);
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------




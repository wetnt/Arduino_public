//-------------------------------------------------------------------------
String netLink_bbkgps = "AT+CIPSTART=\"TCP\",\"www.bbkgps.com\",80";
String cmdHttp_bbkgps = "GET /t.php HTTP/1.1 \r\nHost: www.bbkgps.com \r\nUser-Agent: abc \r\nConnection: close \r\n\r\n";
//-------------------------------------------------------------------------
void NetLink_bbkgps_time() {
  HttpGetPost(netLink_bbkgps, cmdHttp_bbkgps, 5);
  smartDelay(10000);
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
String sDate, sTime, sNows, sPm25, sDays, sSkys, sTemp, sWind;
void NetExp_bbkgps_time() {
    //if (DataIndexOf(bufferBack, "Date:")) { bufferBack = ""; }
    //if (DataIndexOf(bufferBack, ";")) { sDate = bufferBack; bufferBack = ""; }
}
void NetExp_bbkgps_show() {
  lgs.println("----------------------");
  //lgs.println(bufferBack);
  //lgs.println(sDate);  
  lgs.println(GetStringAB(bufferBack, "Time=", ";"));
  lgs.println("----------------------");

  
  //  lgs.println(GetStringAB(sNows, "Nows=", ";"));
  //  lgs.println(GetStringAB(sPm25, "pm25=", ";"));
  //  lgs.println(GetStringAB(sSkys, "skys=", ";"));
  //  lgs.println(GetStringAB(sTemp, "temp=", ";"));
  //  lgs.println(GetStringAB(sWind, "wind=", ";"));
  //lgs.println(bufferBack);
}
//-------------------------------------------------------------------------

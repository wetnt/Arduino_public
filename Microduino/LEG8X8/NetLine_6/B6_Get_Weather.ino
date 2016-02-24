//$
//BMP1:66FFFFFF7E3C18000105;
//BMP2:00247E7E3C1800000205;
//BMP3:66FFFFFF7E3C18000305;
//BMP4:00247E7E3C1800000105;
//BMP5:66FFFFFF7E3C18000205;
//STRM:I LOVE YOU,1314,MaYuan!My Love!;
//STRC:01;
//*
void http_weather_init() {
  HttpBufferSet('$', '*');
}
void WeatherHttpGet() {
  HttpGetPost(
    F("AT+CIPSTART=\"TCP\",\"www.bbkgps.com\",80"),
    F("GET http://www.bbkgps.com/w.php HTTP/1.1\r\nHost: www.bbkgps.com\r\nConnection: keep-alive\r\nCache-Control: max-age=0\r\nAccept: text/html;\r\nUser-Agent: Mozilla/5.0\r\n"),
    3);
}
String ax1, ax2, ax3, ax4, ax5, b1, b2;
void WeatherHttpExp() {
  //------------------------------------------
  HttpBufferShow(); lg();
  lg();
  ax1 = GetStringAB(bufferBack, "BMP1:", ";"); lg("ax1="); lg(ax1); lg();
  ax2 = GetStringAB(bufferBack, "BMP2:", ";"); lg("ax2="); lg(ax2); lg();
  ax3 = GetStringAB(bufferBack, "BMP3:", ";"); lg("ax3="); lg(ax3); lg();
  ax4 = GetStringAB(bufferBack, "BMP4:", ";"); lg("ax4="); lg(ax4); lg();
  ax5 = GetStringAB(bufferBack, "BMP5:", ";"); lg("ax5="); lg(ax5); lg();
  b1 = GetStringAB(bufferBack, "STRM:", ";"); lg("b1="); lg(b1); lg();
  b2 = GetStringAB(bufferBack, "STRC:", ";"); lg("b2="); lg(b2); lg();
  //--------------------------------------------
  for (int i = 0; i < 10; i++) {
    bmp1[i] = getV(ax1[i * 2], ax1[i * 2 + 1]);
    bmp2[i] = getV(ax2[i * 2], ax2[i * 2 + 1]);
    bmp3[i] = getV(ax3[i * 2], ax3[i * 2 + 1]);
    bmp4[i] = getV(ax4[i * 2], ax4[i * 2 + 1]);
    bmp5[i] = getV(ax5[i * 2], ax5[i * 2 + 1]);
  }
  //--------------------------------------------
  str0 = b1;//"I love You,MaYuan!";
  colorKey = getV(b2[0], b2[1]);
  if (colorKey <= 0 || colorKey > 3) colorKey = 1;
  //--------------------------------------------
}

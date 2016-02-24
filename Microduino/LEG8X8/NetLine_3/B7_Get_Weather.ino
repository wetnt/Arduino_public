//$
//BMP1:66FFFFFF7E3C1800;
//BMP2:0030783C3C783000;
//STR:ASDFASDFSAD;
//*
void http_weather_init() {
  HttpBufferSet('$', '*');
}
void WeatherHttpExp() {
  //------------------------------------------
  //HttpBufferShow();lg();
  String a = GetStringAB(bufferBack, "BMP1:", ";");lg("a=");lg(a);lg();
  String b = GetStringAB(bufferBack, "BMP2:", ";");lg("b=");lg(b);lg();
  String c = GetStringAB(bufferBack, "STR:", ";");lg("c=");lg(c);lg();
  //--------------------------------------------
  BMP_Time_Key = 1000; BMP_Color_Key = 1; STR_Color_Key = 2;
  for(int i=0;i<8;i++) {
    rgb8x8_bmp1[i] = getV(a[i*2],a[i*2+1]);
    rgb8x8_bmp2[i] = getV(b[i*2],b[i*2+1]);
  }
  //--------------------------------------------
  rgb_string = c;//"I love You,MaYuan!";
  //--------------------------------------------
}

//$BMP1:FF10FF91D5B9D59301;BMP2:007C00FE2044FE0103;BMP3:FF10FF91D5B9D59301;BMP4:007C00FE2044FE0103;BMP5:FF10FF91D5B9D59301;BMP6:FF10FF91D5B9D59301;STRM:7.22(7)11:58 rain V1 30/33c <3w pm96 TMR cloud 32c <3w;STRC:;*
char bmp1[10] = {0x00, 0x24, 0x7E, 0x7E, 0x3C, 0x18, 0x00, 0x00, 1, 5};
char bmp2[10] = {0x00, 0x66, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C, 0x18, 1, 5};
char bmp3[10] = {0x00, 0x24, 0x7E, 0x7E, 0x3C, 0x18, 0x00, 0x00, 2, 5};
char bmp4[10] = {0x00, 0x66, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C, 0x18, 2, 5};
char bmp5[10] = {0x00, 0x66, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C, 0x18, 1, 5};
char bmp6[10] = {0x00, 0x66, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C, 0x18, 1, 5};

String str0 = "I love you 1314,MaYuan!";
String str1 = "I love you 1314,MaYuan!";
String wthr = "I love you 1314,MaYuan!";
static const String strA[] = {"BMP0", "BMP1:", "BMP2:", "BMP3:", "BMP4:", "BMP5:", "BMP6:"};
void WeatherHttpExp(String bufferBack) {
  //------------------------------------------
  //HttpBufferShow(); lg();
  lg();
  //--------------------------------------------
  String a = "";
  for (int j = 1; j <= 6; j++) {
    a = GetStringAB(bufferBack, strA[j], ";");
    lg("a"); lg(j); lg("="); lg(a); lg();
    for (int i = 0; i < 10; i++) {
      if (j == 1) bmp1[i] = getV(a[i * 2], a[i * 2 + 1]);
      if (j == 2) bmp2[i] = getV(a[i * 2], a[i * 2 + 1]);
      if (j == 3) bmp3[i] = getV(a[i * 2], a[i * 2 + 1]);
      if (j == 4) bmp4[i] = getV(a[i * 2], a[i * 2 + 1]);
      if (j == 5) bmp5[i] = getV(a[i * 2], a[i * 2 + 1]);
      if (j == 6) bmp6[i] = getV(a[i * 2], a[i * 2 + 1]);
    }
  }
  //--------------------------------------------
  str0 = GetStringAB(bufferBack, "STRM:", ";"); lg("b1="); lg(str0); lg();
  str1 = GetStringAB(bufferBack, "STRC:", ";"); lg("b2="); lg(str1); lg();
  wthr = GetStringAB(str0, ")", " ");
  //  colorKey = getV(a[0], a[1]);
  //  if (colorKey <= 0 || colorKey > 3) colorKey = 1;
  //--------------------------------------------
}
void WIFI_NET_EXP(String s) {
  String x = GetStringAB(s, "$", "*");
  WeatherHttpExp(x);
  //oled_str(bmp1); delay(5000);
  //oled_str(str0); delay(5000);
  //oled_str(str1); delay(5000);

  oled.clear();
  oled.setFont(ArialMT_Plain_10);
  oled.drawStringMaxWidth(0, 0, 128, str0);
  oled.drawXbm(0, 40, 8, 8, bmp1);
  oled.drawXbm(10, 40, 8, 8, bmp2);
  oled.display();

  smartDelay(20 * 1000);

  oled.clear();
  oled.setFont(ArialMT_Plain_24);
  oled.drawXbm(0, 0, 8, 8, bmp1);
  oled.drawXbm(10, 0, 8, 8, bmp2);
  oled.drawString(34, 18, wthr);
  oled.display();
}

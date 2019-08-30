//$
//BMP1:66FFFFFF7E3C18000105;
//BMP2:00247E7E3C1800000205;
//BMP3:66FFFFFF7E3C18000305;
//BMP4:00247E7E3C1800000105;
//BMP5:66FFFFFF7E3C18000205;
//STRM:I LOVE YOU,1314,MaYuan!My Love!;
//STRC:01;
//*
//===============================================
//String bb = "BMP1:007C00FE2044FE0103;BMP2:007C00FE2044FE0103;BMP3:925438EE3854920002;BMP4:925438EE3854920002;BMP5:007C00FE2044FE0103;BMP6:007C00FE2044FE0103;STRM:5.24 4:06 cloud A5 33/33c 3-4 pm50  TMR sunny 30c 3-4;STRC:03;";
//===============================================
uint8_t bmp1[10] = {0x00, 0x24, 0x7E, 0x7E, 0x3C, 0x18, 0x00, 0x00, 1, 5};
uint8_t bmp2[10] = {0x00, 0x66, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C, 0x18, 2, 5};
uint8_t bmp3[10] = {0x00, 0x24, 0x7E, 0x7E, 0x3C, 0x18, 0x00, 0x00, 3, 5};
uint8_t bmp4[10] = {0x00, 0x66, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C, 0x18, 1, 5};
uint8_t bmp5[10] = {0x00, 0x66, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C, 0x18, 2, 5};
uint8_t bmp6[10] = {0x00, 0x66, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C, 0x18, 3, 5};
//uint8_t* bmps[] = {bmp1, bmp2, bmp3, bmp4, bmp5, bmp6};
String str0 = "I love you 1314,MaYuan!";
String str1 = "I love you 1314,MaYuan!";
int colorKey = 3;
//===============================================
static const String strA[] = {"BMP0", "BMP1:", "BMP2:", "BMP3:", "BMP4:", "BMP5:", "BMP6:"};
void WeatherHttpExp(String bufferBack) {
  //------------------------------------------
  //bufferBack = bb;
  lg();
  //bmps = {bmp1, bmp2, bmp3, bmp4, bmp5, bmp6};
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
  //--------------------------------------------
  str0 = str0 + str1; lg(str0);
  //--------------------------------------------
  colorKey = getV(a[0], a[1]);
  if (colorKey <= 0 || colorKey > 3) colorKey = 1;
  //--------------------------------------------
}
//===============================================

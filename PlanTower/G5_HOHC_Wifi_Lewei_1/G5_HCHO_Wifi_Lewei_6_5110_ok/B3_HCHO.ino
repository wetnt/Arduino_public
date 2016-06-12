//------------------------------------------------
int iHCHO = 0;
float fHCHO = 0.0f;
float fHCHOnum = 0.0f;
float fHCHOall = 0.0f;
float fHCHOavr = 0.0f;
//------------------------------------------------
//查询命令
const static unsigned char HCHOAskData[7] = {0x42, 0x4D, 0x01, 0x00, 0x00, 0x00, 0x90};
//气体名称
String numName;
const static char numNameInx[][5] = {//50% //String numNameInx[]= {//56%
  "无", "CO", "H2S", "CH4", "CL2", "HCL", "F2", "HF", "NH3", "HCN", "PH3", "NO", "NO2", "O3", "O2", "SO2", "CLO2",
  "COCL", "PH3", "SiH4", "HCHO", "CO2", "VOC", "ETO", "C2H4", "C2H2", "SF6", "AsH3", "H2", "TOX1", "TOX2"//,
  //"气体流量L/M", "电池电量/%"
};
//数据内容 单位
String numUnit;
const static char numUnitInx[][6] = {"", "ppm", "VOL", "LEL", "Ppb", "mg/m3"};
//数据当量
float numKeys = 1;
const float numKeysInx[] = {1, 1, 10, 100, 1000};
//------------------------------------------------
void HCHO_Ask() {//42 4d 01 00 00 00 90
  S3.write(HCHOAskData, 7);//Serial.print(data,HEX)//AskHCHO()
}
//------------------------------------------------
void ShowHCHO() {
  //---------------------------------------
  lg(numName); lg(F(":")); lg(fHCHO); lg(F(" ")); lg(numUnit);
  lg(F(" Avg:")); lg(fHCHOavr); lgln(numUnit);
  //---------------------------------------
}
void LcdHCHO() {
  //LCD1602_Show(0, 0, String(numName) + String(F(": ")) + String(fHCHO) + String(F(" ")) + String(numUnit)   );
  //LCD1602_Show(6, 1, String(dhtH) + String(F("C V:")) + String(fHCHOavr) + String(F(" ")) + String(numUnit) );
}
//------------------------------------------------
byte HCHObuf[10];
int HCHOinx = 0;
void HCHOCheck(byte c) {
  if (HCHOinx == 9) GetHCHO();
  if (HCHOinx == 9) ShowHCHO();
  if (c == 0x42) HCHOinx = 0;
  HCHObuf[HCHOinx] = c;
  HCHOinx++;
}
void GetHCHO() {
  //---------------------------------------
  numName = numNameInx[HCHObuf[3]];
  numUnit = numUnitInx[HCHObuf[4]];
  numKeys = numKeysInx[HCHObuf[5]];
  //---------------------------------------
  iHCHO = HCHObuf[6] * 256 + HCHObuf[7];
  fHCHO = iHCHO / numKeys;
  //---------------------------------------
  fHCHOnum++;
  fHCHOall += fHCHO;
  fHCHOavr = fHCHOall / fHCHOnum;
  //---------------------------------------
}
//------------------------------------------------

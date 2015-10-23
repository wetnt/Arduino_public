//------------------------------------------------
int iHCHO = 0;
float fHCHO = 0.0f;
//------------------------------------------------
//气体名称
String numName = "";
String numNameInx[] = {
  "无", "CO", "H2S", "CH4", "CL2", "HCL", "F2", "HF", "NH3", "HCN", "PH3", "NO", "NO2", "O3", "O2", "SO2", "CLO2",
  "COCL2", "PH3", "SiH4", "HCHO", "CO2", "VOC", "ETO", "C2H4", "C2H2", "SF6", "AsH3", "H2", "TOX1", "TOX2",
  "气体流量L/M", "电池电量/%"
};
//数据内容 单位
String numUnit = "";
String numUnitInx[] = {"", "ppm", "VOL", "LEL", "Ppb", "Mg/m3"};
//数据当量定义
float numKeys = 1;
float numKeysInx[] = {1, 1, 10, 100, 1000};
//------------------------------------------------
void ShowHCHO()
{
  //---------------------------------------
  //lgln("----------------");
  //lg(iHCHO);  lgln("----");
  lg(numName); lg(" "); lg(fHCHO); lg(" "); lgln(numUnit);
  //---------------------------------------
}
//------------------------------------------------
void AskHCHO()
{
  //---------------------------------------
  //42 4d 01 00 00 00 90
  gas.print(0x42);
  gas.print(0x4d);
  gas.print(0x01);
  gas.print(0x00);
  gas.print(0x00);
  gas.print(0x00);
  gas.print(0x90);
  //---------------------------------------
}
//------------------------------------------------
char HCHObuf[10];
int HCHOinx = 0;
void HCHOCheck(char c)
{
  if (HCHOinx == 9) GetHCHO();
  if (HCHOinx == 9) ShowHCHO();
  if (c == 0x42) HCHOinx = 0;
  HCHObuf[HCHOinx] = c;
  HCHOinx++;
}
void GetHCHO()
{
  //---------------------------------------
  //int i, j, k, p;
  //---------------------------------------
  numName = numNameInx[HCHObuf[3]];
  numUnit = numUnitInx[HCHObuf[4]];
  numKeys = numKeysInx[HCHObuf[5]];
  //---------------------------------------
  iHCHO = HCHObuf[6] * 256 +  HCHObuf[7];
  fHCHO = iHCHO / numKeys;
  //---------------------------------------
}
//------------------------------------------------

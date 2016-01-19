const char hz[][32] = {
  "当前电压:",  //0
  "Arduino 电压表演示程序",  //1
  "使用Usart GPU串口液晶屏", //2
};
void GpuClear()
{
  lgln("CLS(0);");
}
void ShowGPU(int x, int y, String s, int c)
{
  //---------------------------------------
  String sHead = String("DS32(") + String(x) + String(",") + String(y) + String(",'");
  String sEnds = String("',") + String(c) + String(");");
  //String sHead = String("DS16(") + String(x) + String(",") + String(y) + String(",\"");
  //String sEnds = String("\",") + String(c) + String(");");
  Serial.print(sHead);
  Serial.print(s);
  Serial.print(sEnds);
  //---------------------------------------
}
void ShowGpuRun() {
  Serial.println("");
}

//void ShowGPU(int x,int y,String s)
//{
//  //---------------------------------------
//  //lgln("CLS(0);");
//  //Serial.println("DS16(2, 2, '1245445', 2);");Serial.flush();delay(200);
//  //lgln("PL(0,40,399,40,1);");//Serial.flush();delay(200);
//  Serial.print("DS16(20,20,'");
//  Serial.print(numName); Serial.print(": "); Serial.print(fHCHO); Serial.print(" "); Serial.print(numUnit);
//  Serial.print("',4);");
//  //---------------------------------------
//}

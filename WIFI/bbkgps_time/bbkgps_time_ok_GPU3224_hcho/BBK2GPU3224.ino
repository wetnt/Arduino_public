//const char hz[][32] = {"当前电压:","Arduino 电压表演示程序"};
void GpuClear() {
  lgln(F("CLS(0);"));
}
void GpuShow(int x, int y, String s, int c,bool endKey){
  lg("DS32(" + String(x) + "," + String(y) + ",'" + s + "'," + String(c) + ");");
  if(endKey)lgln();
}

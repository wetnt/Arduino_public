String strCMD = String("$JML,CAR,SAN,A,B,C,4,5,6,7,8,9,10,11,12;");
void CmdShow() {
  //--------------------------------------------
  strCMD  = String("$JML,CAR,SAN,");
  strCMD += String(IntAX) + String(",");
  strCMD += String(IntAY) + String(",");
  strCMD += String(IntAK) + String(",");
  strCMD += String(IntBX) + String(",");
  strCMD += String(IntBY) + String(",");
  strCMD += String(IntBK) + String(",");
  lgln(strCMD);
  //myCmds.println(strCMD);
  //--------------------------------------------
}

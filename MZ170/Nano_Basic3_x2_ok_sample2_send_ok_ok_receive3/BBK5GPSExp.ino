char GpsKey[12][13];
int  GpsKeyN = 0, GpsKeyCharN = 0;
void GpsLineFeed(char x) {
  if (x == '\r' || x == '\n') {
  } else if (x == ',' || x == ';') {
    //lg(GpsKeyN); lg("="); lgln(GpsKey[GpsKeyN]);
    GpsKeyCharN = 0;
    GpsKeyN++;
    if (x == ';') {
      GpsKeyN = 0;
      GpsLineExp();
    }
  } else {
    GpsKey[GpsKeyN][GpsKeyCharN] = x;
    GpsKeyCharN++;
  }
}
void GpsLineExp() {
  GpsLineExp_log();
  GpsLineExp_log2();
  ShowBeep();
}
//lgln(GpsLine);
// char str[] = "2011-11-21 13:59";
//  printf("strtok: '-' ");
//  char *psub = strtok(str, "-");
//  puts(psub);
//  while ( psub = strtok(NULL, "-") )
//  {
//    puts(psub);
//  }
//  for (int i = 0; i < psub.length; i++) {
//    Serial.print(psub);
//    Serial.println("------");
//}
//  char ** stringarr;
//  int arrayCount = 0;
//  stringarr = cSplit(GpsLine, ',',  & arrayCount);
//  GpsLine = "";
//  for (int i = 0; i < arrayCount; i++) {
//    lgln(stringarr[i]);
//  }
//  lgln("------");

void GpsLineExp_log() {
  lg(F("--A----"));
  lg(GpsKey[0]); lg(F("T")); lg(GpsKey[1]); lg(F(" w"));
  lg(GpsKey[2]); lg(F(" j")); lg(GpsKey[3]); lg(F(" h"));
  lg(GpsKey[4]); lg(F(" v")); lg(GpsKey[5]); lg(F(" x")); lg(GpsKey[6]); lg(F(" r"));
  lg(GpsKey[7]); lg(F(" g")); lg(GpsKey[8]); lg(F(" l")); lg(GpsKey[9]); lg(F(" "));
  lgln();
}
void GpsLineExp_log2() {
  lg("CLS(0);");
  ShowGPU(0, 0, "--A----", 1);
  ShowGPU(0, 32, GpsKey[0], 2);  ShowGPU(120, 32, "                   ", 2);  ShowGPU(150, 32, GpsKey[1], 2);  ShowGPU(200, 32, "             ", 2);
  ShowGPU(0, 64, GpsKey[2], 2);  ShowGPU(136, 64, "                   ", 2);  ShowGPU(150, 64, GpsKey[3], 2);  ShowGPU(240, 64, "             ", 2);
  ShowGPU(0, 96, GpsKey[4], 2);  ShowGPU(40, 96, "                    ", 2);  ShowGPU(48, 96, GpsKey[5], 2);   ShowGPU(72, 96, "               ", 2);
  ShowGPU(80, 96, GpsKey[6], 2);  ShowGPU(120, 96, "                   ", 2);  ShowGPU(150, 96, GpsKey[7], 2);  ShowGPU(180, 96, "              ", 2);
  ShowGPU(200, 96, GpsKey[8], 2);  ShowGPU(240, 96, "                   ", 2);
  ShowGpuRun();
}
void ShowBeep() {
  digitalWrite(7, LOW);
  smartDelay(40);
  digitalWrite(7, HIGH);
}

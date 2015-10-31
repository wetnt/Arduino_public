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
  //GpsLine = "";
  lg(F("--A----"));
  lg(GpsKey[0]); lg(F("T")); lg(GpsKey[1]); lg(F(" w"));
  lg(GpsKey[2]); lg(F(" j")); lg(GpsKey[3]); lg(F(" h"));
  lg(GpsKey[4]); lg(F(" v")); lg(GpsKey[5]); lg(F(" x")); lg(GpsKey[6]); lg(F(" r"));
  lg(GpsKey[7]); lg(F(" g")); lg(GpsKey[8]); lg(F(" l")); lg(GpsKey[9]); lg(F(" "));
  lgln();
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
}

//String GpsLine = "";
char GpsLine[200];
char GpsKey[20][12];
int GpsLineN = 0, GpsKeyN = 0, GpsKeyCharN = 0;
void GpsLineFeed(char x) {
  if (GpsLineN > 199) {
    GpsLineN = 199;
  }
  if (x == '\r' || x == '\n') {
  } else if (x == ',' || x == ';') {
    lg(GpsKeyN); lg("="); lgln(GpsKey[GpsKeyN]);
    GpsKeyCharN = 0;
    GpsKeyN++;
    if (x == ';') {
      GpsLineN = 0;
      GpsKeyN = 0;
      //GpsLineExp();
    }
  } else {
    GpsKey[GpsKeyN][GpsKeyCharN] = x;
    GpsLine[GpsLineN] = x;
    GpsLineN++;
    GpsKeyCharN++;
  }
}
void GpsLineExp() {
  //GpsLine = "";
  lgln(F("--A----"));
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

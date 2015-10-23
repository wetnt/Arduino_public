String GpsLine = "";
void GpsLineFeed(char x) {
  GpsLine += String(x);
  if (x == ';')GpsLineExp();
}
void GpsLineExp() {
  lcd.setCursor(0, 0);  lcd.print(GpsLine);
  GpsLine = "";
  //  Serial.println("--A----");
  //  char str[] = "2011-11-21 13:59";
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
  //  stringarr = cSplit((char *)GpsLine, ',',  & arrayCount);
  //  GpsLine = "";
  //  for (int i = 0; i < arrayCount; i++) {
  //    Serial.println(stringarr[i]);
  //  }
  //  Serial.println("------");
}

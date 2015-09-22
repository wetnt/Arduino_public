static void printInt(unsigned long val, bool valid, int len)
{
  char sz[32] = "*****************";
  if (valid)
    sprintf(sz, "%ld", val);
  sz[len] = 0;
  for (int i = strlen(sz); i < len; ++i)
    sz[i] = ' ';
  if (len > 0)
    sz[len - 1] = ' ';
  lgs.print(sz);
  smartDelay(0);
}
static void printFloat(float val, bool valid, int len, int prec)
{
  if (!valid) {
    while (len-- > 1)
      lgs.print('*');
  } else {
    lgs.print(val, prec);
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1); // . and -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i = flen; i < len; ++i)
      lgs.print(' ');
  }
  smartDelay(0);
}
static void printStr(const char *str, int len)
{
  int slen = strlen(str);
  for (int i = 0; i < len; ++i)
    lgs.print(i < slen ? str[i] : ' ');
  smartDelay(0);
}
static void printDateTime(TinyGPSDate &d, TinyGPSTime &t)
{
  if (!d.isValid()) {
    lgs.print(F("**********"));
  } else {
    char sz[32];
    sprintf(sz, "%02d/%02d/%02d", d.month(), d.day(), d.year());
    lgs.print(sz);
  }
  lgs.print(' ');
  if (!t.isValid()) {
    lgs.print(F("********"));
  } else {
    char sz[32];
    sprintf(sz, "%02d:%02d:%02d", t.hour(), t.minute(), t.second());
    lgs.print(sz);
  }
  //printInt(d.age(), d.isValid(), 5);
  smartDelay(0);
}

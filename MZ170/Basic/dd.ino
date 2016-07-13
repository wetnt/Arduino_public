char s[150];
int cnt = 0;
void  G5Feed(char c) {
  if (c == '$') cnt = 0; else cnt++;
  if (cnt > 99)cnt = 0;
  if (c == ',') c = '_';
  if (c == '\r') c = ' ';
  if (c == '\n') c = ' ';
  s[cnt] = c;
  if (c == '*') {
    lcd.clear();
    lcd.print(s);
  }
}

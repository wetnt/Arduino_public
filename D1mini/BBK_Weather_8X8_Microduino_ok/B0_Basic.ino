//-------------------------------------
double getK(char a, char b, char c,char d) {
  String s = "";
  s.concat(a);  s.concat(b);  s.concat(c); s.concat(d);
  double x = ((double)s.toInt())/10;
  lg(x); lg();
  return x;
}
//-------------------------------------
int getV(char a, char b) {
  return GetHexCharToInt(a) * 16 + GetHexCharToInt(b);
}
//-------------------------------------
int GetHexCharToInt(char c) {
  if (1 == 0) {}
  //-----------------------------
  else if (c == '0') return 0;
  else if (c == '1') return 1;
  else if (c == '2') return 2;
  else if (c == '3') return 3;
  else if (c == '4') return 4;
  else if (c == '5') return 5;
  else if (c == '6') return 6;
  else if (c == '7') return 7;
  else if (c == '8') return 8;
  else if (c == '9') return 9;
  //-----------------------------
  else if (c == 'A') return 10;
  else if (c == 'B') return 11;
  else if (c == 'C') return 12;
  else if (c == 'D') return 13;
  else if (c == 'E') return 14;
  else if (c == 'F') return 15;
  //-----------------------------
  else if (c == 'a') return 10;
  else if (c == 'b') return 11;
  else if (c == 'c') return 12;
  else if (c == 'd') return 13;
  else if (c == 'e') return 14;
  else if (c == 'f') return 15;
  //-----------------------------
}


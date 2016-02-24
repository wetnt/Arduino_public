//-------------------------------------------------------------------------
String GetStringAB(String s, String a, String b) {
  int ln = s.length();
  int an = s.indexOf(a);
  int al = a.length();
  s = s.substring(an);
  int bn = s.indexOf(b);
  s = s.substring(al, bn);
  return s;
}
boolean DataIndexOf(String d, String s) {
  return (d.indexOf(s) != -1);
}
//-------------------------------------------------------------------------

String GetStringAB(String s, String a, String b) {
  int sl = s.length();
  int al = a.length();
  int an = s.indexOf(a);
  if (sl <= an) return "";
  s = s.substring(an);
  int bn = s.indexOf(b);
  if (bn < al) return "";
  s = s.substring(al, bn);
  return s;
}
String GetStringAB(String s, String a, char b) {
  int sl = s.length();
  int al = a.length();
  int an = s.indexOf(a);
  if (sl <= an) return "";
  s = s.substring(an);
  int bn = s.indexOf(b);
  if (bn <= al) return "";
  s = s.substring(al, bn);
  return s;
}
//-------------------------------------------------------------------------

//String GetStringAB(String txt, String a, String b) {
//  int ln = txt.length();
//  int an = txt.indexOf(a);
//  txt = txt.substring(an);//, 100);
//  int bn = txt.indexOf(b);
//  txt = txt.substring(0, bn);
//  return txt;
//}
boolean DataIndexOf(String d, String s) {
  return (d.indexOf(s) != -1);
}
//-------------------------------------------------------------------------

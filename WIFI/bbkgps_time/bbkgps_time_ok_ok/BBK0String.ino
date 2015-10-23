//-------------------------------------------------------------------------
String GetStringAB(String txt, String a, String b) {
  int ln = txt.length();
  int an = txt.indexOf(a);
  txt = txt.substring(an);//, 100);
  int bn = txt.indexOf(b);
  txt = txt.substring(0, bn);
  return txt;
}
boolean DataIndexOf(String d, String s) {
  return (d.indexOf(s) != -1);
}
//-------------------------------------------------------------------------

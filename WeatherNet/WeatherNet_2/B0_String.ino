String GetStringAB(String txt, String a, String b) {
  int ln = txt.length();
  int an = txt.indexOf(a);
  int al = a.length();
  txt = txt.substring(an);
  int bn = txt.indexOf(b);
  txt = txt.substring(al, bn);
  return txt;
}
boolean DataIndexOf(String d, String s) {
  return (d.indexOf(s) != -1);
}
//-------------------------------------------------------------------------
//char *ConvertTo2String(long number, int n) {
//  char *output = NULL;
//  output = (char*)malloc(33);    //include '\0'
//  int i = 0;
//  for (; i < n; i++)  {
//    output[i] = number & (1 << (n - 1) - i);
//    output[i] = output[i] >> (n - 1) - i;
//    output[i] = (output[i] == 0) ? '0' : '1';
//  }
//  output[i] = '\0';
//  return output;
//}
//-------------------------------------------------------------------------
//String GetStringAB(String m, String a, String b) {
//  //--------------------------------------------
//  lgln(m);
//  String s = ""; s.concat(m); //lg(s);
//  //--------------------------------------------
//  int sn = s.length();
//  int al = a.length();
//  int an = s.indexOf(a); //lg("=1="); lg(a); lg("=2="); lg(b);
//  //--------------------------------------------
//  //if (sn <= an + al) return "";
//  s = s.substring(an + al); //lg('='); lg(s);
//  //--------------------------------------------
//  int bn = s.indexOf(b);
//  s = s.substring(0,bn); //lg('='); lg(s); lg();
//  //--------------------------------------------
//  return s;
//  //--------------------------------------------
//}


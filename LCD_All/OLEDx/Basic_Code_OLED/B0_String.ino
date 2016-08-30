//-------------------------------------------------------------------------
String GetStringAB(String txt, String a, String b) {
  int ln = txt.length();
  int an = txt.indexOf(a);
  int al = a.length();
  //lg(txt);lg('=');lg(a);lg('=');lg(b);
  if (ln <= an) return "";
  txt = txt.substring(an);
  //lg('=');lg(txt);
  int bn = txt.indexOf(b);
  if (bn <= al) return "";
  txt = txt.substring(al, bn);  
  //lg('=');lg(txt);lg();
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

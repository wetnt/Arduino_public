//=====================================================
void StringToTimeSet(String ts) {
  //------------------------------------------
  //String ts = "2015-06-13 21:14:12;x";
  //------------------------------------------
  String hs = ts.substring(11, 13);
  String ms = ts.substring(14, 16);
  String ss = ts.substring(17, 19);
  //------------------------------------------
//  Serial.println(ts);
//  Serial.println(hs);
//  Serial.println(ms); 
//  Serial.println(ss);
  //------------------------------------------
  int ht = hs.toInt();
  int mt = ms.toInt();
  int st = ss.toInt();
  //------------------------------------------
  TimeSets(ht,mt,st);
  //------------------------------------------
}

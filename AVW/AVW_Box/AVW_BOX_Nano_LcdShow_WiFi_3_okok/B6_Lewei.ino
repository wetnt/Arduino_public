//-------------------------------------------------------------------------
static String Lewei_Link = "AT+CIPSTART=\"TCP\",\"www.lewei50.com\",80";
static String Lewei_Keys = "4a7c908d0de946de96e041dd84834154";
//-------------------------------------------------------------------------
String Lewei_Post = "";
//-------------------------------------------------------------------------
void GetLeweiPostString(String Key, String Gate, String ValJson) {
  Lewei_Post = "POST http://www.lewei50.com/api/V1/gateway/UpdateSensors/" + String(Gate) + " HTTP/1.1\r\n";
  Lewei_Post += "userkey: " + Key + "\r\n";
  Lewei_Post += "Host: www.lewei50.com\r\n";
  Lewei_Post += "Content-Length: " + String(ValJson.length()) + "\r\n";
  Lewei_Post += "\r\n";
  Lewei_Post += String(ValJson);
  Lewei_Post += "\r\n";
  //lgln(Lewei_Post);
}
String sh = "[";
String sa = "{\"Name\":\"";
String sb = "\",\"Value\":\"";
String sc = "\"}";
String se = "]";
String Lewei_ValueJson() {
  //-------------------------------------------------------------------------
  String s = "";
  s.concat(sh);
  //-------------------------------------------------------------------------
  s.concat(sa); s.concat("GL"); s.concat(sb); s.concat(Watt); s.concat(sc); s.concat(',');
  s.concat(sa); s.concat("DL"); s.concat(sb); s.concat(Amps); s.concat(sc); s.concat(',');
  s.concat(sa); s.concat("YDL"); s.concat(sb); s.concat(Kwhs); s.concat(sc);//s.concat(',');
  //-------------------------------------------------------------------------
  s.concat(se);
  return s;
  //-------------------------------------------------------------------------
  //s.concat(sa); s.concat("DY"); s.concat(sb); s.concat(Volt); s.concat(sc); s.concat(',');
  //s.concat(sa); s.concat("GLYS"); s.concat(sb); s.concat(Pfss); s.concat(sc); s.concat(',');
  //-------------------------------------------------------------------------
}
//-------------------------------------------------------------------------
void Lewei_Report() {
  //-------------------------------------------------------------
  GetLeweiPostString(Lewei_Keys, "01", Lewei_ValueJson());
  HttpGetPost(Lewei_Link, Lewei_Post, 5);
  //-------------------------------------------------------------
}
//-------------------------------------------------------------------------

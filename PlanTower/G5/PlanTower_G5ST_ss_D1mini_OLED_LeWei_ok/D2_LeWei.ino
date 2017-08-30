//===================================================================
const int httpPort = 80;
const char* host = "42.121.254.11";//www.lewei50.com
String back_str = "";

String a1 = "POST http://www.lewei50.com/api/V1/gateway/UpdateSensors/02 HTTP/1.1\r\n";
String a2 = "userkey: 4a7c908d0de946de96e041dd84834154\r\n";
String a3 = "Host: www.lewei50.com\r\n";
String a4a = "Content-Length: ";
String a4b = "\r\n";
String a5 = "Expect: 100-continue\r\n";
String a6 = "Connection: Keep-Alive\r\n";
String a7 = "\r\n";
String a8a = "[";
String b1a = "{\"Name\":\"WD\",\"Value\":\""; String b1b = "\"},";
String b2a = "{\"Name\":\"JQ\",\"Value\":\""; String b2b = "\"},";
String b3a = "{\"Name\":\"PM\",\"Value\":\""; String b3b = "\"},";
String b4a = "{\"Name\":\"SD\",\"Value\":\""; String b4b = "\"}";
String a8b = "]\r\n";
String bb = "";
//===================================================================
float old_hcho;   //甲醛浓度数值/mg/m3//HCHO
float old_tmps;   //温度℃
int old_hums;   //湿度%
int old_pm25;//PM2.5
boolean date_isnew() {
  boolean date_new = false;
  if (old_tmps != g.tmps) date_new = true;
  if (old_hums != g.hums) date_new = true;
  if (old_pm25 != g.pm25) date_new = true;
  if (old_hcho != g.hcho) date_new = true;
  old_tmps = g.tmps;
  old_hums = g.hums;
  old_pm25 = g.pm25;
  old_hcho = g.hcho;
  return date_new;
}
//===================================================================
void lewei_post() {
  //------------------------------------------
  WiFiClient client;
  if (!client.connect(host, httpPort)) {
    lgln("connection failed");
    return;
  }
  //------------------------------------------
  lg("Requesting URL: "); lgln(host);
  //------------------------------------------
  bb = a8a;
  bb = bb + b1a + String(g.tmps, 1) + b1b; //wd
  bb = bb + b2a + String(g.hcho, 3) + b2b; //jq
  bb = bb + b3a + String(g.pm25) + b3b;//pm
  bb = bb + b4a + String(g.hums) + b4b;//sd
  bb = bb + a8b;
  int sl = bb.length();

  bb = a1 + a2 + a3 + a4a + String(sl) + a4b + a5 + a6 + a7 + bb;
  client.print(bb);
  lgln(bb);
  //------------------------------------------
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 10000) {
      lgln(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  //------------------------------------------
  lgln("-------------------------");
  back_str = "";
  while (client.available()) {
    String line = client.readStringUntil('\r');//lg(line);
    back_str += line;
  }
  //------------------------------------------
  lg(); lgln(back_str); lgln("closing connection");
  //------------------------------------------
}

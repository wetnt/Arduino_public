//===================================================================
const int httpPort = 80;
const char* host = "42.121.254.11";//www.bbkgps.com
String back_str = "";

String a1 = "POST http://www.lewei50.com/api/V1/gateway/UpdateSensors/02 HTTP/1.1\r\n";
String a2 = "userkey: 4a7c908d0de946de96e041dd84834154\r\n";
String a3 = "Host: www.lewei50.com\r\n";
String a4 = "Content-Length: 30\r\n";
String a5 = "Expect: 100-continue\r\n";
String a6 = "Connection: Keep-Alive\r\n";
String a7 = "\r\n";
String a8 = "[{\"Name\":\"WDLD\",\"Value\":\"10\"}]\r\n";
String bb="";
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
  bb=a1+a2+a3+a4+a5+a6+a7+a8;
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
  lgln(back_str);
  lgln("closing connection");
  //------------------------------------------
}


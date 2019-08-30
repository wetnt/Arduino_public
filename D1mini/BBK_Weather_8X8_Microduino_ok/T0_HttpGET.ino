//===================================================================
const int httpPort = 80;
const char* host = "112.124.186.245";//www.bbkgps.com
String url_str = "http://www.bbkgps.com/w.php";
String get_str = String("GET ") + url_str + " HTTP/1.1\r\n" +
                "Host: " + host + "\r\n" +
                "Connection: close\r\n\r\n";
String back_str = "";
//===================================================================
void http_get() {
  //------------------------------------------
  WiFiClient client;
  //lg("connecting to "); lgln(host);
  if (!client.connect(host, httpPort)) {
    lgln("connection failed");
    return;
  }
  //------------------------------------------
  lg("Requesting URL: "); lgln(url_str);
  //------------------------------------------
  client.print(get_str);
  lgln(get_str);
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
  //lgln("-------------------------");
  back_str = "";
  while (client.available()) {
    String line = client.readStringUntil('\r');//lg(line);
    back_str += line;    
  }
  //------------------------------------------
  //lgln("closing connection");
  //------------------------------------------  
}


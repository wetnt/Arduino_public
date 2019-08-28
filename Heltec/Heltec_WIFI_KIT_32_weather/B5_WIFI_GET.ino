//--------------------------------------------------
int value = 0;
const char* host = "www.bbkgps.com";
const int   httpPort = 80;
const int   timeOut = 10 * 1000;
//--------------------------------------------------
void Wifi_Weather_GET() {
  //--------------------------------------------------
  ++value;
  lg("connecting to "); lgln(host);
  //--------------------------------------------------
  WiFiClient client;
  if (!client.connect(host, httpPort)) {
    lgln("connection failed");
    wifi_add_new();
    return;
  }
  //--------------------------------------------------
  String urlStr = String("/w.php?value=") + String(value);
  lg("Requesting URL: "); lgln(urlStr);
  //--------------------------------------------------
  String getStr = String("GET ") + urlStr + " HTTP/1.1\r\n" +
                  "Host: " + host + "\r\n" +
                  "Connection: close\r\n\r\n";
  lg("Requesting GET: "); lgln(getStr);
  //--------------------------------------------------
  client.print(getStr);
  //--------------------------------------------------
  unsigned long timeNow = millis();
  while (client.available() == 0) {
    if (millis() - timeNow > timeOut) {
      lgln(">>> Client Timeout !");
      client.stop(); return;
    }
  }
  //--------------------------------------------------
  String getBack = "";
  while (client.available()) {
    String line = client.readStringUntil('\r');
    lg(line);getBack += line;
  }
  lgln("closing connection");
  //--------------------------------------------------  
  //oled_str(getBack);
  WIFI_NET_EXP(getBack);
  //--------------------------------------------------  
}


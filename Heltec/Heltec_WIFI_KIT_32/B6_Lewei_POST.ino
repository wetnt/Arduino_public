//--------------------------------------------------
int value = 0;
const char* host = "www.lewei50.com";
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
  //GetLeweiPostString(Lewei_Keys, "01", Lewei_ValueJson());  
  //--------------------------------------------------
  client.print(Lewei_Post);
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
  //WIFI_NET_EXP(getBack);
  //--------------------------------------------------  
}


//https://blog.csdn.net/Naisu_kun/article/details/86165403
#include <WiFi.h>
#include <WiFiMulti.h>
WiFiMulti wifiMulti;
//--------------------------------------------------
const char* ssid_1 = "MMMM";
const char* pass_1 = "1234567890123";
const char* ssid_2 = "JTFY";
const char* pass_2 = "jtfy2468";
//--------------------------------------------------
void wifi_add_new() {
  //wifi_add_one(ssid_1, pass_1);
  //wifi_add_one(ssid_2,pass_2);
  //wifi_add_config(ssid_1,pass_1);

  wifiMulti.addAP(ssid_1, pass_1);
  wifiMulti.addAP(ssid_2, pass_2);
  
  if (wifiMulti.run() == WL_CONNECTED) {
    //wifi_info();
  }else{
    Serial.println("WIFI ERROR!");
  }
}
void wifi_add_one(const char* ssid, const char* password) {
  lg("Connecting Wifi one..."); lgln(ssid);
  WiFi.begin(ssid, password); //wifi_info();
}
void wifi_add_config(const char* ssid, const char* password) {
  lg("Connecting Wifi config..."); lgln(ssid);
  //--------------------------------------------------
  //北京联通DNS：202.106.196.115　202.106.46.151　202.106.0.20　202.106.195.68
  //--------------------------------------------------
  IPAddress myDevIP(192, 168, 199, 163);
  IPAddress gateway(192, 168, 199, 1);
  IPAddress sub_net(255, 255, 0, 0);
  IPAddress one_DNS(202, 106, 196, 115);
  IPAddress two_DNS(202, 106, 46, 151);
  if (!WiFi.config(myDevIP, gateway, sub_net, one_DNS, two_DNS)) {
    lgln("STA Failed to configure");
  }
  //--------------------------------------------------
  WiFi.begin(ssid, password); //wifi_info();
  //--------------------------------------------------
}
void wifi_setup() {
  //--------------------------------------------------
  WiFi.disconnect(true);
  wifi_add_new();
  WiFi.setAutoReconnect();
  wifi_info();
  //--------------------------------------------------
}
void wifi_info() {
  int wn = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(200); lg(".");
    wn++; if (wn % 20 == 0) {
      Serial.println("");
    }
    if (wn > 20) {
      break;
    }
  }
  lgln("-----------------------------------");
  lgln("WiFi connected!");
  lg("RSSI: ");  lgln(WiFi.RSSI());
  lg("Channel: ");  lgln(WiFi.channel());
  lg("Channel: ");  lgln(WiFi.channel());
  
  lg("DeviceName: ");  lgln(WiFi.getHostname());
  lg("IP Address: ");  lgln(WiFi.localIP());
  lg("MacAddress: ");  lgln(WiFi.macAddress());
  lg("SubnetMask: ");  lgln(WiFi.subnetMask());
  lg("Gateway_IP: ");  lgln(WiFi.gatewayIP());
  lg("NetLinkDNS: ");  lgln(WiFi.dnsIP());
  //lg("SSID: "); lgln(WiFi.SSID(0));
  //lg("RSSI: "); lgln(WiFi.RSSI(0));
  String x = String(WiFi.localIP());
  lgln("-----------------------------------");
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0,  0, 2); M5.Lcd.println(WiFi.getHostname());
  M5.Lcd.setCursor(0, 14, 2); M5.Lcd.println(WiFi.macAddress());
  M5.Lcd.setCursor(0, 28, 2); M5.Lcd.println(WiFi.localIP());
  M5.Lcd.setCursor(0, 42, 2); M5.Lcd.println(WiFi.subnetMask());
  M5.Lcd.setCursor(0, 56, 2); M5.Lcd.println(WiFi.gatewayIP());
  //--------------------------------------------------
}
//============================================================================
String NET_GET_POST_BACK = "";
boolean WIFI_GET_POST(const char* host, int port, int timeOut, String str_Get_Post, boolean logshow) {
  //--------------------------------------------------
  lg("connecting to "); lgln(host);
  //--------------------------------------------------
  if (!WiFi.isConnected()){
    lgln("!WiFi.isConnected()");
    WIFI_TIME_Bad();
    return false;
  }
  //--------------------------------------------------
  WiFiClient client;
  if (!client.connect(host, port)) {
    if (logshow) lgln("connection failed");
    wifi_add_new();
    return false;
  }
  //--------------------------------------------------
  client.print(str_Get_Post);
  //--------------------------------------------------
  unsigned long timeNow = millis();
  while (client.available() == 0) {
    if (millis() - timeNow > timeOut) {
      lgln(">>> Client Timeout !");
      client.stop(); return false;
    }
  }
  //--------------------------------------------------
  NET_GET_POST_BACK = "";
  while (client.available()) {
    String line = client.readStringUntil('\r');
    if (logshow) lg(line);
    NET_GET_POST_BACK += line;
  }
  if (logshow) lgln("closing connection");
  return true;
  //--------------------------------------------------
}
//============================================================================

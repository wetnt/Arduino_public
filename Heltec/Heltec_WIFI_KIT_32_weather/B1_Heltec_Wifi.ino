#include "WiFi.h"
//--------------------------------------------------
const char* ssid_1 = "MMMM"; const char* pass_1 = "1234567890123";
const char* ssid_3 = "JTFY";  const char* pass_3 = "jtfy2468";
const char* ssid_2 = "JTFY2"; const char* pass_2 = "jtfy2468";
//--------------------------------------------------
int wifi_no = 0;
void wifi_add_new() {
  switch (wifi_no) {
    case 0: wifi_add_config(ssid_1, pass_1); break;
    case 1: wifi_add_config(ssid_2, pass_2); break;
    case 2: wifi_add_config(ssid_3, pass_3); break;
    case 3: wifi_no = -1; break;
  };
  wifi_no++;
  lg("wifi_no="); lgln(wifi_no);
}
void wifi_add_one(const char* ssid, const char* password) {
  lg("Connecting Wifi one..."); lgln(ssid);
  WiFi.begin(ssid, password);
  wifi_info();
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
  WiFi.disconnect(true); WiFi.onEvent(WiFiEvent);
  lg("Mac address: "); lgln(WiFi.macAddress());
  wifi_add_new(); lg();
  //--------------------------------------------------
  oled.clear();
  oled.setFont(ArialMT_Plain_10);
  oled.drawString(0, 0,  "Mac: "); oled.drawString(30, 0, WiFi.macAddress());
  oled.drawString(0, 10, " IP: "); oled.drawString(30, 10, String(WiFi.localIP()));
  oled.display();
  //--------------------------------------------------
}
void wifi_info() {
  while (WiFi.status() != WL_CONNECTED) {
    delay(200); lg(".");
  }
  lgln("---------------------------------- -");
  lgln("WiFi connected!");
  lg("DeviceName: ");  lgln(WiFi.getHostname());
  lg("IP Address: ");  lgln(WiFi.localIP());
  lg("MacAddress: ");  lgln(WiFi.macAddress());
  lg("SubnetMask: ");  lgln(WiFi.subnetMask());
  lg("Gateway_IP: ");  lgln(WiFi.gatewayIP());
  lg("NetLinkDNS: ");  lgln(WiFi.dnsIP());
  lg("SSID: "); lgln(WiFi.SSID(0));
  lg("RSSI: "); lgln(WiFi.RSSI(0));
  lgln("---------------------------------- -");
}
void WiFiEvent(WiFiEvent_t event) {
  lgs.printf("[WiFi - event] event: % d\n", event);
  switch (event) {
    case SYSTEM_EVENT_STA_GOT_IP: wifi_info(); break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
      lgln("WiFi lost connection");
      smartDelay(5000); //自动重连不能小于5秒
      wifi_add_new(); break;
  }
}

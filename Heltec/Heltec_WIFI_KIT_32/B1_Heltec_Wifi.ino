#include "WiFi.h"
//--------------------------------------------------
const char* ssid_1 = "MMMM";
const char* pass_1 = "1234567890123";
const char* ssid_2 = "JTWX_DL_2.4G";
const char* pass_2 = "jtwx1234";
//--------------------------------------------------
void wifi_add_new() {
  wifi_add_one(ssid_1,pass_1);
  //wifi_add_one(ssid_2,pass_2);
  //wifi_add_config(ssid_1,pass_1);
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
  WiFi.disconnect(true);WiFi.onEvent(WiFiEvent);
  wifi_add_new();
  //--------------------------------------------------
  String x = String(WiFi.localIP());
  oled.clear();
  oled.setFont(ArialMT_Plain_10);
  oled.drawString(0, 0, "IP address: ");
  oled.drawString(0, 10, x);
  oled.display();
  //--------------------------------------------------
}
void wifi_info() {
  while (WiFi.status() != WL_CONNECTED) {
    delay(200); lg(".");
  }
  lgln("-----------------------------------");
  lgln("WiFi connected!");
  lg("DeviceName: ");  lgln(WiFi.getHostname());
  lg("IP Address: ");  lgln(WiFi.localIP());
  lg("MacAddress: ");  lgln(WiFi.macAddress());
  lg("SubnetMask: ");  lgln(WiFi.subnetMask());
  lg("Gateway_IP: ");  lgln(WiFi.gatewayIP());
  lg("NetLinkDNS: ");  lgln(WiFi.dnsIP());
  lg("SSID: "); lgln(WiFi.SSID(0));
  lg("RSSI: "); lgln(WiFi.RSSI(0));
  lgln("-----------------------------------");
}
void WiFiEvent(WiFiEvent_t event) {
  lgs.printf("[WiFi-event] event: %d\n", event);
  switch (event) {
    case SYSTEM_EVENT_STA_GOT_IP: wifi_info(); break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
      lgln("WiFi lost connection");
      smartDelay(5000); //自动重连不能小于5秒
      wifi_add_new(); break;
  }
}


#include "WiFi.h"
#include <WiFiMulti.h>

WiFiMulti wifiMulti;
//--------------------------------------------------
const char* ssid_1 = "MMMM";
const char* pass_1 = "1234567890123";
const char* ssid_2 = "JTWX_DL_2.4G";
const char* pass_2 = "jtwx1234";
//--------------------------------------------------
void wifi_add_new() {
  wifi_add_multi();
  //wifi_add_one(ssid_1,pass_1);
  //wifi_add_one(ssid_2,pass_2);
  //wifi_add_config(ssid_1,pass_1);
}
void wifi_add_one(const char* ssid, const char* password) {
  Serial.print("Connecting Wifi one..."); Serial.println(ssid);
  WiFi.begin(ssid, password); //wifi_info();
}
void wifi_add_config(const char* ssid, const char* password) {
  Serial.print("Connecting Wifi config..."); Serial.println(ssid);
  //--------------------------------------------------
  //北京联通DNS：202.106.196.115　202.106.46.151　202.106.0.20　202.106.195.68
  //--------------------------------------------------
  IPAddress myDevIP(192, 168, 199, 163);
  IPAddress gateway(192, 168, 199, 1);
  IPAddress sub_net(255, 255, 0, 0);
  IPAddress one_DNS(202, 106, 196, 115);
  IPAddress two_DNS(202, 106, 46, 151);
  if (!WiFi.config(myDevIP, gateway, sub_net, one_DNS, two_DNS)) {
    Serial.println("STA Failed to configure");
  }
  //--------------------------------------------------
  WiFi.begin(ssid, password); //wifi_info();
  //--------------------------------------------------
}
void wifi_add_multi() {
  Serial.print("Connecting Wifi multi...");
  Serial.print(ssid_1); Serial.print("/"); Serial.print(ssid_2);
  Serial.println();
  //--------------------------------------------------
  wifiMulti.addAP(ssid_1, pass_1);
  wifiMulti.addAP(ssid_2, pass_2);
  //--------------------------------------------------
  if (wifiMulti.run() == WL_CONNECTED) {
    wifi_info();
  }
  //--------------------------------------------------
}
void wifi_setup() {
  //--------------------------------------------------
  WiFi.disconnect(true);
  WiFi.onEvent(WiFiEvent);
  //--------------------------------------------------
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
    delay(200); Serial.print(".");
  }
  Serial.println("-----------------------------------");
  Serial.println("WiFi connected!");
  Serial.print("DeviceName: ");  Serial.println(WiFi.getHostname());
  Serial.print("IP Address: ");  Serial.println(WiFi.localIP());
  Serial.print("MacAddress: ");  Serial.println(WiFi.macAddress());
  Serial.print("SubnetMask: ");  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway_IP: ");  Serial.println(WiFi.gatewayIP());
  Serial.print("NetLinkDNS: ");  Serial.println(WiFi.dnsIP());

  Serial.print("SSID: "); Serial.println(WiFi.SSID(0));
  Serial.print("RSSI: "); Serial.println(WiFi.RSSI(0));

  Serial.println("-----------------------------------");
}
void WiFiEvent(WiFiEvent_t event) {
  Serial.printf("[WiFi-event] event: %d\n", event);
  switch (event) {
    case SYSTEM_EVENT_STA_GOT_IP: wifi_info(); break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
      Serial.println("WiFi lost connection");
      delay(5000); //自动重连不能小于5秒
      wifi_add_new(); break;
  }
}


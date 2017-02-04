#include "ESP8266WiFi.h"
//===================================================================
//static const uint8_t LED_BUILTIN = 16;
//static const uint8_t BUILTIN_LED = 16;
//static const uint8_t D0   = 16;
//static const uint8_t D1   = 5;
//static const uint8_t D2   = 4;
//static const uint8_t D3   = 0;
//static const uint8_t D4   = 2;
//static const uint8_t D5   = 14;
//static const uint8_t D6   = 12;
//static const uint8_t D7   = 13;
//static const uint8_t D8   = 15;
//static const uint8_t D9   = 3;
//static const uint8_t D10  = 1;
//===================================================================
void wifi_setup() {
  //------------------------------------------
  WiFi.mode(WIFI_STA); WiFi.disconnect();
  //------------------------------------------
}
String wifi_get_my_mac() {
  byte mac[6];
  WiFi.macAddress(mac);
  String s = ""
             + String(mac[5], HEX) + ":"
             + String(mac[4], HEX) + ":"
             + String(mac[3], HEX) + ":"
             + String(mac[2], HEX) + ":"
             + String(mac[1], HEX) + ":"
             + String(mac[0], HEX);
  s.toUpperCase();
  return s;
}
String wifi_get_ap_mac() {
  int n = WiFi.scanNetworks();
  if (n == 0) {
    //lg("no networks found"); lg();
    return "0:0:0:0:0:0";
  } else {
    //lg(n); lg(" = "); lg(WiFi.BSSIDstr(0)); lg();
    return WiFi.BSSIDstr(0);
  }
}
String wifi_get_ap_mac2() {
  int rs = -999;
  int ri = 0;
  int n = WiFi.scanNetworks();
  if (n == 0) {
    //lg("no networks found"); lg();
    return "0:0:0:0:0:0";
  } else {
    //lg(n); lg(" = "); lg(WiFi.RSSI(0)); lg();
    for (int i = 0; i < n; ++i) {
      int rx = WiFi.RSSI(i);
      if (rs < rx) {
        rs = rx;
        ri = i;
      }
      //lg(rx); lg("="); lg(rs); lg("="); lg(ri); lg();
    }
    return WiFi.BSSIDstr(ri);
  }
}
//===================================================================
void printWifiList() {
  lg("wifi_get_first"); lg();
  int n = WiFi.scanNetworks();
  if (n == 0) {
    lg("no networks found"); lg();
  } else {
    lg(n); lg(" networks found"); lg();
    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      lg(i + 1); lg(": ");
      lg("\t"); lg(WiFi.BSSIDstr(i));
      lg("\t"); lg(" ("); lg(WiFi.RSSI(i)); lg(")");
      lg("\t"); lg(WiFi.SSID(i));
      lg(""); lg((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*"); lg();
      smartDelay(10);
    }
  }
  lg();
}
void printMacAddress() {
  // print your MAC address:
  byte mac[6];
  WiFi.macAddress(mac);
  lg("MAC address: ");
  lgHEX(mac[5]); lg(":"); lgHEX(mac[4]); lg(":"); lgHEX(mac[3]); lg(":");
  lgHEX(mac[2]); lg(":"); lgHEX(mac[1]); lg(":"); lgHEX(mac[0]); lg();
}
void printWifiStatus() {
  // print the SSID of the network you're attached to:
  lg("SSID: "); lg(WiFi.SSID()); lg();

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  lg("IP Address: "); lg(ip); lg();

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  lg("signal strength (RSSI):"); lg(rssi); lg("dBm"); lg();
  // print where to go in a browser:
  lg("To see this page in action, open a browser to http://");
  lg(ip); lg();
}
//===================================================================

#include "ESP8266WiFi.h"

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ;
  }

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  Serial.println("Setup done");
}

void loop() {
  Serial.println("scan start");

  printMacAddress();
  printWifiStatus();
  printWifiList();

  // Wait a bit before scanning again
  delay(5000);
}

void printWifiList() {
  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0)
    Serial.println("no networks found");
  else {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1); Serial.print(": ");
      Serial.print("\t"); Serial.print(WiFi.BSSIDstr(i));
      Serial.print("\t"); Serial.print(" ("); Serial.print(WiFi.RSSI(i)); Serial.print(")");
      Serial.print("\t"); Serial.print(WiFi.SSID(i));
      Serial.print(""); Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");
      delay(10);
    }
  }
  Serial.println("");
}
void printMacAddress() {
  // print your MAC address:
  byte mac[6];
  WiFi.macAddress(mac);
  Serial.print("MAC address: ");
  Serial.print(mac[5], HEX);  Serial.print(":");  Serial.print(mac[4], HEX);  Serial.print(":");  Serial.print(mac[3], HEX);  Serial.print(":");  
  Serial.print(mac[2], HEX);  Serial.print(":");  Serial.print(mac[1], HEX);  Serial.print(":");  Serial.print(mac[0], HEX);  Serial.println("");
}
void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  // print where to go in a browser:
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}

#include "WiFi.h"
const char* ssid     = "MMMM";
const char* password = "1234567890123";

void wifi_setup() {
  int linkTimes = 0;
  WiFi.begin("JTFY1", "jtfy2468");
  //WiFi.begin(ssid, password);delay(100);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
    linkTimes++; if(linkTimes>1000) linkTimes = 0;
    if(linkTimes%30 == 0) Serial.print("\n");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  String x = String(WiFi.localIP());

  oled.clear();
  oled.setFont(ArialMT_Plain_10);
  oled.drawString(0, 0, "IP address: ");
  oled.drawString(0, 10, x);
  oled.display();
}

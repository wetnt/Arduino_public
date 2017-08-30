#include <Arduino.h>
#include <ESP8266WiFi.h>
//------------------------------------------
//char ssid[] = "MMMM";
//char pass[] = "1234567890123";
//------------------------------------------
char ssid[] = "JTWX";
char pass[] = "jtwx1234";
//------------------------------------------
void wifi_setup() {
  wifi_addAP();
}
void wifi_addAP() {
  lg("Connecting to "); lg(ssid); lg();
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500); lg(".");
  }
  lg();

  lg("WiFi connected IP address: ");
  lg(WiFi.localIP()); lg();
}
void wifi_loop() {

}

#include <Arduino.h>
#include <ESP8266WiFi.h>
//------------------------------------------
char bbk_ssid[] = "MMMM";
char bbk_pass[] = "1234567890123";
//------------------------------------------
char sat_ssid[] = "JTWX";
char sat_pass[] = "jtwx1234";
//------------------------------------------
boolean wifi_ok = false;
boolean wifi_isok() {
  return wifi_ok;
}
//------------------------------------------
void wifi_setup() {
  if (!wifi_addAP(sat_ssid, sat_pass))wifi_addAP(bbk_ssid, bbk_pass);
  wifi_ip_show();
}
boolean wifi_addAP(char ssid[], char pass[]) {
  wifi_ok = false;

  lg("Connecting to "); lg(ssid);
  WiFi.begin(ssid, pass);

  for (int i = 0; i < 30; i++) {
    delay(500); lg(".");
    if (WiFi.status() == WL_CONNECTED) {
      wifi_ok = true; break;
    }
  }
  if (WiFi.status() != WL_CONNECTED) lgln("false");
  if (WiFi.status() == WL_CONNECTED) lgln("ok");
  return wifi_ok;
}
void wifi_ip_show() {
  lg("WiFi connected IP address: ");
  lg(WiFi.localIP()); lg();
}
void wifi_loop() {
}
void wifi_restart() {
  lg("WiFi restart");
  lg(WiFi.restart()); lg();
}

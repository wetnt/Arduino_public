//=========================================================================
//https://www.zybuluo.com/kfihihc/note/31135
//http://wiki.iteadstudio.com/ESP8266_Serial_WIFI_Module
//=========================================================================
#include <WiFi.h>
#include <HTTPClient.h>
const char* ssid = "JTFY";
const char* password = "jtfy2468";
//=========================================================================
void wifi_Init() {
//  //-------------------------------------------------
//  lg(F("WiFi.start! = ")); lg(ssid); lg(" "); lg(password); lg();
//  //-------------------------------------------------
//  WiFi.mode(WIFI_STA);
//  WiFi.begin(ssid, password);
//  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
//    lg("Connection Failed! Rebooting..."); lg();
//    delay(5000);
//    ESP.restart();
//  }
//  //-------------------------------------------------
//  lg("IP address: "); lg(WiFi.localIP()); lg();
//  //-------------------------------------------------
//  HttpGet("www.baidu.com");
//  //-------------------------------------------------
}
//=========================================================================
String bufferBack; bool bufferKeys = false;
//=========================================================================
void HttpGet(String url) {
//  lg("[HTTP] GET...");lg(url); lg();
//  HTTPClient http;
//  http.begin(url);
//  int httpCode = http.GET();
//  if (httpCode > 0) {
//    Serial.printf("[HTTP] GET... code: %d\n", httpCode);
//    if (httpCode == HTTP_CODE_OK) {
//      bufferBack = http.getString();
//      lg(bufferBack); lg();
//    }
//  } else {
//    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
//  }
//  http.end();
}
//=========================================================================



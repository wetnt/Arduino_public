//=========================================================================
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
WiFiMulti wifiMulti;
//-------------------------------------------------
const char* ssidname = "JTFY";
const char* password = "jtfy2468";
//=========================================================================
void wifi_Init() {
  //-------------------------------------------------
  lg(F("WiFi.start = ")); lg(ssidname); lg(":"); lg(password); lg();
  //-------------------------------------------------
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssidname, password);
  //wifiMulti.addAP(ssidname,password);
  //-------------------------------------------------
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    lg("Connection Failed! Rebooting..."); lg();
    delay(5000); ESP.restart();
  }
  //-------------------------------------------------
  lg("IP address: ");  Serial.print(WiFi.localIP()); lg();
  //-------------------------------------------------
  HttpGet("http://www.bbkgps.com/w.php",true);
  //-------------------------------------------------
}
//=========================================================================
String bufferBack; boolean HttpGetOK = false;
//=========================================================================
void HttpGet(String url, boolean debugPrint) {
  lg("[HTTP] GET..."); lg(url); lg(); HttpGetOK = false;
  HTTPClient http;
  http.begin(url);
  int httpCode = http.GET();
  if (httpCode > 0) {
    if (debugPrint) Serial.printf("[HTTP] GET...code: %d\n", httpCode);
    if (httpCode == HTTP_CODE_OK) {
      bufferBack = http.getString();
      if (debugPrint)lg(bufferBack); lg();
      HttpGetOK = true;
    }
  } else {
    Serial.printf("[HTTP] GET...failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
  http.end();
}
//=========================================================================



#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
ESP8266WiFiMulti WiFiMulti;

//#define HTTPIP      "14.215.177.37"//baidu
#define HTTPIP      "112.124.186.245"//bbk
#define HTTPPORT    80
#define WIFINAME    "jtwx1234"
#define WIFIPW      ""


void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Connecting");

  WiFiMulti.addAP(WIFINAME, WIFIPW);
  while (WiFiMulti.run() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected!");


  httpRun();
}

void httpRun() {

  HTTPClient http;
  Serial.println("Try link to http.");
  http.begin(HTTPIP, HTTPPORT, "/");
  http.begin("http://www.bbkgps.com/", 80, "/w.php");
  
  //char url[100]="http://www.bbkgps.com/";
  //http.begin(url);
  //http://www.bbkgps.com/w.php
  

  int Code = http.GET();
  if (Code) {
    Serial.printf("HTTP Code:%d\n", Code);
    if (Code == 200) {
      String payload = http.getString();
      Serial.println(payload);
    } else {
      Serial.println("Couldn't link to server");
    }
  }

  delay(5000);
}
void loop() {
}

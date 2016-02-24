#include "DHT.h"
//-------------------------------------------------
#define DHTPIN A1
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
//-------------------------------------------------
DHT dht(DHTPIN, DHTTYPE);
float dhtT, dhtH, dhtF, dhtHif, dhtHic;
void DHT_setup() {
  dht.begin();
  Serial.println("DHTxx test!");
}
void DHT_loop() {
  delay(1000);
  dhtH = dht.readHumidity();
  dhtT = dht.readTemperature();
  dhtF = dht.readTemperature(true);
  if (isnan(dhtH) || isnan(dhtT) || isnan(dhtF)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  dhtHif = dht.computeHeatIndex(dhtF, dhtH);//酷热指数
  dhtHic = dht.computeHeatIndex(dhtT, dhtH, false);
}
void DHT_show() {
  Serial.print(F("Humidity: ")); Serial.print(dhtH); Serial.print(F("%\t"));
  Serial.print(F("Temperature: ")); Serial.print(dhtT); Serial.print(F("C/")); Serial.print(dhtF); Serial.print("F\t");
  Serial.print(F("Heat index: ")); Serial.print(dhtHic); Serial.print(F("C/")); Serial.print(dhtHif); Serial.println("F\t");
}

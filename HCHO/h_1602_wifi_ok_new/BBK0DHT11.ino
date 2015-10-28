#include "DHT.h"
#define DHTPIN 7     // what pin we're connected to

#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);

int dhtH, dhtT, dhtF;
//float dhtHa = 0.0f;
//int dhtHv = 0, dhtHn = 0;
void DHT_setup() {
  dht.begin();
}

void DHT_loop() {
  dhtH = dht.readHumidity();
  dhtT = dht.readTemperature();
  dhtF = dht.readTemperature(true);
  //  dhtHn++;
  //  if (dhtHn > 20) {
  //    dhtHn = 0;
  //    dhtHv = 0;
  //    dhtHa = 0.0f;
  //  }
  //  dhtHa += dhtH;
  //  dhtHv = dhtHa / dhtHn;
  //lg("T:" + String(dhtH) + "C ");//714字节
  //lg(F("T:")); lg(dhtHv); lg(F("C "));
  lg(F("T:")); lg(dhtH); lg(F("C "));//708字节
}

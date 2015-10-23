#include "DHT.h"
#define DHTPIN 7     // what pin we're connected to

#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);

int dhtH, dhtT, dhtF;
void DHT_setup() {
  dht.begin();
}

void DHT_loop() {
  dhtH = dht.readHumidity();
  dhtT = dht.readTemperature();
  dhtF = dht.readTemperature(true);
}

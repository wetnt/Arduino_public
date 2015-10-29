//-------------------------------------------------------------------------
#include "DHT.h"
#define DHTPIN 2     // what pin we're connected to
//-------------------------------------------------------------------------
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);
//-------------------------------------------------------------------------
int dhtH, dhtT, dhtF;
float dhtHa = 0.0f;
int dhtHv = 0, dhtHn = 0;
void DHT_setup() {
  dht.begin();
}
void DHT_loop() {
  //--------------------------------------------
  dhtH = dht.readHumidity();
  dhtT = dht.readTemperature();
  dhtF = dht.readTemperature(true);
  //--------------------------------------------
  if (dhtHn > 6) {
    dhtHn = 0;
    dhtHv = dhtH;
    dhtHa = 0.0f;
  }
  //--------------------------------------------
  dhtHn++;
  dhtHa += dhtH;
  dhtHv = dhtHa / dhtHn;
  //--------------------------------------------
  lg(F("Temperature: ")); lg(dhtH); lg(F("C  "));
  lg(F("  Avg: ")); lg(dhtHv); lgln(F("C "));
  //--------------------------------------------
}
//-------------------------------------------------------------------------

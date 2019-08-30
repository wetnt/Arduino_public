#include "DHT12.h"

DHT12 dht12;
float tmp;
float hum;


void DHT12_setup() {
  lcd_show("DHT12,ok!");
  tmp = dht12.readTemperature();
  hum = dht12.readHumidity();  
  Serial.printf("Temp: %2.1f℃ Humi: %2.0f%%", tmp, hum); lg();
}

void DHT12_loop() {
  // put your main code here, to run repeatedly:
  tmp = dht12.readTemperature();
  hum = dht12.readHumidity();  
  Serial.printf("Temp: %2.1f℃ Humi: %2.0f%%", tmp, hum); lg();
}

#include <SimpleDHT.h>
//------------------------------------------------
// for DHT11,
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 2
//------------------------------------------------
int pinDHT11 = 7;
SimpleDHT11 dht11;
byte temperature = 0;
byte humidity = 0;
//------------------------------------------------
void DHT_setup() {
  lg("DHT_setup: DHT11"); lg();
}
void DHT_loop() {
  for (int i = 0; i < 20; i++) {
    smartDelay(5); lg('.');
    if (!dht11.read(pinDHT11, &temperature, &humidity, NULL))
      break;
  }
}
void DHT_show() {
  lg(); lg("Sample OK: ");
  lg((int)temperature); lg(" *C, ");
  lg((int)humidity); lg(" %"); lg();
  smartDelay(1000);
}

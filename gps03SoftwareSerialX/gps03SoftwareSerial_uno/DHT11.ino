//DHT11 vcc pin->+5v
//DHT11 data pin->d3
//DHT11 gnd pin->gnd
dht11 DHT11;
#define DHT11PIN 3 //dht11数据脚
double DhtT = 0;
double DhtH = 0;

void DHT11Read()
{ 
  int chk = DHT11.read(DHT11PIN);
  switch (chk)
  {
  case DHTLIB_OK: 
    DhtT = DHT11.humidity;
    DhtH = DHT11.temperature;
    break;
  }
}


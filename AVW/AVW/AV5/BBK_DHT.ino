//----------------------------------------------------
#include <dht.h>
//----------------------------------------------------
float DHT_WD = 0, DHT_SD = 0;
#define DHTPIN A5
//----------------------------------------------------
dht DHT;
long DHTTime = millis(), DHTTimeKey = 5*1000;
//----------------------------------------------------
void DHT_Setup(){
}
//----------------------------------------------------
void DHT_Loop(){
  //---------------------------------------
  if( millis() - DHTTime < DHTTimeKey) return; 
  DHTTime = millis();
  //---------------------------------------
  int chk = DHT.read11(DHTPIN); 
  if( chk == DHTLIB_OK ){	
    DHT_WD = DHT.temperature; 
    DHT_SD = DHT.humidity; 
  }
  //---------------------------------------
}


//----------------------------------------------------
#include <dht.h>
//----------------------------------------------------
float DHT_WD = 0, DHT_SD = 0;
const int DHT_Pin = 9;//DHT_Pin
dht DHT;
//----------------------------------------------------
void DHT_Setup(){
}
//----------------------------------------------------
void DHT_Loop(){
  //---------------------------------------
  int chk = DHT.read11(DHT_Pin); 
  if( chk == DHTLIB_OK ){	
    DHT_WD = DHT.temperature; 
    DHT_SD = DHT.humidity; 
  }
  //---------------------------------------
}


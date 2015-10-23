//----------------------------------------------------
#include <dht.h>
//----------------------------------------------------
float DHT_WD = 0, DHT_SD = 0;
const int DHT_Pin = A5;//DHT_Pin
dht DHT;
//----------------------------------------------------
void DHT_Setup(){
  Serial.println("DHT_Setup_OK!");
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


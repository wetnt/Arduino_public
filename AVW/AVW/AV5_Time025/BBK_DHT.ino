//----------------------------------------------------
#include <dht.h>
//----------------------------------------------------
float DHT_WD = 0, DHT_SD = 0;
const int DHT_Pin = A5;//DHT_Pin
dht DHT;
long DHTTime = millis(), DHTTimeKey = 5*1000;
//----------------------------------------------------
void DHT_Setup(){
  Serial.println("DHT_Setup_OK!");
}
//----------------------------------------------------
void DHT_Loop(int showkey){
  //---------------------------------------
  if( millis() - DHTTime < DHTTimeKey) return; 
  DHTTime = millis();
  //---------------------------------------
  int chk = DHT.read11(DHT_Pin); 
  if( chk == DHTLIB_OK ){	
    DHT_WD = DHT.temperature; 
    DHT_SD = DHT.humidity; 
  }
  //---------------------------------------
  if(showkey) DHT_Show();
  //---------------------------------------
}
void DHT_Show(){
  //---------------------------------------
  Serial.print("temperature = ");
  Serial.println(DHT_WD);
  Serial.print("humidity = ");
  Serial.println(DHT_SD);
  //---------------------------------------
}



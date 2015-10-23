
//----------------------------------------------------
void setup() {
  Serial.begin(4800);
  delay(10000);
  DHT_Setup();
  LEWEI_Setup();
}
void loop() {
  //---------------------------------------  
  DHT_Loop();
  LeweiLoop();
  //---------------------------------------       
  delay(15000);
  //---------------------------------------
}
void tempShow(){
  //---------------------------------------  
  //  Serial.print(Voltage);
  //  Serial.print(Amp);
  //  Serial.print(Watt);
  //  Serial.print(Kwh);
  //  Serial.print(Pf);
  //  Serial.print(Cabon);
  //---------------------------------------  
}




void setup() {
  //------------------------------------------
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  //------------------------------------------
  Ethernet_Setup();
  Ethernet_IPShow(); 
  //UDP_Setup(); 
  //------------------------------------------
}
void loop() {
  //UDP_Loop();
}


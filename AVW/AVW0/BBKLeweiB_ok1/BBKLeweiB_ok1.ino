//===============================================================
//#include <LeweiClient.h>
//#include <SPI.h>
//#include <Ethernet.h>
//#include <EthernetUdp.h>
//#include <Dns.h>
//===============================================================
void setup()
{
  //------------------------------------------
  Serial.begin(115200);
  while (!Serial) {
    ;
  }
  Serial.println("AVW5_Time_Start......");
  //------------------------------------------
  Serial.print("Ethernet_Setup......");  
  Ethernet_Setup();  
  Serial.print("Ethernet_IPShow......"); 
  Ethernet_IPShow(); 
  LEWEI_Setup();
  //------------------------------------------
}
void loop() {  
  LEWEI_Loop();
}  
//===============================================================

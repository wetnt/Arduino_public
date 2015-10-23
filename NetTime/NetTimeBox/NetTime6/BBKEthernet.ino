//=====================================================
#include <SPI.h>
#include <Ethernet.h>
//=====================================================
byte mac[] = { 
  0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 };
//=====================================================
void Ethernet_Setup() {
  //------------------------------------------
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    for(;;)
      ;
  }
  //------------------------------------------
}
void Ethernet_IPShow() {
  Serial.print("My IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print("."); 
  }
  Serial.println();
  //------------------------------------------
}

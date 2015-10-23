//=====================================================
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <Dns.h>
//=====================================================
//byte mac[] = {0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 };
byte mac[] = { 
  0x00, 0x00, 0xAA, 0xBB, 0xCC, 0xDD };
unsigned int localPort = 80; // local port to listen for UDP packets
//-----------------------------------------------------
DNSClient   Dns;
EthernetUDP Udp;
//=====================================================
void Ethernet_Setup()
{
  //-------------------------------------------------------------
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    Serial.println("Ethernet_Setup() Stop!!!");
    for(;;)
      ;
  }
  //-------------------------------------------------------------
  Udp.begin(localPort);
  Dns.begin(Ethernet.dnsServerIP());
  //-------------------------------------------------------------
}
void Ethernet_IPShow() {
  //------------------------------------------
  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());
  //------------------------------------------
  //  for (byte thisByte = 0; thisByte < 4; thisByte++) {
  //    Serial.print(Ethernet.localIP()[thisByte], DEC);
  //    if(thisByte<3)Serial.print("."); 
  //  }
  //  Serial.println();
  //------------------------------------------
}


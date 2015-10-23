//=====================================================
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <Dns.h>
//=====================================================
//byte mac[] = {0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 };
byte mac[] = { 0x00, 0x00, 0xAA, 0xBB, 0xCC, 0xDD };
unsigned int localPort = 80; // local port to listen for UDP packets
//-----------------------------------------------------
DNSClient   Dns;
EthernetUDP Udp;
//=====================================================
void Ethernet_Setup()
{
  //Serial.print("Ethernet_Setup......");
  //-------------------------------------------------------------
  if (Ethernet.begin(mac) == 0) {
    //Serial.println("Failed to configure Ethernet using DHCP");
    //Serial.println("Ethernet_Setup() Stop!!!");
    for(;;)
      ;
  }
  //-------------------------------------------------------------
  Udp.begin(localPort);
  Dns.begin(Ethernet.dnsServerIP());
  //-------------------------------------------------------------
  Serial.print(Ethernet.localIP());
  //Serial.println(" OK!");  
  //-------------------------------------------------------------
}

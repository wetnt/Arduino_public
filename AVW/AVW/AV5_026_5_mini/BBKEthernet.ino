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
  //-------------------------------------------------------------
  if (Ethernet.begin(mac) == 0) {
    return;
    //Serial.println("Failed to configure Ethernet using DHCP");
    //for(;;)
    //  ;
  }
  //-------------------------------------------------------------
  Serial.println(Ethernet.localIP());
  Serial.println(Ethernet.dnsServerIP());
  //-------------------------------------------------------------
  Udp.begin(localPort);
  Dns.begin(Ethernet.dnsServerIP());
  //-------------------------------------------------------------
}
//=====================================================

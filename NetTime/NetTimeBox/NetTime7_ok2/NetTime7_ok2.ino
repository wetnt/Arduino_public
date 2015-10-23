#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <Dns.h>


//-------------------------------------------------------------
byte mac[] = {
  0x00, 0x00, 0xAA, 0xBB, 0xCC, 0xDD};
unsigned int localPort = 80;                // local port to listen for UDP packets
//-------------------------------------------------------------
const int NTP_PACKET_SIZE = 48;             // NTP time stamp is in the first 48 bytes of the message
byte packetBuffer[ NTP_PACKET_SIZE];        // buffer to hold incoming and outgoing packets
//-------------------------------------------------------------
IPAddress timeServer(193, 92, 150, 3);      // time.nist.gov NTP server (fallback)
const char* host = "time.asia.apple.com";   // Use random servers through DNS
IPAddress rem_add;
//-------------------------------------------------------------
DNSClient Dns;
EthernetUDP Udp;
//-------------------------------------------------------------

bool Century = false, h12 = false, PM = false;
int year;
byte month, date, day, hour, minute, second, temperature, hundredths;
unsigned long age = 0;
char timeStr[17], dateStr[17];

void setup()
{
  Serial.begin(9600);
  Ethernet_Setup();
  NTP_Setup();

}

void Ethernet_Setup()
{
  //-------------------------------------------------------------
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    delay(2000);
    return;
  }
  //-------------------------------------------------------------
  Udp.begin(localPort);
  Dns.begin(Ethernet.dnsServerIP());
  //-------------------------------------------------------------
}
void NTP_Setup()
{
  //-------------------------------------------------------------
  if (Dns.getHostByName(host, rem_add) == 1 ) {
    Serial.print("DNS resolve : ");
    Serial.print(host);
    Serial.print(" = ");
    Serial.print(rem_add);
    Serial.println();
    //sendNTPpacket(rem_add);
  } 
  else {
    Serial.print("DNS fail...");
    Serial.print("time.nist.gov = ");
    Serial.print(timeServer);        // fallback
    Serial.println();
    //sendNTPpacket(timeServer);         // send an NTP packet to a time server
    rem_add = timeServer;
  }
  //-------------------------------------------------------------
  delay(300);        // wait to see if a reply is available
  //-------------------------------------------------------------
}

void loop()
{
  //NTP_Setup();
  NTPTime_Loop();
  snprintf(timeStr, 17, "NET: %02d:%02d:%02d", hour, minute, second);
  Serial.println(timeStr);
  delay(2000);
}

void NTPTime_Loop()
{
  //-------------------------------------------------------------
  sendNTPpacket(rem_add);
  //-------------------------------------------------------------
  if ( Udp.parsePacket() ) {
    //-------------------------------------------------------------
    // We've received a packet, read the data from it
    Udp.read(packetBuffer, NTP_PACKET_SIZE);         // read the packet into the buffer
    //-------------------------------------------------------------
    //the timestamp starts at byte 40 of the received packet and is four bytes,
    // or two words, long. First, esxtract the two words:
    //-------------------------------------------------------------
    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord  = word(packetBuffer[42], packetBuffer[43]);
    // combine the four bytes (two words) into a long integer
    // this is NTP time (seconds since Jan 1 1900):
    unsigned long secsSince1900 = highWord << 16 | lowWord;
    Serial.print("NTP Time Stamp: ");
    Serial.print(secsSince1900);
    Serial.println();
    // now convert NTP time into everyday time:
    Serial.print("Unix Epoch time = ");
    // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
    const unsigned long seventyYears = 2208988800UL;
    // subtract seventy years:
    delay(200);
    unsigned long epoch = secsSince1900 - seventyYears;
    epoch += 1;
    // print Unix time:
    Serial.print(epoch);
    Serial.print("   ");
    Serial.println();
    //-------------------------------------------------------------
    // print the hour, minute and second: local time +8:00
    hour = (epoch % 86400L) / 3600 + 8;
    if (hour > 23)
    {
      hour -= 24;
    }
    minute = (epoch % 3600) / 60;
    second = epoch % 60;
    //-------------------------------------------------------------
  }
}

// send an NTP request to the time server at the given address
unsigned long sendNTPpacket(IPAddress& address)
{
  //-------------------------------------------------------------
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  //-------------------------------------------------------------
  packetBuffer[0]  = 0b11100011;  // LI, Version, Mode
  packetBuffer[1]  = 0;           // Stratum, or type of clock
  packetBuffer[2]  = 6;           // Polling Interval
  packetBuffer[3]  = 0xEC;  	  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12] = 49;
  packetBuffer[13] = 0x4E;
  packetBuffer[14] = 49;
  packetBuffer[15] = 52;
  //-------------------------------------------------------------
  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  //-------------------------------------------------------------
  Udp.beginPacket(address, 123); //NTP requests are to port 123
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  Udp.endPacket();
  //-------------------------------------------------------------
}





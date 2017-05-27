//------------------------------------------
//IPAddress timeServer(129, 6, 15, 28); // time.nist.gov NTP server
IPAddress timeServerIP; // time.nist.gov NTP server address
const int NTP_Port = 123;
//const char* ntpServerName = "time.nist.gov";
const char* ntpServerName = "128.138.141.172";
const int NTP_PACKET_SIZE = 48;
byte packetBuffer[ NTP_PACKET_SIZE];
//------------------------------------------
unsigned int localPort = 2390;
//------------------------------------------
unsigned long NTPpacket() {
  //lg("sending NTP packet..."); lg();
  memset(packetBuffer, 0, NTP_PACKET_SIZE);//set all bytes in the buffer to 0

  packetBuffer[0] = 0b11100011;// LI, Version, Mode
  packetBuffer[1] = 0;         // Stratum, or type of clock
  packetBuffer[2] = 6;         // Polling Interval
  packetBuffer[3] = 0xEC;      // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;
}
unsigned long getsNTPTime() {
  unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
  unsigned long lowsWord = word(packetBuffer[42], packetBuffer[43]);
  unsigned long secsSince1900 = highWord << 16 | lowsWord;
  const unsigned long seventyYears = 2208988800UL;
  unsigned long Unix_time = secsSince1900 - seventyYears;
  //lg("1900.07.1 = "); lg(secsSince1900); lg();
  //lg("Unix_time = "); lg(Unix_time); lg();
  return Unix_time;
}

//-------------------------------------------------------------
// print the hour, minute and second: local time +8:00
int Local_Time = +8;
//-------------------------------------------------------------
IPAddress timeServer(193,92,150,3);       // time.nist.gov NTP server (fallback)
const char* host = "time.asia.apple.com"; // Use random servers through DNS
//-------------------------------------------------------------
const int NTP_PACKET_SIZE = 48;           // NTP time stamp is in the first 48 bytes of the message
byte packetBuffer[ NTP_PACKET_SIZE];      // buffer to hold incoming and outgoing packets
IPAddress rem_add;
//-------------------------------------------------------------
// combine the four bytes (two words) into a long integer
unsigned long highWord = 0,lowsWord = 0;
//-------------------------------------------------------------
// Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
const unsigned long seventyYears = 2208988800UL;
// this is NTP time (seconds since Jan 1 1900):
unsigned long secondSince1900 = 0;        
unsigned long secondsNtpEpoch = 0;
//-------------------------------------------------------------
int ntpYearss = 2014, ntpMonths = 1, ntpDatess = 1, ntpDayweek = 1;
int ntpHourss = 12, ntpMinute = 0, ntpSecond = 0;
char timeStr[20], dateStr[20];
//-------------------------------------------------------------
void NTP_Setup()
{
  //-------------------------------------------------------------
  if (Dns.getHostByName(host, rem_add) == 1 ) {
    Serial.print("DNS resolve : ");
    Serial.print(host);
    Serial.print(" = ");
    Serial.print(rem_add);
    Serial.println();
  } 
  else {
    Serial.print("DNS fail...");
    Serial.print("time.nist.gov = ");
    Serial.print(timeServer);
    Serial.println();
    rem_add = timeServer;
  }
  //-------------------------------------------------------------
}
void NTPTime_Loop(bool debugshow)
{
  //-------------------------------------------------------------
  sendNTPpacket(rem_add);// send an NTP packet to a time server
  delay(300);            // wait to see if a reply is available
  //-------------------------------------------------------------
  if ( Udp.parsePacket() ) {
    //-------------------------------------------------------------
    // We've received a packet, read the data from it
    // read the packet into the buffer
    Udp.read(packetBuffer, NTP_PACKET_SIZE); 
    //-------------------------------------------------------------
    highWord = word(packetBuffer[40], packetBuffer[41]);
    lowsWord = word(packetBuffer[42], packetBuffer[43]);
    secondSince1900 = highWord << 16 | lowsWord;    
    //-------------------------------------------------------------
    secondsNtpEpoch = secondSince1900 - seventyYears;
    secondsNtpEpoch += 1;
    //-------------------------------------------------------------
    if(debugshow){// print Unix time:
      Serial.print("NTP Time Stamp: ");
      Serial.println(secondSince1900);
      Serial.print("Unix Epoch time = ");
      Serial.println(secondsNtpEpoch);
    }
    //-------------------------------------------------------------
    NTPTime_Setting();
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

void NTPTime_Setting()
{
  //-------------------------------------------------------------
  //-------------------------------------------------------------
  // print the hour, minute and second: local time +8:00
  ntpHourss = (secondsNtpEpoch % 86400L) / 3600 + Local_Time;
  if (ntpHourss > 23)
  {
    ntpHourss -= 24;
  }
  ntpMinute = (secondsNtpEpoch % 3600) / 60;
  ntpSecond =  secondsNtpEpoch % 60;
  //-------------------------------------------------------------
  Time_SetTime(ntpHourss,ntpMinute,ntpSecond);
  //-------------------------------------------------------------
}

void NTPTime_Show()
{
  //-------------------------------------------------------------
  snprintf(dateStr, 22, "NET_Date: %4d-%02d-%02d",  ntpYearss,ntpMonths,ntpDatess);
  snprintf(timeStr, 22, "NET_Time: %02d:%02d:%02d", ntpHourss,ntpMinute,ntpSecond);
  Serial.println(dateStr);
  Serial.println(timeStr);
  //-------------------------------------------------------------
}



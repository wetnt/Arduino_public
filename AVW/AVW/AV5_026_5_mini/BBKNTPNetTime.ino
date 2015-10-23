//=============================================================
int Local_Time = +8;
long NTPTime = millis(), NTPTimeKey = 5*1000;
//=============================================================
char timeStr[20], dateStr[20];
int ntpYearss = 2014, ntpMonths = 1, ntpDatess = 1;
int ntpHourss = 0, ntpMinute = 0, ntpSecond = 0, ntpDayweek = 1;
//=============================================================
IPAddress timeServer_IP;
IPAddress timeServerBack(193,92,150,3);
const char* timeServerHost = "time.asia.apple.com";
//-------------------------------------------------------------
const int NTP_PACKET_SIZE = 48;
byte packetBuffer[NTP_PACKET_SIZE];
unsigned long highWord = 0,lowsWord = 0;
const unsigned long seventyYears = 2208988800UL;
unsigned long secondSince1900 = 0,secondsNtpEpoch = 0;
//=============================================================
//=============================================================
void NTP_Setup(){
  //-------------------------------------------------------------
  Serial.print("NTP_Setup......"); 
  if (Dns.getHostByName(timeServerHost, timeServer_IP) != 1 ) {
    timeServer_IP = timeServerBack;
    Serial.println("Error");
  }
  Serial.print("NTP Host: ");Serial.println(timeServer_IP);
  //-------------------------------------------------------------
}
void NTP_Loop(bool bugshow){
  //-------------------------------------------------------------
  if( millis() - NTPTime < NTPTimeKey) return; 
  NTPTime = millis();
  //-------------------------------------------------------------
  NTP_Get(bugshow);
  //-------------------------------------------------------------
}
void NTP_Get(bool bugshow){
  //-------------------------------------------------------------
  NTPTime_Ask(timeServer_IP);
  delay(300);
  NTPTime_Exp();
  NTPTime_Set();
  NTP_Show(bugshow);
  //-------------------------------------------------------------
  Time_SetTime(ntpHourss,ntpMinute,ntpSecond);
  //-------------------------------------------------------------
}
void NTP_Show(bool bugshow){
  //-------------------------------------------------------------
  if(!bugshow) return;
  //-------------------------------------------------------------
  //Serial.print("NTP Time Stamp: ");Serial.println(secondSince1900);
  //Serial.print("Unix Epoch time = ");Serial.println(secondsNtpEpoch);
  //-------------------------------------------------------------
  //  snprintf(dateStr, 22, "NET_Date: %4d-%02d-%02d",  ntpYearss,ntpMonths,ntpDatess);
  //  snprintf(timeStr, 22, "NET_Time: %02d:%02d:%02d", ntpHourss,ntpMinute,ntpSecond);
  //  Serial.println(dateStr);
  //  Serial.println(timeStr);
  //-------------------------------------------------------------
}
//===============================================================
void NTPTime_Ask(IPAddress& address){
  //-------------------------------------------------------------
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  //-------------------------------------------------------------
  packetBuffer[0]  = 0b11100011;
  packetBuffer[1]  = 0;
  packetBuffer[2]  = 6;
  packetBuffer[3]  = 0xEC;
  packetBuffer[12] = 49;
  packetBuffer[13] = 0x4E;
  packetBuffer[14] = 49;
  packetBuffer[15] = 52;
  //-------------------------------------------------------------
  //NTP requests port 123
  Udp.beginPacket(address, 123);
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  Udp.endPacket();
  //-------------------------------------------------------------
}
void NTPTime_Exp(){
  //-------------------------------------------------------------
  if ( !Udp.parsePacket() ) return; 
  //-------------------------------------------------------------
  Udp.read(packetBuffer, NTP_PACKET_SIZE); 
  //-------------------------------------------------------------
  highWord = word(packetBuffer[40], packetBuffer[41]);
  lowsWord = word(packetBuffer[42], packetBuffer[43]);
  secondSince1900 = highWord << 16 | lowsWord;    
  //-------------------------------------------------------------
  secondsNtpEpoch = secondSince1900 - seventyYears;
  secondsNtpEpoch += 1;
  //-------------------------------------------------------------
}
void NTPTime_Set(){
  //-------------------------------------------------------------
  ntpHourss = (secondsNtpEpoch % 86400L) / 3600 + Local_Time;
  if (ntpHourss > 23)
  {
    ntpHourss -= 24;
  }
  ntpMinute = (secondsNtpEpoch % 3600) / 60;
  ntpSecond =  secondsNtpEpoch % 60;
  //-------------------------------------------------------------
}


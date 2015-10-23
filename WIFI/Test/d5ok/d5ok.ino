
//=============================================================
int Local_Time = +8;
long NTPTime = millis(), NTPTimeKey = 5*1000;
//=============================================================
char timeStr[20], dateStr[20];
int ntpYearss = 2014, ntpMonths = 1, ntpDatess = 1;
int ntpHourss = 0, ntpMinute = 0, ntpSecond = 0, ntpDayweek = 1;
//=============================================================
const int NTP_PACKET_SIZE = 48;
byte packetBuffer[NTP_PACKET_SIZE];
unsigned long highWord = 0,lowsWord = 0;
const unsigned long seventyYears = 2208988800UL;
unsigned long secondSince1900 = 0,secondsNtpEpoch = 0;
//=============================================================


void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  delay(1000);

  Serial.println("begin...");
  delay(1000);

  //ATSend("AT+ID", "done");
  //delay(2000);
  ATSend("AT+JoinAP?", "done");
  delay(1000);
  ATSend("AT+ShowIP", "done");
  delay(1000);
  //ATSend("AT+CWMODE=1", "done");
  //delay(2000);

  //ATSend("AT+NewSTA=\"UDP\",\"192.168.1.100\",8080","done");
  ATSend("AT+NewSTA=\"UDP\",\"193.92.150.3\",123", "ALREAY CONNECT");
  //ATSend("AT+NewSTA=\"UDP\",\"129.6.15.28\",123", "ALREAY CONNECT");
  //ATSend("AT+NewSTA=\"UDP\",\"210.72.145.44\",123", "ALREAY CONNECT");
  //ATSend("AT+NewSTA=\"UDP\",\"time.nist.gov\",123", "ALREAY CONNECT");
  delay(2000);
  //ATSend("1", "SEND OK");
  //delay(2000);  
  //ATSend("123456789012345678901234567890123456789012345678", "SEND OK");
  
  pppp();
  ATSend("AT+UpDate=48", ">");
  Serial1.write(packetBuffer, NTP_PACKET_SIZE);
  
  ATSend("AT+UpDate=1", ">");
  ATSend("\r\n", "SEND OK");
  
  delay(2000);  
  NTPTime_Exp();
  NTPTime_Set();
}

void ATSend(String cmd, String back) {
  Serial1.println(cmd);
  Serial.println(cmd);
  waitBack(back);
}

int wbn = 0;
void waitBack(String str) {
  //------------------------
  //bool backkey = false;
  //------------------------
  String data;
  while (1) {
    if (Serial1.available() > 0)
    {
      char a = Serial1.read();
      data = data + a;
      Serial.print(a);
      wbn++;
    }
    if (data.indexOf("busy") != -1)
    {
      Serial.println("=busy");
      break;
    }
    if (data.indexOf("ERROR") != -1)
    {
      Serial.print(str);
      Serial.println("=ERROR");
      break;
    }
    if (data.indexOf(str) != -1)
    {
      Serial.print(str);
      Serial.println("=ok");
      break;
    }
    if (wbn > 500) {
      wbn = 0;
      Serial.println("timeout");
      break;
    }
  }
  //------------------------
}

void NetSend(String x) {
  int n = x.length() + 1;
  String s = String("AT+UpDate=") + String(n);
  ATSend(s, ">"); //delay(1000);
  ATSend(x, "SEND OK");
}

int dn = 0;
void loop() {
  if (Serial1.available() > 0)
  {
    char a = Serial1.read();
    Serial.print(a);
    dn++;
    //-------------------------------------------------------------
    if (dn > 48) {
      dn = 0;
      //NTPTime_Exp();
      //NTPTime_Set();
      //NTPTime_show();
    }
    //-------------------------------------------------------------
  }
  //ppp();
  //delay(5000);
}


void pppp() {
  //-------------------------------------------------------------
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  //-------------------------------------------------------------
  packetBuffer[0]  = 0b11100011;  // LI, Version, Mode
  packetBuffer[1]  = 0;           // Stratum, or type of clock
  packetBuffer[2]  = 6;           // Polling Interval
  packetBuffer[3]  = 0xEC;      // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12] = 49;
  packetBuffer[13] = 0x4E;
  packetBuffer[14] = 49;
  packetBuffer[15] = 52;
  //-------------------------------------------------------------
}




//=============================================================

//===============================================================
void NTPTime_Exp(){
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


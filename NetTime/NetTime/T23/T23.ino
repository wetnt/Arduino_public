// // ESP8266 connection
////http://forum.arduino.cc/index.php?topic=285188.msg2000806

/* Connect ESP8266 as follows
  I used an Arduino 3.3v Pro Mini with a 3.3V USB-FTDI converter
  The ESP8266 was communicating at 9600 when delivered
  Vcc - 3.3v
  gnd - gnd
  rx - pin 11
  tx - pin 10
  ch_PD - pin 6
*/

// Target Access Point
#define ssid         "MMMM"
#define pass         "1234567890123"

unsigned long time = 0;
const int NTP_PACKET_SIZE = 48;
byte packetBuffer[ NTP_PACKET_SIZE];

//=============================================================
#include <SoftwareSeriala.h>
SoftwareSerial myS(10, 11); //rx tx
//=============================================================
char timeStr[20], dateStr[20];
int ntpYearss = 2014, ntpMonths = 1, ntpDatess = 1;
int ntpHourss = 0, ntpMinute = 0, ntpSecond = 0, ntpDayweek = 1;
//=============================================================
unsigned long highWord = 0,lowsWord = 0;
const unsigned long seventyYears = 2208988800UL;
unsigned long secondSince1900 = 0,secondsNtpEpoch = 0;

int Local_Time = +8;
long NTPTime = millis(), NTPTimeKey = 5*1000;
//=============================================================
void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  // set the data rate for the SoftwareSerial port
  myS.begin(9600);
  delay (1000);

  connectWiFi();

  //IPAddress timeServerBack(193,92,150,3);
  //"129.6.15.28"
  ATSend("AT+NewSTA=\"UDP\",\"time.asia.apple.com\",123", "done");
  //ATSend("AT+NewSTA=\"UDP\",\"193.92.150.3\",123", "done");
  //ATSend("AT+NewSTA=\"UDP\",\"129.6.15.28\",123", "done");
  delay(1000);
  ATSend("AT+UpDate=4", ">");
  delay(1000);
  ATSend("1231", "SEND OK");
  delay(1000);

  
  //-------------------------------------------------------------
   snprintf(dateStr, 22, "NET_Date: %4d-%02d-%02d",  ntpYearss,ntpMonths,ntpDatess);
   snprintf(timeStr, 22, "NET_Time: %02d:%02d:%02d", ntpHourss,ntpMinute,ntpSecond);
   Serial.println(dateStr);
   Serial.println(timeStr);
  //-------------------------------------------------------------  
  setPacket();
  NTPTime_Exp();
  NTPTime_Set();
  //-------------------------------------------------------------
   snprintf(dateStr, 22, "NET_Date: %4d-%02d-%02d",  ntpYearss,ntpMonths,ntpDatess);
   snprintf(timeStr, 22, "NET_Time: %02d:%02d:%02d", ntpHourss,ntpMinute,ntpSecond);
   Serial.println(dateStr);
   Serial.println(timeStr);
  //-------------------------------------------------------------
  
}



void connectWiFi() {

  Serial.begin(9600);
  myS.begin(9600);
  delay(1000);
  Serial.println("begin...");
  delay(5000);

  ATSend("AT+ID", "done");
  delay(1000);
  ATSend("AT+JoinAP?", "JoinAP");
  delay(1000);
  ATSend("AT+ShowIP", "done");
  delay(1000);
  //ATSend("AT+NewSTA=\"UDP\",\"192.168.1.100\",8080", "done");
  delay(1000);
  //ATSend("AT+UpDate=10", ">");
  delay(1000);
  //ATSend("boboking123", "SEND OK");
  delay(1000);
}

void ATSend(String cmd, String back) {
  Serial.println(cmd);
  myS.println(cmd);
  waitBack(back, true);
}

void waitBack(String str, bool backkey) {
  //------------------------
  //bool backkey = false;
  if (backkey) {
    Serial.print("wait--");
    Serial.println(str);
  }
  //------------------------
  String data;
  while (1) {
    if (myS.available() > 0)
    {
      char a = myS.read();
      data = data + a;
      if (backkey) {
        Serial.print(a);
      }
    }
    if (data.indexOf(str) != -1)
    {
      if (backkey) {
        Serial.println("_ok");
      }
      break;
    }
    if (data.indexOf("ERROR") != -1)
    {
      if (backkey) {
        Serial.println("_ERROR");
      }
      break;
    }
    //Serial.print(".");
  }
  //------------------------
}

void NetSend(String x) {
  int n = x.length() + 1;
  String s = String("AT+UpDate=") + String(n);
  ATSend(s, ">"); //delay(1000);
  ATSend(x, "SEND OK");
}

void loop() {
  long t = millis();
  String s = String(t);
  //NetSend(s); delay(2000);
  //NetSend("BOBOKing1234567890"); delay(2000);

    if (myS.available())
    Serial.write(myS.read());

}

void setPacket() {
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
  myS.write(packetBuffer, NTP_PACKET_SIZE);
  //-------------------------------------------------------------
}

void NTPTime_Exp(){
  //myS.read(packetBuffer, NTP_PACKET_SIZE);
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

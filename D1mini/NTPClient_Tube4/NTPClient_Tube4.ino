#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
//------------------------------------------
#include <TM1637Display.h>
TM1637Display tube_4(D2, D3); //CLK, DIO
//https://arduino-info.wikispaces.com/Listing_13_1_CountdownLED_Display
//===================================================================
//static const uint8_t LED_BUILTIN = 16;
//static const uint8_t BUILTIN_LED = 16;
//static const uint8_t D0   = 16;
//static const uint8_t D1   = 5;
//static const uint8_t D2   = 4;
//static const uint8_t D3   = 0;
//static const uint8_t D4   = 2;
//static const uint8_t D5   = 14;
//static const uint8_t D6   = 12;
//static const uint8_t D7   = 13;
//static const uint8_t D8   = 15;
//static const uint8_t D9   = 3;
//static const uint8_t D10  = 1;
//===================================================================
//------------------------------------------
//char ssid[] = "MMMM";
//char pass[] = "1234567890123";
//------------------------------------------
char ssid[] = "jtfybatai2.4";
char pass[] = "1234jtfy";
//------------------------------------------
//IPAddress timeServer(129, 6, 15, 28); // time.nist.gov NTP server
IPAddress timeServerIP; // time.nist.gov NTP server address
const int NTP_Port = 123;
const char* ntpServerName = "time.nist.gov";
const int NTP_PACKET_SIZE = 48;
byte packetBuffer[ NTP_PACKET_SIZE];
//------------------------------------------
unsigned int localPort = 2390;
//------------------------------------------
WiFiUDP udp;
//------------------------------------------
//------------------------------------------
void setup() {
  Serial.begin(115200);
  Serial.println();

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("WiFi connected IP address: ");
  Serial.println(WiFi.localIP());

  udp.begin(localPort);
  Serial.print("Starting UDP Local port: ");
  Serial.println(udp.localPort());
  Serial.println();

  tube_4.setBrightness(0x0f);
}

void loop() {

  WiFi.hostByName(ntpServerName, timeServerIP);
  sendNTPpacket(timeServerIP, NTP_Port);
  delay(1000);

  int cb = udp.parsePacket();
  if (!cb) {
    //Serial.println("no packet yet");
  } else {
    //Serial.print("packet received, length=");
    //Serial.println(cb);
    udp.read(packetBuffer, NTP_PACKET_SIZE);
    unsigned long Unix_time = getsNTPTime();
    TimeShow(Unix_time);
    delay(10000);
  }
}
void TimeShow(unsigned long epoch) {
  int th = (epoch % 86400L) / 3600; //86400 equals secs per day
  int tm = (epoch % 3600) / 60;
  int ts = (epoch % 60);

  Serial.print("The UTC time is ");
  Serial.print(th);
  Serial.print(':');
  if (tm < 10) {
    Serial.print('0');
  }
  Serial.print(tm);
  Serial.print(':');
  if (ts < 10 ) {
    Serial.print('0');
  }
  Serial.println(ts);
  //Serial.println();

  int tth = th + 8;
  tth = tth > 23 ? tth - 24 : tth;
  tube_4.showNumberDec(tth * 100 + tm);
}
unsigned long getsNTPTime() {
  unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
  unsigned long lowsWord = word(packetBuffer[42], packetBuffer[43]);
  unsigned long secsSince1900 = highWord << 16 | lowsWord;
  const unsigned long seventyYears = 2208988800UL;
  unsigned long Unix_time = secsSince1900 - seventyYears;
  //Serial.print("1900.07.1 = "); Serial.println(secsSince1900);
  //Serial.print("Unix_time = "); Serial.println(Unix_time);
  return Unix_time;
}

unsigned long sendNTPpacket(IPAddress& address, int ntp_port) {
  //Serial.println("sending NTP packet...");
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

  udp.beginPacket(address, ntp_port); //NTP requests are to port 123
  udp.write(packetBuffer, NTP_PACKET_SIZE);
  udp.endPacket();
}

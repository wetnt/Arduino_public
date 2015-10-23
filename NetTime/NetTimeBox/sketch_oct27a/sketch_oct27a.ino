#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include "Dns.h"
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "DS3231.h"
#include <TinyGPS.h>
 
 
byte mac[] = {  0x00, 0x00, 0xAA, 0xBB, 0xCC, 0xDD};
unsigned int localPort = 80;                                // local port to listen for UDP packets
IPAddress timeServer(193, 92, 150, 3);                 // time.nist.gov NTP server (fallback)
const int NTP_PACKET_SIZE = 48;                                 // NTP time stamp is in the first 48 bytes of the message
byte packetBuffer[ NTP_PACKET_SIZE];                         // buffer to hold incoming and outgoing packets
const char* host = "time.asia.apple.com";                        // Use random servers through DNS
 
EthernetUDP Udp;
DNSClient Dns;
IPAddress rem_add;
TinyGPS gps;
LiquidCrystal_I2C lcd(0x27, 16, 2);
DS3231 clock;
 
bool Century = false, h12 = false, PM = false;
int year;
byte month, date, day, hour, minute, second, temperature, hundredths;
unsigned long age = 0;
char timeStr[17], dateStr[17];
 
void setup()
{
  Wire.begin();
  Serial.begin(9600);
  Serial1.begin(38400);
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
  pinMode(8, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
 
 
  lcd.init();
  lcd.backlight();
  lcd.clear();
 
  if (digitalRead(2) == 0)
  {
    lcd.setCursor(0, 0);
    lcd.print("WAITING DHCP SRV");
    if (Ethernet.begin(mac) == 0) {
      Serial.println("Failed to configure Ethernet using DHCP");
      lcd.setCursor(0, 1);
      lcd.print("DHCP SRV FAILED");
      delay(2000);
      lcd.clear();
      return;
    }
    Udp.begin(localPort);
    Dns.begin(Ethernet.dnsServerIP() );
 
    lcd.setCursor(0, 1);
    lcd.print("NETWORK OK!");
    delay(1000);
    lcd.clear();
    ntpTime();
    clock.setSecond(second);
    clock.setHour(hour);
    clock.setMinute(minute);
    lcd.print("NET TIME SYNC OK!");
    snprintf(timeStr, 17, "NET: %02d:%02d:%02d", hour, minute, second);
    lcd.setCursor(0, 1);
    lcd.print(timeStr);
    delay(2000);
 
    lcd.clear();
  }
  else
  { lcd.setCursor(0, 1);
    lcd.print("NET TIME BYPASS");
    delay(2000);
 
    lcd.clear();
 
  }
 
  if (digitalRead(8) == 0)
  {
    int timeout = 0;
    lcd.setCursor(0, 0);
    lcd.print("GPS TIME SYNC..");
    do
    {
      timeout += 1;
      smartdelay(250);
      gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age );
    }
    while (age == TinyGPS::GPS_INVALID_AGE);
    if (age != TinyGPS::GPS_INVALID_AGE)
    {
      hour+=8;
      if (hour > 23)
      {
        hour -= 24;
      }
      delay(400);
      second+=1;
      clock.setSecond(second);
      clock.setHour(hour);
      clock.setMinute(minute);
      lcd.setCursor(0, 0);
      lcd.print("GPS TIME OK!   ");
      snprintf(timeStr, 17, "GPS: %02d:%02d:%02d", hour, minute, second);
      lcd.setCursor(0, 1);
      lcd.print(timeStr);
      delay(2000);
      lcd.clear();
    }
    else
    {
      lcd.setCursor(0, 0);
      lcd.print("GPS TIME FAILED");
      delay(2000);
      lcd.clear();
    }
 
  }
  else
  {
    lcd.setCursor(0, 1);
    lcd.print("GPS TIME BYPASS");
    delay(2000);
 
    lcd.clear();
 
  }
}
 
void loop()
{
 
  hour = clock.getHour(h12, PM);
  minute = clock.getMinute();
  second = clock.getSecond();
 
  snprintf(timeStr, 17, "DS3231: %02d:%02d:%02d", hour, minute, second);
  //  snprintf(dateStr,8,"%4d-%02d-%02d",year,month,date);
  lcd.setCursor(0, 0);
  lcd.print(timeStr);
  delay(50);
 
}
 
void ntpTime()
{
  if (Dns.getHostByName(host, rem_add) == 1 ) {
    Serial.print("DNS resolve : ");
    Serial.print(host);
    Serial.print("  = ");
    Serial.print(rem_add);
    sendNTPpacket(rem_add);
  } else {
    Serial.print("DNS fail...");
    Serial.print("time.nist.gov = ");
    Serial.print(timeServer);        // fallback
    sendNTPpacket(timeServer);         // send an NTP packet to a time server
  }
  delay(300);        // wait to see if a reply is available
  if ( Udp.parsePacket() ) {
    // We've received a packet, read the data from it
    Udp.read(packetBuffer, NTP_PACKET_SIZE);         // read the packet into the buffer
 
    //the timestamp starts at byte 40 of the received packet and is four bytes,
    // or two words, long. First, esxtract the two words:
 
    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
    // combine the four bytes (two words) into a long integer
    // this is NTP time (seconds since Jan 1 1900):
    unsigned long secsSince1900 = highWord << 16 | lowWord;
    Serial.print("  NTP Time Stamp: ");
    Serial.print(secsSince1900);
    // now convert NTP time into everyday time:
    Serial.print("      Unix Epoch time = ");
    // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
    const unsigned long seventyYears = 2208988800UL;
    // subtract seventy years:
    delay(200);
    unsigned long epoch = secsSince1900 - seventyYears;
    epoch += 1;
    // print Unix time:
    Serial.print(epoch);
    Serial.print("   ");
 
    // print the hour, minute and second: local time +8:00
    hour = (epoch % 86400L) / 3600 + 8;
    if (hour > 23)
    {
      hour -= 24;
    }
    minute = (epoch % 3600) / 60;
    second = epoch % 60;
  }
}
 
// send an NTP request to the time server at the given address
unsigned long sendNTPpacket(IPAddress& address)
{
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;          // LI, Version, Mode
  packetBuffer[1] = 0;           // Stratum, or type of clock
  packetBuffer[2] = 6;           // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]        = 49;
  packetBuffer[13]        = 0x4E;
  packetBuffer[14]        = 49;
  packetBuffer[15]        = 52;
 
  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
 
  Udp.beginPacket(address, 123); //NTP requests are to port 123
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  Udp.endPacket();
}
 
static void smartdelay(unsigned long ms)
{
  unsigned long start = millis();
  do
  {
    while (Serial1.available())
      gps.encode(Serial1.read());
  } while (millis() - start < ms);
}


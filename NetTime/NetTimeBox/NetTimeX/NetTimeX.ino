#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUDP.h>

#define SECONDS_IN_DAY          86400
#define START_YEAR              1900
#define TIME_ZONE               +1
static int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

static byte mymac[] = {0x00,0x1A,0x4B,0x38,0x0C,0x5C};
//byte Ethernet::buffer[700];

EthernetUDP Udp;

static byte ntpServer[] = {193,204,114,232};
static byte srcPort = 0;

uint32_t timeStamp;
boolean requestSent;

#define INTERVAL                10000
unsigned long lastTime = 0;


// A UDP instance to let us send and receive packets over UDP
EthernetUDP Udp;
 
// send an NTP request to the time server at the given address 
void sendNTPpacket(IPAddress& address)
{
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE); 
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0xe3;  // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49; 
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;
 
  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:   
  Udp.beginPacket(address, 123); //NTP requests are to port 123
  Udp.write(packetBuffer,NTP_PACKET_SIZE);
  Udp.endPacket(); 
}

void setup () {
 
  Serial.begin(9600);
  Serial.println("NTP Demo");
 
  if (!Ethernet.begin(mymac))
    Serial.println( "Failed to access Ethernet controller");
 else
   Serial.println("Ethernet controller initialized");
 
  Serial.println();
  
  Udp.begin(localPort);
  requestSent = false;
}
 
void loop() {
 

  
  if(requestSent && ether.ntpProcessAnswer(&timeStamp, srcPort)) {
    Serial.println("NTP answer received");
    Serial.println();
    Serial.print("Timestamp: ");
    Serial.println(timeStamp);
    Serial.println();
    printDate(timeStamp + 3600 * TIME_ZONE);
    requestSent = false;
  }
  
  unsigned long time = millis();
  if(time - lastTime > INTERVAL) {
    lastTime = time;
    ether.ntpRequest(ntpServer, srcPort);
    Serial.println("NTP request sent");
    requestSent = true;
  }
}

void printDate(uint32_t timeStamp) {
  
  unsigned int year = START_YEAR;
  while(1) {
    uint32_t seconds;
    if(isLeapYear(year)) seconds = SECONDS_IN_DAY * 366;
    else seconds = SECONDS_IN_DAY * 365;
    if(timeStamp >= seconds) {
      timeStamp -= seconds;
      year++;
    } else break;
  }
  
  unsigned int month = 0;
  while(1) {    
    uint32_t seconds = SECONDS_IN_DAY * days_in_month[month];
    if(isLeapYear(year) && month == 1) seconds = SECONDS_IN_DAY * 29;
    if(timeStamp >= seconds) {
      timeStamp -= seconds;
      month++;
    } else break;
  }  
  month++;
  
  unsigned int day = 1;
  while(1) {
    if(timeStamp >= SECONDS_IN_DAY) {
      timeStamp -= SECONDS_IN_DAY;
      day++;
    } else break;
  }  

  unsigned int hour = timeStamp / 3600;
  unsigned int minute = (timeStamp - (uint32_t)hour * 3600) / 60;
  unsigned int second = (timeStamp - (uint32_t)hour * 3600) - minute * 60;
  
  Serial.println("Current date and time:");

  if(day < 10) Serial.print("0");
  Serial.print(day);
  Serial.print("/");
  
  if(month < 10) Serial.print("0");
  Serial.print(month);
  Serial.print("/");  
  
  Serial.println(year);
  
  if(hour < 10) Serial.print("0");
  Serial.print(hour);
  Serial.print(":");
  
  if(minute < 10) Serial.print("0");
  Serial.print(minute);
  Serial.print(":");
  
  if(second < 10) Serial.print("0");
  Serial.println(second);
  
  Serial.println();
}

boolean isLeapYear(unsigned int year) {
  
  return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}


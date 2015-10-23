#include <Ethernet.h>

int second,minute,hour; 
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
unsigned int localPort = 8888;
IPAddress timeServer(132,163,4,101);
const int NTP_PACKET_SIZE= 48; 
byte packetBuffer[ NTP_PACKET_SIZE]; 
EthernetUDP Udp;
unsigned char xitong[]={
  0xCF, 0xB5,
  0xCD, 0xB3,
  0xB3, 0xF5,
  0xCA, 0xBC,
  0xBB, 0xAF
};                    //系统初始化
unsigned char shijian[]={
  0xB1, 0xB1,
  0xBE, 0xA9,
  0xCA, 0xB1,
  0xBC, 0xE4
};                    //北京时间
void setup() 
{
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    for(;;)
      ;
  }
  Udp.begin(localPort);
}

void loop()
{
  sendNTPpacket(timeServer); 
  delay(1000);  
  if ( Udp.parsePacket() ) {  

    Udp.read(packetBuffer,NTP_PACKET_SIZE);  

    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);  

    unsigned long secsSince1900 = highWord << 16 | lowWord;  
    Serial.print("Seconds since Jan 1 1900 = " );
    Serial.println(secsSince1900); 

    Serial.print("Unix time = ");

    const unsigned long seventyYears = 2208988800UL;     

    unsigned long epoch = secsSince1900 - seventyYears;  

    Serial.println(epoch);      

    Serial.print("beijing time is "); 
    if((epoch % 86400L) / 3600+8>=24) 
    {
      Serial.print((epoch % 86400L) / 3600+8-24);
    }
    if((epoch % 86400L) / 3600+8<24)
    {                   
      Serial.print((epoch % 86400L) / 3600+8); 
      hour=(epoch % 86400L) / 3600+8;
    }
    Serial.print(':');  
    if ( ((epoch % 3600) / 60) < 10 ) {
      Serial.print('0');
    }
    Serial.print((epoch  % 3600) / 60); 
    minute=(epoch  % 3600) / 60;

    Serial.print(':'); 
    if ( (epoch % 60) < 10 )
    {
      Serial.print('0');
    }
    Serial.println(epoch); 
    second=epoch;
  }
  shijianx();

}


unsigned long sendNTPpacket(IPAddress& address)
{

  memset(packetBuffer, 0, NTP_PACKET_SIZE); 

  packetBuffer[0] = 0b11100011;   
  packetBuffer[1] = 0;     
  packetBuffer[2] = 6;     
  packetBuffer[3] = 0xEC;  

  packetBuffer[12]  = 49; 
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;

  Udp.beginPacket(address, 123); 
  Udp.write(packetBuffer,NTP_PACKET_SIZE);
  Udp.endPacket(); 
}

void shijianx()
{
}


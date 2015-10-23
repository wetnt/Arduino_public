//http://www.ocrobot.com/doku.php?id=zh:ocrobot:modules:seed:at
void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  delay(1000);

  Serial.println("begin...");
  delay(1000);

  ATSend("AT", "OK");
  delay(2000);
  ATSend("AT+GMR", "OK");
  delay(2000);
  ATSend("AT+RST", "ready");
  delay(2000);
  ATSend("AT+CWMODE?", "OK");
  delay(2000);
  ATSend("AT+CWJAP?", "OK");
  delay(2000);
//  ATSend("AT+CWSAP?", "OK");
//  delay(2000);
//  ATSend("AT+CWLIF", "OK");
//  delay(2000);
//  ATSend("AT+CIPSTATUS", "OK");
//  delay(2000);


 long tx = GetTime();
 Serial.println("----------");
 Serial.println(tx, DEC);


//  ATSend("AT+CIPSTART=\"TCP\",\"www.baidu.com\",80", "CONNECT");
//  delay(2000);
//  ATSend("AT+CIPMODE=1", "OK");
//  delay(2000);
//  ATSend("AT+CIPSEND", ">");
//  delay(2000);
//  Serial1.println("GET / HTTP/1.1 \r\nHost: www.baidu.com \r\nUser-Agent: abc \r\nConnection: close \r\n\r\n");
//  Serial1.println(0x1a, HEX);
  //delay(1000);
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
  String s = String("AT+CIPSEND=0,") + String(n);
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




//http://forum.arduino.cc/index.php?topic=285188.15

const int NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of the message
byte packetBuffer[ NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets

unsigned long GetTime()
{
  String cmd = "AT+CIPSTART=\"UDP\",\"193.92.150.3\",123"; // my own NTP server, synced by GPS
  Serial1.println(cmd);
  delay(2000);
  if (Serial1.find("Error")) {
    Serial.print("RECEIVED: Error");
    return 0;
  }

  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision

  Serial1.print("AT+CIPSEND=");
  Serial1.println(NTP_PACKET_SIZE);
  if (Serial1.find(">"))
  {
    for (byte i = 0; i < NTP_PACKET_SIZE; i++)
    {
      Serial1.write(packetBuffer[i]);
      delay(5);
    }
  } else {
    Serial1.println("AT+CIPCLOSE");
    return 0;
  }

  //Serial1.find("+IPD,48:");

  int acksize = NTP_PACKET_SIZE + 1 + 2 + 8; // ESP8266 adds a space, a CRLF and starts with "+IPD,48:"

  Serial.println("ESP2866 ACK : ");
  for (byte i = 0; i < acksize; i++)
  {
    while (Serial1.available() == 0) // you may have to wait for some bytes
    {
      //Serial.print(".");
    }
    byte ch = Serial1.read();
    if (ch < 0x10) Serial.print('0');
    Serial.print(ch, HEX);
    Serial.print(' ');
    if ( (((i + 1) % 15) == 0) ) {
      Serial.println();
    }
  }
  Serial.println();
  Serial.println();

  memset(packetBuffer, 0, NTP_PACKET_SIZE);

  Serial.println("Server answer : ");

  int i = 0;
  while (Serial1.available() > 0) {
    byte ch = Serial1.read();
    if (i <= NTP_PACKET_SIZE)
    {
      packetBuffer[i] = ch;
    }
    if (ch < 0x10) Serial.print('0');
    Serial.print(ch, HEX);
    Serial.print(' ');
    if ( (((i + 1) % 15) == 0) ) {
      Serial.println();
    }
    delay(5);
    i++;
    if ( ( i < NTP_PACKET_SIZE ) && ( Serial1.available() == 0 ) )
    {
      while (Serial1.available() == 0)  // you may have to wait for some bytes
      {
        Serial.print("!");
      }
    }
  }

  Serial.println();
  Serial.println();
  Serial.print(i + 1);
  Serial.println(" bytes received"); // will be more than 48
  Serial.print(packetBuffer[40], HEX);  Serial.print(" ");
  Serial.print(packetBuffer[41], HEX);  Serial.print(" ");
  Serial.print(packetBuffer[42], HEX);  Serial.print(" ");
  Serial.print(packetBuffer[43], HEX);  Serial.print(" = ");

  unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
  unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
  // combine the four bytes (two words) into a long integer
  // this is NTP time (seconds since Jan 1 1900):
  unsigned long secsSince1900 = highWord << 16 | lowWord;

  Serial.print(secsSince1900, DEC);
  // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
  const unsigned long seventyYears  = 2208988800UL;
  // subtract seventy years:
  unsigned long epoch = secsSince1900 - seventyYears;
  unsigned long DST = 60 * 60 * 2; // adjust to your GMT+DST
  unsigned long timestamp = epoch + DST;

  Serial.println();
  Serial.print("Epoch : ");
  Serial.println(epoch, DEC);

  return timestamp;
}


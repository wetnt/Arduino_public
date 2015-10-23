
void setup() {
  
  Serial.begin(9600);
  Serial1.begin(9600);
  delay(1000);
  Serial.println("begin...");
  delay(1000);

  //NetInit();
  NetATStart();

  ATSend("AT+CIPSTART=\"TCP\",\"www.bbkgps.com\",80", "Linked", "CONNECT", 20, true); loopSerial1(); delay(100); loopSerial1();
  //ATSend("AT+CIPSEND=90", ">", "", 20, true); loopSerial1(); delay(1000); loopSerial1();
  //Serial1.println("GET /time.php HTTP/1.1 \r\nHost: www.bbkgps.com \r\nUser-Agent: abc \r\nConnection: close \r\n\r\n");
  String cmd = "GET /time.php HTTP/1.1 \r\nHost: www.bbkgps.com \r\nUser-Agent: abc \r\nConnection: close \r\n\r\n";
  NetSend(cmd); 
  //ATSend(cmd, "CLOSED", "", 10, true); loopSerial1(); 
  
}

void loop() {
  if (Serial.available() > 0)
  {
    char a = Serial.read();
    Serial1.print(a);
  }
  if (Serial1.available() > 0)
  {
    char a = Serial1.read();
    Serial.print(a);
  }
}

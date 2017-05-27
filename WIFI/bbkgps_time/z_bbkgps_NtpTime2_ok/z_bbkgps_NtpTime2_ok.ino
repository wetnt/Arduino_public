//http://www.ocrobot.com/doku.php?id=zh:ocrobot:modules:seed:at
//http://www.geek-workshop.com/forum.php?mod=viewthread&tid=12492&highlight=8266
void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  delay(1000);

  Serial.println("begin...");
  delay(1000);

boolean key = true;
  // ATSend( String cmd, String backA, String backB,int TimeOutSecond,boolean backKey) {

  Serial.println("+++");delay(200);
  ATSend("AT", "OK", "", 10, key);  delay(200);
  ATSend("AT+CWMODE=1", "OK", "no change", 10, key); delay(200);
  //ATSend("AT+RST", "ready", "invalid", 20, key);  delay(200);
  //ATSend("AT+CWJAP=\"MMMM\",\"1234567890123\"", "OK", "", 10, key);  delay(200);
  ATSend("AT+CWJAP=\"jtwx1\",\"jtwx1234\"", "OK", "", 10, key);  delay(200);
  ATSend("AT+CWJAP?", "OK", "", 10, key);  delay(200);
  ATSend("AT+CIFSR", "OK", "", 10, key);  delay(200);
  ATSend("AT+CIPSTART=\"TCP\",\"www.bbkgps.com\",80", "Linked", "", 20, key); delay(200);
  //ATSend("AT+CIPSTART=\"TCP\",\"www.baidu.com\",80", "Linked", "",10, key); delay(200);
  ATSend("AT+CIPMODE=1", "OK", "", 20, key); delay(200);
  //ATSend("AT+CIPMUX=1", "OK", "builded", 20, key); delay(200);
  ATSend("AT+CIPSEND", "OK", "", 20, true); delay(20);

  //  Serial1.println("GET / HTTP/1.1 \r\nHost: www.bbkgps.com \r\nUser-Agent: abc \r\nConnection: close \r\n\r\n");
  //  Serial1.println("");

//  ATSend("GET /time.php HTTP/1.1", "", "", 10, key); delay(20);
//  ATSend("Host:www.bbkgps.com", "", "", 10, key); delay(20);
//  //ATSend("Host:www.baidu.com", "", "", 10, key); delay(20);
//  ATSend("User-Agent:abc", "", "", 10, key); delay(20);
//  ATSend("Connection:close", "", "", 10, key); delay(20);
//  ATSend("", "", "", 10, key); delay(20);

  Serial1.println("GET /time.php HTTP/1.1"); delay(20);
  Serial1.println("Host:www.bbkgps.com"); delay(20);
  //ATSend("Host:www.baidu.com", "", "", 10, key); delay(20);
  Serial1.println("User-Agent:abc"); delay(20);
  Serial1.println("Connection:close"); delay(20);
  Serial1.println(""); delay(20);

  //NetWaitBack(String strA, String strB,int TimeOutSecond,boolean backKey) {
// String bk = NetWaitBack("2015", "", 100, true);
//  Serial.println("-----------------");
//  Serial.println(bk);
//  Serial.println("-----------------");

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

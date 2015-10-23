//https://www.zybuluo.com/kfihihc/note/31135

String ssid = "MMMM";
String pass = "1234567890123";
boolean backKey = false;

String testAT = "AT";
String jionAP = "AT+CWJAP=\"" + ssid + "\",\"" + pass + "\"";
String seesAP = "AT+CWJAP?";
String seesIP = "AT+CIFSR";
String reStar = "AT+RST";
String beWiFi = "AT+CWMODE=1";

//=====================================================
String netLink = "AT+CIPSTART=\"TCP\",\"www.bbkgps.com\",80";
String cmdHttp = "GET /t.php HTTP/1.1 \r\nHost: www.bbkgps.com \r\nUser-Agent: abc \r\nConnection: close \r\n\r\n";
//String netLink = "AT+CIPSTART=\"TCP\",\"www.baidu.com\",80";
//String cmdHttp = "GET / HTTP/1.0\r\n\r\n";

void netStart() {
  gas.println(testAT); smartDelay(2000);
  gas.println(seesAP); smartDelay(2000);
  gas.println(seesIP); smartDelay(2000);
  gas.println(beWiFi); smartDelay(2000);

  //NetLoop();
}
void NetLoop() {
  gas.println(netLink); smartDelay(4000);
  NetSend(cmdHttp); smartDelay(4000);
}
void NetSend(String x) {
  int n = x.length() + 2;
  String s = String("AT+CIPSEND=") + String(n);
  gas.println(s);
  smartDelay(5000);
  gas.println(x);
}

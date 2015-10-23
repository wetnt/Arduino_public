//https://www.zybuluo.com/kfihihc/note/31135
//=====================================================
char ssid[5] = "MMMM";
char pass[14] = "1234567890123";
boolean backKey = false;
//=====================================================
char testAT[3] = "AT";
char reStar[7] = "AT+RST";
char seesAP[10] = "AT+CWJAP?";
char seesIP[9] = "AT+CIFSR";
char beWiFi[12] = "AT+CWMODE=1";
String jionAP = "AT+CWJAP=\"" + String(ssid) + "\",\"" + String(pass) + "\"";
//=====================================================
char netLink[38] = "AT+CIPSTART=\"TCP\",\"www.bbkgps.com\",80";
char cmdHttp[86] = "GET /t.php HTTP/1.1 \r\nHost: www.bbkgps.com \r\nUser-Agent: abc \r\nConnection: close \r\n\r\n";
//char netLinks[38] = "AT+CIPSTART=\"TCP\",\"www.baidu.com\",80";
//char cmdHttps[20] = "GET / HTTP/1.0\r\n\r\n";

void netStart() {
  //gas.println(testAT); smartDelay(2000);
  //gas.println(seesAP); smartDelay(2000);
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

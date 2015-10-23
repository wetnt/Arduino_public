//=========================================================================
//https://www.zybuluo.com/kfihihc/note/31135
//=========================================================================
String ssid = "MMMM";
String pass = "1234567890123";
boolean backKey = false;
//-------------------------------------------------------------------------
String testAT = "AT";
String jionAP = "AT+CWJAP=\"" + ssid + "\",\"" + pass + "\"";
String seesAP = "AT+CWJAP?";
String seesIP = "AT+CIFSR";
String reStar = "AT+RST";
String beWiFi = "AT+CWMODE=1";
//-------------------------------------------------------------------------
String prSend = "AT+CIPSEND=";
//-------------------------------------------------------------------------
String netLink = "AT+CIPSTART=\"TCP\",\"www.baidu.com\",80";
String cmdHttp = "GET / HTTP/1.0\r\n\r\n";
//=========================================================================
void netStart() {
  gas.println(testAT); smartDelay(2000);
  gas.println(seesAP); smartDelay(2000);
  gas.println(seesIP); smartDelay(2000);
  gas.println(beWiFi); smartDelay(2000);
}
void netJoinAP(String s,String p) {
  jionAP = "AT+CWJAP=\"" + s + "\",\"" + p + "\"";
  gas.println(jionAP); smartDelay(2000);
}
//-------------------------------------------------------------------------
void HttpGetPost(String link,String text,int seconds) {
  int n = text.length() + 2;
  gas.println(link); smartDelay(4000);
  gas.println(prSend + String(n));  smartDelay(1000);
  gas.println(text);                smartDelay(seconds*1000);
}
//-------------------------------------------------------------------------
void NetLinkTestBaidu() {
  HttpGetPost(netLink,cmdHttp,5); smartDelay(10000);
}
//-------------------------------------------------------------------------

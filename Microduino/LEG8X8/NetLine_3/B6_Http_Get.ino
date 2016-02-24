static String BBKGPS_Link = "AT+CIPSTART=\"TCP\",\"www.bbkgps.com\",80";
void WeatherHttpGet() {
  String s = "";
  s += "GET http://www.bbkgps.com/t.txt HTTP/1.1\r\n";
  s += "Host: www.bbkgps.com\r\n";
  s += "Connection: keep-alive\r\n";
  s += "Cache-Control: max-age=0\r\n";
  s += "Accept: text/html;\r\n";
  s += "User-Agent: Mozilla/5.0\r\n";

  HttpGetPost(BBKGPS_Link,s,5);
}


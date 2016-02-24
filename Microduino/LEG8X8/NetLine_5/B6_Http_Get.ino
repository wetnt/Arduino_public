//static String BBKGPS_Link = "AT+CIPSTART=\"TCP\",\"www.bbkgps.com\",80";
void WeatherHttpGet() {
//  String s = "";
//  s += "GET http://www.bbkgps.com/t.txt HTTP/1.1\r\n";
//  s += "Host: www.bbkgps.com\r\n";
//  s += "Connection: keep-alive\r\n";
//  s += "Cache-Control: max-age=0\r\n";
//  s += "Accept: text/html;\r\n";
//  s += "User-Agent: Mozilla/5.0\r\n";

  HttpGetPost(
    F("AT+CIPSTART=\"TCP\",\"www.bbkgps.com\",80"),
    F("GET http://www.bbkgps.com/t.txt HTTP/1.1\r\nHost: www.bbkgps.com\r\nConnection: keep-alive\r\nCache-Control: max-age=0\r\nAccept: text/html;\r\nUser-Agent: Mozilla/5.0\r\n"),
    3);
}


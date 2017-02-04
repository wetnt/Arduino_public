//===================================================================
void gsm_init() {
  //------------------------------------------
  ss.println(F("AT"       )); smartDelay(1000);
  ss.println(F("AT+CSQ"   )); smartDelay(1000);//信号质量
  ss.println(F("AT+CREG?" )); smartDelay(1000);//网络注册
  ss.println(F("AT+CGATT?")); smartDelay(1000);//GPRS网络
  ss.println(F("AT+CSTT"  )); smartDelay(1000);//设置APN
  ss.println(F("AT+CIICR" )); smartDelay(1000);//激活移动场景
  ss.println(F("AT+CIFSR" )); smartDelay(1000);//本机IP地址
  //------------------------------------------
  ss.println(F("AT+CGPSPWR=0")); smartDelay(1000);//关闭GPS模块
  //------------------------------------------
  ss.println(F("AT+SAPBR=3,1,\"CONTYPR\",\"GPRS\""  )); smartDelay(1 * 1000);
  ss.println(F("AT+SAPBR=3,1,\"APN\",\"CMNET\""     )); smartDelay(1 * 1000);
  ss.println(F("AT+SAPBR=1,1"                       )); smartDelay(1 * 1000);
  //------------------------------------------
  ss.println(F("AT+HTTPINIT"                        )); smartDelay(1 * 1000);
  ss.println(F("AT+HTTPPARA=\"CID\",1"              )); smartDelay(1 * 1000);
  ss.println(F("AT+CIPSTART=\"TCP\",\"112.124.186.245\",80")); smartDelay(5*1000);//建立连接
  ss.println(F("AT+HTTPPARA=\"URL\",\"http://www.bbkgps.com/t.php\"")); smartDelay(1 * 1000); //
  ss.println(F("AT+HTTPACTION=0")); smartDelay(10 * 1000); //激活HTTP请求,0Get,1Post,2head//+HTTPACTION:0,200,16
  ss.println(F("AT+HTTPREAD")); smartDelay(3 * 1000);
  //------------------------------------------  
}
void gsm_get_url(String str) {
  ss.print(F("AT+HTTPPARA=\"URL\",\"http://"));
  ss.print(str);
  ss.println("\"");smartDelay(1 * 1000);
  ss.println(F("AT+HTTPACTION=0")); smartDelay(10 * 1000); //激活HTTP请求,0Get,1Post,2head//+HTTPACTION:0,200,16
  ss.println(F("AT+HTTPREAD")); smartDelay(3 * 1000);
}
//===================================================================

String netLinkLewei = "AT+CIPSTART=\"TCP\",\"www.lewei50.com\",80";
String userkeyLewei = "4a7c908d0de946de96e041dd84834154";
String cmdHttpLewei = "";
String valuessLewei = "";

void GetLeweiString(String Gate, String ValueStr) {
  int n = ValueStr.length();
  cmdHttpLewei = "";
  cmdHttpLewei += "POST http://www.lewei50.com/api/V1/gateway/UpdateSensors/"+Gate+" HTTP/1.1\r\n";
  cmdHttpLewei += "userkey: "+userkeyLewei+"\r\n";
  cmdHttpLewei += "Host: www.lewei50.com\r\n";
  cmdHttpLewei += "Content-Length: "+String(n)+"\r\n";
  cmdHttpLewei += "Expect: 100-continue\r\n";
  cmdHttpLewei += "Connection: Keep-Alive\r\n";
  cmdHttpLewei += "\r\n";
  cmdHttpLewei += "[{\"Name\":\"WD\",\"Value\":\"" + String(n) + "\"}]";
  //cmdHttpLewei += ValueStr;
  cmdHttpLewei += "\r\n";
  //Serial.println(cmdHttpLewei);
}

void GetLeweiValue(float tp){  
  //valuessLewei = "[{\"Name\":\"WD\",\"Value\":\"" + String((int)tp) + "\"}]";
  valuessLewei = "[{\"Name\":\"WD\",\"Value\":\"50\"}]";
}

void Lewei_Loop() {
  gas.println(netLinkLewei); smartDelay(5000);
  //GetLeweiValue(dhtH);
  GetLeweiString("02",valuessLewei);
  NetSend(cmdHttpLewei); smartDelay(4000);
}

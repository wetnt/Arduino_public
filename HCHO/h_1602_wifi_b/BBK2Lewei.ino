String netLinkLewei = "AT+CIPSTART=\"TCP\",\"www.lewei50.com\",80";
//String userkeyLewei = "4a7c908d0de946de96e041dd84834154";
String cmdHttpLewei = "";
//String valuessLewei = "";

void GetLeweiString(String Gate,String Val) {
  //int inx =95;
  cmdHttpLewei = "";
  cmdHttpLewei += "POST http://www.lewei50.com/api/V1/gateway/UpdateSensors/"+String(Gate)+" HTTP/1.1\r\n";
  cmdHttpLewei += "userkey: 4a7c908d0de946de96e041dd84834154\r\n";
  cmdHttpLewei += "Host: www.lewei50.com\r\n";
  cmdHttpLewei += "Content-Length: 28\r\n";
  //cmdHttpLewei += "Expect: 100-continue\r\n";
  //cmdHttpLewei += "Connection: Keep-Alive\r\n";
  cmdHttpLewei += "\r\n";
  cmdHttpLewei += "[{\"Name\":\"JQ\",\"Value\":\""+String(Val)+"\"}]";
  cmdHttpLewei += "\r\n";
}

void Lewei_Loop() {
  gas.println(netLinkLewei); smartDelay(5000);
  //GetLeweiValue(dhtH);
  GetLeweiString("02",String(fHCHO));
  NetSend(cmdHttpLewei); smartDelay(5000);
}

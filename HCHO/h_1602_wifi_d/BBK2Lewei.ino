char netLinkLewei[39] = "AT+CIPSTART=\"TCP\",\"www.lewei50.com\",80";
char cmdHttpLeweiA[190] = "POST http://www.lewei50.com/api/V1/gateway/UpdateSensors/02  HTTP/1.1\r\nuserkey: 4a7c908d0de946de96e041dd84834154\r\nHost: www.lewei50.com\r\nContent-Length: 28\r\n\r\n[{\"Name\":\"JQ\",\"Value\":\"22\"}]\r\n";
void Lewei_Loop() {
  //GetLeweiString("02", String(fHCHO));
  HttpGetPost(netLinkLewei, cmdHttpLeweiA,  5);
}

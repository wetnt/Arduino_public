char netLinkLewei[39] = "AT+CIPSTART=\"TCP\",\"www.lewei50.com\",80";
char userkeyLewei[33] = "4a7c908d0de946de96e041dd84834154";
char cmdHttpLeweiA[58] = "POST http://www.lewei50.com/api/V1/gateway/UpdateSensors/";
char cmdHttpLeweiB[12] = " HTTP/1.1\r\n";
char cmdHttpLeweiC[44] = "userkey: 4a7c908d0de946de96e041dd84834154\r\n";
char cmdHttpLeweiD[24] = "Host: www.lewei50.com\r\n";
char cmdHttpLeweiG[21] = "Content-Length: 28\r\n";
char cmdHttpLeweiH[3] = "\r\n";
char cmdHttpLeweiJA[24] = "[{\"Name\":\"JQ\",\"Value\":\"";
char cmdHttpLeweiJB[4] = "\"}]";
char cmdHttpLeweiK[3] = "\r\n";

void Lewei_Loop() {
  //GetLeweiString("02", String(fHCHO));
  HttpGetPost(netLinkLewei,
              cmdHttpLeweiA + String("02") + cmdHttpLeweiB +
              cmdHttpLeweiC + cmdHttpLeweiD + cmdHttpLeweiG + cmdHttpLeweiH +
              cmdHttpLeweiJA +  String("23") + cmdHttpLeweiJB,  5);
}

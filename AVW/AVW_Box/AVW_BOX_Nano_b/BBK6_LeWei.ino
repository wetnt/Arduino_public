void Lewei_Loop() {
  //-----------------------------------------------------------------------------------
  String x =
    String(F("[")) +
    //String(F("{\"Name\":\"WD\",\"Value\":\"")) + String(dhtH) + String(F("\"}")) +
    String(F(",")) +
    //String(F("{\"Name\":\"JQ\",\"Value\":\"")) + String(fHCHO) + String(F("\"}")) +
    String(F("]")) +
    String(F("\r\n"));
  lg(x);
  //-----------------------------------------------------------------------------------
  HttpGetPost(
    String(F("AT+CIPSTART=\"TCP\",\"www.lewei50.com\",80")),
    String(F("POST http://www.lewei50.com/api/V1/gateway/UpdateSensors/02 HTTP/1.1\r\n")) +
    String(F("userkey: 4a7c908d0de946de96e041dd84834154\r\n")) +
    String(F("Host: www.lewei50.com\r\n")) +
    String(F("Content-Length: 58\r\n")) +
    String(F("\r\n")) + x + String(F("\r\n")),
    //-----------------------------------------------------------------------------------
    5
  );
}

void SerialShow(){
  //---------------------------------------------------
  Serial.println("----");
  //-------------------------
  Serial.println(tDate);
  Serial.println(sLats);
  Serial.println(sLons);
  //-------------------------
  Serial.print(sHigh);
  Serial.print(" ");
  Serial.print(sSped);
  Serial.print(" ");
  Serial.print(sFans);
  Serial.println();
  //-------------------------
  Serial.print(cLock);
  Serial.print(" ");
  Serial.print(cType);
  Serial.print(" ");
  Serial.print(sGpsn);
  Serial.print(" ");
  Serial.print(sRads);
  Serial.print(" ");
  Serial.print(sSeal);
  Serial.println();
  //---------------------------------------------------
}

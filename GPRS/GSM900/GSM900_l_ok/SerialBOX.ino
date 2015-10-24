void SerialShow(){
  //---------------------------------------------------
  Serial.println("----");
  //-------------------------
  Serial.println(tDate);
  Serial.println(sLats);
  Serial.println(sLons);
  //-------------------------
  Serial.print(" h=");
  Serial.print(sHigh);
  Serial.print(" s=");
  Serial.print(sSped);
  Serial.print(" f=");
  Serial.print(sFans);
  Serial.println();
  //-------------------------
  Serial.print(" y=");
  Serial.print(cLock);
  Serial.print(" t=");
  Serial.print(cType);
  Serial.print(" s=");
  Serial.print(sGpsn);
  Serial.print(" r=");
  Serial.print(sRads);
  Serial.print(" e=");
  Serial.print(sSeal);
  Serial.println();
  //---------------------------------------------------
}

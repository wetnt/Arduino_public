void LcdIntShow(){
  myGLCD.InitLCD(50);
  //----------------------------------------------
  myGLCD.clrScr();
  myGLCD.setFont(SmallFont);
  myGLCD.print("GPS Read Start", CENTER, 14); 
  myGLCD.print("(C)2013 by", CENTER, 36);
  myGLCD.print("BOBOKing.COM", CENTER, 42);
  myGLCD.update();
  //----------------------------------------------
  delay(1000); 
  //----------------------------------------------
  myGLCD.clrScr();
  myGLCD.setFont(SmallFont);
  myGLCD.print("BBK_GPS_GPRS", CENTER, 10); 
  myGLCD.print("DataUp Start", CENTER, 24); 
  myGLCD.update();
  delay(1000); 
  //----------------------------------------------
}

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

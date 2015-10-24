
void BBKLCDShow(){
  //-------------------------------------------------------------------------
  myGLCD.clrScr();
  myGLCD.setFont(SmallFont);
  myGLCD.print("BBK_GPS_GPRS", CENTER, 14); 
  myGLCD.print("(C)2013 by", CENTER, 36);
  myGLCD.print("BOBOKing.COM", CENTER, 42);
  myGLCD.update();
  //-------------------------------------------------------------------------
}

void UpdLCDShow(){
  //-------------------------------------------------------------------------
  myGLCD.clrScr();
  myGLCD.setFont(SmallFont);
  myGLCD.print("GPS_Data_UP", CENTER, 10); 
  myGLCD.print("Upload Start", CENTER, 24); 
  myGLCD.update();
  delay(500); 
  //-------------------------------------------------------------------------
}

void GpsLCDShow(){
  //-------------------------------------------------------------------------
  myGLCD.clrScr();
  myGLCD.setFont(SmallFont);
  //-------------------------------------------------------------------------
  myGLCD.print(sDate,0,  0);
  myGLCD.print(sTime,36,  0);
  //------------------------------------------------
  myGLCD.print("W",  0,  9);  
  myGLCD.print(sLats, 18,  9);  
  myGLCD.print("J",  0, 18);  
  myGLCD.print(sLons, 12, 18);
  //------------------------------------------------
  myGLCD.print("H", 0, 27);  
  myGLCD.print(sHigh, 8, 27);
  myGLCD.print("S", 46, 27); 
  myGLCD.print(sGpsn, 52, 27);  
  myGLCD.print(sRads, 66, 27);   
  ////------------------------------------------------
  myGLCD.print("V",  0, 36); 
  myGLCD.print(sSped,  8, 36); 
  myGLCD.print(cLock,  34, 36); 
  myGLCD.print(cType,  40, 36); 
  myGLCD.print("F",  46, 36); 
  myGLCD.print(sFans, 54, 36);
  //-------------------------------------------------------------------------
  //myGLCD.print(myGPS.charGPRMC,  0, 36);  
  //-------------------------------------------------------------------------
  myGLCD.update();
  //-------------------------------------------------------------------------
}

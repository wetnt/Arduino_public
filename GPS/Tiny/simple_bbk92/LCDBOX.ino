void BBKLCDShowString(String str){
  //-------------------------------------------------------------------------
  myGLCD.clrScr();
  myGLCD.setFont(SmallFont);
  myGLCD.print(str,0,14); 
  myGLCD.update();
  //-------------------------------------------------------------------------
}


void BBKLCDShow(){
  //-------------------------------------------------------------------------
  myGLCD.clrScr();
  myGLCD.setFont(SmallFont);
  myGLCD.print("BBK_GPS_GPRS", CENTER, 14); 
  //myGLCD.print("(C)2013 by", CENTER, 30);
  myGLCD.print("BOBOKing.COM", CENTER, 40);
  myGLCD.update();
  //-------------------------------------------------------------------------
}
void GpsLCDShow(){
  //-------------------------------------------------------------------------
  myGLCD.clrScr();
  myGLCD.setFont(SmallFont);
  //-------------------------------------------------------------------------
  myGLCD.print(gs.sDate,0,  0);
  myGLCD.print(gs.sTime,36,  0);
  //------------------------------------------------
  myGLCD.print("W",  0,  9);  
  myGLCD.print(gs.sLats, 18,  9);  
  myGLCD.print("J",  0, 18);  
  myGLCD.print(gs.sLons, 12, 18);
  //------------------------------------------------
  myGLCD.print("H", 0, 27);  
  myGLCD.print(gs.sHigh, 8, 27);
  myGLCD.print("S", 46, 27); 
  myGLCD.print(gs.sGpsn, 52, 27);  
  myGLCD.print(gs.sRads, 66, 27);   
  ////------------------------------------------------
  myGLCD.print("V",  0, 36); 
  myGLCD.print(gs.sSped,  8, 36); 
  myGLCD.print(gs.cLock,  34, 36); 
  myGLCD.print(gs.cType,  40, 36); 
  myGLCD.print("F",  46, 36); 
  myGLCD.print(gs.sFans, 54, 36);
  //-------------------------------------------------------------------------
  myGLCD.update();
  //-------------------------------------------------------------------------
}

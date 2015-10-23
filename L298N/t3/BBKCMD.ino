//---------------------------------------------------
//http://www.arduino.cc/en/Reference/String
//---------------------------------------------------
//$JML,CAR,SAN,A,B,C,4,5,6,7,8,9,10,11,12;
//---------------------------------------------------
String strAll = String("");
String strLoc = String("JML");
String strDev = String("CAR");
String strIds = String("SAN");
//---------------------------------------------------
char strRh = '$',strRv = ',',strRl = ';';
//---------------------------------------------------
String getLoc,getDev,getIds;
String getCmd[13] = {//
  String("1"),String("2"),String("3"),//
  String("4"),String("5"),String("6"),//
  String("7"),String("8"),String("9"),//
  String("10"),String("11"),String("12")//
  };
//---------------------------------------------------
int strRnKey = 0;
String tmpAll = String("");
String tmpVal = String("");
//---------------------------------------------------
void CmdExp(char inChar){
  //-------------------------------------------------
  tmpAll += inChar;
  //Serial.print(inChar);
  //-------------------------------------------------
  if( inChar == strRh ){//$
    CmdTempClear();
  }
  else if( inChar == strRv ){//,
    CmdTempAdd(inChar);
  }
  else if( inChar == strRl ){//;
    CmdTempAdd(inChar);
    CmdCheck();
  }
  else {
    tmpVal += (char)inChar;
  }
  //-------------------------------------------------
}
void CmdTempAdd(char inChar){
  //------------------------------------------
  strRnKey++;
  CmdTempSet(inChar);
  tmpVal = String("");
  //------------------------------------------
}
void CmdTempSet(char inChar){
  //------------------------------------------
  if( strRnKey == 0){
  }
  else if( strRnKey == 1){ 
    getLoc = tmpVal; 
  }
  else if( strRnKey == 2){ 
    getDev = tmpVal; 
  }
  else if( strRnKey == 3){ 
    getIds = tmpVal; 
  }
  else if( strRnKey >= 4){ 
    getCmd[strRnKey-4] = tmpVal; 
  }
  //CmdShow();
  //------------------------------------------
}
void CmdTempClear(){
  //------------------------------------------
  strRnKey = 0;
  tmpAll = String("");
  tmpVal = String("");
  //------------------------------------------
}
//---------------------------------------------------
void CmdCheck(){
  //-------------------------------------------------
  if( getLoc != strLoc ) return;
  if( getDev != strDev ) return;
  if( getIds != strIds ) return;
  //-------------------------------------------------
  //CmdShow();
  CmdRun();
  //-------------------------------------------------
}
//---------------------------------------------------
void CmdShow(){
  //-------------------------------------------------
  Serial.println(getLoc);
  Serial.println(getDev);
  Serial.println(getIds);
  for(int i=0;i<13;i++){
    Serial.println(getCmd[i]);
  }
  //-------------------------------------------------
}


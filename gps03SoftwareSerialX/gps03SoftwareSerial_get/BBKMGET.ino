//-------------------------------------------------------------------------
String getLoc = String("");
String getDev = String("");
String getIds = String("");
//-------------------------------------------------------------------------
int strRnKey = 0;
int strRvKey = 0;
String tmpAll = String("");
String tmpVal = String("");
String tmpInt = String("");
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
void SerialExp(int inChar){
  //-------------------------------------------------------------------------
   tmpAll += (char)inChar;
  //-------------------------------------------------------------------------
  if( inChar == strRl ){//;
    //---------------------------------
    GetShow();
    SerialTempClear();
    //---------------------------------
  }else if( inChar == strRn ){//:
    //---------------------------------
    strRnKey++;
    if( strRnKey == 0){
    }else if( strRnKey == 1){ getLoc = tmpVal; 
    }else if( strRnKey == 2){ getDev = tmpVal; 
    }else if( strRnKey == 3){ getIds = tmpVal; 
    }
    tmpVal = String("");
    tmpInt = String("");
    //---------------------------------
  }else if( inChar == strRv ){//,
    ValExp(inChar);
  }else {
    tmpVal += (char)inChar;
    tmpInt += (char)inChar;
  }
  //-------------------------------------------------------------------------
}

void SerialTempClear(){
  //---------------------------------
  tmpAll = String("");
  tmpVal = String("");
  tmpInt = String("");
  strRnKey = 0;
  strRvKey = 0;
  //---------------------------------
}

//-------------------------------------------------------------------------
String YS = String("");
String DY = String("");
String DM = String("");
String DD = String("");
String TH = String("");
String TM = String("");
String TS = String("");
String WW = String("");
String JJ = String("");
String HH = String("");
String VV = String("");
String SN = String("");
String SR = String("");
//-------------------------------------------------------------------------
void ValExp(int inChar){
    //-------------------------------------------------------------------------
    strRvKey++;
    if( strRvKey == 0){
    }else if( strRvKey == 1){  YS = tmpInt;
    }else if( strRvKey == 2){  DY = tmpInt;
    }else if( strRvKey == 3){  DM = tmpInt;
    }else if( strRvKey == 4){  DD = tmpInt;
    }else if( strRvKey == 5){  TH = tmpInt;
    }else if( strRvKey == 6){  TM = tmpInt;
    }else if( strRvKey == 7){  TS = tmpInt;
    }else if( strRvKey == 8){  WW = tmpInt;
    }else if( strRvKey == 9){  JJ = tmpInt;
    }else if( strRvKey == 10){ HH = tmpInt;
    }else if( strRvKey == 11){ VV = tmpInt;
    }else if( strRvKey == 12){ SN = tmpInt;
    }else if( strRvKey == 13){ SR = tmpInt;
    }
    tmpInt = String("");
  //-------------------------------------------------------------------------
}
void GetShow(){
  //-------------------------------------------------------------------------
  Serial.println("---------------");
  Serial.println(tmpAll);
  Serial.println("---------------");
  Serial.println(getLoc);
  Serial.println(getDev);
  Serial.println(getIds);
  Serial.println(YS);
  Serial.println(DY);
  Serial.println(DM);
  Serial.println(DD);
  Serial.println(TH);
  Serial.println(TM);
  Serial.println(TS);
  Serial.println(WW);
  Serial.println(JJ);
  Serial.println(HH);
  Serial.println(VV);
  Serial.println(SN);
  Serial.println(SR);  
  //-------------------------------------------------------------------------
}

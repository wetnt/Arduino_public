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
int YS = 0;
int DY = 0;
int DM = 0;
int DD = 0;
int TH = 0;
int TM = 0;
int TS = 0;
double WW = 0;
double JJ = 0;
double HH = 0;
double VV = 0;
int SN = 0;
int SR = 0;
//-------------------------------------------------------------------------
void ValExp(int inChar){
    //-------------------------------------------------------------------------
    strRvKey++;
    if( strRvKey == 0){
    }else if( strRvKey == 1){  YS = tmpInt.toInt();
    }else if( strRvKey == 2){  DY = tmpInt.toInt();
    }else if( strRvKey == 3){  DM = tmpInt.toInt();
    }else if( strRvKey == 4){  DD = tmpInt.toInt();
    }else if( strRvKey == 5){  TH = tmpInt.toInt();
    }else if( strRvKey == 6){  TM = tmpInt.toInt();
    }else if( strRvKey == 7){  TS = tmpInt.toInt();
    }else if( strRvKey == 8){  WW = tmpInt.toInt()/1000000.0;
    }else if( strRvKey == 9){  JJ = tmpInt.toInt()/1000000.0;
    }else if( strRvKey == 10){ HH = tmpInt.toInt()/100.0;
    }else if( strRvKey == 11){ VV = tmpInt.toInt()/100.0;
    }else if( strRvKey == 12){ SN = tmpInt.toInt();
    }else if( strRvKey == 13){ SR = tmpInt.toInt();
    }
    tmpInt = String("");
  //-------------------------------------------------------------------------
}
void GetDouble(int n){
  
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
  Serial.println(WW,DEC);
  Serial.println(JJ,DEC);
  Serial.println(HH,DEC);
  Serial.println(VV,DEC);
  Serial.println(SN);
  Serial.println(SR);  
  //-------------------------------------------------------------------------
}

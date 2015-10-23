//-------------------------------------------------------------------------
//JML:GPS:MAIN:?:;
//-------------------------------------------------------------------------
String getLoc = String("");
String getDev = String("");
String getIds = String("");
String getCmd = String("");
//-------------------------------------------------------------------------
int strRnKey = 0;
int strRvKey = 0;
String tmpAll = String("");
String tmpVal = String("");
String tmpInt = String("");
//-------------------------------------------------------------------------
void SerialExp(char inChar){
  //-------------------------------------------------------------------------
   tmpAll += inChar;
   Serial.print(inChar);
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
    }else if( strRnKey == 4){ getCmd = tmpVal; 
    }
    tmpVal = String("");
    tmpInt = String("");
    //---------------------------------
  }else {
    tmpVal += (char)inChar;
    tmpInt += (char)inChar;
  }
  //-------------------------------------------------------------------------
}
void SerialTempClear(){
  //---------------------------------
  strRnKey = 0;
  strRvKey = 0;
  tmpAll = String("");
  tmpVal = String("");
  tmpInt = String("");
  //---------------------------------
}
//-------------------------------------------------------------------------
bool show = false;
void GetShow(){
  show = true;
}
//-------------------------------------------------------------------------
void GetShow2(){
  if(!show)return;
  show = false;
  //-------------------------------------------------------------------------
  Serial.println(getLoc);
  Serial.println(getDev);
  Serial.println(getIds);
  Serial.println(getCmd);  
  //-------------------------------------------------------------------------
  if( getLoc != strLoc ) return;
  if( getDev != strDev ) return;
  if( getIds != strIds ) return;
  if( tmpInt != strCmd ) return;
  //-------------------------------------------------------------------------
  //StrSendOut();  
  //-------------------------------------------------------------------------
}

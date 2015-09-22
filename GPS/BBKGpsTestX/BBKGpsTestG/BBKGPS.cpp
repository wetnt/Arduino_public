/*
//-----------------------------------------------------------------
 //$GPRMC,160546.000,A,3958.8450,N,11621.4676,E,0.00,,110412,,*12
 //$GPRMC,<1>,<2>,<3>,<4>,<5>,<6>,<7>,<8>,<9>,<10>,<11>,<12>*hh 
 //-----------------------------------------------------------------
 //<1> UTC时间，hhmmss.sss(时分秒.毫秒)格式 
 //<2> 定位状态，A=有效定位，V=无效定位 
 //<3> 纬度ddmm.mmmm(度分)格式(前面的0也将被传输) 
 //<4> 纬度半球N(北半球)或S(南半球) 
 //<5> 经度dddmm.mmmm(度分)格式(前面的0也将被传输) 
 //<6> 经度半球E(东经)或W(西经) 
 //<7> 地面速率(000.0~999.9节，前面的0也将被传输) 
 //<8> 地面航向(000.0~359.9度，以正北为参考基准，前面的0也将被传输) 
 //<9> UTC日期，ddmmyy(日月年)格式 
 //<10> 磁偏角(000.0~180.0度，前面的0也将被传输) 
 //<11> 磁偏角方向，E(东)或W(西) 
 //<12> 模式指示(仅NMEA0183 3.00版本输出，A=自主定位，D=差分，E=估算，N=数据无效)
 //-----------------------------------------------------------------
 //$GPGGA,035538.000,3958.0495,N,11620.7022,E,2,7,1.07,78.4,M,-6.4,M,0000,0000*7E
 //$GPGGA,<1>,<2>,<3>,<4>,<5>,<6>,<7>,<8>,<9>,M,<10-11>,M,<11-13>,<12>*xx<CR><LF>
 //$GPGGA：起始引导符及语句格式说明(本句为GPS定位数据)；
 //<1> UTC时间，格式为hhmmss.sss；
 //<2> 纬度，格式为ddmm.mmmm(第一位是零也将传送)；
 //<3> 纬度半球，N或S(北纬或南纬)
 //<4> 经度，格式为dddmm.mmmm(第一位零也将传送)；
 //<5> 经度半球，E或W(东经或西经)
 //<6> GPS状态， 0未定位， 1非差分定位， 2差分定位， 3无效PPS， 6正在估算
 //<7> 使用卫星数量，从00到12(第一个零也将传送)
 //<8> 水平精确度，0.5到99.9
 //<9> 天线离海平面的高度，-9999.9到9999.9米 
 //<10>M 指单位米
 //<10-11> 大地水准面高度，-9999.9到9999.9米
 //<10-12> M 指单位米
 //<11-13> 差分GPS数据期限(RTCM SC-104)，最后设立RTCM传送的秒数量，如不是差分定位则为空
 //<12> 差分参考基站标号，从0000到1023(首位0也将传送)。
 //* 语句结束标志符
 //xx 从$开始到*之间的所有ASCII码的异或校验和
 //<CR> 回车
 //<LF> 换行
 //-----------------------------------------------------------------
 */

#include <Arduino.h>
#include <SoftwareSerial.h>
#include "BBKGPS.h"

BBKGPS::BBKGPS()
{
}

void BBKGPS::InitGPS(HardwareSerial &porth,NewSoftSerial &ports,int hard,int baudrates,int TimeZones)
{
  //-----------------------------------------------------------------
  lengGPRMC = 100;
  HeadGPRMC = "$GPRMC";
  HeadGPGGA = "$GPGGA";
  byteGPS = '0';
  gpsreadcount = 0;
  //-----------------------------------------------------------------
  YY = 0;  
  MT = 0;  
  DD = 0;  
  HH = 0;  
  MM = 0;  
  SC = 0;  
  MS = 0;
  WW = 0;  
  JJ = 0;  
  HB = 0;  
  VV = 0;  
  FF = 0;
  KK = 0;  
  KT = 0;  
  SN = 0;  
  RN = 0;  
  HZ = 0;
  //-----------------------------------------------------------------
  SerialIsHard = hard;  
  if( SerialIsHard == 0 ){
    gpssoft = &ports; gpssoft->begin(baudrates);
  }
  if( SerialIsHard == 1 ){
    gpshard = &porth; gpshard->begin(baudrates);
  }
  if( SerialIsHard == 2 ){
    gpssoft = &ports; gpssoft->begin(baudrates);
    gpshard = &porth; gpshard->begin(baudrates);
  }  
  //-----------------------------------------------------------------
  //delay(200);==会引起LCD初始化失败
  TimeZone = TimeZones;
  TempValueClear();
  //-----------------------------------------------------------------
}


void BBKGPS::Read(bool debug)
{
  //-------------------------------------
  if( SerialIsHard == 0 ){
    ReadSoft(debug);
  }
  if( SerialIsHard == 1 ){
    ReadHard(debug);
  }
  if( SerialIsHard == 2 ){
    ReadSoft(debug);
    ReadHard(debug);
  }
  //-------------------------------------
}

void BBKGPS::ReadHard(bool debug)
{
	//---------------------------------
	if( gpshard->available() <= 0 ) { 
		delay(1);
	}else{
		byteGPS = gpshard->read();
		ReadByteCheck(debug);
	}
	//---------------------------------
}
void BBKGPS::ReadSoft(bool debug)
{
	//---------------------------------
	if( gpssoft->available() <= 0 ) { 
		delay(1);
	}else{
		byteGPS = gpssoft->read();
		ReadByteCheck(debug);
	}
	//---------------------------------
}


void BBKGPS::TempValueClear()
{
  //-----------------------------------------------------------------
  gpsreadcount = 0;
  //-----------------------------------------------------------------
  for (int i=0;i<lengGPRMC;i++){ 
    charGPRMC[i] = 0;
  }
  //-----------------------------------------------------------------
}

int BBKGPS::CheckHeadGPRMC()
{
  //-----------------------------------------------------------------
  int i_gprmc = 0, i_gpgga = 0;
  for(int i=0;i<6;i++){
    //-----------------------------------------
    //Serial.print(charGPRMC[i]); 
    //Serial.print("==");
    //Serial.print(HeadGPRMC[i]);
    //Serial.println();
    //-----------------------------------------
    if( charGPRMC[i] == HeadGPRMC[i] ){ 
      i_gprmc++; 
    }
    if( charGPRMC[i] == HeadGPGGA[i] ){ 
      i_gpgga++; 
    }
    //-----------------------------------------
  }
  //-----------------------------------------------------------------
  if( i_gprmc == 6 ){ 
    return 1; 
  }
  if( i_gpgga == 6 ){ 
    return 2; 
  }
  return 0;
  //-----------------------------------------------------------------
}

void BBKGPS::MarkDotGPRMC()
{
  //-----------------------------------------------------------------
  int cont = 0;
  for (int i=0;i<lengGPRMC;i++){
    if ( charGPRMC[i] == ',' ){ 
      dotIndexs[cont] = i; 
      cont++; 
    }
  }
  //-----------------------------------------------------------------
}

void BBKGPS::GetDateTime(int i,int j)
{
  //-----------------------------------------------------------------
  DD = (charGPRMC[i+0]-48)*10 + (charGPRMC[i+1]-48);
  MT = (charGPRMC[i+2]-48)*10 + (charGPRMC[i+3]-48);
  YY = (charGPRMC[i+4]-48)*10 + (charGPRMC[i+5]-48);
  //-----------------------------------------------------------------
  HH = (charGPRMC[j+0]-48)*10 + (charGPRMC[j+1]-48);
  MM = (charGPRMC[j+2]-48)*10 + (charGPRMC[j+3]-48);
  SC = (charGPRMC[j+4]-48)*10 + (charGPRMC[j+5]-48);
  MS = MS+(charGPRMC[j+7]-48)*100;
  MS = MS+(charGPRMC[j+8]-48)*10; 
  MS = MS+(charGPRMC[j+9]-48);
  //-----------------------------------------------------------------
  HH = HH + TimeZone;
  if(HH>= 24){ 
    HH = HH - 24; 
    DD = DD +  1; 
  }
  //-----------------------------------------------------------------
}

float BBKGPS::GetLongLat(int j)
{
  //-----------------------------------------------------------------
  float x = 0;
  x  = ( charGPRMC[j+0] - 48 ) * 10;
  x += ( charGPRMC[j+1] - 48 );
  x += GetIDValue(j+2) / 60;
  //-----------------------------------------------------------------
  if( charGPRMC[j+10] == 83 ) { 
    x = (x)*-1; 
  }
  //-----------------------------------------------------------------
  return x;
  //-----------------------------------------------------------------
}

float BBKGPS::GetLongLon(int j)
{
  //-----------------------------------------------------------------
  float x = 0;
  x  = ( charGPRMC[j+0] - 48 ) * 100;
  x += ( charGPRMC[j+1] - 48 ) *  10;
  x += ( charGPRMC[j+2] - 48 );
  x += GetIDValue(j+3) / 60;
  //-----------------------------------------------------------------
  if( charGPRMC[j+11] == 87 ) { 
    x = (x)*-1; 
  }
  //-----------------------------------------------------------------
  return x;
  //-----------------------------------------------------------------
}

bool BBKGPS::GetGpsLock(int j)
{
  //-----------------------------------------------------------------
  if( charGPRMC[ j ] == 'A'){
    return 1;
  }
  else{
    return 0;
  }
  //-----------------------------------------------------------------
  return 0;
  //-----------------------------------------------------------------
}

float BBKGPS::GetSpedKMH(int j)
{
  return GetIDValue(j) * 1.852;
}

float BBKGPS::GetOrientD(int j)
{
  return GetIDValue(j);
}

float BBKGPS::GetIDValue(int j){
  //-----------------------------------------------------------------
  int dotIndex = 0;
  int strigEnd = 0;
  float x = 0, tempNumb = 1;
  int pluskey = 1;
  //-----------------------------------------------------------------
  if( charGPRMC[j] == '-' ){
    pluskey = -1;
    j=j+1;
  }
  //-----------------------------------------------------------------
  for (int i=0;i<12;i++){
    if( charGPRMC[j+i] == '.' ){ 
      dotIndex = i; 
      i=99;
    }
  }
  //-----------------------------------------------------------------
  for (int i=0;i<12;i++){
    if( charGPRMC[j+i] == ',' ){ 
      strigEnd = i;  
      i=99;
    }
  }
  //-----------------------------------------------------------------
  if( dotIndex == 0 ){ 
    return 0; 
  }
  if( strigEnd == 0 ){ 
    return 0; 
  }
  if( strigEnd <= dotIndex ){ 
    return 0; 
  }
  //-----------------------------------------------------------------
  tempNumb = 1;
  for (int i=0;i<dotIndex;i++){
    x = x + ( charGPRMC[j + dotIndex - i -1] - 48 ) * tempNumb;
    tempNumb = tempNumb * 10;
  }
  //-----------------------------------------------------------------
  tempNumb = 0.1;
  for (int i=dotIndex+1;i<strigEnd;i++){
    x = x + ( charGPRMC[j + i] - 48 ) * tempNumb;
    tempNumb = tempNumb * 0.1;
  }
  //-----------------------------------------------------------------
  return x*pluskey;
  //-----------------------------------------------------------------
}

int BBKGPS::GetStrInt(int j){
  //-----------------------------------------------------------------
  int x = 0, strigEnd = 0, tempNumb = 1;
  //-----------------------------------------------------------------
  for (int i=0;i<12;i++){
    if( charGPRMC[j+i] == ',' ){ 
      strigEnd = i;  
      i=99;
    }
  }
  //-----------------------------------------------------------------
  if( strigEnd == 0 ){ 
    return 0; 
  }
  //-----------------------------------------------------------------
  for (int i=0;i<strigEnd;i++){
    x = x + ( charGPRMC[j + strigEnd - i -1] - 48 ) * tempNumb;
    tempNumb = tempNumb * 10;
  }
  //-----------------------------------------------------------------
  return x;
  //-----------------------------------------------------------------
}

void BBKGPS::ReadByteCheck(bool debug)
{
    //-----------------------------------------------------------------
	charGPRMC[gpsreadcount] = byteGPS;
	gpsreadcount++;
    //-----------------------------------------------------------------
	if( byteGPS == 13 ){
		//-----------------------------------------------------------------
		if( debug ){ 
			Serial.print(charGPRMC); 
		}
		if( CheckHeadGPRMC() == 1 ){ 
			MarkDotGPRMC(); 
			GPRMCSplit(); 
		}
		if( CheckHeadGPRMC() == 2 ){ 
			MarkDotGPRMC();
			GPGGASplit(); 
		}
		//-----------------------------------------------------------------
		TempValueClear(); 
		//-----------------------------------------------------------------
    }
    if( byteGPS == 10 ){
      TempValueClear(); 
    }
    //-----------------------------------------------------------------
}

//$GPRMC,160546.000,A,3958.8450,N,11621.4676,E,0.00,,110412,,*12
//$GPRMC,000250.599,V,3958.8450,N,11621.4676,E,0.00,0.00,060180,,,N*7C
void BBKGPS::GPRMCSplit()
{
  //-----------------------------------------------------------------
  GetDateTime(     dotIndexs[8] + 1, dotIndexs[0] + 1 );
  KK = GetGpsLock( dotIndexs[1] + 1 );
  WW = GetLongLat( dotIndexs[2] + 1 );
  JJ = GetLongLon( dotIndexs[4] + 1 );
  VV = GetSpedKMH( dotIndexs[6] + 1 );
  FF = GetOrientD( dotIndexs[7] + 1 );
  //-----------------------------------------------------------------
}

//$GPGGA,035537.000,3958.0494,N,11620.7021,E,2,7,1.07,78.5,M,-6.4,M,0000,0000*72
//$GPGGA,<0T>,<1W>,<2N>,<3J>,<4E>,<5KT>,<6SN>,<7RN>,<8HB>,<9M>,<10HZ>,<11M>,<12>*xx<CR><LF>
void BBKGPS::GPGGASplit()
{
  //-----------------------------------------------------------------
  KT = GetStrInt( dotIndexs[5] + 1 );
  SN = GetStrInt( dotIndexs[6] + 1 );
  RN = GetIDValue( dotIndexs[7] + 1 );
  HB = GetIDValue( dotIndexs[8] + 1 );  
  HZ = GetIDValue( dotIndexs[10] + 1 );  
  //-----------------------------------------------------------------
  //  Serial.println(KT);
  //  Serial.println(SN);
  //  Serial.println(RN);
  //  Serial.println(HB);
  //  Serial.println(HZ);
  //-----------------------------------------------------------------
}

void BBKGPS::toStr(bool debug)
{
  //-----------------------------------------------------------------	
  sDate = String( String(YY,DEC) + "/" + String(MT,DEC) + "/" + String(DD,DEC) );
  tDate = String( String(MT,DEC) + "/" + String(DD,DEC) );
  sTime = String( String(HH,DEC) + ":" + String(MM,DEC) + ":" + String(SC,DEC) );
  //-----------------------------------------------------------------
  dtostrf(WW,3,6,str); 
  sLats = str;
  dtostrf(JJ,3,6,str); 
  sLons = str;
  dtostrf(HB,3,6,str); 
  sHigh = str;
  dtostrf(VV,4,2,str); 
  sSped = str;
  dtostrf(FF,4,2,str); 
  sFans = str;
  //-----------------------------------------------------------------
  cLock = "V"; 
  if(KK){ 
    cLock = "A"; 
  }
  cType = String(KT,DEC);
  sGpsn = String(SN,DEC);
  //-----------------------------------------------------------------	
  dtostrf(RN,4,2,str); 
  sRads = str;
  dtostrf(HZ,4,2,str); 
  sSeal = str;
  //-----------------------------------------------------------------	
  if(!debug){ 
    return; 
  }
  //-----------------------------------------------------------------
  Serial.println(sDate);
  Serial.println(tDate);
  Serial.println(sTime);
  //-------------------------
  Serial.println(sLats);
  Serial.println(sLons);
  Serial.println(sHigh);
  Serial.println(sSped);
  Serial.println(sFans);
  //-------------------------
  Serial.println(cLock);
  Serial.println(cType);
  Serial.println(sGpsn);
  Serial.println(sRads);
  Serial.println(sSeal);
  //-----------------------------------------------------------------	
}


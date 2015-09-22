#ifndef BBKGPS_h
#define BBKGPS_h

#include <Arduino.h>
//#include "WProgram.h" //此句声明了Arduino的标准常量和变量，必须要
#include <SoftwareSerial.h>

class BBKGPS //类名称（可与文件名不同）
{
public: //此处定义全局函数和变量
  //-----------------------------------------------------------------
  int YY,MT,DD,HH,MM,SC,MS;
  bool KK;
  float WW,JJ,VV,FF;
  //-----------------------------------------------------------------
  String sDate,tDate,sTime,sLats,sLons,sSped,sFans,cLock;
  //-----------------------------------------------------------------
  char	charGPRMC[100];
  //-----------------------------------------------------------------
  BBKGPS();
  //-----------------------------------------------------------------
  void InitGPS(HardwareSerial &port = Serial,int baudrates = 9600,int TimeZones = 8);
  void	Read(bool back = 0);
  void	toStr(bool back = 0);
  //-----------------------------------------------------------------

private: //此处定义私有函数和变量
  //-----------------------------------------------------------------
  HardwareSerial* gpsport;
  //SoftwareSerial *gpsport;
  //-----------------------------------------------------------------
  int	TimeZone;
  int	lengGPRMC;
  char	*HeadGPRMC;
  char	byteGPS;
  int	gpsreadcount;
  int	dotIndexs[13];
  //-----------------------------------------------------------------
  void	TempValueClear();
  char	ReadAddGPRMC();
  bool	CheckHeadGPRMC();
  void	converNMEA();
  void	MarkDotGPRMC();
  void	GetDateTime(int i,int j);
  bool	GetGpsLock(int j);
  float	GetLongLat(int j);
  float	GetLongLon(int j);
  float	GetSpedKMH(int j);
  float	GetIDValue(int j);
  float GetOrientD(int j);
  //-----------------------------------------------------------------
  char str[20];
  //-----------------------------------------------------------------
};

#endif



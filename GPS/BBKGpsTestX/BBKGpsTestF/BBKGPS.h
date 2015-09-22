#ifndef BBKGPS_h
#define BBKGPS_h

#include <Arduino.h>
#include <SoftwareSerial.h>

class BBKGPS //类名称（可与文件名不同）
{
public: //此处定义全局函数和变量
  //-----------------------------------------------------------------
  int YY,MT,DD,HH,MM,SC,MS;//年月日时分秒毫秒
  float WW,JJ,HB,VV,FF;//纬/经/海拔/速度/方向
  bool KK;//定位成功标记
  int KT,SN;//定位类型=0未定位/1非差分/2差分/3无效/6估算;//SN=view/使用卫星数
  float RN,HZ; //水平精确度//大地水准面高度
  //-----------------------------------------------------------------
  String sDate,tDate,sTime;//YMDHMS
  String sLats,sLons,sHigh,sSped,sFans;//WJHVF
  String cLock,cType,sGpsn,sRads,sSeal;//KK;KT;SN;RN;HZ;
  //-----------------------------------------------------------------
  char	charGPRMC[100];
  //-----------------------------------------------------------------
  BBKGPS();
  //-----------------------------------------------------------------
  void  InitGPS(HardwareSerial &porth,SoftwareSerial &ports,int hard = 1,int baudrates = 9600,int TimeZones = 8);
  void  Read(bool debug = 0);
  void  toStr(bool debug = 0);
  //-----------------------------------------------------------------

private: //此处定义私有函数和变量
  //-----------------------------------------------------------------
  int SerialIsHard;
  HardwareSerial* gpshard;
  SoftwareSerial* gpssoft;
  //-----------------------------------------------------------------
  int	TimeZone;
  int	lengGPRMC;
  char	*HeadGPRMC;
  char	*HeadGPGGA;
  char	byteGPS;
  int	gpsreadcount;
  int	dotIndexs[13];
  //-----------------------------------------------------------------
  void	TempValueClear();
  void	ReadHard(bool debug);
  void	ReadSoft(bool debug);
  void	ReadByteCheck(bool debug);
  int	CheckHeadGPRMC();
  void	GPRMCSplit();
  void	GPGGASplit();
  void	MarkDotGPRMC();
  void	GetDateTime(int i,int j);
  bool	GetGpsLock(int j);
  float	GetLongLat(int j);
  float	GetLongLon(int j);
  float	GetSpedKMH(int j);
  float GetOrientD(int j);
  float	GetIDValue(int j);
  int	GetStrInt(int j);
  //-----------------------------------------------------------------
  char str[20];
  //-----------------------------------------------------------------
};

#endif



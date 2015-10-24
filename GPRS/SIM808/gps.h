#ifndef _GPS_H_
#define _GPS_H_

#include "SIM900.h"

class GPSGSM {
public:
     char getBattInf(char *str_perc, char *str_vol);
     char getBattTVol(char *str_vol);
     char attachGPS();
     char deattachGPS();
     char getStat();
     char getPar(char *lat, char *lon, char *alt, char *sat);
     void parseTime(char *field, int *time);
     double convertLat(void);
     double convertLong(void);
};

#endif

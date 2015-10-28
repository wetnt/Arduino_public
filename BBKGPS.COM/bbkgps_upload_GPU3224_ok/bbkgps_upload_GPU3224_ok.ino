//-------------------------------------------------------------------------
#include <SoftwareSerial.h>
//-------------------------------------------------------------------------
SoftwareSerial wfs(10, 11); //RX,TX
static const long GasBaud = 9600;
//-------------------------------------------------------------------------
#define  lgs  Serial
static const long LGSBaud = 115200;
//-------------------------------------------------------------------------
void setup() {
  //-----------------------------------------------------------------------
  lgs.begin(LGSBaud); lg(F("Log.Serial.start! = ")); lg(LGSBaud); lgln("");
  wfs.begin(GasBaud); lg(F("Gas.Serial.start! = ")); lg(GasBaud); lgln("");
  //-----------------------------------------------------------------------
  GpuClear(); delay(1000);
  GpuShow(0, 0, F("Time="), 2, true);
  //-----------------------------------------------------------------------
  //netStart();
  //netJoinAP(F("MMMM"),F("1234567890123"));
  //netJoinAP(F("acDev"), F("AbroadCar2015()"));
  //-----------------------------------------------------------------------
}
char * floatToString(char * outstr, float value, int places, int minwidth = 0, bool rightjustify = false) {
  // this is used to write a float value to string, outstr.  oustr is also the return value.
  int digit;
  float tens = 0.1;
  int tenscount = 0;
  int i;
  float tempfloat = value;
  int c = 0;
  int charcount = 1;
  int extra = 0;
  // make sure we round properly. this could use pow from <math.h>, but doesn't seem worth the import
  // if this rounding step isn't here, the value  54.321 prints as 54.3209

  // calculate rounding term d:   0.5/pow(10,places)
  float d = 0.5;
  if (value < 0)
    d *= -1.0;
  // divide by ten for each decimal place
  for (i = 0; i < places; i++)
    d /= 10.0;
  // this small addition, combined with truncation will round our values properly
  tempfloat +=  d;

  // first get value tens to be the large power of ten less than value
  if (value < 0)
    tempfloat *= -1.0;
  while ((tens * 10.0) <= tempfloat) {
    tens *= 10.0;
    tenscount += 1;
  }

  if (tenscount > 0)
    charcount += tenscount;
  else
    charcount += 1;

  if (value < 0)
    charcount += 1;
  charcount += 1 + places;

  minwidth += 1; // both count the null final character
  if (minwidth > charcount) {
    extra = minwidth - charcount;
    charcount = minwidth;
  }

  if (extra > 0 and rightjustify) {
    for (int i = 0; i < extra; i++) {
      outstr[c++] = ' ';
    }
  }

  // write out the negative if needed
  if (value < 0)
    outstr[c++] = '-';

  if (tenscount == 0)
    outstr[c++] = '0';

  for (i = 0; i < tenscount; i++) {
    digit = (int) (tempfloat / tens);
    itoa(digit, &outstr[c++], 10);
    tempfloat = tempfloat - ((float)digit * tens);
    tens /= 10.0;
  }

  // if no places after decimal, stop now and return otherwise, write the point and continue on
  if (places > 0)
    outstr[c++] = '.';

  // now write out each decimal place by shifting digits one by one into the ones place and writing the truncated value
  for (i = 0; i < places; i++) {
    tempfloat *= 10.0;
    digit = (int) tempfloat;
    itoa(digit, &outstr[c++], 10);
    // once written, subtract off that digit
    tempfloat = tempfloat - (float) digit;
  }
  if (extra > 0 and not rightjustify) {
    for (int i = 0; i < extra; i++) {
      outstr[c++] = ' ';
    }
  }

  outstr[c++] = '\0';
  return outstr;
}
int tl = 0;
float ww = 29;
float jj = 116;
String ts = "000";
void loop() {
  //-----------------------------------------------------------------------
  tl++;
  ww = ww + 0.1;
  jj = jj + 0.1;

  if (tl < 10)
    ts = "00" + String(tl);
  else if (tl < 100)
    ts = "0" + String(tl);
  else
    ts = String(tl);

  lgln(ts);
  char buffer[25];
  String ul = NetGpsLog(F("boboking"), String("123xjp"), floatToString(buffer, ww, 5), floatToString(buffer, jj, 5), "8848", "120", "60", "9999", String("1446048000" + ts));
  lgln(ul);
  NetLink_bbkgps_log(ul);
  NetExp_bbkgps_show();
  smartDelay(10000);
  //-----------------------------------------------------------------------
}
//-------------------------------------------------------------------------
void wfsLoop() {
  while (wfs.available()) {
    //------------------------------------
    char c = wfs.read();
    lgs.write(c);
    HttpBufferSave(c);
    //------------------------------------
  }
}
void lgsLoop() {
  while (lgs.available()) {
    char c = lgs.read();
    wfs.write(c);
  }
}
//-------------------------------------------------------------------------
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis(); do {
    //------------------------------------------
    wfsLoop();
    lgsLoop();
    //------------------------------------------
  } while (millis() - start < ms);
}
//-------------------------------------------------------------------------

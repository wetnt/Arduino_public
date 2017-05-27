//------------------------------------------
//http://bbs.mydigit.cn/read.php?tid=2025973
#include <TM1637Display.h>
TM1637Display tube_4(D3, D4); //CLK, DIO
//------------------------------------------
unsigned char ClockPoint = 1;
uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };
int th,tm,ts,tth;
uint8_t  m0, m1, h0, h1;
//------------------------------------------
void tube_setup() {
  tube_4.setBrightness(0x0f);
  tube_4.showNumberDec(1234);
}
void TimeSet(unsigned long epoch) {
   th = (epoch % 86400L) / 3600; //86400 equals secs per day
   tm = (epoch % 3600) / 60;
   ts = (epoch % 60);

  lg("The UTC time is ");
  lg(th);
  lg(':');
  if (tm < 10) {
    lg('0');
  }
  lg(tm);
  lg(':');
  if (ts < 10 ) {
    lg('0');
  }
  lg(ts);
  lg();

  tth = th + 8;
  tth = tth > 23 ? tth - 24 : tth;
  //tube_4.showNumberDec(tth * 100 + tm);
}

void TimeShow() {
  //------------------------------------------
  m1 = tm / 10;
  m0 = tm % 10;
  h1 = tth / 10;
  h0 = tth % 10;

  data[0] = tube_4.encodeDigit(h1);
  data[1] = tube_4.encodeDigit(h0);
  data[2] = tube_4.encodeDigit(m1);
  data[3] = tube_4.encodeDigit(m0);

  ClockPoint = (~ClockPoint) & 0x01;
  if (ClockPoint) data[1] |= 0x80; else data[1] &= 0x7F;
    
  tube_4.setSegments(data);
}


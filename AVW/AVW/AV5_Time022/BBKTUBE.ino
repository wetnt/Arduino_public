//-------------------------------------------------------------------
const int dataPin =  2;// SER - DIO //DATA
const int latchPin = 3;// RCK //ST_CP 低電位鎖定資料並輸出Q0~Q7;高電位更新 
const int clockPin = 4;// SCK //SH_CP 
//-------------------------------------------------------------------
unsigned char fseg[]={ 0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xbf};
unsigned char segbit[]={ 0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};
unsigned char disbuf[8]={ 0,0,0,0,0,0,0,0};
//-------------------------------------------------------------------
void Tube_Setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
}
void TimePrint()
{
  //-------------------------------------------------------------------
  disbuf[0]=time_second%10;
  disbuf[1]=time_second/10;
  disbuf[2]=10;
  disbuf[3]=time_minute%10;
  disbuf[4]=time_minute/10;
  disbuf[5]=10;
  disbuf[6]=time_hourss%10;
  disbuf[7]=time_hourss/10;
  //-------------------------------------------------------------------
}
void Tube_Loop() {
  //-------------------------------------------------------------------
  //t.update();
  //-------------------------------------------------------------------
  //数码管循环显示
  for (int j = 0; j < 8; j++) {
    digitalWrite(latchPin, 0);
    shiftOut(dataPin, clockPin, MSBFIRST, segbit[j]);
    shiftOut(dataPin, clockPin, MSBFIRST, fseg[disbuf[j]]);
    digitalWrite(latchPin, 1);
    //delay(1);
  }
  //-------------------------------------------------------------------
}

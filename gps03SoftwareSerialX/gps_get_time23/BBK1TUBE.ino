const int dataPin =  5;// SER - DIO //DATA
const int latchPin = 6;// RCK //ST_CP 低電位鎖定資料並輸出Q0~Q7;高電位更新 
const int clockPin = 7;// SCK //SH_CP 

//static unsigned char time_hour,time_minute,time_second;
int time_hour,time_minute,time_second;

unsigned char fseg[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xbf};
unsigned char segbit[]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};
unsigned char disbuf[8]={0,0,0,0,0,0,0,0};

unsigned long t = millis(); 

void TubeSetup() {
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
}

void TubeLoop() {

  if( millis()-t > 1000 )
  {
    TimeAdds(); 
    t = millis(); 
  }


  for (int j = 0; j < 8; j++) {
    digitalWrite(latchPin, 0);
    shiftOut(dataPin, clockPin, MSBFIRST, segbit[j]);
    shiftOut(dataPin, clockPin, MSBFIRST, fseg[disbuf[j]]);
    digitalWrite(latchPin, 1);
    //delay(1);
  }

}


void TimeAdds()
{
  time_second++;
  if(time_second==60){
    time_second=0;
    time_minute++;
    if(time_minute==60){
      time_minute=0;
      time_hour++;
      if(time_hour==24){
        time_hour=0;
      }
    }
  }
  disbuf[0]=time_second%10;
  disbuf[1]=time_second/10;
  disbuf[2]=10;
  disbuf[3]=time_minute%10;
  disbuf[4]=time_minute/10;
  disbuf[5]=10;
  disbuf[6]=time_hour%10;
  disbuf[7]=time_hour/10;
}

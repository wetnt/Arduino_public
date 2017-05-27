#include <Arduino.h>
#include <TM1637Display.h>

// Module connection pins (Digital Pins)
//#define CLK 3
//#define DIO 2
#define CLK A5
#define DIO A4
#define TEST_DELAY   200
TM1637Display display(CLK, DIO);

uint8_t data[]={ 0xff, 0xff, 0xff, 0xff };

int k = 0;
void setup() {
  display.setBrightness(0x0f);
  k = 0;
}
void loop() {
  //  display.setSegments(data);  delay(TEST_DELAY);// All segments on

  //参数：数字,是否补充0,变化位数,
  k++;
  //display.showNumberDec(k, false, 4, 0);    
  //delay(TEST_DELAY);


  //data[1] &= 0x7F;
  //display.setSegments(data);  
  //delay(TEST_DELAY);



  volatile uint8_t ss,mm,hh,m0,m1,h0,h1;
 // rTime.getTime(tr);
  ss=32; 
  mm=22; 
  hh=11; 
  m1=mm/10;
  m0=mm%10;
  h1=hh/10;
  h0=hh%10;

  data[0] = display.encodeDigit(h1);
  data[1] = display.encodeDigit(h0);
  data[2] = display.encodeDigit(m1);
  data[3] = display.encodeDigit(m0);
  data[1] |= 0x80;
  display.setSegments(data);
  delay(1000);
  data[1] &= 0x7F;
  display.setSegments(data);
  delay(1000);
}

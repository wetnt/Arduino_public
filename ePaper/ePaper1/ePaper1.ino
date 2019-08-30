#include "B0_ePaper.h"
#include "Utf8ToGbk.h"

//http://www.atool.org/urlencode.php
//https://bluehua.org/2016/04/25/2311.html
//http://blog.csdn.net/tge7618291/article/details/7608510
//http://jimmee.iteye.com/blog/2174693
//http://bbs.elecfans.com/jishu_352010_1_1.html
//http://blog.csdn.net/armcsdn/article/details/70320055
//http://www.verysource.com/code/6064304_1/gb2uni.h.html
void setup() {
  Serial.begin(115200); delay(200);
  Serial2.begin(115200); delay(200);

  while (!Serial) {
    ;
  }
  while (!Serial2) {
    ;
  }

  //----------------------------------------------------------
  const void * p = "我们";
  epd_clear();
  epd_set_ch_font(GBK32);
  epd_set_en_font(ASCII32);
  //epd_disp_string(p, 10, 10);
  epd_disp_string("Hello, World!", 0, 350);
  epd_udpate();

  //char buff[] = { 0xc4, 0xe3, 0xba, 0xc3, 0xca, 0xc0, 0xbd, 0xe7, 0};
  char buff[] ={ 0xCE, 0xD2, 0xB0, 0xAE, 0xC4, 0xE3, 0xB1, 0xA6, 0xB1, 0xB4, 0x21, 0};


const unsigned char* pszBufIn="我是国王";
unsigned char* pszBufOut;
 SwitchToGbk(pszBufIn,9,pszBufOut,9);



  
  //epd_set_color(BLACK, WHITE);
  epd_clear();
  epd_set_ch_font(GBK32);
  epd_set_en_font(ASCII32);
  epd_disp_string(pszBufOut, 0, 50);
  epd_disp_string("Hello, World!", 0, 300);
  epd_udpate();
  //----------------------------------------------------------
  //----------------------------------------------------------
  //----------------------------------------------------------
}

void loop() {
  Serial_Loop();
}
void Serial_Loop(void) {
  while (Serial2.available() > 0) {
    byte b = Serial2.read();
    Serial.write(b);
  }
  while (Serial.available() > 0) {
    Serial2.write(Serial.read());
  }
}
static void smartDelay(unsigned long ms) {
  //------------------------------------------
  unsigned long start = millis();
  do {
    //-------------------------------
    Serial_Loop(); delay(2);
    //-------------------------------
  } while (millis() - start < ms);
  //------------------------------------------
}


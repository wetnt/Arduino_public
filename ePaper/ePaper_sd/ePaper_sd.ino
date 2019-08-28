#include "B0_ePaper.h"

//http://www.atool.org/urlencode.php
//https://bluehua.org/2016/04/25/2311.html
//http://blog.csdn.net/tge7618291/article/details/7608510
//http://jimmee.iteye.com/blog/2174693
//http://bbs.elecfans.com/jishu_352010_1_1.html
//http://blog.csdn.net/armcsdn/article/details/70320055
//http://www.verysource.com/code/6064304_1/gb2uni.h.html


//----------------------------------------------------------
//const void * p = "我们";
char buff[] = { 0xc4, 0xe3, 0xba, 0xc3, 0xca, 0xc0, 0xbd, 0xe7, 0};
//char buff[] = { 0xCE, 0xD2, 0xB0, 0xAE, 0xC4, 0xE3, 0xB1, 0xA6, 0xB1, 0xB4, 0x21, 0};

void setup() {
  //Serial.begin(115200); delay(200);
  lgsetup("ePaper SD"); delay(200);
  Serial2.begin(115200); delay(200);

  while (!Serial) {
    ;
  }
  while (!Serial2) {
    ;
  }
  //----------------------------------------------------------
  //sss(buff, 5);
  //----------------------------------------------------------
  SD_setup();
  sd_file_init();
  //sd_file_Remove();
  //sd_file_Create();
  //sd_file_save();
  sd_file_read();
  //----------------------------------------------------------
  //s2();
  //s1();
  //----------------------------------------------------------
}

void sss_int() {
  epd_clear();
  epd_set_ch_font(GBK32);
  epd_set_en_font(ASCII32);
}
void sss_write(char * txt, int n) {
  epd_disp_string(txt, 0, n * 32);
}
void sss_show() {
  epd_udpate();
}
void sss(char * txt, int n) {
  epd_clear();
  epd_set_ch_font(GBK32);
  epd_set_en_font(ASCII32);
  epd_disp_string(txt, 0, n * 32);
  epd_udpate();
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


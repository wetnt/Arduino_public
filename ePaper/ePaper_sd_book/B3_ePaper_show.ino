char buff[] = { 0xc4, 0xe3, 0xba, 0xc3, 0xca, 0xc0, 0xbd, 0xe7, 0};
//----------------------------------------------------------
//sss(buff, 5);
//----------------------------------------------------------
void ePaper_clear() {
  epd_clear();
  epd_set_ch_font(GBK32);
  epd_set_en_font(ASCII32);
}
void ePaper_write(char * txt, int n) {
  epd_disp_string(txt, 0, n * 32);
}
void ePaper_udpate() {
  epd_udpate();
}
//----------------------------------------------------------
void ePaper_show(char * txt, int n) {
  epd_clear();
  epd_set_ch_font(GBK32);
  epd_set_en_font(ASCII32);
  epd_disp_string(txt, 0, n * 32);
  epd_udpate();
}
void sss_test(){
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

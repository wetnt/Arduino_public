//===============================================
//===============================================
//===============================================
int bmpstr_type = 0;//10秒切换一次
void bmpstr_type_loop() {
  if (bmpstr_type == 0) {
    bmpstr_type = 1;
  } else {
    bmpstr_type = 0;
  }
  lg("bmpstr_type="); lg(bmpstr_type); lg();
}

int bmp_int = 0;//1秒切换一次
void bmp_int_loop() {
  bmp_int = bmp_int + 1;
  if (bmp_int > 5) {
    bmp_int = 0;
    if (bmpstr_type == 0) {
      bmpstr_type_loop();
    }
  }
  //lg("bmp_int="); lg(bmp_int); lg();
}

void weather_loop() { //100毫秒一次

  if (bmpstr_type == 0) {
    weather_bmp_show();
  } else {
    weather_str_show();
  }

}



void weather_bmp_show() {
  uint8_t* bmp;
  if (bmp_int == 0) bmp = bmp1;
  if (bmp_int == 1) bmp = bmp2;
  if (bmp_int == 2) bmp = bmp3;
  if (bmp_int == 3) bmp = bmp4;
  if (bmp_int == 4) bmp = bmp5;
  if (bmp_int == 5) bmp = bmp6;
  microduino_8x8_bmp(bmp, LED_RED);
}


int we_x = matrix.width();
int we_c = 0;
int we_n = (str0.length() + 1) * 6;
void weather_str_show() {
  //------------------------------------------
  we_n = (str0.length() + 1) * 6;
  //------------------------------------------
  matrix.fillScreen(0);
  matrix.setCursor(we_x, 0);
  matrix.print(str0);
  //lgln(str0);
  //------------------------------------------
  if (--we_x < -we_n) {
    we_x = matrix.width();
    if (++we_c >= 3) we_c = 0;
    lg("we_x="); lg(we_x); lg(" ");
    lg("we_n="); lg(we_n); lg(" "); lg();
    matrix.setTextColor(3);
    bmp_int = 0;
    bmpstr_type_loop();
  }
  //------------------------------------------
  matrix.writeDisplay();
  //------------------------------------------
}

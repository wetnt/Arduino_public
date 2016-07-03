/*****  LED  *****/
void blinkLED(uint8_t num, uint8_t ontime,uint8_t repeat) {
  uint8_t i,r;
  for (r=0;r<repeat;r++) {  //重复次数
    for(i=0;i<num;i++) {  //闪烁次数
      LEDPIN_TOGGLE; //LED状态切换
      delay(ontime);  //闪烁频率
    }
    delay(60); //等待 60 ms
  }
}


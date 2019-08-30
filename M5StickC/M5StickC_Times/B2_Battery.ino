//APX192
//电池的单位是Wh，手机电池默认电压为3.7v，
//2000mAh的电池的容量为 2000mAh*3.7v=7400mWh。
//在7400mW（7.4W）的功率下，能工作一个小时。
// 2000mAh*3.7v=7400mWh/7400mW=1h
//--------------------------------------------------
double tBat = 0.0;//C  芯片温度 axp192 inside temp
double vBat = 0.0;//v  电池电压 battery voltage
double pBat = 0.0;//mW 电池放电功率 battery power
int iBat = 0.0;//mA 充电电流
int oBat = 0.0;//mA 放电电流

double iCol = 0.0;//Coulomb 输入电量
double oCol = 0.0;//Coulomb 输出电量
double wBat = 0.0;//mAh 充电电量

double vAci = 0.0;//mV ACIN vin电压
double iAci = 0.0;//mA ACIN vin电流
double iUSB = 0.0;//mA USB电流
double vUSB = 0.0;//mV USB电压
//--------------------------------------------------
double sTim = 0;//可持续使用时间
long sleep_count = 0;
float cBat = 0.0;//电量百分比
float startcBat = 0.0;
//double a,b,c,d,e,f;
//--------------------------------------------------

void Battery_setup() {
  M5.Axp.EnableCoulombcounter();
  Battery_loop();
  startcBat = cBat;
}
void Battery_Warning() {
  if (M5.Axp.GetWarningLeve()) {
    sleep_count++;
    if (sleep_count >= 1) {
      M5.Lcd.fillScreen(WHITE);
      M5.Lcd.setCursor(0, 20, 1);
      M5.Lcd.setTextColor(RED, WHITE);
      M5.Lcd.printf("Warning: low battery");
      if (sleep_count >= 10) {
        sleep_count = 0;
        M5.Axp.SetSleep();
      }
    }
  } else {
    sleep_count = 0;
  }
}
void Battery_loop() {
  //--------------------------------------------------
  Battery_Warning();
  //--------------------------------------------------
  tBat = -144.7 + M5.Axp.GetTempData() * 0.1;//C
  vBat = M5.Axp.GetVbatData() * 1.1 / 1000;//V
  pBat = M5.Axp.GetPowerbatData() * 1.1 * 0.5 / 1000;//mW

  iBat = M5.Axp.GetIchargeData() / 2;//mA
  oBat = M5.Axp.GetIdischargeData() / 2;//mA

  iCol = M5.Axp.GetCoulombchargeData();
  oCol = M5.Axp.GetCoulombdischargeData();
  wBat = M5.Axp.GetCoulombData();//mAh

  vAci = M5.Axp.GetVinData() * 1.7; //mV
  iAci = M5.Axp.GetIinData() * 0.625; //mA

  vUSB = M5.Axp.GetVusbinData() * 1.7 / 1000; //mV
  iUSB = M5.Axp.GetIusbinData() * 0.375; //mA
  //--------------------------------------------------
  cBat = getBatteryLevel(vBat);
  if (pBat <= 0) {
    sTim = 0;
  } else {
    sTim = (wBat - 80) * vBat * 60 / pBat;
    //sTim = cBat * millis()/1000 / (startcBat - cBat);
  }
  //--------------------------------------------------  
  //--------------------------------------------------
}
void Battery_Lcd() {
  //--------------------------------------------------
  M5.Lcd.setCursor(0, 0, 2);
  M5.Lcd.printf("T %.1f C\r\n" , tBat);
  M5.Lcd.printf("B %.3f V\r\n" , vBat);
  M5.Lcd.printf("B %.1fmAh\r\n", wBat);
  M5.Lcd.printf("B %.0f mW\r\n", pBat);

  M5.Lcd.printf("O %d mA\r\n", oBat);
  M5.Lcd.printf("N %d mA\r\n", iBat);

  M5.Lcd.printf("U %.0f mA\r\n", iUSB);
  M5.Lcd.printf("U %.3f V\r\n" , vUSB);

  M5.Lcd.printf("C %.0f%% \r\n", cBat * 100);
  M5.Lcd.printf("R %.0f m\r\n", sTim);
  
  //M5.Lcd.printf("W %d    \r\n", M5.Axp.GetWarningLeve());
  //M5.Lcd.printf("X %.1f mV\r\n", vAci);
  //M5.Lcd.printf("X %.1f mA\r\n", iAci);
  //M5.Lcd.printf("Ci %d\r\n", iCol);
  //M5.Lcd.printf("Co %d\r\n", oCol);
  //--------------------------------------------------
}
void Battery_Serial() {
  //--------------------------------------------------
  Serial.printf("芯片温度 tBat:%.1f C\r\n", tBat); //芯片温度 axp192 inside temp
  Serial.printf("电池电压 vBat:%.3f V\r\n", vBat); //电池电压 battery voltage
  Serial.printf("充电电流 iBat:%d mA\r\n",  iBat); //充电电流 battery charging current
  Serial.printf("放电电流 oBat:%d mA\r\n",  oBat); //放电电流 battery output current
  Serial.printf("电池功率 wBat:%.3f mW\r\n", pBat); //电池电量 battery power
  Serial.printf("输入电量 iCol:%d \r\n", iCol); //输入电量 coulomb in current
  Serial.printf("输出电量 oCol:%d \r\n", oCol); //输出电量 coulomb out current
  Serial.printf("充电电量 pBat:%.2f mAh\r\n", wBat); //充电电量 value of coulomb after calculate
  Serial.printf("芯片电压 vAci:%.3f mV\r\n",  vAci); //VIN电压 ACIN vin voltage
  Serial.printf("芯片电流 iAci:%.3f mA\r\n",  iAci); //VIN电流 ACIN vin current
  Serial.printf("USB电压 vUSB:%.3f V\r\n" ,  vUSB); //USB电压 usb vin voltage
  Serial.printf("USB电流 iUSB:%.3f mA\r\n",  iUSB); //USB电流 usb vin current
  Serial.printf("电池余量 cBat:%.0f%% \r\n", cBat * 100);
  Serial.printf("可持续工作  R:%.0f m\r\n",  sTim); //可持续工作
  Serial.printf("WarningLeve:%d    \r\n",  M5.Axp.GetWarningLeve()); //M5.Axp.GetWarningLeve()

  Serial.println(""); Serial.println("");
  //--------------------------------------------------
}



//--------------------------------------------------
//--------------------------------------------------
static const float levels[] = {4.20, 4.06, 3.98, 3.92, 3.87, 3.82, 3.79, 3.77, 3.74, 3.68, 3.45, 3.00};
float getBatteryLevel(float voltage) {
  float level = 1;
  if (voltage >= levels[0]) {
    level = 1;
  } else if (voltage >= levels[1]) {
    level = 0.9;
    level += 0.1 * (voltage - levels[1]) / (levels[0] - levels[1]);
  } else if (voltage >= levels[2]) {
    level = 0.8;
    level += 0.1 * (voltage - levels[2]) / (levels[1] - levels[2]);
  } else if (voltage >= levels[3]) {
    level = 0.7;
    level += 0.1 * (voltage - levels[3]) / (levels[2] - levels[3]);
  } else if (voltage >= levels[4]) {
    level = 0.6;
    level += 0.1 * (voltage - levels[4]) / (levels[3] - levels[4]);
  } else if (voltage >= levels[5]) {
    level = 0.5;
    level += 0.1 * (voltage - levels[5]) / (levels[4] - levels[5]);
  } else if (voltage >= levels[6]) {
    level = 0.4;
    level += 0.1 * (voltage - levels[6]) / (levels[5] - levels[6]);
  } else if (voltage >= levels[7]) {
    level = 0.3;
    level += 0.1 * (voltage - levels[7]) / (levels[6] - levels[7]);
  } else if (voltage >= levels[8]) {
    level = 0.2;
    level += 0.1 * (voltage - levels[8]) / (levels[7] - levels[8]);
  } else if (voltage >= levels[9]) {
    level = 0.1;
    level += 0.1 * (voltage - levels[9]) / (levels[8] - levels[9]);
  } else if (voltage >= levels[10]) {
    level = 0.05;
    level += 0.05 * (voltage - levels[10]) / (levels[9] - levels[10]);
  } else if (voltage >= levels[11]) {
    level = 0.00;
    level += 0.05 * (voltage - levels[11]) / (levels[10] - levels[11]);
  } else {
    level = 0.00;
  }
  return level;
}

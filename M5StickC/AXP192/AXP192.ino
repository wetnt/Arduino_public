#include <M5StickC.h>
#include <WiFi.h>

void setup() {
  // put your setup code here, to run once:
  M5.begin();
  M5.Axp.ScreenBreath(8);
  M5.Lcd.fillScreen(BLACK);

  Serial.begin(115200);
  WiFi.mode(WIFI_OFF);

  M5.Axp.EnableCoulombcounter();
}
double vbat = 0.0;
int discharge, charge;
double temp = 0.0;
double bat_p = 0.0;
double usbin = 0.0;

void loop() {

  vbat      =  M5.Axp.GetVbatData() * 1.1 / 1000;
  charge    =  M5.Axp.GetIchargeData() / 2;
  discharge =  M5.Axp.GetIdischargeData() / 2;
  temp      =  -144.7 + M5.Axp.GetTempData() * 0.1;
  bat_p     =  M5.Axp.GetPowerbatData() * 1.1 * 0.5 / 1000;
  usbin     =  M5.Axp.GetVusbinData() * 1.7 / 1000;

  M5.Lcd.setCursor(0, 0, 2);
  M5.Lcd.printf("T %.1f C\r\n", temp); //axp192 inside temp
  M5.Lcd.printf("B %.1fmAh\r\n", M5.Axp.GetCoulombData()); //value of coulomb after calculate
  M5.Lcd.printf("B %.3f V\r\n", vbat); //battery voltage
  M5.Lcd.printf("B %.0f mW\r\n", bat_p); //battery power

  M5.Lcd.printf("N %d mA\r\n", charge); //battery charging current
  M5.Lcd.printf("O %d mA\r\n", discharge); //battery output current

  M5.Lcd.printf("U %.3f V\r\n", usbin); //usb vin voltage
  M5.Lcd.printf("U %.0f mA\r\n", M5.Axp.GetIusbinData() * 0.375); // usb vin current

  M5.Lcd.printf("X %.1f mV\r\n", M5.Axp.GetVinData() * 1.7);   // ACIN vin voltage
  M5.Lcd.printf("X %.1f mA\r\n", M5.Axp.GetIinData() * 0.625); // ACIN vin current

  //M5.Lcd.printf("CoIn :%d\r\n", M5.Axp.GetCoulombchargeData()); //coulomb in current
  //M5.Lcd.printf("CoOut:%d\r\n", M5.Axp.GetCoulombdischargeData()); //coulomb out current


  Serial.printf("电池电压 vbat:%.3fV\r\n", vbat);      //电池电压 battery voltage
  Serial.printf("充电电流 icharge:%dmA\r\n", charge);  //充电电流 battery charging current
  Serial.printf("放电电流 idischg:%dmA\r\n", discharge); //放电电流 battery output current
  Serial.printf("芯片温度 temp:%.1fC\r\n", temp);      //芯片温度 axp192 inside temp
  Serial.printf("电池电量 pbat:%.3fmW\r\n", bat_p);    //电池电量 battery power
  Serial.printf("输入电量 CoIn :%d\r\n", M5.Axp.GetCoulombchargeData());   //输入电量 coulomb in current
  Serial.printf("输出电量 CoOut:%d\r\n", M5.Axp.GetCoulombdischargeData()); //输出电量 coulomb out current
  Serial.printf("充电电量 CoD:%.2fmAh\r\n", M5.Axp.GetCoulombData());      //充电电量 value of coulomb after calculate
  Serial.printf("芯片电压 Vin:%.3fmV\r\n", M5.Axp.GetVinData() * 1.7);     //？芯片电压 ACIN vin voltage
  Serial.printf("芯片电流 Iin:%.3fmA\r\n", M5.Axp.GetIinData() * 0.625);   //？芯片电流 ACIN vin current
  Serial.printf("USB电压 Vuin:%.3fmV\r\n", M5.Axp.GetVusbinData() * 1.7); //USB电压 usb vin voltage
  Serial.printf("USB电流 Iuin:%.3fmA\r\n", M5.Axp.GetIusbinData() * 0.375); //USB电流 usb vin current
  Serial.println(""); Serial.println("");


  if (digitalRead(M5_BUTTON_HOME) == LOW) {
    M5.Lcd.fillScreen(BLACK);
    delay(200);
  }

  if (digitalRead(M5_BUTTON_RST) == LOW) {
    //M5.Axp.LightSleep(SLEEP_SEC(2));
    //delay(6);
    //M5.Axp.DeepSleep(SLEEP_SEC(2));
    delay(200);
    esp_restart();
  }

  delay(200);
}

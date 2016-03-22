#include <AltSoftSerial.h>
#include <LiquidCrystal_I2C.h>

//软串口，Uno开发板：Tx-D9、Rx-D8。Rx接传感器的Tx。
AltSoftSerial altSerial;

//YWrobot I2C 1602液晶屏
LiquidCrystal_I2C lcd(0x27, 16, 2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

//攀藤G5的数据格式
struct _panteng {
  unsigned char len[2];
  unsigned char pm1_cf1[2];
  unsigned char pm2_5_cf1[2];
  unsigned char pm10_0_cf1[2];
  unsigned char pm1_0[2];
  unsigned char pm2_5[2];
  unsigned char pm10_0[2];
  unsigned char d[20];
} panteng;

void setup()
{
  lcd.init();                      // initialize the lcd
  lcd.backlight();

  Serial.begin(115200);        //USB串口向PC发送数据
  altSerial.begin(9600);        //软串口连接传感器
}

void loop()
{
  unsigned char c;
  char str[100];
  static int state = 0;
  static int count = 0;
  static int time = 0;
  int pm1_0, pm2_5, pm10_0;        //PM1.0、PM2.5、PM10
  int i;

  if (altSerial.available()) {
    c = altSerial.read();
    switch (state) {
      case 0:
        if (0x42 == c)
          state = 1;
        break;
      case 1:
        if (0x4d == c) {
          state = 2;
          count = 0;
          //Serial.println(' ');
        }
        break;
      case 2:
        ((unsigned char *) &panteng)[count++] = c;
        sprintf(str, "%02X ", c);
        //Serial.print(str);
        if (count > 28) {
          state = 0;
          pm1_0 = panteng.pm1_0[0] * 256 + panteng.pm1_0[1];
          pm2_5 = panteng.pm2_5[0] * 256 + panteng.pm2_5[1];
          pm10_0 = panteng.pm10_0[0] * 256 + panteng.pm10_0[1];

          sprintf(str, "%d\t%d\t%d\t%d", time++, pm1_0, pm2_5, pm10_0);
          Serial.println(str);

          snprintf(str, 16, "PM2.5=%d    ", pm2_5);
          //lcd.clear();
          for (i = 0; i < strlen(str); i++) {
            lcd.setCursor(i, 0);
            lcd.print(&str[i]);
          }
        }
        break;
      default:
        break;
    }
  }
}


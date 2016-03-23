/**
 * PM2.5&温湿度显示
 * 激光PM2.5传感器：攀藤 G5 PMS5005
 * 温湿度传感器：DHT22
 * Arduino Nano
 * SSD1306
 *
 * @Author: Coeus <r.anerg at gmail.com>
 */
#include <DHT.h>
#include <U8glib.h>
#include <SoftwareSerial.h>
 
#define DHTPIN 3        //DHT SIG口接PIN3
#define DHTTYPE DHT22   //定义DHT型号
 
 SoftwareSerial mySerial(9, 10);
 U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);
 DHT dht(DHTPIN, DHTTYPE);
 
 struct PARAMS {
  float T;//显示温度
  float H;//显示湿度
  long P;//显示PM2.5
  long _P;//读取PM2.5
} _params;
 
//G5 相关变量
static unsigned char ucRxBuffer[250];
static unsigned char ucRxCnt = 0;
 
//循环计数器
unsigned char loopCnt = 0;
 
void setup() {
  Serial.begin(9600);
  //软串口读取G5
  mySerial.begin(9600);
  delay(500);
  //设置屏幕字体和背景颜色
  u8g.setColorIndex(255);
  u8g.setHiColorByRGB(255, 255, 255);
  delay(800);
}
 
void showTemperature(void) {
  int x = 30, y = 10;//温度显示位置
  //画LOGO
  u8g.drawRFrame(x, y, 16, 16, 1);
  u8g.drawFrame(x + 5, y + 3, 3, 6);
  u8g.drawDisc(x + 6, y + 10, 2);
  u8g.setFont(u8g_font_04b_03b);
  u8g.setPrintPos(x + 10, y + 8);
  u8g.print("C");
 
  //设置双倍大小字体显示
  u8g.setScale2x2();
  u8g.setPrintPos(x / 2 + 11, y / 2 + 7);
  u8g.setFont(u8g_font_orgv01);
  u8g.print(_params.T);
  u8g.undoScale();
}
 
void showPM25(void) {
  int x = 30, y = 28;//PM2.5显示位置
  //画LOGO
  u8g.drawRFrame(x, y, 16, 16, 1);
  u8g.setFont(u8g_font_orgv01);
  u8g.setPrintPos(x + 3, y + 10);
  u8g.print("pm");
 
  //设置双倍大小字体显示
  u8g.setScale2x2();
  u8g.setPrintPos(x / 2 + 11, y / 2 + 7);
  u8g.setFont(u8g_font_orgv01);
  u8g.print(_params.P);
  u8g.undoScale();
}
 
void showRH() {
  int x = 30, y = 46;//湿度显示位置
  //画LOGO
  u8g.drawRFrame(x, y, 16, 16, 1);
  u8g.drawFrame(x + 5, y + 3, 3, 6);
  u8g.drawDisc(x + 6, y + 10, 2);
  u8g.setFont(u8g_font_04b_03b);
  u8g.setPrintPos(x + 10, y + 8);
  u8g.print("H");
 
  //设置双倍大小字体显示
  u8g.setScale2x2();
  u8g.setPrintPos(x / 2 + 11, y / 2 + 7);
  u8g.setFont(u8g_font_orgv01);
  u8g.print(_params.H);
  u8g.undoScale();
}
 
 
//画界面
void draw(void) {
  showTemperature();
  showPM25();
  showRH();
}
 
//获取温湿度
void getDHT22() {
  _params.H = dht.readHumidity();
  _params.T = dht.readTemperature();
}
 
//获取PM2.5的值
void getPM25(unsigned char ucData) {
 
  ucRxBuffer[ucRxCnt++] = ucData;
 
  if (ucRxBuffer[0] != 0x42 && ucRxBuffer[1] != 0x4D)  {
    ucRxCnt = 0;
  }
  if (ucRxCnt > 31) {
    _params._P = (float)ucRxBuffer[6] * 256 + (float)ucRxBuffer[7]; //美国标准
    //    _params._P = (float)ucRxBuffer[12] * 256 + (float)ucRxBuffer[13]; //中国标准
    ucRxCnt = 0;
  }
}
 
//中位值平均滤波，处理PM2.5的值
#define FILTER_N 5
int Filter() {
  int i;
  int filter_sum = 0;
  int filter_max, filter_min;
  int filter_buf[FILTER_N];
  for (i = 0; i < FILTER_N; i++) {
    filter_buf[i] = _params._P;
    delay(1);
  }
  filter_max = filter_buf[0];
  filter_min = filter_buf[0];
  filter_sum = filter_buf[0];
  for (i = FILTER_N - 1; i > 0; i--) {
    if (filter_buf[i] > filter_max)
      filter_max = filter_buf[i];
    else if (filter_buf[i] < filter_min)
      filter_min = filter_buf[i];
    filter_sum = filter_sum + filter_buf[i];
    filter_buf[i] = filter_buf[i - 1];
  }
  i = FILTER_N - 2;
  filter_sum = filter_sum - filter_max - filter_min + i / 2; // +i/2 的目的是为了四舍五入
  filter_sum = filter_sum / i;
  return filter_sum;
}
 
void loop() {
 
  while (mySerial.available())   {
    getPM25(mySerial.read());
  }
  _params.P = Filter();
 
  //DHT22更新数据速度很慢，所以不要读的那么快
  if (loopCnt % 40 == 0) {
    getDHT22();
  }
 
  if (++loopCnt > 99) {
    loopCnt = 0;
  }
 
  u8g.firstPage();
  do {
    draw();
  } while ( u8g.nextPage());
}


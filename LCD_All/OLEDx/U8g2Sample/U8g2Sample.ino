#include <U8g2lib.h>
#include <U8x8lib.h>


/*
   本例用于演示 u8glib2图形 函数 drawXBMP, drawXBM的使用。
   void   U8GLIB ::  drawXBM (  u8g_uint_t x ,   u8g_uint_t y ,   u8g_uint_t w ,   u8g_uint_t h ,  <span class="kwd">const   uint8_t  *  bitmap )
   void   U8GLIB ::  drawXBMP (  u8g_uint_t x ,   u8g_uint_t y ,   u8g_uint_t w ,   u8g_uint_t h ,  <span class="kwd">const   u8g_pgm_uint8_t  *  bitmap )
   (x,y)组成的坐标表示待显示内容的左上角在屏幕上的坐标
   [w,h] 表示显示内容的宽和高,单位是像素
 * *bimmap是指向内容的指针

   本例中所用到的硬件包括 Arduino UNO R3, Newbit OLED Shield

   作者: Tome / Newbit Studio
   网店: newbit.taobao.com
   资料: www.newbitstudio.com
   版本: 1.00
   日期：2016.12.16
*/

// 使用 3线 SPI 驱动 Newbit OLED Shield (SSD1306屏)
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, 2);

#define ICON_X_POS  30

// 国际象棋图标
const uint8_t rook_bitmap[]  PROGMEM = {
  0X00, 0X55, 0X7F, 0X3E, 0X3E, 0X3E, 0X3E, 0X7F,
};

// 显示一个国际象棋图标
void drawSimpleRook(void) {
  u8g2.drawXBMP(ICON_X_POS, 20, 8, 8, rook_bitmap);
}

//-------------------------------------以下用一个数组来表示一个三角形--------------------------------------

/*       3*3点阵 1/2
 *           * * *
 *             * *
 *               *
*/
const uint8_t ele3x3[] PROGMEM = {
  0X07,
  0X06,
  0X04,
};


/*           6*6点阵 1/2
 *           * * * * * *
 *             * * * * *
 *               * * * *
 *                 * * *
 *                   * *
 *                     *
*/
const uint8_t ele6x6[] PROGMEM = {
  0x3F,
  0x3e,
  0x3c,
  0x38,
  0x30,
  0x20
};

/*               10*10点阵 1/2
 *           * * * * * * * * * *
 *             * * * * * * * * *
 *               * * * * * * * *
 *                 * * * * * * *
 *                   * * * * * *
 *                     * * * * *
 *                       * * * *
 *                         * * *
 *                           * *
 *                             *
*/

const uint8_t ele10x10[] PROGMEM = {
  0xff, 0x03,
  0xfe, 0x03,
  0xfc, 0x03,
  0xf8, 0x03,
  0xf0, 0x03,
  0xe0, 0x03,
  0xc0, 0x03,
  0x80, 0x03,
  0x00, 0x03,
  0x00, 0x02,


  /*
    0xff,0x03,
    0x7f,0x03,
    0x3f,0x03,
    0x1f,0x03,
    0x0f,0x03,
    0x07,0x03,
    0x03,0x03,
    0xff,0x03,
    0xff,0x03,
    0xff,0x03,
  */
};



void drawSample3x3(void) {
  /* display 3x3 */

  //输出一个 3x3的正方形作为参考
  // u8g2.drawBox(ICON_X_POS, 10, 3, 3);


  // 使用带P后辍的函数，可以直接输出 ROM上存放的图片
  u8g2.drawXBMP(ICON_X_POS, 30, 3, 3, ele3x3);

  /*
    // 使用不带P的函数，需要图片数据复制到ram上，之后再调用显示函数
      uint8_t ele[10];

      //输出一系列的内容，助于理解函数输入与显示之间的关系
      for ( int i  = 0; i< 3; i++ )
          ele[i] = 0xf3;
      u8g2.drawXBM(ICON_X_POS,20, 3, 3,ele);

      for ( int i  = 0; i< 3; i++ )
          ele[i] = 0xfd;
      u8g2.drawXBM(ICON_X_POS,25, 3, 3,ele);

      for ( int i  = 0; i< 3; i++ )
          ele[i] = 0xfe;
      u8g2.drawXBM(ICON_X_POS,30, 3, 3,ele);

      for ( int i  = 0; i< 3; i++ )
          ele[i] = 0x07;
      u8g2.drawXBM(ICON_X_POS,35, 3, 3,ele);
  */
}


void drawSample6x6(void) {
  u8g2.drawBox(ICON_X_POS, 10, 6, 6);
  u8g2.drawXBMP(ICON_X_POS, 30, 6, 6, ele6x6);
}

void drawSample10x10(void) {
  u8g2.drawBox(ICON_X_POS, 10, 10, 10);
  u8g2.drawXBMP(ICON_X_POS, 30, 10, 10, ele10x10);
}

void drawSample(uint8_t state) {

  switch (state)  {
    case 0:
    case 1:
    case 2: drawSample3x3(); break;

    case 3:
    case 4:
    case 5:
      drawSample6x6();
      break;

    case 6:
    case 7:
    case 8:
      drawSample10x10();
      break;

    default:
      drawSimpleRook();
      break;
  }

}

/*
  显示 【NEWBIT STUDIO】 工作室的信息
*/
void newbit_info(void) {
  //u8g2.drawFrame(0, 50, 128, 14);             // 划框
  u8g2.drawLine(0, 50, 127, 50);                // 划分界线
  u8g2.setFont(u8g_font_5x8);                   // 设置 字体
  //u8g2.drawStr(20,60, "Newbit Studio");       //
  u8g2.drawStr(15, 60, "www.newbitstudio.com"); // 显示网址
}

/*
   显示实验信息
*/
void project_inof(void) {
  u8g2.setFont(u8g_font_5x8);
  u8g2.drawStr(65, 20, "drawXBM()");
  u8g2.drawStr(65, 30, "3x3,6x6");
  u8g2.drawStr(65, 40, "10x10");
}


void setup() {
  u8g2.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

  static uint8_t state = 0;

  u8g2.firstPage();
  do {
    drawSample(state);
    newbit_info();
    project_inof();
  } while ( u8g2.nextPage() );
  delay(1000);

  state++; if ( ++state > 10)
    state = 0;
}



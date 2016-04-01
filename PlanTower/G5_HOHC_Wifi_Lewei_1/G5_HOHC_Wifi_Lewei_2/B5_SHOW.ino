//void infoDraw() {
//  showTemperature();
//  showPM25();
//  showRH();
//}
//void showTemperature(void) {
//  int x = 30, y = 10;//温度显示位置
//  //画LOGO
//  u8g.drawRFrame(x, y, 16, 16, 1);
//  u8g.drawFrame(x + 5, y + 3, 3, 6);
//  u8g.drawDisc(x + 6, y + 10, 2);
//  u8g.setFont(u8g_font_04b_03b);
//  u8g.setPrintPos(x + 10, y + 8);
//  u8g.print("C");
//
//  //设置双倍大小字体显示
//  u8g.setScale2x2();
//  u8g.setPrintPos(x / 2 + 11, y / 2 + 7);
//  u8g.setFont(u8g_font_orgv01);
//  u8g.print(g.pm25);
//  u8g.undoScale();
//}
//
//void showPM25(void) {
//  int x = 30, y = 28;//PM2.5显示位置
//  //画LOGO
//  u8g.drawRFrame(x, y, 16, 16, 1);
//  u8g.setFont(u8g_font_orgv01);
//  u8g.setPrintPos(x + 3, y + 10);
//  u8g.print("pm");
//
//  //设置双倍大小字体显示
//  u8g.setScale2x2();
//  u8g.setPrintPos(x / 2 + 11, y / 2 + 7);
//  u8g.setFont(u8g_font_orgv01);
//  u8g.print(g.cf25);
//  u8g.undoScale();
//}
//
//void showRH() {
//  int x = 30, y = 46;//湿度显示位置
//  //画LOGO
//  u8g.drawRFrame(x, y, 16, 16, 1);
//  u8g.drawFrame(x + 5, y + 3, 3, 6);
//  u8g.drawDisc(x + 6, y + 10, 2);
//  u8g.setFont(u8g_font_04b_03b);
//  u8g.setPrintPos(x + 10, y + 8);
//  u8g.print("H");
//
//  //设置双倍大小字体显示
//  u8g.setScale2x2();
//  u8g.setPrintPos(x / 2 + 11, y / 2 + 7);
//  u8g.setFont(u8g_font_orgv01);
//  u8g.print(28);
//  u8g.undoScale();
//}

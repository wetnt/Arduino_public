void infoDraw() {
  show_TH(0, 0,'C',Si_Temperature);
  show_TH(0,20,'H',Si_Humidity);
  show_PM(0,40,"PM",g.cf25);     
  show_PM(64, 0,"1.0",g.cf10);
  show_PM(64,20,"2.5",g.cf25);
  show_PM(64,40,"10.0",g.cf1X);
}
//===================================================
void showTemperature(int xx, int yy, char cc, int vv) {
  int x = xx, y = yy;//温度显示位置
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
  u8g.print(Si_Temperature);
  u8g.undoScale();
}
void showRH(int xx, int yy, char cc, int vv) {
  int x = xx, y = yy;//湿度显示位置
  //画LOGO
  u8g.drawRFrame(x, y, 16, 16, 1);
  u8g.drawFrame(x + 5, y + 3, 3, 6);
  u8g.drawDisc(x + 6, y + 10, 2);
  u8g.setFont(u8g_font_04b_03b);
  u8g.setPrintPos(x + 10, y + 8);
  u8g.print(cc);

  //设置双倍大小字体显示
  u8g.setScale2x2();
  u8g.setPrintPos(x / 2 + 11, y / 2 + 7);
  u8g.setFont(u8g_font_orgv01);
  u8g.print(vv);
  u8g.undoScale();
}


void showPM25(int xx, int yy) {
  int x = xx, y = yy;//PM2.5显示位置
  //画LOGO
  u8g.drawRFrame(x, y, 16, 16, 1);
  u8g.setFont(u8g_font_orgv01);
  u8g.setPrintPos(x + 3, y + 10);
  u8g.print("pm");

  //设置双倍大小字体显示
  u8g.setScale2x2();
  u8g.setPrintPos(x / 2 + 11, y / 2 + 7);
  u8g.setFont(u8g_font_orgv01);
  u8g.print(g.cf25);
  u8g.undoScale();
}
//===================================================
void show_TH(int x, int y, char c, int v) {
  draw_Icon(x,y,c);
  draw_Value(x,y,v);
}
void show_PM(int x, int y, String s, int v) {
  draw_String(x,y,s);
  draw_Value(x,y,v);
}
void draw_String(int x, int y,String s) {//画LOGO
  u8g.drawRFrame(x, y, 16, 16, 1);
  u8g.setFont(u8g_font_orgv01);
  u8g.setPrintPos(x + 3, y + 10);
  u8g.print(s);
}
void draw_Icon(int x,int y,char c){//画LOGO ICON  
  u8g.drawRFrame(x, y, 16, 16, 1);
  u8g.drawFrame(x + 5, y + 3, 3, 6);
  u8g.drawDisc(x + 6, y + 10, 2);
  u8g.setFont(u8g_font_04b_03b);
  u8g.setPrintPos(x + 10, y + 8);
  u8g.print(c);
}
void draw_Value(int x,int y,int v){//设置双倍大小字体显示
  u8g.setScale2x2();
  u8g.setPrintPos(x / 2 + 11, y / 2 + 7);
  u8g.setFont(u8g_font_orgv01);
  u8g.print(v);
  u8g.undoScale();
}
//===================================================

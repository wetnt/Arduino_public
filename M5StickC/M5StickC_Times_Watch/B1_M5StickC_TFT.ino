//https://docs.m5stack.com/#/zh_CN/api/lcd_m5stickc
int lcd_Breath = 8;//(7+16)/2;
//--------------------------------------------------
void lcd_setup() {
  //--------------------------------------------------
  M5.Lcd.setRotation(3);
  //M5.Axp.ScreenBreath(8);
  M5.Axp.ScreenBreath(lcd_Breath);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0, 2);
  M5.Lcd.println("M5StickC LCD TEST");
  //--------------------------------------------------
  pinMode(M5_BUTTON_HOME, INPUT);
  //--------------------------------------------------
}
void lcd_Breath_set() {
  lcd_Breath += 8;
  if (lcd_Breath > 16)lcd_Breath = 8;
  M5.Axp.ScreenBreath(lcd_Breath);
}
void lcd_show(String str) {
  Serial.println(str);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0, 2);
  M5.Lcd.println(str);
}
//============================================================================
void drawFontFaceDemo() {
  //oled.setTextAlignment(TEXT_ALIGN_LEFT);
  //oled.setFont(ArialMT_Plain_10); oled.drawString(0, 0, "Hello world");
  //oled.setFont(ArialMT_Plain_16); oled.drawString(0, 10, "Hello world");
  //oled.setFont(ArialMT_Plain_24); oled.drawString(0, 26, "Hello world");
  //oled.display();
}
void drawTextFlowDemo() {
  //oled.setFont(ArialMT_Plain_10); oled.setTextAlignment(TEXT_ALIGN_LEFT);
  //oled.drawStringMaxWidth(0, 0, 128, "I love you Baby!!!" );
}
//============================================================================

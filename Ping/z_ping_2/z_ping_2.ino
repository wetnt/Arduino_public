float len = 0;
float box = 10.70;
float lenbox = 0;
void setup() {
  Serial.begin(115200);
  LCD_setup();
  PingSetup(A2, A3);
}

void loop() {
  //--------------------------------------------------------
  len = PingLoop();
  lenbox = len + box;
  //--------------------------------------------------------
  lcd_clear();
  lcd_show_float(0, 0, len);
  lcd_show_string(6, 0, "+ ");
  lcd_show_float(8, 0, box);
  lcd_show_string(0, 1, "=");
  lcd_show_float(2, 1, lenbox);
  lcd_show_string(8, 1, "cm");
  //--------------------------------------------------------
  delay(500);
  //--------------------------------------------------------
}

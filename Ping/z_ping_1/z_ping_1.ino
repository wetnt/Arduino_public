float cm = 0;
void setup() {
  Serial.begin(115200);
  LCD_setup();
  PingSetup(A2,A3);
}

void loop() {
  //--------------------------------------------------------
  cm = PingLoop();
  lcd_show_float(0,0,cm);
  //--------------------------------------------------------
  delay(500);
  //--------------------------------------------------------
}

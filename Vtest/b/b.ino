static const String codeName = "Battery_Test_b!";
void setup() {
  //------------------------------------------------
  lgsetup(codeName);
  //------------------------------------------------
  LCD1602_setup(); LCD1602_Clear();
  LCD1602_Show(0, 0, codeName);
  //------------------------------------------------
  Battery_Setup();
  //------------------------------------------------
}
void loop() {
  Battery_Setup();
  Battery_loop();
  Battery_log();
  Battery_Lcd();
}


void setup() {
  //-------------------------------------
  Log_setup();
  //APC220_setup();
  //-------------------------------------
  LcdSetup(5, 6, 7, 9, 8, 70);
  //-------------------------------------
  JoystickSetup();
  //-------------------------------------
  delay(2000);
  LcdClear();
  //-------------------------------------
}


void loop() {
  //LcdTest();
  JoystickReadRun();
  JoystickReadShow();
  JoystickShowLcd();
  delay(50);
}


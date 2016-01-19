
void setup() {
  //-------------------------------------
  Log_setup();
  //-------------------------------------
  LcdSetup(5, 6, 7, 9, 8, 70);
  JoystickSetup();
  APC220_setup();
  //-------------------------------------
  delay(1000);
  LcdClear();
  //-------------------------------------
}


void loop() {
  //-------------------------------------
  JoystickReadRun();
  JoystickShowLcd();
  smartDelay(200);
  //-------------------------------------
}
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis(); do {
    //------------------------------------------
    APC220_Feed();
    //------------------------------------------
  } while (millis() - start < ms);
}


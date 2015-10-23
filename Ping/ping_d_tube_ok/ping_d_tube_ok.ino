float cm = 0;
char cmt[8] = {0, 0, 0, 0, 0, 0, 0, 0};

void setup()
{
  Serial.begin(115200);
  PingSetup(3, 2);
  Tube_Setup();
}
void loop()
{
  cm = PingLoop();
  dtostrf(cm, 4, 2, cmt);
  tube_show((unsigned char *)cmt);
}


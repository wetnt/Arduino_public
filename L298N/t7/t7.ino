float cm = 100;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  BKMOTO(42,40,38,36,34,32);
  //BKMOTO(4,5,6,7,8,9);
  Code_setIn();
  LCD_Setup();
  Serial.println("$JML,CAR,SAN,0,0,0,0,0,0;");
}

void loop() {
  //-----------------------
  SerialRead();
  //-----------------------------
  cm = 100;
  LCD_Loop(true);
  CmdLoop(cm);
  //-----------------------  
}

void SerialRead()
{
  //-------------------------------------------------------------------------
  while (Serial1.available()>0)
  {
    CmdExp(Serial1.read());    
  }
  //-------------------------------------------------------------------------
}


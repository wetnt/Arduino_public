float cm = 0;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  //BKMOTO(4,5,6,7,8,9);
  BKMOTO(22,24,26,28,30,32);
  PingSetup();
  IR_Setup(53,51,49);
  Code_setIn();
  Serial.println("$JML,CAR,SAN,0,0,0,0,0,0;");
}

void loop() {
  //-----------------------
  SerialRead();
  //PingLoop();
  IR_Loop();
  //-----------------------------
  //cm = PingGetCM();
  cm = IR_Get();
  //-----------------------------
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


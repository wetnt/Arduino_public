void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  //BKMOTO(4,5,6,7,8,9);
  //BKMOTO(9,8,7,6,5,4);
  BKMOTO(22,24,26,28,30,32);
  //BKMOTO(42,40,38,36,34,32);
  Code_setIn();
  Serial.println("$JML,CAR,SAN,0,0,0,0,0,0;");
}

void loop() {
  //-----------------------
  //CmdLoop(100);
  RunF(100,0);
  delay(2000);
  RunStop();
  delay(2000);
  RunB(100,0);
  delay(2000);
  RunStop();
  delay(2000);
  //-----------------------  
}


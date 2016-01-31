//====================================
int PinAX = A0,PinAY = A1,PinAK = 12;
int PinBX = A2,PinBY = A3,PinBK = 13;
int PinCX = A6,PinCY = A7,PinCK = A4;
//====================================
int IntAX = 0,IntAY = 0,IntAK = 0;
int IntBX = 0,IntBY = 0,IntBK = 0;
int IntCX = 0,IntCY = 0,IntCK = 0;
//====================================
String strCMD = String("$JML,CAR,SAN,A,B,C,4,5,6,7,8,9,10,11,12;");
//====================================
void setup()
{
  //-------------------------------------------- 
  Serial.begin(9600);
  //-------------------------------------------- 
  pinMode(PinAX, INPUT);
  pinMode(PinAY, INPUT);
  pinMode(PinAK, INPUT);
  pinMode(PinBX, INPUT);
  pinMode(PinBY, INPUT);
  pinMode(PinBK, INPUT);
  //pinMode(PinCX, INPUT);
  //pinMode(PinCY, INPUT);
  //pinMode(PinCK, INPUT);
  //-------------------------------------------- 
}

void loop(){
  readRun();
  readShow();
}

void readRun(){
  //-------------------------------------------- 
  IntAX = readAxis(PinAX);
  IntAY = readAxis(PinAY);
  IntAK = digitalRead(PinAK);
  IntBX = readAxis(PinBX);
  IntBY = readAxis(PinBY);
  IntBK = digitalRead(PinBK);
  //IntCX = readAxis(PinCX);
  //IntCY = readAxis(PinCY);
  //IntCK = readAxis(PinCK);
  //-------------------------------------------- 
}

void readShow(){
  //-------------------------------------------- 
  Serial.print(IntAX, DEC);  Serial.print(" "); 
  Serial.print(IntAY, DEC);  Serial.print(" "); 
  Serial.print(IntAK, DEC);  Serial.print(" "); 
  Serial.print(IntBX, DEC);  Serial.print(" "); 
  Serial.print(IntBY, DEC);  Serial.print(" "); 
  Serial.print(IntBK, DEC);  Serial.print(" "); 
  Serial.print(IntCX, DEC);  Serial.print(" "); 
  Serial.print(IntCY, DEC);  Serial.print(" "); 
  Serial.print(IntCK, DEC);  Serial.print(" "); 
  Serial.println(""); 
  
  strCMD  = String("$JML,CAR,SAN,");
  strCMD += String("$JML,CAR,SAN,");A,B,C,4,5,6,7,8,9,10,11,12;");
  //--------------------------------------------  
}




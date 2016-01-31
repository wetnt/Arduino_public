//====================================
int PinAX = A0;
int PinAY = A1;
int PinAK = A6;
int PinBX = A2;
int PinBY = A3;
int PinBK = A7;
//====================================
void setup()
{
  Serial.begin(9600);
  pinMode(inputPin, INPUT);
  pinMode(inputPin, INPUT);
  pinMode(inputPin, INPUT);
  pinMode(inputPin, INPUT);
  pinMode(inputPin, INPUT);
  pinMode(inputPin, INPUT);
  pinMode(ledssPin,OUTPUT);
}

void loop(){
  readRun();
}

void readRun(){
  //-------------------------------------------- 
  int vala = readAxis(A0);
  int valb = readAxis(A1);
  Serial.print(vala, DEC);
  Serial.print(" "); 
  Serial.println(valb, DEC); 
  //--------------------------------------------  
}



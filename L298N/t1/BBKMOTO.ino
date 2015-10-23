int motoA1,motoA2,motoAS,motoB1,motoB2,motoBS;
void BKMOTO(int aa,int ac,int as,int ba,int bc,int bs){
  motoA1 = aa;
  motoA2 = ac;
  motoAS = as;
  motoB1 = ba;
  motoB2 = bc;
  motoBS = bs;
  pinMode(motoA1, OUTPUT);
  pinMode(motoA2, OUTPUT);
  pinMode(motoAS, OUTPUT);
  pinMode(motoB1, OUTPUT);
  pinMode(motoB2, OUTPUT);
  pinMode(motoBS, OUTPUT);
}
void MotoRunA(int a,int s){
  if(s>255)s=255;
  analogWrite(motoAS, s);
  if (a == 0) {
    digitalWrite(motoA1, LOW);
    digitalWrite(motoA2, LOW);
  } 
  else if (a > 0) {
    digitalWrite(motoA1, HIGH);
    digitalWrite(motoA2, LOW);
  } 
  else if (a < 0) {
    digitalWrite(motoA1, LOW);
    digitalWrite(motoA2, HIGH);
  }
}
void MotoRunB(int a,int s){
  if(s>255)s=255;
  analogWrite(motoBS, s);
  if (a == 0) {
    digitalWrite(motoB1, LOW);
    digitalWrite(motoB2, LOW);
  } 
  else if (a > 0) {
    digitalWrite(motoB1, HIGH);
    digitalWrite(motoB2, LOW);
  } 
  else if (a < 0) {
    digitalWrite(motoB1, LOW);
    digitalWrite(motoB2, HIGH);
  }
}


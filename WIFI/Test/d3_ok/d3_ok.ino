
void setup() {

  Serial.begin(9600);
  delay(1000);
  Serial.println("begin...");
  delay(5000);  

  ATSend("AT+ID","done");
  delay(2000);
  ATSend("AT+JoinAP?","done");
  delay(2000);
  ATSend("AT+ShowIP","done");
  delay(2000);
  ATSend("AT+NewSTA=\"UDP\",\"192.168.1.100\",8080","done");
  delay(2000);
  ATSend("AT+UpDate=10",">");
  delay(2000);
  ATSend("boboking123","SEND OK");
  delay(2000);
}

void ATSend(String cmd,String back){
  Serial.println(cmd);
  waitBack(back);  
}


void waitBack(String str){
  //------------------------
  //bool backkey = false;
  //------------------------
  String data;
  while (1) {
    if(Serial.available()>0)
    {
      char a = Serial.read();
      data = data+a;
    }
    if (data.indexOf(str)!=-1)
    {
      break;
    }
    if (data.indexOf("ERROR")!=-1)
    {
      break;
    }
    //Serial.print(".");
  }
  //------------------------
}

void NetSend(String x) {
  int n = x.length()+1;
  String s = String("AT+UpDate=")+String(n);
  ATSend(s,">");//delay(1000);
  ATSend(x,"SEND OK");
}

void loop() {  
  long t = millis();
  String s = String(t);
  //NetSend(s);delay(2000);  
  //NetSend("BOBOKing1234567890");delay(2000);
}



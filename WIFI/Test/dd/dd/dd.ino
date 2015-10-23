
void setup() {

  Serial.begin(9600);
  Serial1.begin(9600);
  delay(1000);
  Serial.println("begin...");
  delay(5000);  

  ATSend("AT+ID","done");
  delay(1000);
  ATSend("AT+JoinAP?","JoinAP");
  delay(1000);
  ATSend("AT+ShowIP","done");
  delay(1000);
  ATSend("AT+NewSTA=\"UDP\",\"192.168.1.100\",8080","done");
  delay(1000);
  ATSend("AT+UpDate=10",">");
  delay(1000);
  ATSend("boboking123","SEND OK");
  delay(1000);
}

void ATSend(String cmd,String back){
  Serial1.println(cmd);
  waitBack(back);  
}


void waitBack(String str){
  //------------------------
  Serial.print("wait--");
  Serial.println(str);
  //------------------------
  String data;
  while (1) {
    if(Serial1.available()>0)
    {
      char a = Serial1.read();
      data = data+a;
      Serial.print(a);
    }
    if (data.indexOf(str)!=-1)
    {
      Serial.println("_ok");
      break;
    }
    if (data.indexOf("ERROR")!=-1)
    {
      Serial.println("_ERROR");
      break;
    }
    //Serial.print(".");
  }
  //------------------------
}

void NetSend(String str) {
  int n = str.length()+1;
  String s = String("AT+UpDate=")+String(n);
  ATSend(s,">");//delay(1000);
  ATSend(str,"SEND OK");
}

void loop() {  
  long t = millis();
  String s = String(t);
  NetSend(s);delay(2000);  
}



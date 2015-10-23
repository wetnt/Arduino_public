
void setup() {

  Serial.begin(9600);
  Serial1.begin(9600);
  delay(1000);
  Serial.println("begin...");
  delay(5000);

  Serial1.println("AT+ID");
  waitBack("192"); 
}

void waitBack(String str){
  //------------------------
  Serial.print("wait--");
  Serial.print(str);
  //------------------------
  while(1){
    if(//
    Serial1.find("192")==true || 
      Serial1.find("done")==true || 
      Serial1.find("Link is builded")==true)//
    {
      Serial.println("ok");
      break;
    }
    Serial.print(".");
  }
  //------------------------
}

void loop() {
  while (Serial1.available()>0)
  {
    char x = Serial1.read();  
    Serial.print(x);  
  }  
}





//arduino的String类
//http://blog.csdn.net/sh307976/article/details/36421055

void setup() {
  Serial.begin(9600);
}

String tm = "2015-06-08 13:54:15";
String tp = "";
void loop() {
  //-----------------------------------
  if (Serial.available() > 0) {
    char inChar = Serial.read();
    tp += inChar;
  }
  //-----------------------------------
  if (tp.length() >= 19) {
    tm = tp;
    tp = "";
    
    Serial.println(tm.substring(0,2));
    Serial.println(tm.substring(3,4));
    Serial.println(tm.substring(0,2));
    Serial.println(tm.substring(0,2));
    Serial.println(tm.substring(0,2));
    Serial.println(tm.substring(0,2));
    Serial.println(tm.substring(0,2));
    Serial.println(tm.substring(0,2));
  }
  //-----------------------------------
}

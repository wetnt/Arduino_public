
float a[3], w[3], Angle[3], T;
unsigned char sign = 0;
unsigned char Re_buf[11],counter=0;

void setup() {

  Serial.begin(115200);
  Serial3.begin(115200);

}

void loop() {


  //Serial.print("angle:");
  //Serial.print(Angle[0]);  Serial.print(" ");
  //Serial.print(Angle[1]);  Serial.print(" ");
  //Serial.print(Angle[2]);  Serial.print(" ");
  //Serial.print(" ");
  //
  //Serial.print("a:");
  //Serial.print(a[0]);  Serial.print(" ");
  //Serial.print(a[1]);  Serial.print(" ");
  //Serial.print(a[2]);  Serial.print(" ");
  //Serial.print(" ");
  //
  //Serial.print("w:");
  //Serial.print(w[0]);  Serial.print(" ");
  //Serial.print(w[1]);  Serial.print(" ");
  //Serial.print(w[2]);  Serial.print(" ");
  //Serial.print(" ");
  //
  Serial.print("T:");
  Serial.print(T);  Serial.print(" ");
  Serial.println(" ");
  
  //Serial.println(Re_buf);
  delay(200);
  


}

void serialEvent() {
  
  while (Serial3.available()) {
    
    Re_buf[counter] = (unsigned char)Serial3.read();
    if (counter == 0 && Re_buf[0] != 0x55) return; //第0号数据不是帧头
    counter++;
    if (counter == 11)          //接收到11个数据
    {
      counter = 0;             //重新赋值，准备下一帧数据的接收
      switch (Re_buf [1])
      {
        case 0x51:
          a[0] = float(short(Re_buf [3] << 8 | Re_buf [2])) / 32768 * 16;
          a[1] =  float(short(Re_buf [5] << 8 | Re_buf [4])) / 32768 * 16;
          a[2] =  float(short(Re_buf [7] << 8 | Re_buf [6])) / 32768 * 16;
          break;
        case 0x52:
          w[0] =  float(short(Re_buf [3] << 8 | Re_buf [2])) / 32768 * 250;
          w[1] =  float(short(Re_buf [5] << 8 | Re_buf [4])) / 32768 * 250;
          w[2] =  float(short(Re_buf [7] << 8 | Re_buf [6])) / 32768 * 250;
          break;
        case 0x53:
          Angle[0] =  float(short(Re_buf [3] << 8 | Re_buf [2])) / 32768 * 180;
          Angle[1] =  float(short(Re_buf [5] << 8 | Re_buf [4])) / 32768 * 180;
          Angle[2] =  float(short(Re_buf [7] << 8 | Re_buf [6])) / 32768 * 180;
          T =  float(short(Re_buf [9] << 8 | Re_buf [8])); ///340.0+36.25
          sign = 1;
          //Serial.println("a");
          break;
      }
    }
  }
  
}




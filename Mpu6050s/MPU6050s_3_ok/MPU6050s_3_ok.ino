
float a[3], w[3], angle[3], T;
unsigned char sign = 0;
unsigned char Re_buf[11], counter = 0;

//---------------------------------------
long t0;//计时器
long RunTime()
{
  return ( micros() - t0 ) / 1000;
}
//---------------------------------------


void setup() {
  Serial.begin(115200);
  Serial3.begin(115200);
}

void loop() {
  
  if (RunTime() > 200)
  {
    t0 = micros();
    mathSensors();

    Serial.print("angle:");
    Serial.print(angle[0]);  Serial.print(" ");
    Serial.print(angle[1]);  Serial.print(" ");
    Serial.print(angle[2]);  Serial.print(" ");
    Serial.print(" ");

    Serial.print("a:");
    Serial.print(a[0]);  Serial.print(" ");
    Serial.print(a[1]);  Serial.print(" ");
    Serial.print(a[2]);  Serial.print(" ");
    Serial.print(" ");

    Serial.print("w:");
    Serial.print(w[0]);  Serial.print(" ");
    Serial.print(w[1]);  Serial.print(" ");
    Serial.print(w[2]);  Serial.print(" ");
    Serial.print(" ");

    Serial.print("T:");
    Serial.print(T);  Serial.print(" ");
    Serial.println(" ");

    //Serial.println(Re_buf);

  }

}

void mathSensors() {
  if (sign)
  {
    sign = 0;
    if (Re_buf[0] == 0x55)   //检查帧头
    {
      switch (Re_buf [1])
      {
        case 0x51:
          a[0] = (short(Re_buf [3] << 8 | Re_buf [2])) / 32768.0 * 16;
          a[1] = (short(Re_buf [5] << 8 | Re_buf [4])) / 32768.0 * 16;
          a[2] = (short(Re_buf [7] << 8 | Re_buf [6])) / 32768.0 * 16;
          T = (short(Re_buf [9] << 8 | Re_buf [8])) / 340.0 + 36.25;
          break;
        case 0x52:
          w[0] = (short(Re_buf [3] << 8 | Re_buf [2])) / 32768.0 * 2000;
          w[1] = (short(Re_buf [5] << 8 | Re_buf [4])) / 32768.0 * 2000;
          w[2] = (short(Re_buf [7] << 8 | Re_buf [6])) / 32768.0 * 2000;
          T = (short(Re_buf [9] << 8 | Re_buf [8])) / 340.0 + 36.25;
          break;
        case 0x53:
          angle[0] = (short(Re_buf [3] << 8 | Re_buf [2])) / 32768.0 * 180;
          angle[1] = (short(Re_buf [5] << 8 | Re_buf [4])) / 32768.0 * 180;
          angle[2] = (short(Re_buf [7] << 8 | Re_buf [6])) / 32768.0 * 180;
          T = (short(Re_buf [9] << 8 | Re_buf [8])) / 340.0 + 36.25;
          break;
      }
    }
  }
}

void serialEvent3() {//伪终端，loop()里不能有有delay
  //---------------------------while---------------------------------
  while (Serial3.available()) {
    //---------------------------while---------------------------------
    Re_buf[counter] = (unsigned char)Serial3.read();
    if (counter == 0 && Re_buf[0] != 0x55) return; //第0号数据不是帧头
    //------------------------------------------------------------
    counter++;
    if (counter == 11)          //接收到11个数据
    {
      counter = 0;             //重新赋值，准备下一帧数据的接收
      sign = 1;
    }
    //---------------------------while---------------------------------
  }
  //---------------------------while---------------------------------
}




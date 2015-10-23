int pinI1=8;//定义I1接口
int pinI2=9;//定义I2接口
int speedpin=11;//定义EA(PWM调速)接口
int pinI3=6;//定义I3接口
int pinI4=7;//定义I4接口
int speedpin1=10;//定义EB(PWM调速)接口
int IRR=3;//定义右侧避障传感器接口
int IRM=4;//定义中间避障传感器接口
int IRL=5;//定义左侧避障传感器接口
void setup()
{
  pinMode(pinI1,OUTPUT);
  pinMode(pinI2,OUTPUT);
  pinMode(speedpin,OUTPUT);
  pinMode(pinI3,OUTPUT);
  pinMode(pinI4,OUTPUT);
  pinMode(speedpin1,OUTPUT);
  pinMode(IRR,INPUT);
  pinMode(IRM,INPUT);
  pinMode(IRL,INPUT);
}
void advance(int a)//前进
{
     analogWrite(speedpin,a);//输入模拟值进行设定速度
     analogWrite(speedpin1,a);
     digitalWrite(pinI4,LOW);//使直流电机（右）逆时针转
     digitalWrite(pinI3,HIGH);
     digitalWrite(pinI1,LOW);//使直流电机（左）顺时针转
     digitalWrite(pinI2,HIGH);
}
void right(int b)//右转
{
     analogWrite(speedpin,b);//输入模拟值进行设定速度
     analogWrite(speedpin1,b);
     digitalWrite(pinI4,HIGH);//使直流电机（右）顺时针转
     digitalWrite(pinI3,LOW);
     digitalWrite(pinI1,LOW);//使直流电机（左）顺时针转
     digitalWrite(pinI2,HIGH);
}
void left(int c)//左转
{
     analogWrite(speedpin,c);//输入模拟值进行设定速度
     analogWrite(speedpin1,c);
     digitalWrite(pinI4,LOW);//使直流电机（右）逆时针转
     digitalWrite(pinI3,HIGH);
     digitalWrite(pinI1,HIGH);//使直流电机（左）逆时针转
     digitalWrite(pinI2,LOW);
}
void stop()//停止
{
     digitalWrite(pinI4,HIGH);//使直流电机（右）制动
     digitalWrite(pinI3,HIGH);
     digitalWrite(pinI1,HIGH);//使直流电机（左）制动
     digitalWrite(pinI2,HIGH);
}
void back(int d)//后退
{
     analogWrite(speedpin,d);//输入模拟值进行设定速度
     analogWrite(speedpin1,d);
     digitalWrite(pinI4,HIGH);//使直流电机（右）顺时针转
     digitalWrite(pinI3,LOW);
     digitalWrite(pinI1,HIGH);//使直流电机（左）逆时针转
     digitalWrite(pinI2,LOW);
}
void loop()
{
    int r,m,l;
    r=digitalRead(IRR);
    m=digitalRead(IRM);
    l=digitalRead(IRL);
    if(l==HIGH &&m==HIGH && r==HIGH)
    advance(120);
    if(l==LOW &&m==LOW  && r==LOW )
      {
        back(120);
        delay(300);
        right(100);
        delay(100);
      }
    if(l==LOW &&m==HIGH  && r==LOW )
      {
        back(120);
        delay(300);
        right(100);
        delay(100);
      }
    if(l==HIGH  &&m==LOW  && r==HIGH  )
          {
        back(120);
        delay(300);
        right(100);
        delay(100);
      }
    if(l==LOW &&m==LOW  && r==HIGH )
    right(100);
    if(l==LOW && m==HIGH && r==HIGH)
    right(80);
    if(l==HIGH &&m==LOW  && r==LOW )
    left(100);
    if(l==HIGH &&m==HIGH  && r==LOW )
    left(80);
  
}

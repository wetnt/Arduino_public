//=====================================================================
int M11 = 50;
int M12 = 48;
int M21 = 42;
int M22 = 44;

int EN1 = 52; //使能端口1
int EN2 = 46; //使能端口2
//=====================================================================
void achou_init() {
  //------------------------------------------------------------
  int i;
  for (i = 42; i <= 50; i++) //为Ardunio 电机驱动板
    pinMode(i, OUTPUT); //设置数字端口4,5,6,7为输出模式
  //------------------------------------------------------------
  //设置数字端口10  11为输出模式
  pinMode(EN1, OUTPUT); digitalWrite(EN1, HIGH);
  pinMode(EN2, OUTPUT); digitalWrite(EN2, HIGH);
  //------------------------------------------------------------
}
void achou_run() {
  //------------------------------------------------------------
	if(angle[0]>30 && angle[0]<-30){
		SetMotor(0, 0);
		return;
	}
  //------------------------------------------------------------
  //float kp = 30, ki = 0.0, kd = 10, r1, r2;
  float kp = 500, ki = 0.0, kd = 10, r1, r2;
  kd = (float)analogRead(0) / 1024 * 200;
  //PID1、PID2函数就是第四节的PID函数，为了区分左右轮，所以分成两个。
  r1 = PID1(angle[0], kp, ki, kd); 
  r2 = PID2(angle[0], kp, ki, kd);
  SetMotor(r1, r2); //设置电机转速。
  //------------------------------------------------------------
}
//=====================================================================
void SetMotor(float v1, float v2)
{
  if (v1 > 255) {
    v1 = 255;
    analogWrite(M11, 0);
    analogWrite(M12, v1);
  }
  else if (v1 > 0) {
    analogWrite(M11, 0);
    analogWrite(M12, v1);
  }
  else if (v1 > -255) {
    analogWrite(M11, -v1);
    analogWrite(M12, 0);
  }
  else  {
    v1 = -255;
    analogWrite(M11, -v1);
    analogWrite(M12, 0);
  }

  if (v2 > 255) {
    v2 = 255;
    analogWrite(M21, 0);
    analogWrite(M22, v2);
  }
  else if (v2 > 0) {
    analogWrite(M21, 0);
    analogWrite(M22, v2);
  }
  else if (v2 > -255) {
    analogWrite(M21, -v2);
    analogWrite(M22, 0);
  }
  else {
    v2 = -255;
    analogWrite(M21, -v2);
    analogWrite(M22, 0);
  }
}

float PID1(float e, float kp, float ki, float kd)
{
  static float es = 0, sum = 0;
  float r;
  sum += e;
  r = kp * e + ki * sum + kd * (e - es);
  es = e;
  return r;
}
float PID2(float e, float kp, float ki, float kd)
{
  static float es = 0, sum = 0;
  float r;
  sum += e;
  r = kp * e + ki * sum + kd * (e - es);
  es = e;
  return r;
}
//=====================================================================
//=====================================================================
//=====================================================================
//=====================================================================
//=====================================================================
//=====================================================================
//=====================================================================

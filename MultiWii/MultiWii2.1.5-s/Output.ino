uint8_t PWM_PIN[8] = {9,10,11,3,6,5,A2,12};   //电机引脚顺序

/*****  写电机的PWM比较寄存器值  *****/
void writeMotors() { // [1000;2000] => [125;250]
  OCR1A = motor[0]>>3; //  pin 9: OCR1A与TCNT1进行比较,匹配改变OC1A的输出
  OCR1B = motor[1]>>3; //  pin 10: OCR1B与TCNT1进行比较,匹配改变OC1B的输出
  OCR2A = motor[2]>>3; //  pin 11: OCR2A与TCNT2进行比较,匹配改变OC2A的输出
  OCR2B = motor[3]>>3; //  pin 3: OCR2B与TCNT2进行比较,匹配改变OC2B的输出
}

/*****   将命令发送给所有的电机   *****/
void writeAllMotors(int16_t mc) {
  for (uint8_t i =0;i<4;i++) {
    motor[i]=mc;
  }
  writeMotors();  //写电机的PWM比较寄存器值
}

/*****   PWM定时寄存器初始化  *****/
void initOutput() {
  for(uint8_t i=0;i<4;i++) {
    pinMode(PWM_PIN[i],OUTPUT);  //所有的PWM引脚设置为输出
  }
    
  /*****  指定各PWM的定时寄存器   *****/
  TCCR1A |= _BV(COM1A1); //引脚9(PB1)连接到定时器1通道A(比较输出模式)
  TCCR1A |= _BV(COM1B1); //引脚10(PB2)连接到定时器1通道B(比较输出模式)
  TCCR2A |= _BV(COM2A1); //引脚11(PB3)连接到定时器2通道A(比较输出模式)
  TCCR2A |= _BV(COM2B1); //引脚3(PD3)连接到定时器2通道B(比较输出模式)

  /*****  电调校准 *****/
  #if defined(ESC_CALIB_CANNOT_FLY)
    writeAllMotors(ESC_CALIB_HIGH);
    delay(3000);
    writeAllMotors(ESC_CALIB_LOW);
    delay(500);
    while (1) {
      delay(5000);
      blinkLED(2,20, 2);
    }
    exit; // statement never reached
  #endif
  writeAllMotors(MINCOMMAND);  //将命令发送给所有的电机
  delay(300);
}

/***** 电机的稳定值混合计算  *****/
void mixTable() {
  int16_t maxMotor;
  uint8_t i;

  #define PIDMIX(X,Y,Z) rcCommand[THROTTLE] + axisPID[ROLL]*X + axisPID[PITCH]*Y + axisPID[YAW]*Z
  //防止“偏航跳跃”,偏航修正
  axisPID[YAW] = constrain(axisPID[YAW],-100-abs(rcCommand[YAW]),+100+abs(rcCommand[YAW]));
  /*****   组合表   *****/
  motor[0] = PIDMIX(-1,+1,-1); //向后_R
  motor[1] = PIDMIX(-1,-1,+1); //向前_R
  motor[2] = PIDMIX(+1,+1,+1); //向后_L
  motor[3] = PIDMIX(+1,-1,-1); //向前_L

  maxMotor=motor[0];
  for(i=1; i< 4; i++)
    if (motor[i]>maxMotor) maxMotor=motor[i];
  for(i=0; i< 4; i++) {
    if (maxMotor > MAXTHROTTLE) //
      motor[i] -= maxMotor - MAXTHROTTLE;
    motor[i] = constrain(motor[i], conf.minthrottle, MAXTHROTTLE);
    if ((rcData[THROTTLE] < MINCHECK))
      motor[i] = MINCOMMAND;
    if (!f.ARMED)
      motor[i] = MINCOMMAND;
  }
}

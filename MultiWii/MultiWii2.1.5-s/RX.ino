/*****   全局接收机相关变量   *****/
volatile uint16_t rcValue[RC_CHANS] = {1502, 1502, 1502, 1502, 1502, 1502, 1502, 1502}; //各通道值，区间[1000;2000]
static uint8_t rcChannel[RC_CHANS]  = {ROLLPIN, PITCHPIN, YAWPIN, THROTTLEPIN, AUX1PIN, AUX2PIN, AUX3PIN, AUX4PIN}; //各通道引脚
static uint8_t PCInt_RX_Pins[5] = {(1 << 2), (1 << 4), (1 << 5), (1 << 6), (1 << 7)}; //(1<<2)表示1向左移2位,等同于二进制的0b000000100

/*****   RX 引脚设置  *****/
void configureReceiver() {
  for (uint8_t i = 0; i < 5; i++) { //PCINT_PIN_COUNT = 5
    PORTD |= PCInt_RX_Pins[i];    //接收机的输入端口设置为上拉,参见ATmega168中文手册（P60）
    PCMSK2 |= PCInt_RX_Pins[i];   //电平变化中断,参见ATmega168中文手册（P76）
  }
  PCICR = (1 << 2);               //引脚电平变化中断控制寄存器
  PCICR  |= (1 << 0) ;            //PCINT激活B端口上引脚(D8-D13)
  PCMSK0 = (1 << 0);              //禁止D8电平变化中断,参见ATmega168中文手册（P60）
}

/*****   读标准RX引脚   *****/
#define RX_PIN_CHECK(pin_pos, rc_value_pos)\
if (mask & PCInt_RX_Pins[pin_pos]) {          
  if (!(pin & PCInt_RX_Pins[pin_pos])) {       //与D口输入值比较
    dTime = cTime - edgeTime[pin_pos];         //计算该引脚的PPM时间值
    if (900 < dTime && dTime < 2200) {         //范围判断
      rcValue[rc_value_pos] = dTime;           //保存该PPM值
    }
  } else edgeTime[pin_pos] = cTime;            //否则记录边沿时间值
}
//反斜杠起到换行作用,用于宏定义和字符串换行

//端口变化中断
ISR(PCINT2_vect) { //D2,4,5,6,7引脚电平变化中断请求2,接收机PCINT2中断
  uint8_t mask;                 //掩码值,获取改变的位
  uint8_t pin;                  //D口输入值
  uint16_t cTime, dTime;        //实时时间,PPM时间
  static uint16_t edgeTime[8];  //边沿时刻的时间
  static uint8_t PCintLast;     //最后一次的输入状态
  pin = PIND;                   //读D口值

  mask = pin ^ PCintLast;       //获取改变的位
  cTime = micros();             //获取当前微秒时间, micros()返回32位,这里只保留16位
  sei();                        //开全局中断
  PCintLast = pin;              //保存最后一次的D口状态

  RX_PIN_CHECK(0, 2);           //计算D2的PPM值
  RX_PIN_CHECK(1, 4);           //计算D4的PPM值
  RX_PIN_CHECK(2, 5);           //计算D5的PPM值
  RX_PIN_CHECK(3, 6);           //计算D6的PPM值
  RX_PIN_CHECK(4, 7);           //计算D7的PPM值
}

ISR(PCINT0_vect) {              //D8引脚电平变化中断请求0
  uint8_t pin;                  //原理同上
  uint16_t cTime, dTime;
  static uint16_t edgeTime;
  pin = PINB;
  cTime = micros();
  sei();
  if (!(pin & 1 << 0)) {        //D8(PB0)PPM脉冲
    dTime = cTime - edgeTime; if (900 < dTime && dTime < 2200) rcValue[0] = dTime;
  } else edgeTime = cTime;      //
}

/*****   读原始的RC数据    *****/
uint16_t readRawRC(uint8_t chan) {
  uint16_t data;
  uint8_t oldSREG;
  oldSREG = SREG; cli();           //保存状态寄存器,禁止中断
  data = rcValue[rcChannel[chan]]; //复制数据
  SREG = oldSREG;                  //恢复中断状态
  return data;                     //当IRQ是禁用时,我们返回的是正确复制数据
}

/*****   计算滤波RC数据   *****/
void computeRC() {
  static uint16_t rcData4Values[RC_CHANS][4], rcDataMean[RC_CHANS];  //4次RC数据,RC平均值
  static uint8_t rc4ValuesIndex = 0;    //4次的指针
  uint8_t chan, a;                      //通道

  rc4ValuesIndex++;  //rc信号指针自加1
  if (rc4ValuesIndex == 4) rc4ValuesIndex = 0;  //等于4时则表明一个通道的四个传输完成,指针清零
  for (chan = 0; chan < RC_CHANS; chan++) {     //所有通道
    rcData4Values[chan][rc4ValuesIndex] = readRawRC(chan);  //读原始的RC数据
    rcDataMean[chan] = 0;                       //RC平均值清零
    for (a = 0; a < 4; a++) rcDataMean[chan] += rcData4Values[chan][a]; //求4次RC数据累加值
    rcDataMean[chan] = (rcDataMean[chan] + 2) >> 2; //求平均值
    if ( rcDataMean[chan] < (uint16_t)rcData[chan] - 3)  rcData[chan] = rcDataMean[chan] + 2; //减小遥控数据的波动
    if ( rcDataMean[chan] > (uint16_t)rcData[chan] + 3)  rcData[chan] = rcDataMean[chan] - 2; //减小遥控数据的波动
  }
}




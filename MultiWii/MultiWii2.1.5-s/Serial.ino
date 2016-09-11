#define RX_BUFFER_SIZE 64    //接收缓冲区大小
#define TX_BUFFER_SIZE 128   //发送缓冲区大小
#define INBUF_SIZE 64        //输入缓冲区大小

static volatile uint8_t serialHeadRX, serialTailRX; //接收头, 接收尾
static uint8_t serialBufferRX[RX_BUFFER_SIZE];      //串口接收缓冲区
static volatile uint8_t serialHeadTX, serialTailTX; //发送头, 发送尾
static uint8_t serialBufferTX[TX_BUFFER_SIZE];      //串口发送缓冲区
static uint8_t inBuf[INBUF_SIZE];                   //输入缓冲

#define MSP_VERSION              0     //Multiwii串口协议版本

//to multiwii developpers/committers : do not add new MSP messages without a proper argumentation/agreement on the forum
#define MSP_IDENT                100   //out message         multiwii version + multitype + protocol version
#define MSP_STATUS               101   //out message         cycletime & errors_count & sensor present & box activation & current setting number
#define MSP_RAW_IMU              102   //out message         9 DOF
#define MSP_MOTOR                104   //out message         8 motors
#define MSP_RC                   105   //out message         8 rc chan and more
#define MSP_ATTITUDE             108   //out message         2 angles 1 heading
#define MSP_ALTITUDE             109   //out message         altitude, variometer
#define MSP_RC_TUNING            111   //out message         rc rate, rc expo, rollpitch rate, yaw rate, dyn throttle PID
#define MSP_PID                  112   //out message         P I D coeff (9 are used currently)
#define MSP_BOX                  113   //out message         BOX setup (number is dependant of your setup)
#define MSP_MOTOR_PINS           115   //out message         which pins are in use for motors & servos, for GUI 
#define MSP_BOXNAMES             116   //out message         the aux switch names

#define MSP_SET_PID              202   //in message          P I D coeff (9 are used currently)
#define MSP_SET_BOX              203   //in message          BOX setup (number is dependant of your setup)
#define MSP_SET_RC_TUNING        204   //in message          rc rate, rc expo, rollpitch rate, yaw rate, dyn throttle PID
#define MSP_ACC_CALIBRATION      205   //in message          no param
#define MSP_RESET_CONF           208   //in message          no param
#define MSP_EEPROM_WRITE         250   //in message          no param

static uint8_t checksum;  //校验和
static uint8_t indRX;     //接收索引
static uint8_t cmdMSP;    //命令MSP

uint32_t read32() {       //读32位
  uint32_t t = read16();
  t += (uint32_t)read16() << 16;
  return t;
}
uint16_t read16() {       //读16位
  uint16_t t = read8();
  t += (uint16_t)read8() << 8;
  return t;
}
uint8_t read8()  {        //读8位
  return inBuf[indRX++] & 0xff;
}

void headSerialResponse(uint8_t err, uint8_t s) {  //
  serialize8('$');                //发送'$'
  serialize8('M');                //发送'M'
  serialize8(err ? '!' : '>');    //如果err = 1，则发送'!'，否则发送'>'
  checksum = 0;                   //开始计算一个新的校验和
  serialize8(s);                  //发送数据长度信息
  serialize8(cmdMSP);             //发送命令字信息
}

void headSerialReply(uint8_t s) {    //发送数据头与数据长度信息
  headSerialResponse(0, s);
}

void inline headSerialError(uint8_t s) {  //发送错误信息"$M!"
  headSerialResponse(1, s);
}    //inline内联函数的目的是为了解决程序中函数调用的效率问题

void tailSerialReply() {  //消息的校验和信息
  serialize8(checksum); UartSendData(); //发送校验和
}

void serializeNames(PGM_P s) {  //
  for (PGM_P c = s; pgm_read_byte(c); c++) {
    serialize8(pgm_read_byte(c));
  }
}

void serialCom() {             //解析缓冲区的数据
  uint8_t c, n;
  static uint8_t offset;       //偏移量
  static uint8_t dataSize;     //数据长度
  static enum _serial_state {  //串口的几种状态
    IDLE,                      //空闲
    HEADER_START,              //数据头开始,$
    HEADER_M,                  //数据头,M
    HEADER_ARROW,              //数据箭头,<
    HEADER_SIZE,               //数据尺寸
    HEADER_CMD,                //指令
  } c_state;                   // = IDLE; 状态数组,默认空闲

  while (SerialAvailable()) {  //判断串口是否收到数据
    uint8_t bytesTXBuff = ((uint8_t)(serialHeadTX - serialTailTX)) % TX_BUFFER_SIZE; //发送缓冲区占用字节标定
    if (bytesTXBuff > TX_BUFFER_SIZE - 50 ) return; //确保有足够的发送缓冲区(50字节的余量)
    c = SerialRead(); //读串口缓冲区
    //该缓冲区的数据是由串口接收中断函数inline store_uart_in_buf(uint8_t data, uint8_t portnum)获取的来自GUI的数据
    if (c_state == IDLE) { //这是一组完整指令代码 24 4D 3C 00 64 64 $M<\#0dd,串口状态空闲,等待HEADER_START状态的到来
      c_state = (c == '$') ? HEADER_START : IDLE; //判定是$字符吗？是进入HEADER_START状态
    } else if (c_state == HEADER_START) {
      c_state = (c == 'M') ? HEADER_M : IDLE; //判定是M字符吗？是进入HEADER_M状态
    } else if (c_state == HEADER_M) {
      c_state = (c == '<') ? HEADER_ARROW : IDLE; //是字符<吗？是表示有数据要进入MWC，此前发送都是数据头
    } else if (c_state == HEADER_ARROW) {  //是ARROW字符，判定缓冲区的大小
      if (c > INBUF_SIZE) {  //如果数据长度超过输入缓冲区
        c_state = IDLE;  //数据位置不够,退出循环
        continue;  //不执行该while循环包含的后面的语句，开始下一轮循环
      }
      dataSize = c;  //缓冲区够，将收到的数据赋值给当前端口的数据尺寸数组dataSize[串口端口号]
      offset = 0;  //设置数据指针的偏移位0
      checksum = 0;  //初始化数据的校验和为0,存入数组中
      indRX = 0;
      checksum ^= c;  //数据长度是校验的第一个字母
      c_state = HEADER_SIZE;  //MWC串口状态进入HWADER_SIZE,后面就是命令字
    } else if (c_state == HEADER_SIZE) {  //MWC串口是在HEADER_SIZE状态吗?
      cmdMSP = c;  //收到的第一个数据是指令
      checksum ^= c;  //将该数据异或进入校验和的数组中去
      c_state = HEADER_CMD;  //MWC进入HEAFER_CMD指令状态
    } else if (c_state == HEADER_CMD && offset < dataSize) {
      checksum ^= c;  //进入校验和异或
      inBuf[offset++] = c;  //MWC将收到的数据存入缓冲区,offset[CURRENTPORT]加1
    } else if (c_state == HEADER_CMD && offset >= dataSize) {  //判定偏移指针大于等于数据预留位置大小
      if (checksum == c) {  //与已经累计异或的checksum[]中的校验和数据对比
        evaluateCommand();  //获得一个有效的数据包，解析数据
      }
      c_state = IDLE;  //MWC串口开始进入空闲状态
    }
  }
}

void evaluateCommand() {  //处理指令
  switch (cmdMSP) {       //命令字分类处理
    case MSP_SET_PID:      //
      for (uint8_t i = 0; i < PIDITEMS; i++) {
        conf.P8[i] = read8();
        conf.I8[i] = read8();
        conf.D8[i] = read8();
      }
      headSerialReply(0);  //处理完成后,发送数据长度为0的信息
      break;
    case MSP_SET_BOX:       //
      for (uint8_t i = 0; i < CHECKBOXITEMS; i++) {
        conf.activate[i] = read16();
      }
      headSerialReply(0);
      break;
    case MSP_SET_RC_TUNING:  //
      conf.rcRate8 = read8();
      conf.rcExpo8 = read8();
      conf.rollPitchRate = read8();
      conf.yawRate = read8();
      conf.dynThrPID = read8();
      conf.thrMid8 = read8();
      conf.thrExpo8 = read8();
      headSerialReply(0);
      break;
    case MSP_IDENT:          //飞控版本,飞行器类型,串口协议版本
      headSerialReply(3);    //发送数据头与数据长度(3)信息
      serialize8(VERSION);   // multiwii version
      serialize8(MULTITYPE); // type of multicopter
      serialize8(MSP_VERSION);         // MultiWii Serial Protocol Version
      break;
    case MSP_STATUS:         //各种状态
      headSerialReply(11);
      serialize16(cycleTime);
      serialize16(i2c_errors_count);
      serialize16(ACC | BARO << 1 | SONAR << 4); //
      serialize32(
        f.ANGLE_MODE << BOXANGLE |
        f.HORIZON_MODE << BOXHORIZON |
        f.BARO_MODE << BOXBARO |
        f.ARMED << BOXARM);
      serialize8(global_conf.currentSet);   // current setting
      break;
    case MSP_RAW_IMU:        //IMU原始数据
      headSerialReply(18);
      for (uint8_t i = 0; i < 3; i++) serialize16(accSmooth[i]);
      for (uint8_t i = 0; i < 3; i++) serialize16(gyroData[i]);
      for (uint8_t i = 0; i < 3; i++) serialize16(0); //(magADC[i]);
      break;
    case MSP_MOTOR:          //电机值
      headSerialReply(16);
      for (uint8_t i = 0; i < 8; i++) {
        serialize16( (i < 4) ? motor[i] : 0 );
      }
      break;
    case MSP_RC:             //遥控器值
      headSerialReply(RC_CHANS * 2);
      for (uint8_t i = 0; i < RC_CHANS; i++) serialize16(rcData[i]);
      break;
    case MSP_ATTITUDE:       //飞行器姿态信息
      headSerialReply(8);
      for (uint8_t i = 0; i < 2; i++) serialize16(angle[i]);
      serialize16(0);        //(heading);
      serialize16(0);        //(headFreeModeHold);
      break;
    case MSP_ALTITUDE:       //高度信息
      headSerialReply(4);
      serialize32(EstAlt);   //
      break;
    case MSP_RC_TUNING:      //接收机调谐
      headSerialReply(7);
      serialize8(conf.rcRate8);
      serialize8(conf.rcExpo8);
      serialize8(conf.rollPitchRate);
      serialize8(conf.yawRate);
      serialize8(conf.dynThrPID);
      serialize8(conf.thrMid8);
      serialize8(conf.thrExpo8);
      break;
    case MSP_PID:            //PID参数
      headSerialReply(3 * PIDITEMS);
      for (uint8_t i = 0; i < PIDITEMS; i++) {
        serialize8(conf.P8[i]);
        serialize8(conf.I8[i]);
        serialize8(conf.D8[i]);
      }
      break;
    case MSP_BOX:            //飞行模式
      headSerialReply(2 * CHECKBOXITEMS);
      for (uint8_t i = 0; i < CHECKBOXITEMS; i++) {
        serialize16(conf.activate[i]);
      }
      break;
    case MSP_BOXNAMES:        //ARM,ANGLE,HORIZON
      headSerialReply(strlen_P(boxnames));
      serializeNames(boxnames);
      break;
    case MSP_MOTOR_PINS:      //电机引脚定义
      headSerialReply(8);
      for (uint8_t i = 0; i < 8; i++) {
        serialize8(PWM_PIN[i]);
      }
      break;
    case MSP_RESET_CONF:       //复位命令
      if (!f.ARMED) LoadDefaults();
      headSerialReply(0);
      break;
    case MSP_ACC_CALIBRATION:  //加速度校准
      if (!f.ARMED) calibratingA = 512;
      headSerialReply(0);
      break;
    case MSP_EEPROM_WRITE:     //写命令
      writeParams(0);
      headSerialReply(0);
      break;
    default:                   //我们不知道如何处理的消息
      headSerialError(0);      //发送错误信息"$M!"
      break;
  }
  tailSerialReply();          //发送校验和
}

// UART发送器中断驱动,使用循环缓冲区
void serialize32(uint32_t a) {  //发送32位
  serialize8((a    ) & 0xFF);
  serialize8((a >> 8) & 0xFF);
  serialize8((a >> 16) & 0xFF);
  serialize8((a >> 24) & 0xFF);
}

void serialize16(int16_t a) {  //发送16位
  serialize8((a   ) & 0xFF);
  serialize8((a >> 8) & 0xFF);
}

void serialize8(uint8_t a) {          //发送8位
  uint8_t t = serialHeadTX;           //发送头索引
  if (++t >= TX_BUFFER_SIZE) t = 0;   //头索引+1,如果大于发送缓冲区,清零
  serialBufferTX[t] = a;              //数据送入发送缓冲区
  checksum ^= a;                      //求校验和
  serialHeadTX = t;                   //保存发送头索引
}

ISR(USART_UDRE_vect) {                //串口数据寄存器空中断
  uint8_t t = serialTailTX;           //发送尾索引
  if (serialHeadTX != t) {            //如果头不等于尾
    if (++t >= TX_BUFFER_SIZE) t = 0; //尾索引+1,如果大于发送缓冲区,清零
    UDR0 = serialBufferTX[t];         //将数据放入缓冲器,发送数据
    serialTailTX = t;                 //保存发送尾索引
  }
  if (t == serialHeadTX) UCSR0B &= ~(1 << UDRIE0); //检查所有数据是否传输完，如果是禁用发送数据空UDRE中断
}

void UartSendData() {                             //串口发送数据
  UCSR0B |= (1 << UDRIE0);                        //数据寄存器空中断使能
}

static void inline SerialOpen(uint32_t baud) {    //打开串口
  uint8_t h = ((F_CPU  / 4 / baud - 1) / 2) >> 8; //波特率值H
  uint8_t l = ((F_CPU  / 4 / baud - 1) / 2);      //波特率值L
  UCSR0A  = (1 << U2X0);                          //USART控制和状态寄存器A:倍速发送
  UBRR0H = h; UBRR0L = l;                         //波特率设置
  UCSR0B |= (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0); //USART控制和状态寄存器B:接收使能,发送使能,接收结束中断使能
}

static void inline store_uart_in_buf(uint8_t data) {  //储存串口数据到输入缓冲区
  uint8_t h = serialHeadRX;              //接收头
  if (++h >= RX_BUFFER_SIZE) h = 0;      //头索引+1,如果大于接收缓冲区,清零
  if (h == serialTailRX) return;         //如果头尾重叠，返回
  serialBufferRX[serialHeadRX] = data;   //接收数据送入接收缓冲区
  serialHeadRX = h;                      //保存头索引
}

ISR(USART_RX_vect)  {
  store_uart_in_buf(UDR0);  //串口接收中断
}

uint8_t SerialRead() {                    //读串口
  uint8_t t = serialTailRX;               //接收尾索引
  uint8_t c = serialBufferRX[t];          //读取接收缓冲区一个字节数据
  if (serialHeadRX != t) {                //如果头不等于尾
    if (++t >= RX_BUFFER_SIZE) t = 0;     //尾+1,大于接收缓冲区尺寸,尾清0
    serialTailRX = t;                     //保存尾索引
  }
  return c;                               //返回所读数据
}

uint8_t SerialAvailable() {               //串口有数据
  return (serialHeadRX - serialTailRX) % RX_BUFFER_SIZE; //返回接收缓冲区数据的字节数
}

void SerialWrite(uint8_t c) {             //串口写数据
  serialize8(c); UartSendData();          //写一个字节数据,并发送
}


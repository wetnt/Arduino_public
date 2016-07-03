#define LEDPIN_PINMODE             pinMode (13, OUTPUT);  //D13（LED）设置为输出
#define LEDPIN_TOGGLE              PINB |= 1<<5;          //改变LED状态 (数字PIN 13)
#define LEDPIN_OFF                 PORTB &= ~(1<<5);      //LED灭
#define LEDPIN_ON                  PORTB |= (1<<5);       //LED亮

//RX引脚分配(D口) 
#define THROTTLEPIN                2
#define ROLLPIN                    4
#define PITCHPIN                   5
#define YAWPIN                     6
#define AUX1PIN                    7
#define AUX2PIN                    0 //PIN 8
#define AUX3PIN                    1 //未使用 
#define AUX4PIN                    3 //未使用 
  
#define MULTITYPE 3  //QUADX多旋翼类型
#define RC_CHANS 8   //接收机通道数

#define ACC 1
#define BARO 1
#define SONAR 1


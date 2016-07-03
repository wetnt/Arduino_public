#include <avr/eeprom.h>

uint8_t calculate_sum(uint8_t *cb , uint8_t siz) {    //计算校验和
  uint8_t sum=0x55;            //校验和初始化 checksum init
  while(--siz) sum += *cb++;   //计算校验和(不含校验和字节)
  return sum;
}

void readGlobalSet() {      //读全局设置
  eeprom_read_block((void*)&global_conf, (void*)0, sizeof(global_conf));  
  //从EEPROM的(void*)0地址开始,读取sizeof(global_conf)个字节到(void*)&global_conf
  if(calculate_sum((uint8_t*)&global_conf, sizeof(global_conf)) != global_conf.checksum) {
    global_conf.currentSet = 0;
    global_conf.accZero[ROLL] = 5000;    //用于配置错误信号
  }
}
 
void readEEPROM() {         //读EEPROM
  uint8_t i;
  global_conf.currentSet=0;
  eeprom_read_block((void*)&conf, (void*)(global_conf.currentSet * sizeof(conf) + sizeof(global_conf)), sizeof(conf));
  //从EEPROM的(void*)(global_conf.currentSet * sizeof(conf) + sizeof(global_conf))地址开始,读取sizeof(conf)个字节到(void*)&conf
  if(calculate_sum((uint8_t*)&conf, sizeof(conf)) != conf.checksum) {
    blinkLED(6,100,3);    
    LoadDefaults();                 //加载默认参数 
  }
  for(i=0;i<6;i++) {
    lookupPitchRollRC[i] = (2500+conf.rcExpo8*(i*i-25))*i*(int32_t)conf.rcRate8/2500;
  }
  for(i=0;i<11;i++) {
    int16_t tmp = 10*i-conf.thrMid8;
    uint8_t y = 1;
    if (tmp>0) y = 100-conf.thrMid8;
    if (tmp<0) y = conf.thrMid8;
    lookupThrottleRC[i] = 10*conf.thrMid8 + tmp*( 100-conf.thrExpo8+(int32_t)conf.thrExpo8*(tmp*tmp)/(y*y) )/10; // [0;1000]
    lookupThrottleRC[i] = conf.minthrottle + (int32_t)(MAXTHROTTLE-conf.minthrottle)* lookupThrottleRC[i]/1000;            // [0;1000] -> [conf.minthrottle;MAXTHROTTLE]
  }
}

void writeGlobalSet(uint8_t b) {  //写全局设置
  global_conf.checksum = calculate_sum((uint8_t*)&global_conf, sizeof(global_conf));
  eeprom_write_block((const void*)&global_conf, (void*)0, sizeof(global_conf));
  //由(void*)0地址开始写入sizeof(global_conf)长度的EEPROM数据到(const void*)&global_conf
  if (b == 1) blinkLED(15,20,1);
}
 
void writeParams(uint8_t b) {     //写参数
  global_conf.currentSet=0;
  conf.checksum = calculate_sum((uint8_t*)&conf, sizeof(conf));
  eeprom_write_block((const void*)&conf, (void*)(global_conf.currentSet * sizeof(conf) + sizeof(global_conf)), sizeof(conf));
  //由(void*)(global_conf.currentSet * sizeof(conf) + sizeof(global_conf))地址开始写入sizeof(conf)长度的EEPROM数据到(const void*)&conf
  readEEPROM();                   //读EEPROM
  if (b == 1) blinkLED(15,20,1);
}

void LoadDefaults() {             //加载默认参数
  conf.P8[ROLL]     = 33;  conf.I8[ROLL]    = 30; conf.D8[ROLL]     = 23;
  conf.P8[PITCH]    = 33; conf.I8[PITCH]    = 30; conf.D8[PITCH]    = 23;
  conf.P8[YAW]      = 68;  conf.I8[YAW]     = 45;  conf.D8[YAW]     = 0;
  conf.P8[PIDALT]   = 64; conf.I8[PIDALT]   = 25; conf.D8[PIDALT]   = 24;

  conf.P8[PIDPOS]  = POSHOLD_P * 100;     conf.I8[PIDPOS]    = POSHOLD_I * 100;       conf.D8[PIDPOS]    = 0;
  conf.P8[PIDPOSR] = POSHOLD_RATE_P * 10; conf.I8[PIDPOSR]   = POSHOLD_RATE_I * 100;  conf.D8[PIDPOSR]   = POSHOLD_RATE_D * 1000;
  conf.P8[PIDNAVR] = NAV_P * 10;          conf.I8[PIDNAVR]   = NAV_I * 100;           conf.D8[PIDNAVR]   = NAV_D * 1000;

  conf.P8[PIDLEVEL] = 90; conf.I8[PIDLEVEL] = 10; conf.D8[PIDLEVEL] = 100;
  conf.P8[PIDMAG]   = 40;
  
  conf.P8[PIDVEL] = 0;      conf.I8[PIDVEL] = 0;    conf.D8[PIDVEL] = 0;
  
  conf.rcRate8 = 90; conf.rcExpo8 = 65;
  conf.rollPitchRate = 0;
  conf.yawRate = 0;
  conf.dynThrPID = 0;
  conf.thrMid8 = 50; conf.thrExpo8 = 0;
  for(uint8_t i=0;i<CHECKBOXITEMS;i++) {conf.activate[i] = 0;}
  conf.angleTrim[0] = 0; conf.angleTrim[1] = 0;
  conf.powerTrigger1 = 0;
  conf.minthrottle = MINTHROTTLE;
  writeParams(0);
}


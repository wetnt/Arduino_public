static unsigned int pm_cf_10;           //定义全局变量
static unsigned int pm_cf_25;
static unsigned int pm_cf_100;
static unsigned int pm_at_10;
static unsigned int pm_at_25;
static unsigned int pm_at_100;
static unsigned int particulate03;
static unsigned int particulate05;
static unsigned int particulate10;
static unsigned int particulate25;
static unsigned int particulate50;
static unsigned int particulate100;
static float HCHO;

void getG5(unsigned char ucData)//获取G5的值
{
  static unsigned int ucRxBuffer[250];
  static unsigned int ucRxCnt = 0;
  ucRxBuffer[ucRxCnt++] = ucData;
  if (ucRxBuffer[0] != 0x42 && ucRxBuffer[1] != 0x4D)//数据头判断
  {
    ucRxCnt = 0;
    return;
  }
  if (ucRxCnt > 32)//数据位判断
  {
       pm_cf_10=(int)ucRxBuffer[4] * 256 + (int)ucRxBuffer[5];      //大气环境下PM2.5浓度计算        
       pm_cf_25=(int)ucRxBuffer[6] * 256 + (int)ucRxBuffer[7];
       pm_cf_100=(int)ucRxBuffer[8] * 256 + (int)ucRxBuffer[9];
       pm_at_10=(int)ucRxBuffer[10] * 256 + (int)ucRxBuffer[11];               
       pm_at_25=(int)ucRxBuffer[12] * 256 + (int)ucRxBuffer[13];
       pm_at_100=(int)ucRxBuffer[14] * 256 + (int)ucRxBuffer[15];
       particulate03=(int)ucRxBuffer[16] * 256 + (int)ucRxBuffer[17];
       particulate05=(int)ucRxBuffer[18] * 256 + (int)ucRxBuffer[19];
       particulate10=(int)ucRxBuffer[20] * 256 + (int)ucRxBuffer[21];
       particulate25=(int)ucRxBuffer[22] * 256 + (int)ucRxBuffer[23];
       particulate50=(int)ucRxBuffer[24] * 256 + (int)ucRxBuffer[25];
       particulate100=(int)ucRxBuffer[26] * 256 + (int)ucRxBuffer[27]; 
       HCHO=((int)ucRxBuffer[28] * 256 +(int)ucRxBuffer[29])/1000.000;
       
    if (pm_cf_25 >  999)//如果PM2.5数值>1000，返回重新计算
    {
      ucRxCnt = 0;
      return;
    }
    
    ucRxCnt = 0;
    return;
  }

}

void setup() {

   Serial.begin(9600);
  
}

void loop() {
     while (Serial.available())
      {
        getG5(Serial.read());
      }
         Serial.print("   PM_CF1.0:");Serial.print(pm_cf_10);Serial.print(" ug/m3");//硬件串口输出数据
         Serial.print("   PM_CF2.5:");Serial.print(pm_cf_25);Serial.print(" ug/m3");
         Serial.print("   PM_CF10 :");Serial.print(pm_cf_100);Serial.println(" ug/m3");
         Serial.print("   PM_AQI1.0:");Serial.print(pm_at_10);Serial.print(" ug/m3");
         Serial.print("   PM_AQI2.5:");Serial.print(pm_at_25);Serial.print(" ug/m3");
         Serial.print("   PM_AQI10:");Serial.print(pm_at_100);Serial.println(" ug/m3");
         Serial.print("   PM_count03:");Serial.print(particulate03);Serial.print(" pcs/0.01cf");
         Serial.print("   PM_count05:");Serial.print(particulate05);Serial.print(" pcs/0.01cf");
         Serial.print("   PM_count10:");Serial.print(particulate10);Serial.print(" pcs/0.01cf");
         Serial.print("   PM_count25:");Serial.print(particulate25);Serial.print(" pcs/0.01cf");
         Serial.print("   PM_count100:");Serial.print(particulate100);Serial.println(" pcs/0.01cf");   
         Serial.print("   HCHO:");Serial.print(HCHO,3);Serial.println(" mg/m3");      
         Serial.println("*********************************************");
         delay(2000);

}

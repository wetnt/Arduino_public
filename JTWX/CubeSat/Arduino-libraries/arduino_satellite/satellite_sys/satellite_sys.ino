#include "High_Temp.h"
#include "Wire.h"
#include "I2Cdev.h"
#include "MPU9250.h"
#include <SPI.h>
#include <arduino.h>
#include <SD.h>
#include <Servo.h>
#include "SHT31.h"
#include "TimerOne.h"
#include <avr/wdt.h>

//Camera vary
#define PIC_PKT_LEN    128
#define PIC_FMT_VGA    7
#define PIC_FMT_CIF    5
#define PIC_FMT_OCIF   3 
#define CAM_ADDR       0
#define CAM_SERIAL     Serial1
#define PIC_FMT        PIC_FMT_VGA

#define SERVO_PIN      A0
#define SERVO1_PIN     A1

#define sample_num_mdate  5000

#define HEATER_BAND_PIN 8
#define GPS_SERIAL Serial2
#define RF_SERIAL Serial3

#define HEADTING_DUTY_SETTING 250//40  // 加热板占空比设置（0~255），注意占空比不要设置过高，温度过高危险
#define HEATER_ON true
#define HEATER_OFF false

#define L_SERVOR_DOWN 150
#define L_SERVOR_UP   70
#define R_SERVOR_DOWN 80
#define R_SERVOR_UP   160

// SD card shield
File myFile;

// RF port
bool RF_busy = false;

const byte cameraAddr = (CAM_ADDR << 5);  // addr
unsigned long picTotalLen = 0;            // picture length

//GPS vary
String GPS_data = "";

//GYRO vray
MPU9250 accelgyro;
I2Cdev   I2C_M;


float Axyz[3];
float Gxyz[3];
float Mxyz[3];


volatile float mx_sample[3];
volatile float my_sample[3];
volatile float mz_sample[3];

static float mx_centre = 0;
static float my_centre = 0;
static float mz_centre = 0;

volatile int mx_max =0;
volatile int my_max =0;
volatile int mz_max =0;

volatile int mx_min =0;
volatile int my_min =0;
volatile int mz_min =0;

volatile bool heater_state = false;
volatile uint8_t operation_index = 0;
// Servo
Servo myservo,myservo1;

// temp control
// High Tempature Sensor vary
HighTemp ht(A4, A3);

// SHT31 Temperature&Huminity Sensor
SHT31 sht31 = SHT31();

// sys_data
struct SYS_DATA{
    // 传感器数据
    int heating_panel_temp = 0;
    float inside_temp = 0.0;
    float inside_humi = 0.0;
    float posture_x = 0.0;
    float posture_y = 0.0;
    float posture_z = 0.0;
    float heading = 0.0;
    float gps_latitude = 110.988356;
    float gps_longitude = 19.646334;
    // 执行器状态
    bool is_solar_panel_on = false;
}sys_data;

enum communicate {
    COMM_SOH = 0x01,
    COMM_EOT = 0x04,
    COMM_ACK = 0x06,
    COMM_NAK = 0x15,
    COMM_CAN = 0x18,
    COMM_FAK = 0xFF,

    // command
    COMM_REQUEST_SAT_DATA = 254,
    COMM_OPEN_SOLAR_PANEL = 253,
    COMM_CLOSE_SOLAR_PANEL = 252,
    COMM_RESET_SYS = 251,
    COMM_TURN_ON_HEATER = 250,
    COMM_TURN_OFF_HEATER = 249,
    // COMM_TAKE_PHOTO = 248,
    COMM_PRE_CAPTURE = 247,
    COMM_GET_PIC_LEN = 246,
    COMM_SEND_PIC_DATA = 245,
    COMM_RESET = 244,
};

enum Option_Index {
    // comm execute index
    opt_Pre_Capture = 0,
    opt_Get_Pic_Len,
    opt_Send_Pic_data,
    opt_Turn_On_Heater,
    opt_Turn_Off_Heater,
    opt_Open_Solar_Panel,
    opt_Close_Solar_Panel,
    opt_Request_Sat_Data,
    opt_Reset,
    opt_default,
};

bool is_opt_busy = false;


void comm_run(HardwareSerial* port);
void RFSerial_ISR();
void set_heater(bool state);
void set_heater_on();
void set_heater_off();
void set_solar_panel_up();
void set_solar_panel_down();
void RF_Serial_test();
bool RF_data_update(void);
String getGPSdata();
byte crc8(byte *data, byte len) ;
float getHeading(void);
float getTiltHeading(void);
void Mxyz_init_calibrated ();
void get_calibration_Data ();
void get_one_sample_date_mxyz();
void getAccel_Data(void);
void getGyro_Data(void);
void getCompass_Data(void);
void getCompassDate_calibrated ();
void clearRxBuf();
void cam_sendCmd(char cmd[], int cmd_len);
void camera_initialize();
int preCapture(void);
int Capture();
int GetData(void);
int sendData(void);

volatile uint8_t cnt = 0;

void comm_run(HardwareSerial* port)
{
    char data;

    if(port->available()) {
        data = port->read();
        //port->write(data);
        Serial.print("Reveived data: 0x");
        Serial.println(data, HEX);

        if(is_opt_busy == true) {
            return;
        } 
        
        switch((uint8_t)data) {
            case COMM_SOH:
                operation_index = opt_default;
                break;

            case COMM_EOT:  // End of transmit
                break;

            case COMM_ACK:

                break;

            case COMM_NAK:
                break;

            case COMM_CAN:  // Cancle anyway
                break;

            case COMM_REQUEST_SAT_DATA:
                operation_index = opt_Request_Sat_Data;
                break;

            case COMM_OPEN_SOLAR_PANEL:
                operation_index = opt_Open_Solar_Panel;
                break;
            
            case COMM_CLOSE_SOLAR_PANEL:
                operation_index = opt_Close_Solar_Panel;

                break;

            case COMM_TURN_ON_HEATER:
                operation_index = opt_Turn_On_Heater;
                break;

            case COMM_TURN_OFF_HEATER:
                operation_index = opt_Turn_Off_Heater;
                break;

            case COMM_PRE_CAPTURE:
                operation_index = opt_Pre_Capture;
                break;

            case COMM_GET_PIC_LEN:
                operation_index = opt_Get_Pic_Len;
                break;

            case COMM_SEND_PIC_DATA:
                operation_index = opt_Send_Pic_data;
                break;

            case COMM_RESET:
                operation_index = opt_Reset;
                break;

            default: break;
        }
    }
}


void setup() {
    //Serial init
    Serial.begin(115200);  // Sreial0 init
    Serial.println("init....");
    
    //SD carc shield init
    pinMode(4,OUTPUT);          // CS pin of SD Card Shield
    if (!SD.begin(4))
    {
        Serial.println("sd init failed\n");
        // return;
    } else {
      Serial.println("sd init done.\n");
    }
    
    // RF Serial init
    // RF_SERIAL.begin(115200);  
    RF_SERIAL.begin(9600);
    
    // Camera init
    CAM_SERIAL.begin(115200);  
    camera_initialize();

    // GPS Serial init
    GPS_SERIAL.begin(9600);  
    Serial.println("GPS init succeed");

    //High Temperature Sensor init
    ht.begin();
    Serial.println("High Temperature Sensor init suceed");

    //gyro init
    Wire.begin();
    accelgyro.initialize();
    Serial.println(accelgyro.testConnection() ? "MPU9250 connection successful" : "MPU9250 connection failed");

    //servo init
    myservo.attach(SERVO_PIN);
    myservo1.attach(SERVO1_PIN);
    myservo.write(R_SERVOR_DOWN);
    myservo1.write(L_SERVOR_DOWN);
    sys_data.is_solar_panel_on = false;

    // Temperature and humidity sensor init
    sht31.begin();

    //temp control
    pinMode(HEATER_BAND_PIN, OUTPUT);
    analogWrite(HEATER_BAND_PIN, 0);

    Timer1.initialize(5000);  // 定时中断 us
    Timer1.attachInterrupt( RFSerial_ISR );

    // heater_state = true;  // 加热板状态 - 开

    RF_SERIAL.setTimeout(1000);

    operation_index = opt_default;

}

/**
 * @函数：void RFSerial_ISR()
 * @说明： 无线串口定时中断服务, 中断里面时间是静止的，
 *        millis()不会得到更新，delay() 函数用不了。
 *        
 */
void RFSerial_ISR() {
    if(RF_SERIAL.available()) {
        Serial.println("Enter timer1 interrupt!");
        comm_run(&RF_SERIAL);
        // RF_Serial_test();
    }
}

void set_heater(bool state)
{
    if (HEATER_ON == state) {
        analogWrite(HEATER_BAND_PIN, HEADTING_DUTY_SETTING);
    }else {
        analogWrite(HEATER_BAND_PIN, 0);
    }
}

void set_heater_off()
{
    heater_state = false;
}

void set_heater_on()
{
    heater_state = true;
}

/**
 * @函数：void set_solar_panel_on()
 */
void set_solar_panel_up()
{
    if(sys_data.is_solar_panel_on == false) {
        sys_data.is_solar_panel_on = true;
         for(int l = L_SERVOR_DOWN, r = R_SERVOR_DOWN; (l >= L_SERVOR_UP) || (r <=R_SERVOR_UP); l--, r++) {
            myservo.write(r);
            myservo1.write(l);
            delay(40);
        }
    }

}

/**
 * @函数：void set_solar_panel_off()
 */
void set_solar_panel_down()
{    
    if(sys_data.is_solar_panel_on == true) {
        sys_data.is_solar_panel_on = false;
        for(int l = L_SERVOR_UP, r = R_SERVOR_UP; (l <= L_SERVOR_DOWN) && (r >= R_SERVOR_DOWN); l++, r--) {
            myservo.write(r);
            myservo1.write(l);
            delay(40);    
        }      
    }
}

void loop() {

    static volatile uint32_t timer_start = millis();
    char *p;
    char buf[512] = {};
    long temp = 0;

    if (1000 < millis() - timer_start) {
        // Serial.println("fresh sensor data!");

        timer_start = millis();
        
        set_heater(HEATER_OFF);
        delay(5);

        for(int i = 0; i < 50; i++) {
            temp += ht.getThmc();
        }
        temp = temp / 50;
        sys_data.heating_panel_temp = temp;

        set_heater(heater_state);

        // get Temperature and humiduty
        sys_data.inside_temp = sht31.getTemperature();

        sys_data.inside_humi = sht31.getHumidity();

        // 9DOF posture
        getAccel_Data();
        sys_data.posture_x = Axyz[0];
        sys_data.posture_y = Axyz[1];
        sys_data.posture_z = Axyz[2];
        
        // compass heading
        sys_data.heading = getHeading();

        // get GPS data
        if (GPS_data.length() > 0) {
            GPS_data.toCharArray(buf, GPS_data.length());
            p = strtok(buf, ",");
            p = strtok(NULL, ",");
            p = strtok(NULL, ",");
            sys_data.gps_longitude = atof(p);
            Serial.print("GPS: ");
            Serial.print(sys_data.gps_longitude, 4);
            p = strtok(NULL, ",");
            p = strtok(NULL, ",");
            sys_data.gps_latitude = atof(p);
            Serial.print(", ");
            Serial.println(sys_data.gps_latitude, 4);
        } 
    }

    switch(operation_index) {

        case opt_Pre_Capture:
            RF_SERIAL.write(COMM_PRE_CAPTURE);
            if(-1 == preCapture()) {
                operation_index == opt_default;
                break;
            }
            if(-1 == Capture()) {
                operation_index == opt_default;
                break;
            }
            
            if (0 == GetData()) {
                Serial.println("GetData Succeed!");
            } else {
                Serial.println("GetData Error!");
            }

            operation_index = opt_default;

            break;

        case opt_Get_Pic_Len:
            operation_index = opt_default;
            RF_SERIAL.println(picTotalLen);
            picTotalLen = 0;
            break;

        case opt_Send_Pic_data:
            RF_SERIAL.write(COMM_SEND_PIC_DATA);
            sendData();
            break;

        case opt_Turn_On_Heater:
            operation_index = opt_default;  // 恢复到默认状态。
            set_heater_on();
            RF_SERIAL.write(COMM_TURN_ON_HEATER);
            heater_state = true;
            break;

        case opt_Turn_Off_Heater:
            operation_index = opt_default;  // 恢复到默认状态。
            set_heater_off();
            RF_SERIAL.write(COMM_TURN_OFF_HEATER);
            heater_state = false;
            break;

        case opt_Open_Solar_Panel:
            operation_index = opt_default;  // 恢复到默认状态。
            is_opt_busy = true;

            RF_SERIAL.write(COMM_OPEN_SOLAR_PANEL);
            //RF_SERIAL.write(COMM_FAK);

            set_solar_panel_up();
            is_opt_busy = false;

            break;

        case opt_Close_Solar_Panel:
            operation_index = opt_default;  // 恢复到默认状态。
            is_opt_busy = true;

            RF_SERIAL.write(COMM_CLOSE_SOLAR_PANEL);
            //RF_SERIAL.write(COMM_FAK);

            set_solar_panel_down();
            is_opt_busy = false;
            break;

        case opt_Request_Sat_Data:
            operation_index = opt_default;
            RF_data_update();
            break;

        case opt_Reset:
            operation_index = opt_default;
            RF_SERIAL.write(COMM_RESET);
            //RF_SERIAL.write(COMM_FAK);
            break;



        default: break;
    }

    /* 加热板功率过高，在发射RF信号和检测温度时禁用了
       加热，这里恢复禁用前的加热板状态 */
    set_heater(heater_state);
}


/**
 * @function: RF_Serial_test()
 */
void RF_Serial_test()
{
    if(RF_SERIAL.available()) {
        char chr = RF_SERIAL.read();
        RF_SERIAL.write(chr);
        Serial.print(chr, HEX);
    }
}



/**
 * @function：RF_data_update()
 * @数据格式： “传感器名:数值;校验值”
 * @校验值: 与一个特定的数字进行和校验，这里让传感器数值加“1”
 */
bool RF_data_update(void)
{
    int checkValue = 1;

    RF_SERIAL.print("{");
    // 加热板温度
    RF_SERIAL.print("\"HEAT_TMP\":");
    RF_SERIAL.print("{");
    RF_SERIAL.print("\"value\": ");
    RF_SERIAL.print(sys_data.heating_panel_temp);
    RF_SERIAL.print(",\"check\": ");
    RF_SERIAL.print(sys_data.heating_panel_temp + checkValue);
    RF_SERIAL.print("},");
    // string.toFloat
    // 内温度
    RF_SERIAL.print("\"IN_TMP\":");
    RF_SERIAL.print("{");
    RF_SERIAL.print("\"value\": ");
    RF_SERIAL.print(sys_data.inside_temp);
    RF_SERIAL.print(",\"check\": ");
    RF_SERIAL.print(sys_data.inside_temp + checkValue);
    RF_SERIAL.print("},");

    // 内湿度
    RF_SERIAL.print("\"IN_HUMI\":");
    RF_SERIAL.print("{");
    RF_SERIAL.print("\"value\": ");
    RF_SERIAL.print(sys_data.inside_humi);
    RF_SERIAL.print(",\"check\": ");
    RF_SERIAL.print(sys_data.inside_humi + checkValue);
    RF_SERIAL.print("},");

    // 姿态X轴
    RF_SERIAL.print("\"POS_X\":");
    RF_SERIAL.print("{");
    RF_SERIAL.print("\"value\": ");
    RF_SERIAL.print(sys_data.posture_x);
    RF_SERIAL.print(",\"check\": ");
    RF_SERIAL.print(sys_data.posture_x + checkValue);
    RF_SERIAL.print("},");

    // 姿态Y轴
    RF_SERIAL.print("\"POS_Y\":");
    RF_SERIAL.print("{");
    RF_SERIAL.print("\"value\": ");
    RF_SERIAL.print(sys_data.posture_y);
    RF_SERIAL.print(",\"check\": ");
    RF_SERIAL.print(sys_data.posture_y + checkValue);
    RF_SERIAL.print("},");

    // 姿态Z轴
    RF_SERIAL.print("\"POS_Z\":");
    RF_SERIAL.print("{");
    RF_SERIAL.print("\"value\": ");
    RF_SERIAL.print(sys_data.posture_z);
    RF_SERIAL.print(",\"check\": ");
    RF_SERIAL.print(sys_data.posture_z + checkValue);
    RF_SERIAL.print("},");

    // 地磁航向
    RF_SERIAL.print("\"HEAD\":");
    RF_SERIAL.print("{");
    RF_SERIAL.print("\"value\": ");
    RF_SERIAL.print(sys_data.heading);
    RF_SERIAL.print(",\"check\": ");
    RF_SERIAL.print(sys_data.heading + checkValue);
    RF_SERIAL.print("},");

    // GPS 纬度
    RF_SERIAL.print("\"GPS_LAT\":");
    RF_SERIAL.print("{");
    RF_SERIAL.print("\"value\": ");
    RF_SERIAL.print(sys_data.gps_latitude, 4);
    RF_SERIAL.print(",\"check\": ");
    RF_SERIAL.print(sys_data.gps_latitude + checkValue, 4);
    RF_SERIAL.print("},");

    // GPS 经度
    RF_SERIAL.print("\"GPS_LON\":");
    RF_SERIAL.print("{");
    RF_SERIAL.print("\"value\": ");
    RF_SERIAL.print(sys_data.gps_longitude, 4);
    RF_SERIAL.print(",\"check\": ");
    RF_SERIAL.print(sys_data.gps_longitude + checkValue, 4);
    RF_SERIAL.print("},");

    RF_SERIAL.print("}");
    RF_SERIAL.println("");
    //RF_SERIAL.print(0xFF);


    return true;
}

/*
 * @brief Use seiral2 to reveive GPS data   
 */
void serialEvent2()
//String getGPSdata()
{
    String inString = "";
    //if (!RF_busy) {
        //Serial.println("GPS data actived...");
        if (GPS_SERIAL.available()) {
            char inChar = GPS_SERIAL.read();

            if(inChar == '$'){             //'$' means a new line of data
                //inChar = GPS_SERIAL.read();
                GPS_SERIAL.setTimeout(100);
                String inString = GPS_SERIAL.readStringUntil('\n');
                if(inString.substring(0,5) == "GPGGA"){     //"GPGGA" is a line of message which include the message of possition, then send it with Serial
                    GPS_data = inString;
                    // Serial.println(GPS_data);
                }
            }
        }
        //return inString;
    //}
}

/*
 * @brief a simple crc8
 */
byte crc8(byte *data, byte len) {
  byte crc = 0x00;

  while (len--) {
    byte extract = *data++;
    for (byte bit = 8; bit; bit--) {
      byte sum = (crc ^ extract) & 0x01;
      crc >>= 1;
      if (sum) {
        crc ^= 0x8C;
      }
      extract >>= 1;
    }
  }
  return crc;
}

/**
* Gyro functions
*/

float getHeading(void) {
    float heading;

    getCompassDate_calibrated(); // compass data has been calibrated here
    heading=180*atan2(Mxyz[1],Mxyz[0])/PI;
    if(heading <0) heading +=360;

    return heading;
}

float getTiltHeading(void)
{
    float tiltheading;
    float pitch = asin(-Axyz[0]);
    float roll = asin(Axyz[1]/cos(pitch));

    getCompassDate_calibrated(); // compass data has been calibrated here
    float xh = Mxyz[0] * cos(pitch) + Mxyz[2] * sin(pitch);
    float yh = Mxyz[0] * sin(roll) * sin(pitch) + Mxyz[1] * cos(roll) - Mxyz[2] * sin(roll) * cos(pitch);
    float zh = -Mxyz[0] * cos(roll) * sin(pitch) + Mxyz[1] * sin(roll) + Mxyz[2] * cos(roll) * cos(pitch);
    tiltheading = 180 * atan2(yh, xh)/PI;
    if(yh<0)    tiltheading +=360;

    return tiltheading;
}

void Mxyz_init_calibrated () {

    Serial.println(F("Before using 9DOF,we need to calibrate the compass frist,It will takes about 2 minutes."));
    Serial.print("  ");
    Serial.println(F("During  calibratting ,you should rotate and turn the 9DOF all the time within 2 minutes."));
    Serial.print("  ");
    Serial.println(F("If you are ready ,please sent a command data 'ready' to start sample and calibrate."));
    while(!Serial.find("ready"));
    Serial.println("  ");
    Serial.println("ready");
    Serial.println("Sample starting......");
    Serial.println("waiting ......");

    get_calibration_Data ();

    Serial.println("     ");
    Serial.println("compass calibration parameter ");
    Serial.print(mx_centre);
    Serial.print("     ");
    Serial.print(my_centre);
    Serial.print("     ");
    Serial.println(mz_centre);
    Serial.println("    ");
}


void get_calibration_Data () {
    for (int i=0; i<sample_num_mdate;i++)
    {
        get_one_sample_date_mxyz();

        if (mx_sample[2]>=mx_sample[1])mx_sample[1] = mx_sample[2];
        if (my_sample[2]>=my_sample[1])my_sample[1] = my_sample[2]; //find max value
        if (mz_sample[2]>=mz_sample[1])mz_sample[1] = mz_sample[2];

        if (mx_sample[2]<=mx_sample[0])mx_sample[0] = mx_sample[2];
        if (my_sample[2]<=my_sample[0])my_sample[0] = my_sample[2];//find min value
        if (mz_sample[2]<=mz_sample[0])mz_sample[0] = mz_sample[2];

    }

    mx_max = mx_sample[1];
    my_max = my_sample[1];
    mz_max = mz_sample[1];

    mx_min = mx_sample[0];
    my_min = my_sample[0];
    mz_min = mz_sample[0];

    mx_centre = (mx_max + mx_min)/2;
    my_centre = (my_max + my_min)/2;
    mz_centre = (mz_max + mz_min)/2;

}

void get_one_sample_date_mxyz() {
    getCompass_Data();
    mx_sample[2] = Mxyz[0];
    my_sample[2] = Mxyz[1];
    mz_sample[2] = Mxyz[2];
}

void getAccel_Data(void)
{
    int16_t ax, ay, az;
    int16_t gx, gy, gz;
    int16_t   mx, my, mz;

    accelgyro.getMotion9(&ax, &ay, &az, &gx, &gy, &gz, &mx, &my, &mz);
    Axyz[0] = (double) ax / 16384;//16384  LSB/g
    Axyz[1] = (double) ay / 16384;
    Axyz[2] = (double) az / 16384;
}

void getGyro_Data(void)
{
    int16_t ax, ay, az;
    int16_t gx, gy, gz;
    int16_t   mx, my, mz;

    accelgyro.getMotion9(&ax, &ay, &az, &gx, &gy, &gz, &mx, &my, &mz);
    Gxyz[0] = (double) gx * 250 / 32768; //131 LSB(????/s)
    Gxyz[1] = (double) gy * 250 / 32768;
    Gxyz[2] = (double) gz * 250 / 32768;
}

void getCompass_Data(void)
{
    int16_t   mx, my, mz;
    uint8_t buffer_m[6];

    I2C_M.writeByte(0x0C, 0x0A, 0x01); //enable the magnetometer
    delay(10);
    I2C_M.readBytes(0x0C, 0x03, 6, buffer_m);

    mx = ((int16_t)(buffer_m[1]) << 8) | buffer_m[0];
    my = ((int16_t)(buffer_m[3]) << 8) | buffer_m[2];
    mz = ((int16_t)(buffer_m[5]) << 8) | buffer_m[4];

    Mxyz[0] = (double) mx * 4800 / 8192;
    Mxyz[1] = (double) my * 4800 / 8192;
    Mxyz[2] = (double) mz * 4800 / 8192;
}

void getCompassDate_calibrated ()
{
    getCompass_Data();
    Mxyz[0] = Mxyz[0] - mx_centre;
    Mxyz[1] = Mxyz[1] - my_centre;
    Mxyz[2] = Mxyz[2] - mz_centre;
}


/**
* camera functions
*/
void clearRxBuf()
{
    while (CAM_SERIAL.available())
    {
        CAM_SERIAL.read();
    }
}

void cam_sendCmd(char cmd[], int cmd_len)
{
    for (char i = 0; i < cmd_len; i++) CAM_SERIAL.print(cmd[i]);
}

void camera_initialize()
{
    char cmd[] = {0xaa,0x0d|cameraAddr,0x00,0x00,0x00,0x00} ;
    unsigned char resp[6];
    int init_cnt = 5;
    bool init_state = false;

    CAM_SERIAL.setTimeout(500);
    while (1)
    {

        init_cnt --;
        if(0 == init_cnt) {
            break;
        }

        //clearRxBuf();
        cam_sendCmd(cmd,6);
        if (CAM_SERIAL.readBytes((char *)resp, 6) != 6)
        {
            continue;
        }
        if (resp[0] == 0xaa && resp[1] == (0x0e | cameraAddr) && resp[2] == 0x0d && resp[4] == 0 && resp[5] == 0)
        {
            if (CAM_SERIAL.readBytes((char *)resp, 6) != 6) continue;
            if (resp[0] == 0xaa && resp[1] == (0x0d | cameraAddr) && resp[2] == 0 && resp[3] == 0 && resp[4] == 0 && resp[5] == 0) {init_state = true; break;}
        }
    }
    cmd[1] = 0x0e | cameraAddr;
    cmd[2] = 0x0d;
    cam_sendCmd(cmd, 6);
    if(init_state) {
        Serial.println("\nCamera initialization done.\n");
    } else {
        Serial.println("\nCamera initialize failed...\n");
    }
    
}

/**
 * @函数：int preCapture(void)
 * @说明：摄像头拍照，照片数据存在摄像头模块中
 * @返回值：成功返回0， 失败返回-1
 */
int preCapture(void)
{
    char cmd[] = { 0xaa, 0x01 | cameraAddr, 0x00, 0x07, 0x00, PIC_FMT };
    unsigned char resp[6];
    int err_cnt = 0;

    CAM_SERIAL.setTimeout(100);
    while (err_cnt < 10)
    {
        clearRxBuf();
        cam_sendCmd(cmd, 6);
        if (CAM_SERIAL.readBytes((char *)resp, 6) != 6) continue;
        if (resp[0] == 0xaa && resp[1] == (0x0e | cameraAddr) && resp[2] == 0x01 && resp[4] == 0 && resp[5] == 0) 
        {
            return 0;
        }
        err_cnt ++;
    }

    return -1;
}

/**
 * @函数：int Capture(void)
 * @说明：拍照并储存照片数据到Serial Camera 模块
 * @返回：成功返回0， 失败返回-1
 */

int Capture(void)
{
    char cmd[] = { 0xaa, 0x06 | cameraAddr, 0x08, PIC_PKT_LEN & 0xff, (PIC_PKT_LEN>>8) & 0xff ,0};
    unsigned char resp[6];
    int err_cnt = 0;

    CAM_SERIAL.setTimeout(100);
    while (err_cnt < 10)
    {
        clearRxBuf();
        cam_sendCmd(cmd, 6);
        if (CAM_SERIAL.readBytes((char *)resp, 6) != 6) continue;
        if (resp[0] == 0xaa && resp[1] == (0x0e | cameraAddr) && resp[2] == 0x06 && resp[4] == 0 && resp[5] == 0) break;
        err_cnt ++;

    }
    cmd[1] = 0x05 | cameraAddr;
    cmd[2] = 0;
    cmd[3] = 0;
    cmd[4] = 0;
    cmd[5] = 0;

    err_cnt = 0;
    while (err_cnt < 10)
    {
        clearRxBuf();
        cam_sendCmd(cmd, 6);
        if (CAM_SERIAL.readBytes((char *)resp, 6) != 6) continue;
        if (resp[0] == 0xaa && resp[1] == (0x0e | cameraAddr) && resp[2] == 0x05 && resp[4] == 0 && resp[5] == 0) break;
        err_cnt ++;

    }
    cmd[1] = 0x04 | cameraAddr;
    cmd[2] = 0x1;
    err_cnt = 0;

    while (err_cnt < 10)
    {
        clearRxBuf();
        cam_sendCmd(cmd, 6);
        if (CAM_SERIAL.readBytes((char *)resp, 6) != 6) continue;
        if (resp[0] == 0xaa && resp[1] == (0x0e | cameraAddr) && resp[2] == 0x04 && resp[4] == 0 && resp[5] == 0)
        {
            CAM_SERIAL.setTimeout(1000);
            if (CAM_SERIAL.readBytes((char *)resp, 6) != 6)
            {
                continue;
            }
            if (resp[0] == 0xaa && resp[1] == (0x0a | cameraAddr) && resp[2] == 0x01)
            {
                picTotalLen = (resp[3]) | (resp[4] << 8) | (resp[5] << 16);
                break;
            }
        }
        err_cnt ++;
    }

    return 0;

}

int GetData(void)
{
    unsigned int pktCnt = (picTotalLen) / (PIC_PKT_LEN - 6);
    if ((picTotalLen % (PIC_PKT_LEN-6)) != 0) pktCnt += 1;

    char cmd[] = { 0xaa, 0x0e | cameraAddr, 0x00, 0x00, 0x00, 0x00 };
    unsigned char pkt[PIC_PKT_LEN];

    char picName[] = "pic.jpg";     //make a jpg file named "pic.jpg", the file will be removed if it has already exist.

    if (SD.exists(picName)) {
        SD.remove(picName);
    }

    myFile = SD.open(picName, FILE_WRITE);
    if(!myFile) {
        Serial.print("Error: ["); 
        Serial.print(__LINE__);
        Serial.print("]: ");
        Serial.println("Open file error!");
        return -1;
    }

    CAM_SERIAL.setTimeout(1000);
    for (unsigned int i = 0; i < pktCnt; i++)
    {
        cmd[4] = i & 0xff;
        cmd[5] = (i >> 8) & 0xff;

        int retry_cnt = 0;
        retry:
        delay(10);
        clearRxBuf();
        cam_sendCmd(cmd, 6);
        uint16_t cnt = CAM_SERIAL.readBytes((char *)pkt, PIC_PKT_LEN);

        unsigned char sum = 0;
        for (int y = 0; y < cnt - 2; y++)
        {
            sum += pkt[y];
        }
        if (sum != pkt[cnt-2])
        {
            if (++retry_cnt < 100) goto retry;
            else break;
        }

        myFile.write((const uint8_t *)&pkt[4], cnt-6);  //write the date getted from camera.
    }
    cmd[4] = 0xf0;
    cmd[5] = 0xf0;
    cam_sendCmd(cmd, 6);

    myFile.close();

    return 0;
}

/**
 * @函数：int sendData(void)
 * @说明：发送图片数据
 * @返回值：int， 成功返回0， 异常返回（-1 ， -2 收到是控制台退出命令）
 */
int sendData(void){

    const int dataSize = 127;
    byte dataBuffer[dataSize];
    int tail = 0;
    // uint32_t time_cnt = 0;

    delay(1000);
    File photoFile = SD.open("pic.jpg");

    if(!photoFile) {
        Serial.print("Error: ["); 
        Serial.print(__LINE__);
        Serial.print("]: ");        
        Serial.println("Open photoFile error！");
        return -1;
    }

    while (photoFile.position() < photoFile.size()) {   //do when there is bytes in jpg file.

        // if(0 == (tail % dataSize)){
        //     time_cnt = millis();
        // }

        dataBuffer[tail++] = photoFile.read();   //fullfill the databuffer
        


        if(tail == dataSize){          //if already get dataSize byte from jpg file
            int val;
            // Serial.print("Read photoFile by 127 bytes: ");
            // Serial.println(millis() - time_cnt);

            do{
                // time_cnt = millis();
                int sum = 0;
                for(int i=0; i< dataSize; i++){
                    RF_SERIAL.write(dataBuffer[i]); // send the data in buffer
                    sum += dataBuffer[i];
                    sum = sum % 0xFF;           //calc the check byte.
                }
                RF_SERIAL.write(sum);            //send the check byte.
                tail = 0;

                // Serial.print("Send dataSize + 1 bytes: ");
                // Serial.println(millis() - time_cnt);

                // 等待监控台发来命令
                while(RF_SERIAL.available() <= 0){
                }

                val = RF_SERIAL.read();


                if(val == COMM_CAN ){
                    Serial.println("Received cancle!");
                    photoFile.close();
                    return -2;
                } else if(val == COMM_ACK) {
                    break;
                } else if(val != COMM_NAK) { // 收到指令，既不退出也不是重传，则退出。
                    Serial.println("Received rubbish!");
                    photoFile.close();
                    return -3;
                }
            } while (val == COMM_NAK);


        }
    }
    if(tail > 0){
        int val;
        do{
            int sum = 0;
            for(int i=0; i< dataSize; i++){
                if(i < tail){
                    RF_SERIAL.write(dataBuffer[i]);
                    sum += dataBuffer[i];
                    sum = sum % 0xFF;
                }else{
                    RF_SERIAL.write(0);    //if there are no bytes in jpg file, fill it with 0x00;
                }
            }
            Serial.print("[");
            Serial.print(__LINE__);
            Serial.print("]: ");
            Serial.println("Sent last pic data!");
            RF_SERIAL.write(sum);
            // 等待监控台发来命令
            while(RF_SERIAL.available() <= 0){
            }

            val = RF_SERIAL.read();
            if(val == COMM_CAN ){
                Serial.println("Received cancle!");
                photoFile.close();
                return -2;
            } else if(val == COMM_ACK) {
                break;
            } else if(val != COMM_NAK) { // 收到指令，既不退出也不是重传，则退出。
                Serial.println("Received rubbish!");
                photoFile.close();
                return -2;
            }
        } while (val == COMM_NAK);
    } /*End of "while (photoFile.position() < photoFile.size())"" */

    photoFile.close();

    return 0;
}


// END FILE

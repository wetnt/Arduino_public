#ifndef __UARLWIFI_H__
#define __UARLWIFI_H__
#include <Arduino.h>
#include <SoftwareSerial.h>

#define    OPEN          0
#define    WEP           1
#define    WAP_PSK       2
#define    WAP2_PSK      3
#define    WAP_WAP2_PSK  4

#define    TCP     1
#define    tcp     1
#define    UDP     0
#define    udp     0

#define    OPEN    1
#define    CLOSE   0

#define    STA     1
#define    AP      2
#define    AT+STA  3

#define SERIAL_TX_BUFFER_SIZE 128
#define SERIAL_RX_BUFFER_SIZE 128

class WIFI
{
  public:

    WIFI(void);
    //String begin(void);
    /*=================WIFI功能指令=================*/
    void Reset(void);    //重启模块
    String showMode(void);   //查询模块目前模式
    void confMode(byte a);   //设置模块的模式
    String showAP(void);   //返回wifi列表
    String showJAP(void);  //返回目前连接的wifi接入点信息
    void confJAP(String ssid , String pwd);    //配置登陆wifi接入点
    void quitAP(void);    //退出当前wifi连接
    String showSAP(void);     //显示ap模式下的模块的ssid 密码 通道号 以及加密方式
    void confSAP(String ssid , String pwd , byte chl , byte ecn);       //配置ap模式下的网络参数 ssid 密码 通道号 以及加密方式

    /*================TCP/IP指令================*/
    String showStatus(void);    //查询链接状态
    String showMux(void);       //查询目前的链接模式（单链接or多链接）
    void confMux(boolean a);    //设置链接模式（单链接【0】or多链接【1】）
    void newMux(byte type, String addr, int port);   //创建 tcp或者udp链接（单路模式)
    void newMux(byte id, byte type, String addr, int port);   //创建 tcp或者udp链接（多路模式)（id:0-4） 0号可以连接客户端和服务器，其他只能连接服务器
    void Send(String str);  //单路模式发送数据
    void Send(byte id, String str);  //多路模式发送数据
    void closeMux(void);   //关闭tcp或udp （单路模式）
    void closeMux(byte id); //关闭tcp货udp （多路模式）
    String showIP(void);    //显示本机目前获取的ip地址
    void confServer(byte mode, int port);  //配置服务器

};

#endif

#include <uarlWIFI.h>

//String WIFI::begin(void)

WIFI::WIFI(void)
{
  SoftwareSerial mySerial(10,11);
  mySerial.begin(9600);
  
}

/*===================================*/
/*
 * 重启wifi芯片
 *
 * */
/*===================================*/
void WIFI::Reset(void)
{
  SoftwareSerial mySerial(10,11);
  mySerial.begin(9600);
    mySerial.println("AT+Reset");
    while (1) {                            //当串口有完成数据返回时，结束语句
        if(mySerial.find("OCROBOT WIFI ready!!!")==true)
        {
           break;
        }
    }
}

/*********************************************
 *********************************************
 *********************************************
                   WIFI功能指令
 *********************************************
 *********************************************
 *********************************************
 */

/*==============================*/
/*
 *
 * 查询目前wifi模块的工作模式
 * */
/*===============================*/
String WIFI::showMode()
{
  SoftwareSerial mySerial(10,11);
  mySerial.begin(9600);
    String data;
    mySerial.println("AT+oakMODE?");  //发送AT指令
    while (1) {
     if(mySerial.available()>0)
     {
     char a =mySerial.read();
     data=data+a;
     }
     if (data.indexOf("done")!=-1)
     {
         break;
     }
  }
    if(data.indexOf("1")!=-1)
    {
        return "Station";
    }else if(data.indexOf("2")!=-1)
    {
            return "AP";
    }else if(data.indexOf("3")!=-1)
    {
         return "AP+Station";
    }
}



/*================================*/
/*
 *
 * 配置WIFI模块的工作模式(需要重启后方可生效)(done)
 *
 * */
/*================================*/

void WIFI::confMode(byte a)
{
  SoftwareSerial mySerial(10,11);
  mySerial.begin(9600);
    String data;
     mySerial.print("AT+oakMODE=");  //发送AT指令
     mySerial.println(String(a));
     while (1) {
      if(mySerial.available()>0)
      {
      char a =mySerial.read();
      data=data+a;
      }
      if (data.indexOf("done")!=-1 || data.indexOf("no change")!=-1)
      {
          break;
      }
   }
}




/*===================================*/
/*
 * 返回（字符串）当前wifi搜索到的接入点信息(只能在)
 * 加密类型、SSID、信号强度
 * */
/*===================================*/
String WIFI::showAP(void)
{
  SoftwareSerial mySerial(10,11);
  mySerial.begin(9600);
    String data;
    mySerial.println("AT+oakShowAP");  //发送AT指令
    while (1) {
   if(mySerial.available()>0)
   {
     char a =mySerial.read();
     data=data+a;
   }
     if (data.indexOf("done")!=-1 || data.indexOf("ERROR")!=-1 )
     {
         break;
     }
  }
    if(data.indexOf("ERROR")!=-1)
    {
        return "ERROR";
    }
    else{
       char head[4] = {0x0D,0x0A};   //头部多余字符串
       char tail[7] = {0x0D,0x0A,0x0D,0x0A};        //尾部多余字符串
       data.replace("AT+oakShowAP","");
       data.replace("done","");
       data.replace("+ShowAP","WIFI");
       data.replace(head,"");
       data.replace(tail,"");
        return data;
        }
 }


/*===================================*/
/*
 * 查询返回目前连接的wifi接入点信息  （done）
 *
 **/
/*===================================*/
String WIFI::showJAP(void)
{
  SoftwareSerial mySerial(10,11);
  mySerial.begin(9600);
    mySerial.println("AT+oakJoinAP?");  //发送AT指令
      String data;
      while (1) {
       if(mySerial.available()>0)
       {
       char a =mySerial.read();
       data=data+a;
       }
       if (data.indexOf("done")!=-1 || data.indexOf("ERROR")!=-1 )
       {
           break;
       }
    }
      char head[4] = {0x0D,0x0A};   //头部多余字符串
      char tail[7] = {0x0D,0x0A,0x0D,0x0A};        //尾部多余字符串
      data.replace("AT+oakJoinAP?","");
      data.replace("+oakJoinAP","AP");
      data.replace("done","");
      data.replace(head,"");
      data.replace(tail,"");
          return data;
}
/*=======================================*/
/*
 * 配置登陆网络需要的ssid名称以及密码(未验证，未测试)
 *
 * */
/*=======================================*/
void WIFI::confJAP(String ssid , String pwd)
{
  SoftwareSerial mySerial(10,11);
  mySerial.begin(9600);
    mySerial.print("AT+oakJoinAP=");
    mySerial.print("\"");     //"ssid"
    mySerial.print(ssid);
    mySerial.print("\"");

    mySerial.print(",");

    mySerial.print("\"");      //"pwd"
    mySerial.print(pwd);
    mySerial.println("\"");


    while (1) {                            //当串口有完成数据返回时，结束语句
        if(mySerial.find("done")==true)
        {
           break;
        }
    }
}
/*=============================================*/
/*
 * 退出目前登录的wifi节点
 *
 * /
 /*============================================*/

void WIFI::quitAP(void)
{
  SoftwareSerial mySerial(10,11);
  mySerial.begin(9600);
    mySerial.println("AT+oakExtAP");
    while (1) {                            //当串口有完成数据返回时，结束语句
        if(mySerial.find("done")==true)
        {
           break;
        }
    }

}

/*===============================================*/
/*
 *
 * AP模式下的网络配置
 *
 * */
/*==============================================*/
String WIFI::showSAP()
{
  SoftwareSerial mySerial(10,11);
  mySerial.begin(9600);
    mySerial.println("AT+oakSAP?");  //发送AT指令
      String data;
      while (1) {
       if(mySerial.available()>0)
       {
       char a =mySerial.read();
       data=data+a;
       }
       if (data.indexOf("done")!=-1 || data.indexOf("ERROR")!=-1 )
       {
           break;
       }
    }
      char head[4] = {0x0D,0x0A};   //头部多余字符串
      char tail[7] = {0x0D,0x0A,0x0D,0x0A};        //尾部多余字符串
      data.replace("AT+oakSAP?","");
      data.replace("+oakSAP","mySAP");
      data.replace("done","");
      data.replace(head,"");
      data.replace(tail,"");
          return data;
}

/*==============================================*/
/*
 *
 * 设置AP模式下的SSID 密码 信道 加密方式等信息  (只能用于ap模式或者ap+Station模式下，重启芯片后生效)
 *
 * /
 /*============================================*/

void WIFI::confSAP(String ssid , String pwd , byte chl , byte ecn)
{
  SoftwareSerial mySerial(10,11);
  mySerial.begin(9600);
    mySerial.print("AT+oakSAP=");  //发送AT指令
    mySerial.print("\"");     //"ssid"
    mySerial.print(ssid);
    mySerial.print("\"");

    mySerial.print(",");

    mySerial.print("\"");      //"pwd"
    mySerial.print(pwd);
    mySerial.print("\"");

    mySerial.print(",");
    mySerial.print(String(chl));

    mySerial.print(",");
    mySerial.println(String(ecn));
    while (1) {                            //当串口有完成数据返回时，结束语句
        if(mySerial.find("done")==true ||mySerial.find("ERROR")==true)
        {
           break;
        }
     }

}


/*********************************************
 *********************************************
 *********************************************
                   TPC/IP功能指令
 *********************************************
 *********************************************
 *********************************************
 */


/*==============================================*/
/*
 *
 * 获取目前的链接状态
 * <ID>  0-4
 * <type>  tcp or udp
 * <addr>  ip
 * <port>  port number
 * /
 /*============================================*/
String WIFI::showStatus(void)
{
  SoftwareSerial mySerial(10,11);
  mySerial.begin(9600);
    mySerial.println("AT+oakShowSTA");  //发送AT指令
      String data;
      while (1) {
       if(mySerial.available()>0)
       {
       char a =mySerial.read();
       data=data+a;
       }
       if (data.indexOf("done")!=-1)
       {
           break;
       }
    }

          char head[4] = {0x0D,0x0A};   //头部多余字符串
          char tail[7] = {0x0D,0x0A,0x0D,0x0A};        //尾部多余字符串
          data.replace("AT+oakShowSTA","");
          data.replace("done","");
          data.replace(head,"");
          data.replace(tail,"");
          return data;
}

/*============================================*/
/*
 * 查询目前的链接模式（单链接or多链接）
 * */
/*============================================*/
String WIFI::showMux(void)
{
  SoftwareSerial mySerial(10,11);
  mySerial.begin(9600);
    String data;
    mySerial.println("AT+oakMUX?");  //发送AT指令

      while (1) {
       if(mySerial.available()>0)
       {
       char a =mySerial.read();
       data=data+a;
       }
       if (data.indexOf("done")!=-1)
       {
           break;
       }
    }
          char head[3]={0x0D,0x0A};   //将回显数据处理成需要的格式
          data.replace("AT+oakMUX?","");
          data.replace("+oakMUX","showMux");
          data.replace("done","");
          data.replace(head,"");
          return data;
}

/*============================================*/
/*
 * 设置链接模式（单链接or多链接）
 * */
/*============================================*/
void WIFI::confMux(boolean a)
{
  SoftwareSerial mySerial(10,11);
  mySerial.begin(9600);
 mySerial.print("AT+oakMUX=");
 mySerial.println(a);           //发送AT指令
 while (1) {                            //当串口有完成数据返回时，结束语句
     if(mySerial.find("done")==true || mySerial.find("Link is builded")==true)
     {
        break;
     }
  }
}


/*============================================*/
/*
 * 建立tcp链接或者注册UDP端口号（单路模式）
 *
 * */
/*===========================================*/
void WIFI::newMux(byte type, String addr, int port)

{
  SoftwareSerial mySerial(10,11);
  mySerial.begin(9600);
    String data;
    mySerial.print("AT+oakNewSTA=");
    if(type>0)
    {
        mySerial.print("\"TCP\"");
    }else
    {
        mySerial.print("\"UDP\"");
    }
    mySerial.print(",");
    mySerial.print("\"");
    mySerial.print(addr);
    mySerial.print("\"");
    mySerial.print(",");
//    mySerial.print("\"");
    mySerial.println(String(port));
//    mySerial.println("\"");
    while (1) {
     if(mySerial.available()>0)
     {
     char a =mySerial.read();
     data=data+a;
     }
     if (data.indexOf("done")!=-1 || data.indexOf("ALREAY CONNECT")!=-1 || data.indexOf("ERROR")!=-1)
     {
         break;
     }
  }
}
/*============================================*/
/*
 * 建立tcp链接或者注册UDP端口号（多路模式）（0-4共计5路）
 *
 * */
/*===========================================*/
void WIFI::newMux( byte id, byte type, String addr, int port)

{
  SoftwareSerial mySerial(10,11);
  mySerial.begin(9600);
    mySerial.print("AT+oakNewSTA=");
    mySerial.print("\"");
    mySerial.print(String(id));
    mySerial.print("\"");
    if(type>0)
    {
        mySerial.print("\"tcp\"");
    }else
    {
        mySerial.print("\"UDP\"");
    }
    mySerial.print(",");
    mySerial.print("\"");
    mySerial.print(addr);
    mySerial.print("\"");
    mySerial.print(",");
//    mySerial.print("\"");
    mySerial.println(String(port));
//    mySerial.println("\"");
    String data;
    while (1) {

     if(mySerial.available()>0)
     {
     char a =mySerial.read();
     data=data+a;
     }
     if (data.indexOf("done")!=-1 || data.indexOf("ALREAY CONNECT")!=-1 || data.indexOf("ERROR")!=-1)
     {
         break;
     }
  }

}
/*==============================================*/
/*
 * 发送数据(单路模式)
 *
 * */
/*==============================================*/
void WIFI::Send(String str)
{
  SoftwareSerial mySerial(10,11);
  mySerial.begin(9600);
    mySerial.print("AT+oakUpDate=");
//    mySerial.print("\"");
    mySerial.println(str.length());
//    mySerial.println("\"");
    while (1) {                            //当串口有完成数据返回时，结束语句
        if(mySerial.find(">")==true )
        {
           break;
        }
     }
    mySerial.println(str);


    String data;
    while (1) {
     if(mySerial.available()>0)
     {
     char a =mySerial.read();
     data=data+a;
     }
     if (data.indexOf("SEND OK")!=-1)
     {
         break;
     }
  }
}

/*==============================================*/
/*
 * 发送数据(多路路模式)
 *
 * */
/*==============================================*/
void WIFI::Send(byte id, String str)
{
  SoftwareSerial mySerial(10,11);
  mySerial.begin(9600);
    mySerial.print("AT+oakUpDate=");

    mySerial.print(String(id));
    mySerial.println(",");
    mySerial.println(str.length());
    while (1) {                            //当串口有完成数据返回时，结束语句
        if(mySerial.find(">")==true )
        {
           break;
        }
     }
    mySerial.println(str);


    String data;
    while (1) {
     if(mySerial.available()>0)
     {
     char a =mySerial.read();
     data=data+a;
     }
     if (data.indexOf("SEND OK")!=-1)
     {
         break;
     }
  }
}

/*========================================*/
/*
 *
 * 关闭TCP或UDP链接（单路模式）
 *
 * *-*/
/*=======================================*/
void WIFI::closeMux(void)
{
  SoftwareSerial mySerial(10,11);
  mySerial.begin(9600);
    mySerial.println("AT+oakCLOSE");

    String data;
    while (1) {
     if(mySerial.available()>0)
     {
     char a =mySerial.read();
     data=data+a;
     }
     if (data.indexOf("Linked")!=-1 || data.indexOf("ERROR")!=-1 || data.indexOf("we must restart")!=-1)
     {
         break;
     }
  }
}


/*========================================*/
/*
 *
 * 关闭TCP或UDP链接（多路模式）
 *
 * *-*/
/*=======================================*/
void WIFI::closeMux(byte id)
{
  SoftwareSerial mySerial(10,11);
  mySerial.begin(9600);
    mySerial.print("AT+oakCLOSE=");
    mySerial.println(String(id));
    String data;
    while (1) {
     if(mySerial.available()>0)
     {
     char a =mySerial.read();
     data=data+a;
     }
     if (data.indexOf("done")!=-1 || data.indexOf("Link is not")!=-1 || data.indexOf("Cant close")!=-1)
     {
         break;
     }
  }

}

/*=========================================*/
/*
 * 获取目前的本机IP地址
 * */
/*=========================================*/
String WIFI::showIP(void)
{  
SoftwareSerial mySerial(10,11);
  mySerial.begin(9600);

    mySerial.println("AT+oakShowIP");  //发送AT指令
    String data;
    while (1) {
     if(mySerial.available()>0)
     {
     char a =mySerial.read();
     data=data+a;
     }
     if (data.indexOf("done")!=-1)
     {
         break;
     }
  }
    return data;
}

/*=======================================*/
/*
 *
 * 配置为服务器
 *
*/
/*=======================================*/

void WIFI::confServer(byte mode, int port)
{
  SoftwareSerial mySerial(10,11);
  mySerial.begin(9600);
    mySerial.print("AT+oakServer=");  //发送AT指令
    mySerial.print(String(mode));
    mySerial.print(",");
    mySerial.println(String(port));

    String data;
    while (1) {
     if(mySerial.available()>0)
     {
     char a =mySerial.read();
     data=data+a;
     }
     if (data.indexOf("done")!=-1 || data.indexOf("Link is builded")!=-1)
     {
         break;
     }
  }
}

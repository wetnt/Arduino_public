//http://www.geek-workshop.com/forum.php?mod=viewthread&tid=15778&highlight=8266
//http://wiki.iteadstudio.com/ESP8266_Serial_WIFI_Module
//--------------------------------------------
//AT  OK
//--------------------------------------------
//AT+GMR
//AT version:0.21.0.0
//SDK version:0.9.5
//--------------------------------------------
//AT+CWMODE=1
//AT+RST
//OK
//AT+CIOBAUD=9600
//OK
//--------------------------------------------
//AT+CWMODE?
//+CWMODE:1
//OK
//--------------------------------------------
//AT+CWJAP?
//No AP
//+CWJAP:"acDev"
//OK
//--------------------------------------------
//AT+CWJAP="MMMM","1234567890123"
//AT+CWJAP="acDev","AbroadCar2015()"
//OK
//--------------------------------------------
//AT+CWJAP?
//+CWJAP:"acDev"
//OK
//--------------------------------------------
//AT+CIFSR
//+CIFSR:STAIP,"172.16.102.154"
//+CIFSR:STAMAC,"18:fe:34:a1:9b:1c"
//OK
//--------------------------------------------
//AT+CIPSTART="TCP","www.bbkgps.com",80
//CONNECT
//OK
//--------------------------------------------
//AT+CIPSEND=97
//OK
//--------------------------------------------
//GET /t.php HTTP/1.1 \r\nHost: www.bbkgps.com \r\nUser-Agent: abc \r\nConnection: close \r\n\r\n
//SEND OK
//--------------------------------------------
//AT+CIPCLOSE
//CLOSED
//OK
//--------------------------------------------
//--------------------------------------------
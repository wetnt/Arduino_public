
uchar com2cuont=0;
uchar xdata HCHObuf[10];
void Uart2() interrupt 8 using 1   //UART2 中断服务程序
{		
    if (S2CON & S2RI)
    {
			S2CON &= ~S2RI;
			HCHObuf[com2cuont] = S2BUF;   //吧数据接收到数组。
			com2cuont++;
			if(com2cuont==10)com2cuont=0;
    }
    if (S2CON & S2TI)
    {
        S2CON &= ~S2TI;             //清除TI位
        busy2 = 0;                  //清忙标志
    }
}
void GETHCHO()
{
	uint i,j,k,p;
	HCHOxc();
	i=HCHObuf[6]/16;
	switch(i)
		{
			case '0': i=0;break;
			case '1': i=1;break;
			case '2': i=2;break;
			case '3': i=3;break;
			case '4': i=4;break;
			case '5': i=5;break;
			case '6': i=6;break;
			case '7': i=7;break;
			case '8': i=8;break;
			case '9': i=9;break;
			case 'A': i=10;break;
			case 'B': i=11;break;
			case 'C': i=12;break;
			case 'D': i=13;break;
			case 'E': i=14;break;
			case 'F': i=15;break;
		}
	j=i*16;
	i=HCHObuf[6]%16;
	switch(i)
		{
			case '0': i=0;break;
			case '1': i=1;break;
			case '2': i=2;break;
			case '3': i=3;break;
			case '4': i=4;break;
			case '5': i=5;break;
			case '6': i=6;break;
			case '7': i=7;break;
			case '8': i=8;break;
			case '9': i=9;break;
			case 'A': i=10;break;
			case 'B': i=11;break;
			case 'C': i=12;break;
			case 'D': i=13;break;
			case 'E': i=14;break;
			case 'F': i=15;break;
		}		
	k=(j+i)*256;
	i=HCHObuf[7]/16;
	switch(i)
		{
			case '0': i=0;break;
			case '1': i=1;break;
			case '2': i=2;break;
			case '3': i=3;break;
			case '4': i=4;break;
			case '5': i=5;break;
			case '6': i=6;break;
			case '7': i=7;break;
			case '8': i=8;break;
			case '9': i=9;break;
			case 'A': i=10;break;
			case 'B': i=11;break;
			case 'C': i=12;break;
			case 'D': i=13;break;
			case 'E': i=14;break;
			case 'F': i=15;break;
		}
	j=i*16;
	i=HCHObuf[7]%16;
	switch(i)
		{
			case '0': i=0;break;
			case '1': i=1;break;
			case '2': i=2;break;
			case '3': i=3;break;
			case '4': i=4;break;
			case '5': i=5;break;
			case '6': i=6;break;
			case '7': i=7;break;
			case '8': i=8;break;
			case '9': i=9;break;
			case 'A': i=10;break;
			case 'B': i=11;break;
			case 'C': i=12;break;
			case 'D': i=13;break;
			case 'E': i=14;break;
			case 'F': i=15;break;
		}		
	p=j+i;

	HCHO=k+p;
	
	baiwei=HCHO/100; 
	shiwei=(HCHO%100)/10;
	gewei=(HCHO%100)%10; 	

	HCHOdata[0]=baiwei;
	HCHOdata[1]=shiwei;
	HCHOdata[2]=gewei;
}

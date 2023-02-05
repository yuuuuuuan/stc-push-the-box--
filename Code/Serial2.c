#include "STC15F.h"
#include "intrins.h"
#include "Serial2.h"
bit mode;
u8 RcvCNT;  //接收到的字符个数
void Serial2_INI(void)  //串口初始化程序：baud=9600@11.0592MHZ，T2完成：方式0，1T模式
{ //串口2初始化	//11.0592MhZ
    TH2=0xFE;
	  TL2=0xE0;
	  AUXR=0x14;    //采用T2产生波特率，1T模式，启动T2	
    //P_SW2|=0x01;   //S2口管脚选定在P46(RXD) P47(TXD)
	  //P_SW2&=0xFE;   //S2口管脚选定在P10(RXD) P11(TXD)
	  S2CON=0x50;   //启动串口2，方式0:8位数据，波特率可变模式，接收允许     
}

//串口中断服务程序
void Serial2INT(void) interrupt 8 using 1
{  
   if((S2CON & 1) != 0) //接收中断
    {
        S2CON &= ~1;    //清除接收中断标志
			
			switch (RcvCNT)
			{case 0:	
				     {if (S2BUF=='A')
						      RcvCNT=1;						 
						     break;						 
						  }
          case 1:
             	{if (S2BUF=='T')
						      RcvCNT=2;						 
						   else	
                  RcvCNT=0;	
							 break;
						  }		
          case 2:
             	{if (S2BUF=='+')
						      RcvCNT=3;						 
						   else	
                  RcvCNT=0;	
							 break;
						  }	
          case 3:
             	{if (S2BUF=='C') //检测到一次AT+C指令
						       { mode=~mode;
										 RcvCNT=0;
									  }						 
						   else	
                  RcvCNT=0;	
							 break;
						  }	
			}   						   							
	     
	 	}
  
 }
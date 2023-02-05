/*****************************************
*延时函数
*入口参数：Nms，延时的ms数1~65535
*出口参数：无
*函数功能：软件不精确延时
*******************************************/
#include "Delay.h"
void DelayNms(unsigned int Nms)
    { unsigned int i;
			 do
			   {
					  i=MAIN_Fosc/13000;
				    while(--i);
				 } while(--Nms);
		}
void DelayNds(unsigned char N)//延时Nx0.1秒 N=1~255 	//@12.000MHz 示波器测试验证比较精确
   {	 
	unsigned char i, j, k;
	do {
	     i = 2;
		 j = 105;
		 k = 90;
	     while(i--)
		    { while(j--)
		        {
			      while(k--)
		            {
			      	  ;
				    }
				}
			 }
	   }while (--N);
   }
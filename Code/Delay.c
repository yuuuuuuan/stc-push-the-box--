/*****************************************
*��ʱ����
*��ڲ�����Nms����ʱ��ms��1~65535
*���ڲ�������
*�������ܣ��������ȷ��ʱ
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
void DelayNds(unsigned char N)//��ʱNx0.1�� N=1~255 	//@12.000MHz ʾ����������֤�ȽϾ�ȷ
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
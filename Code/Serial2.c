#include "STC15F.h"
#include "intrins.h"
#include "Serial2.h"
bit mode;
u8 RcvCNT;  //���յ����ַ�����
void Serial2_INI(void)  //���ڳ�ʼ������baud=9600@11.0592MHZ��T2��ɣ���ʽ0��1Tģʽ
{ //����2��ʼ��	//11.0592MhZ
    TH2=0xFE;
	  TL2=0xE0;
	  AUXR=0x14;    //����T2���������ʣ�1Tģʽ������T2	
    //P_SW2|=0x01;   //S2�ڹܽ�ѡ����P46(RXD) P47(TXD)
	  //P_SW2&=0xFE;   //S2�ڹܽ�ѡ����P10(RXD) P11(TXD)
	  S2CON=0x50;   //��������2����ʽ0:8λ���ݣ������ʿɱ�ģʽ����������     
}

//�����жϷ������
void Serial2INT(void) interrupt 8 using 1
{  
   if((S2CON & 1) != 0) //�����ж�
    {
        S2CON &= ~1;    //��������жϱ�־
			
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
             	{if (S2BUF=='C') //��⵽һ��AT+Cָ��
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
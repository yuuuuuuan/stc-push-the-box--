//�������ɨ������
//4x4���󰴼�����P0�ڣ����÷�ת��ʶ��
//��ڲ�������
//���ڲ�����Key:��������0~F,û�а��������򷵻�ֵΪ0x55
#include "STC15F.h"
#include "intrins.h"
#include "KeyScan.h"
#include "Delay.h"
unsigned char  KeyScan(void)
  {	 //������̼��
	   u8 KeyNO=0x10;     //��ת��ʶ���ɨ����,û�а������»��߰�����������ɨ���벻����֪�ķ�Χ������0x55
     u8 row,colm;       //���롢���뼰ɨ��õ��ļ���
     u8 Key=0x55;    
		 P0=0xF0; //�Ƚ�P0�ڸ���λ������1������λ������0������м�����
		          //����Ӧ���б����ͣ���ʱP0�ڲ�����0xF0��
		 NOP5();  //�ȴ��˿������ȶ�
		
		 if (P0!=0xF0)//��������м�����
			{ DelayNms(3);//��ʱ2-5ms������������
		    if (P0!=0xF0) //ȷʵ�м����£�����������ʶ��
				   {
						row=P0;       //����ɨ����
						
					  P0=0x0F;			  //���з�ת
					  NOP5();         //�ȴ��˿������ȶ�  
					  colm=P0;        //����ɨ����
					  
						KeyNO=row+colm;	 //����ɨ����ϲ����õ���ɨ����
						
						 switch (KeyNO)
								{ 
									case 0xee: Key=0;break;
									case 0xed: Key=1;break;
									case 0xeb: Key=2;break;
									case 0xe7: Key=3;break;
									case 0xde: Key=4;break;
									case 0xdd: Key=5;break;
									case 0xdb: Key=6;break;
									case 0xd7: Key=7;break;
									case 0xbe: Key=8;break;
									case 0xbd: Key=9;break;
									case 0xbb: Key=0xA;break;
									case 0xb7: Key=0xB;break;
									case 0x7e: Key=0xC;break;
									case 0x7d: Key=0xD;break;
									case 0x7b: Key=0xE;break;
									case 0x77: Key=0xF;break;
								
									default: Key=0x55;
		            }
						while(P0!=0x0F); //�ȴ������ɿ�		
						}
				
		  }
	      return Key;		
  }	

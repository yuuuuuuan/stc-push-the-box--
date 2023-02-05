//矩阵键盘扫描程序包
//4x4矩阵按键接在P0口，采用反转法识别
//入口参数：无
//出口参数：Key:按键编码0~F,没有按键按下则返回值为0x55
#include "STC15F.h"
#include "intrins.h"
#include "KeyScan.h"
#include "Delay.h"
unsigned char  KeyScan(void)
  {	 //矩阵键盘监控
	   u8 KeyNO=0x10;     //反转法识别键扫描码,没有按键按下或者按键不正常，扫描码不在已知的范围，返回0x55
     u8 row,colm;       //行码、列码及扫描得到的键码
     u8 Key=0x55;    
		 P0=0xF0; //先将P0口高四位行线置1，低四位列线置0，如果有键按下
		          //则相应的行被拉低，此时P0口不等于0xF0。
		 NOP5();  //等待端口数据稳定
		
		 if (P0!=0xF0)//矩阵键盘有键按下
			{ DelayNms(3);//延时2-5ms，按键消抖动
		    if (P0!=0xF0) //确实有键按下，则启动按键识别
				   {
						row=P0;       //存行扫描码
						
					  P0=0x0F;			  //行列反转
					  NOP5();         //等待端口数据稳定  
					  colm=P0;        //存列扫描码
					  
						KeyNO=row+colm;	 //行列扫描码合并，得到键扫描码
						
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
						while(P0!=0x0F); //等待按键松开		
						}
				
		  }
	      return Key;		
  }	

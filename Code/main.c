#include "STC15F.h"
#include "intrins.h"
#include "Delay.h"
#include "KeyScan.h"
#include "LCD12864.h"
#include "GPIO.H"
#include "Serial2.h"

#define BLANK 0
#define WALL 1
#define PLAYER 2
#define BOX 3
#define DES 4
#define LEVEL 1
#define ROW 8
#define COL 8
#define MOVE_UP 2
#define MOVE_DOWN 6
#define MOVE_LEFT 5
#define MOVE_RIGHT 7


void game_draw(void);
void game_move(void);
void Displaycube (u8 r,u8 c,u8 code *DData);
void		 DisplayClear (void);
u8 button = 0X55;
u8  Tcount=0;
u8 PLAYER_ROW;
u8 PLAYER_COL;
u8 cookie[]={
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};
u8 MAP[LEVEL][ROW][COL] = 
{
	{
		{0,0,0,1,1,1,0,0},
		{0,0,0,1,4,1,0,0},
		{0,0,0,1,0,1,0,0},
		{1,1,1,1,3,1,1,1},
		{1,4,0,3,2,3,4,1},
		{1,1,1,1,3,1,1,1},
		{0,0,0,1,4,1,0,0},
		{0,0,0,1,1,1,0,0}
	}
};

code u8 Img_DB[64] = 
{
	0xFF,0xC3,0xA5,0x99,0x99,0xA5,0xC3,0xFF
};


code u8 Img_DP[64] = 
{
	0x18,0x3C,0x7E,0x5A,0x5A,0x5A,0x3C,0x24
};

code u8 Img_DES[64] = 
{
	0x00,0x18,0x24,0x42,0x42,0x24,0x18,0x00
};

code u8 Img_BLANK[64] = 
{
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

code u8 Img_BOX[64] = 
{
	0xFF,0x81,0xFF,0x81,0x81,0xFF,0x81,0xFF
};

code u8 Img_PLAYER[64] = 
{
	0x18,0x18,0x7E,0x5A,0x5A,0x18,0x24,0x24
};

code u8 Img_WALL[64] = 
{
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff
};



u8 DES_CNT[LEVEL] = {4};
u8 DESBOX = 0;
u8 LEVEL_CNT = 0;

u8  code open_line1[] = {" GAME"};
u8  code open_line2[] = {" Push the Boxes"};
u8  code open_line3[] = {" OPEN"};
u8  code open_line4[] = {" MadeByYuuuan"};

u8  code frame_line1[] = {"TIME"};
u8  code frame_line2[] = {""};
u8  code frame_line3[] = {"GOAT"};
u8  code frame_line4[] = {""};

code u8 frame_img[1024] = {

0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,

		
};



void main(void)
{
		
		GPIO();
    TMOD=0x00; //T0 T1方式0：16位自动重装定时器模式，使用12分频系统时钟   
    TH0=0x3C;  //@12MHZ 定时50ms，中断20次为1s
	  TL0=0xB0;
	  ET0=1;     //开启定时器T0中断
	  TR0=1;     //启动定时器，开始计时
		
	    
			
	
		DisableHC595();     //禁止掉学习板上的HC595显示，省电

    delay_ms(100); //启动等待，等LCD讲入工作状态
    LCDInit(); //LCM初始化
    delay_ms(5); //延时片刻(可不要)
	  LCDClear();
		DisplayClear ();
	if(0)
	{
		while(1)
		{
	  
			button=KeyScan();
			delay_ms(5);
			if(button!=KeyScan())
			{
				button = 0X55;
			}
			DisplayListChar(0,1,open_line1);
			DisplayListChar(0,2,open_line2);
			DisplayListChar(0,3,open_line3);
			DisplayListChar(0,4,open_line4);
			//game_frame();
		}
	}
	if(1)
	{
		while(1)
		{
			game_draw();
			delay_ms(5);
			game_move();
			delay_ms(5);
		}
	}
}

void Displaycube (u8 r,u8 c,u8 code *DData)

{
    u8 x,i;
		i=c%2;
		if(r<4)       
    {
        for(x=0;x<8;x++)
        {
            WriteCommandLCD(0x36,1);
            WriteCommandLCD((0x80+r*8+x),1);
            WriteCommandLCD((0x80+c/2),1);    
            WriteCommandLCD(0x30,1);        
						if(i==0)
						{
							WriteDataLCD(DData[x]);
							cookie[x]=DData[x];
						}
						else
							
						{
							
							WriteDataLCD(cookie[x]);
							WriteDataLCD(DData[x]);
						}
        }
    }
		if(r>=4)      
    {
        for(x=0;x<8;x++)
        {
            WriteCommandLCD(0x36,1);
            WriteCommandLCD((0x80+(r-4)*8+x),1);
            WriteCommandLCD((0x88+c/2),1);    
            WriteCommandLCD(0x30,1);        
						if(i==0)
						{
							WriteDataLCD(DData[x]);
							cookie[x]=DData[x];
						}
						else
							
						{
							
							WriteDataLCD(cookie[x]);
							WriteDataLCD(DData[x]);
						}
        }
    }
		WriteCommandLCD(0x34,1);
    WriteCommandLCD(0x30,1);
}

void game_draw(void)
{
	u8 j=0,k=0;
	for(j=0;j<ROW;j++)
	{	
		for(k=0;k<COL;k++)
		{
			if(MAP[LEVEL_CNT][j][k]==PLAYER||MAP[0][j][k]==PLAYER+DES)
			{
				PLAYER_ROW=j;
				PLAYER_COL=k;
			}
			
			if(MAP[LEVEL_CNT][j][k]==DES+BOX)
			{
				DESBOX++;
				if(DES_CNT[LEVEL_CNT]==DESBOX)
				{
					DESBOX = 0;
					LEVEL_CNT++;
				}
			}
			switch(MAP[LEVEL_CNT][j][k])
			{
				case BLANK:
					Displaycube (j,k,Img_BLANK);
					break;
				case WALL:
					Displaycube (j,k,Img_WALL);
					break;
				case PLAYER:
					Displaycube (j,k,Img_PLAYER);
					break;
				case BOX:
					Displaycube (j,k,Img_BOX);
					break;
				case DES:
					Displaycube (j,k,Img_DES);
					break;
				case PLAYER+DES:
					Displaycube (j,k,Img_DP);
					break;
				case BOX+DES:
					Displaycube (j,k,Img_DB);
					break;
			}

		}
	}
}



void game_move(void)
{
	delay_ms(5);
	button=KeyScan();
	delay_ms(5);
	switch(button)
	{
				case MOVE_UP:
					switch(MAP[LEVEL_CNT][PLAYER_ROW-1][PLAYER_COL])
					{
						case BOX:
							if(MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL]==PLAYER+DES)
							{
								if(MAP[LEVEL_CNT][PLAYER_ROW-2][PLAYER_COL]==BLANK)
								{
									MAP[LEVEL_CNT][PLAYER_ROW-2][PLAYER_COL]=BOX;
									MAP[LEVEL_CNT][PLAYER_ROW-1][PLAYER_COL]=PLAYER;
									MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL]=DES;
								}
								else if(MAP[LEVEL_CNT][PLAYER_ROW-2][PLAYER_COL]==DES)
								{
									MAP[LEVEL_CNT][PLAYER_ROW-2][PLAYER_COL]=BOX+DES;
									MAP[LEVEL_CNT][PLAYER_ROW-1][PLAYER_COL]=PLAYER;
									MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL]=DES;
								}
								else
								{
								
								}
							}
							
							else
							{
								if(MAP[LEVEL_CNT][PLAYER_ROW-2][PLAYER_COL]==BLANK)
								{
									MAP[LEVEL_CNT][PLAYER_ROW-2][PLAYER_COL]=BOX;
									MAP[LEVEL_CNT][PLAYER_ROW-1][PLAYER_COL]=PLAYER;
									MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL]=BLANK;
								}
								else if(MAP[LEVEL_CNT][PLAYER_ROW-2][PLAYER_COL]==DES)
								{
									MAP[LEVEL_CNT][PLAYER_ROW-2][PLAYER_COL]=BOX+DES;
									MAP[LEVEL_CNT][PLAYER_ROW-1][PLAYER_COL]=PLAYER;
									MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL]=BLANK;
								}
								else
								{
								
								}
							}
						break;
						
						case WALL:
							
						break;
						
						case BLANK:
							if(MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL]==PLAYER+DES)
							{
								MAP[LEVEL_CNT][PLAYER_ROW-1][PLAYER_COL]=PLAYER;
								MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL]=DES;
							}
							else
							{
								MAP[LEVEL_CNT][PLAYER_ROW-1][PLAYER_COL]=PLAYER;
								MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL]=BLANK;
							}
						
						break;
						
						case DES:
							if(MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL]==PLAYER+DES)
							{
								MAP[LEVEL_CNT][PLAYER_ROW-1][PLAYER_COL]=PLAYER+DES;
								MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL]=DES;
							}
							else
							{
								MAP[LEVEL_CNT][PLAYER_ROW-1][PLAYER_COL]=PLAYER+DES;
								MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL]=BLANK;
							}
						
						break;
					}
					break;
				case MOVE_DOWN:
					switch(MAP[LEVEL_CNT][PLAYER_ROW+1][PLAYER_COL])
					{
						case BOX:
							if(MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL]==PLAYER+DES)
							{
								if(MAP[LEVEL_CNT][PLAYER_ROW+2][PLAYER_COL]==BLANK)
								{
									MAP[LEVEL_CNT][PLAYER_ROW+2][PLAYER_COL]=BOX;
									MAP[LEVEL_CNT][PLAYER_ROW+1][PLAYER_COL]=PLAYER;
									MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL]=DES;
								}
								else if(MAP[LEVEL_CNT][PLAYER_ROW+2][PLAYER_COL]==DES)
								{
									MAP[LEVEL_CNT][PLAYER_ROW+2][PLAYER_COL]=BOX;
									MAP[LEVEL_CNT][PLAYER_ROW+1][PLAYER_COL]=PLAYER;
									MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL]=DES;
								}
								else
								{
								
								}
							}
							
							else
							{
								if(MAP[LEVEL_CNT][PLAYER_ROW+2][PLAYER_COL]==BLANK)
								{
									MAP[LEVEL_CNT][PLAYER_ROW+2][PLAYER_COL]=BOX;
									MAP[LEVEL_CNT][PLAYER_ROW+1][PLAYER_COL]=PLAYER;
									MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL]=BLANK;
								}
								else if(MAP[LEVEL_CNT][PLAYER_ROW+2][PLAYER_COL]==DES)
								{
									MAP[LEVEL_CNT][PLAYER_ROW+2][PLAYER_COL]=BOX;
									MAP[LEVEL_CNT][PLAYER_ROW+1][PLAYER_COL]=PLAYER;
									MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL]=BLANK;
								}
								else
								{
								
								}
							}
						break;
						
						case WALL:
							
						break;
						
						case BLANK:
							if(MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL]==PLAYER+DES)
							{
								MAP[LEVEL_CNT][PLAYER_ROW+1][PLAYER_COL]=PLAYER;
								MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL]=DES;
							}
							else
							{
								MAP[LEVEL_CNT][PLAYER_ROW+1][PLAYER_COL]=PLAYER;
								MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL]=BLANK;
							}
						
						break;
						
						case DES:
							if(MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL]==PLAYER+DES)
							{
								MAP[LEVEL_CNT][PLAYER_ROW+1][PLAYER_COL]=PLAYER+DES;
								MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL]=DES;
							}
							else
							{
								MAP[LEVEL_CNT][PLAYER_ROW+1][PLAYER_COL]=PLAYER+DES;
								MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL]=BLANK;
							}
						
						break;
					}
					break;
				case MOVE_LEFT:
					switch(MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL-1])
					{
						case BOX:
							if(MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL]==PLAYER+DES)
							{
								if(MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL-2]==BLANK)
								{
									MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL-2]=BOX;
									MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL-1]=PLAYER;
									MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL]=DES;
								}
								else if(MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL-2]==DES)
								{
									MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL-2]=BOX;
									MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL-1]=PLAYER;
									MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL]=DES;
								}
								else
								{
								
								}
							}
							
							else
							{
								if(MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL-2]==BLANK)
								{
									MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL-2]=BOX;
									MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL-1]=PLAYER;
									MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL]=BLANK;
								}
								else if(MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL-2]==DES)
								{
									MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL-2]=BOX;
									MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL-1]=PLAYER;
									MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL]=BLANK;
								}
								else
								{
								
								}
							}
						break;
						
						case WALL:
							
						break;
						
						case BLANK:
							if(MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL]==PLAYER+DES)
							{
								MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL-1]=PLAYER;
								MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL]=DES;
							}
							else
							{
								MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL-1]=PLAYER;
								MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL]=BLANK;
							}
						
						break;
						
						case DES:
							if(MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL]==PLAYER+DES)
							{
								MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL-1]=PLAYER+DES;
								MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL]=DES;
							}
							else
							{
								MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL-1]=PLAYER+DES;
								MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL]=BLANK;
							}
						
						break;
					}
					break;
				case MOVE_RIGHT:
					switch(MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL+1])
					{
						case BOX:
							if(MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL]==PLAYER+DES)
							{
								if(MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL+2]==BLANK)
								{
									MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL+2]=BOX;
									MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL+1]=PLAYER;
									MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL]=DES;
								}
								else if(MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL+2]==DES)
								{
									MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL+2]=BOX;
									MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL+1]=PLAYER;
									MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL]=DES;
								}
								else
								{
								
								}
							}
							
							else
							{
								if(MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL+2]==BLANK)
								{
									MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL+2]=BOX;
									MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL+1]=PLAYER;
									MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL]=BLANK;
								}
								else if(MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL+2]==DES)
								{
									MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL+2]=BOX;
									MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL+1]=PLAYER;
									MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL]=BLANK;
								}
								else
								{
								
								}
							}
						break;
						
						case WALL:
							
						break;
						
						case BLANK:
							if(MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL]==PLAYER+DES)
							{
								MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL+1]=PLAYER;
								MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL]=DES;
							}
							else
							{
								MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL+1]=PLAYER;
								MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL]=BLANK;
							}
						
						break;
						
						case DES:
							if(MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL]==PLAYER+DES)
							{
								MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL+1]=PLAYER+DES;
								MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL]=DES;
							}
							else
							{
								MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL+1]=PLAYER+DES;
								MAP[LEVEL_CNT][PLAYER_ROW][PLAYER_COL]=BLANK;
							}
						
						break;
					}
					break;
				
	}
		
}

void timer0 (void) interrupt 1
{
  Tcount++;  //50ms中断次数计数器加一 ，如果等于20,1s到，主程序中查询此变量计时，并清零。
}

		
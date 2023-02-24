
/*************  功能说明    **************

ST7920的基本驱动程序

******************************************/

typedef 	unsigned char	u8 ;
typedef 	unsigned int	u16 ;
typedef 	unsigned long	u32 ;
#include    "reg51.h"
#include    "intrins.h"
#include    "LCD12864.h"
#define     MAIN_Fosc       11059200L   //定义主时钟


sfr TH2  = 0xD6;
sfr TL2  = 0xD7;
sfr IE2   = 0xAF;
sfr INT_CLKO = 0x8F;
sfr AUXR = 0x8E;
sfr AUXR1 = 0xA2;
sfr P_SW1 = 0xA2;
sfr P_SW2 = 0xBA;
sfr S2CON = 0x9A;
sfr S2BUF = 0x9B;

sfr ADC_CONTR = 0xBC;   //带AD系列
sfr ADC_RES   = 0xBD;   //带AD系列
sfr ADC_RESL  = 0xBE;   //带AD系列
sfr P1ASF = 0x9D;   //只写，模拟输入(AD或LVD)选择

sfr P4   = 0xC0;
sfr P5   = 0xC8;
sfr P6   = 0xE8;
sfr P7   = 0xF8;
sfr P1M1 = 0x91;    //PxM1.n,PxM0.n     =00--->Standard,    01--->push-pull
sfr P1M0 = 0x92;    //                  =10--->pure input,  11--->open drain
sfr P0M1 = 0x93;
sfr P0M0 = 0x94;
sfr P2M1 = 0x95;
sfr P2M0 = 0x96;
sfr P3M1 = 0xB1;
sfr P3M0 = 0xB2;
sfr P4M1 = 0xB3;
sfr P4M0 = 0xB4;
sfr P5M1 = 0xC9;
sfr P5M0 = 0xCA;
sfr P6M1 = 0xCB;
sfr P6M0 = 0xCC;
sfr P7M1 = 0xE1;
sfr P7M0 = 0xE2;

sbit P00 = P0^0;
sbit P01 = P0^1;
sbit P02 = P0^2;
sbit P03 = P0^3;
sbit P04 = P0^4;
sbit P05 = P0^5;
sbit P06 = P0^6;
sbit P07 = P0^7;
sbit P10 = P1^0;
sbit P11 = P1^1;
sbit P12 = P1^2;
sbit P13 = P1^3;
sbit P14 = P1^4;
sbit P15 = P1^5;
sbit P16 = P1^6;
sbit P17 = P1^7;
sbit P20 = P2^0;
sbit P21 = P2^1;
sbit P22 = P2^2;
sbit P23 = P2^3;
sbit P24 = P2^4;
sbit P25 = P2^5;
sbit P26 = P2^6;
sbit P27 = P2^7;
sbit P30 = P3^0;
sbit P31 = P3^1;
sbit P32 = P3^2;
sbit P33 = P3^3;
sbit P34 = P3^4;
sbit P35 = P3^5;
sbit P36 = P3^6;
sbit P37 = P3^7;
sbit P40 = P4^0;
sbit P41 = P4^1;
sbit P42 = P4^2;
sbit P43 = P4^3;
sbit P44 = P4^4;
sbit P45 = P4^5;
sbit P46 = P4^6;
sbit P47 = P4^7;
sbit P50 = P5^0;
sbit P51 = P5^1;
sbit P52 = P5^2;
sbit P53 = P5^3;
sbit P54 = P5^4;
sbit P55 = P5^5;
sbit P56 = P5^6;
sbit P57 = P5^7;



sbit    P_HC595_SER   = P4^0;   //pin 14    SER     data input
sbit    P_HC595_RCLK  = P5^4;   //pin 12    RCLk    store (latch) clock
sbit    P_HC595_SRCLK = P4^3;   //pin 11    SRCLK   Shift data clock

sbit    LCD_RS = P2^5;  //定义引脚
sbit    LCD_RW = P2^6;
sbit    LCD_E  = P2^7;
sbit    PSB    = P2^4;      //PSB脚为12864-12系列的串、并通讯功能切换，我们使用8位并行接口，PSB=1
sbit    LCD_RESET   =   P2^3;   //  17---RESET  L-->Enable
#define LCD_Data P0



#define Busy    0x80 //用于检测LCD状态字中的Busy标识
void    delay_ms(u16 ms);
void    DisableHC595(void);
void    WriteDataLCD(u8 WDLCD);
void    WriteCommandLCD(u8 WCLCD,BuysC);
u8      ReadDataLCD(void);
u8      ReadStatusLCD(void);
void    LCDInit(void);
void    LCDClear(void);
void    LCDFlash(void);
void    DisplayOneChar(u8 X, u8 Y, u8 DData);
void    DisplayListChar(u8 X, u8 Y, u8 code *DData);
void 		DisplayListNum(u8 X, u8 Y, u8 DData);
void    DisplayImage (u8 code *DData);



    //128*64点阵图形数据







//========================================================================
// 函数: void  delay_ms(u8 ms)
// 描述: 延时函数。
// 参数: ms,要延时的ms数, 这里只支持1~255ms. 自动适应主时钟.
// 返回: none.
// 版本: VER1.0
// 日期: 2013-4-1
// 备注: 
//========================================================================
void  delay_ms(u16 ms)
{
     u16 i;
     do{
          i = MAIN_Fosc / 13000;
          while(--i)    ;   //14T per loop
     }while(--ms);
}

void DisableHC595(void)
{       
    u8  i;
    P_HC595_SER   = 1;
    for(i=0; i<20; i++)
    {
        P_HC595_SRCLK = 1;
        P_HC595_SRCLK = 0;
    }
    P_HC595_RCLK = 1;
    P_HC595_RCLK = 0;                           //锁存输出数据
    P_HC595_RCLK = 1;
    P_HC595_RCLK = 0;                           //锁存输出数据
}


//******************************************
void    LCD_delay(void)
{
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
}


//写数据
void WriteDataLCD(u8 WDLCD)
{
    ReadStatusLCD(); //检测忙 
    LCD_RS = 1;
    LCD_RW = 0;
    LCD_Data = WDLCD;
        LCD_delay();
    LCD_E = 1;
    LCD_delay();
    LCD_E = 0;
}

//写指令
void WriteCommandLCD(u8 WCLCD,BuysC) //BuysC为0时忽略忙检测
{
    if (BuysC) ReadStatusLCD(); //根据需要检测忙 
    LCD_RS = 0;
    LCD_RW = 0; 
    LCD_Data = WCLCD;
        LCD_delay();
    LCD_E = 1; 
    LCD_delay();
    LCD_E = 0;  
}

//读状态
u8 ReadStatusLCD(void)
{
    LCD_Data = 0xFF; 
    LCD_RS = 0;
    LCD_RW = 1; 
        LCD_delay();
    LCD_E = 1;
        LCD_delay();
    while (LCD_Data & Busy); //检测忙信号
    LCD_E = 0;
    return(LCD_Data);
}

void LCDInit(void) //LCM初始化
{
    PSB = 1;    //并口
//  PSB = 0;    //SPI口
    delay_ms(10);
    LCD_RESET = 0;
    delay_ms(10);
    LCD_RESET = 1;
    delay_ms(100);
    
    WriteCommandLCD(0x30,1); //显示模式设置,开始要求每次检测忙信号
    WriteCommandLCD(0x01,1); //显示清屏
    WriteCommandLCD(0x06,1); // 显示光标移动设置
    WriteCommandLCD(0x0C,1); // 显示开及光标设置
}

void LCDClear(void) //清屏
{
    WriteCommandLCD(0x01,1); //显示清屏
    WriteCommandLCD(0x34,1); // 显示光标移动设置
    WriteCommandLCD(0x30,1); // 显示开及光标设置
}


//按指定位置显示一串字符
void DisplayListChar(u8 X, u8 Y, u8 code *DData)
{
    u8 ListLength,X2;
    ListLength = 0;
    X2 = X;
    if(Y < 1)   Y=1;
    if(Y > 4)   Y=4;
    X &= 0x0F; //限制X不能大于16，Y在1-4之内
    switch(Y)
    {
        case 1: X2 |= 0X80; break;  //根据行数来选择相应地址
        case 2: X2 |= 0X90; break;
        case 3: X2 |= 0X88; break;
        case 4: X2 |= 0X98; break;
    }
    WriteCommandLCD(X2, 1); //发送地址码
    while (DData[ListLength] >= 0x20) //若到达字串尾则退出
    {
        if (X <= 0x0F) //X坐标应小于0xF
        {
            WriteDataLCD(DData[ListLength]); //
            ListLength++;
            X++;
        }
    }
}
void DisplayListNum(u8 X, u8 Y, u8 DData)
{
	  u8 ListLength,X2;
    ListLength = 0;
    X2 = X;
    if(Y < 1)   Y=1;
    if(Y > 4)   Y=4;
    X &= 0x0F; //限制X不能大于16，Y在1-4之内
    switch(Y)
    {
        case 1: X2 |= 0X80; break;  //根据行数来选择相应地址
        case 2: X2 |= 0X90; break;
        case 3: X2 |= 0X88; break;
        case 4: X2 |= 0X98; break;
    }
    WriteCommandLCD(X2, 1); //发送地址码
    WriteDataLCD(0x30+DData); //
            

}
//图形显示122*32
void DisplayImage (u8 code *DData)
{
    u8 x,y,i;
    unsigned int tmp=0;
    for(i=0;i<9;)       //分两屏，上半屏和下半屏，因为起始地址不同，需要分开
    {
        for(x=0;x<32;x++)   //32行
        {
            WriteCommandLCD(0x34,1);
            WriteCommandLCD((0x80+x),1);//列地址
            WriteCommandLCD((0x80+i),1);    //行地址，下半屏，即第三行地址0X88
            WriteCommandLCD(0x30,1);        
            for(y=0;y<16;y++)   
                WriteDataLCD(DData[tmp+y]);//读取数据写入LCD
            tmp+=16;        
        }
        i+=8;
    }
    WriteCommandLCD(0x36,1);    //扩充功能设定
    WriteCommandLCD(0x30,1);
}

void DisplayClear (void)
{
    u8 x,y,i;
    for(i=0;i<9;)       //分两屏，上半屏和下半屏，因为起始地址不同，需要分开
    {
        for(x=0;x<32;x++)   //32行
        {
            WriteCommandLCD(0x34,1);
            WriteCommandLCD((0x80+x),1);//列地址
            WriteCommandLCD((0x80+i),1);    //行地址，下半屏，即第三行地址0X88
            WriteCommandLCD(0x30,1);        
            for(y=0;y<16;y++)   
                WriteDataLCD(0x00);//读取数据写入LCD      
        }
        i+=8;
    }
    WriteCommandLCD(0x36,1);    //扩充功能设定
    WriteCommandLCD(0x30,1);
}

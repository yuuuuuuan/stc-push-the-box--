#ifndef __SERIAL2_H__
#define __SERIAL2_H__
extern u8 dsplybuf[];    //中断处理函数中用到的外部变量，显示缓冲区的字符
void Serial2_INI(void); //串口初始化程序：baud=9600@11.0592MHZ，T2完成：方式0，1T模式

#endif
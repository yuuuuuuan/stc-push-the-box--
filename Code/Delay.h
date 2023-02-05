#ifndef __DELAY_H__
#define __DELAY_H__

#define MAIN_Fosc 11059200              //根据系统时钟频率修改

extern void DelayNms(unsigned int Nms);//延时子程序声明
extern void DelayNds(unsigned char N);             //延时Nx0.1秒 N=1~255 	//@12.000MHz 示波器测试验证比较精确

#endif
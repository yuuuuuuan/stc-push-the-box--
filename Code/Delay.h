#ifndef __DELAY_H__
#define __DELAY_H__

#define MAIN_Fosc 11059200              //����ϵͳʱ��Ƶ���޸�

extern void DelayNms(unsigned int Nms);//��ʱ�ӳ�������
extern void DelayNds(unsigned char N);             //��ʱNx0.1�� N=1~255 	//@12.000MHz ʾ����������֤�ȽϾ�ȷ

#endif
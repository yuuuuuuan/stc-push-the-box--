#ifndef __LCD12864_H__
#define __LCD12864_H__

extern void    delay_ms(u16 ms);
extern void    DisableHC595(void);
extern void    WriteDataLCD(u8 WDLCD);
extern void    WriteCommandLCD(u8 WCLCD,BuysC);
extern u8      ReadDataLCD(void);
extern u8      ReadStatusLCD(void);
extern void    LCDInit(void);
extern void    LCDClear(void);
extern void    LCDFlash(void);
extern void    DisplayOneChar(u8 X, u8 Y, u8 DData);
extern void    DisplayListChar(u8 X, u8 Y, u8 code *DData);
extern void		 DisplayListNum(u8 X, u8 Y, u8 DData);
extern void    DisplayImage (u8 code *DData);
extern void		 DisplayClear (void);
#endif
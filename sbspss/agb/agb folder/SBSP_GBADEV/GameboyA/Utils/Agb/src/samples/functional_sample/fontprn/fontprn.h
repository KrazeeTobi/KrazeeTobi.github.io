//======================================================
//    fontprn.h                                         
//    Routine to output string to console (header)
//                                                      
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.         
//======================================================

#ifndef _AGB_TYPES_H
#include <AgbTypes.h>
#endif	// _AGB_TYPES_H

#ifndef	_FONTPRN_H_
#define	_FONTPRN_H_

void FontPrintInit(u8 x,u8 y,u8 col,u8 row,u32 vram,u8 pltno);
void FontPalletLoad(u8 pltno);
void FontColor(u8 color);
void FontPrint(u8 x,u8 y,u8 *str);
void FontPrintC(u8 x,u8 y,u8 color,u8 *str);
void FontPrintCls(void);
void FontPrintSync(void);

void NumPrint(u8 x,u8 y,s16 val,s16 dig);
#define	_NumPrint(x,y,val,dig)	{char __buf[8];fp_itoa(val,__buf,dig);FontPrint(x,y,__buf);}

void NumPrintC(u8 x,u8 y,u8 color,s16 val,s16 dig);

char *fp_itoa(int val,char *s,int digit);

#endif	// _FONTPRN_H_
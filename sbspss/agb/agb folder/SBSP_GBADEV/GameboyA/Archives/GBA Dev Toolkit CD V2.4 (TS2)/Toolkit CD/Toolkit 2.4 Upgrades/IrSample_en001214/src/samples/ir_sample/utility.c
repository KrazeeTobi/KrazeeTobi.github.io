/********************************************************************/
/*          utility.c                                               */
/*             Utility                                              */
/*                                                                  */
/*          Copyright (C) 1999-2000 NINTENDO Co.,Ltd.               */
/********************************************************************/
#include "utility.h"


const u8 hexdata[16] = {
	'0', '1', '2', '3', '4', '5', '6', '7',
	'8', '9', 'A', 'B', 'C', 'D', 'E', 'F',
};


void DispCharSet8( OamData* Oam, vu8* target)
{
	vu8 work;

	work = *target >> 4;
	Oam->CharNo = hexdata[work];
	work = *target & 0x0F;
	(Oam+1)->CharNo = hexdata[work];
}

void CharSet8BG( vu8* BGScr, vu8* target)
{
	vu8 work;
	
	work = *target >> 4;					// Lower 4bit
	*(vu16 *)BGScr &= (vu16)0xFC00;				// Complement of 0x3FF
	*(vu16 *)BGScr |= (vu16)hexdata[work];
	work = *target & 0x0F;					// Upper 4bit
	*(vu16 *)(BGScr+2) &= (vu16)0xFC00;
	*(vu16 *)(BGScr+2) |= (vu16)hexdata[work];
}




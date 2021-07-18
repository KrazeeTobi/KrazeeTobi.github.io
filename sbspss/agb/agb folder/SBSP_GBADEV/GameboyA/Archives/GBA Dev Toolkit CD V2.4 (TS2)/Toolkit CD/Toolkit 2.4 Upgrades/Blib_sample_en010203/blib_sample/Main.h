/********************************************************************/
/*      Main.h                                                      */
/*          Library Header Include and                              */
/*         Global Symbol External Declaration                       */
/*                                                                  */
/*              Copyright (C) 1999-2001 NINTENDO Co.,Ltd.           */
/********************************************************************/
#ifndef	__MAIN_H__
#define	__MAIN_H__

#define	__SRAM_FAST_SELECT    // When using AgbSramFast.h, make this definition
				// effective, When using AgbSram.h
							// make ineffective.

#ifdef	__SRAM_FAST_SELECT
#include <AgbSramFast.h>
#else
#include <AgbSram.h>
#endif
#include <AgbFlash.h>
#include <AgbEeprom.h>

#define	COMMON_BUFFER		0x02010000


extern void (*IntrTable[14])();
extern void (*ActiveProcess)();
extern void ReturnMain();

#endif	/* __MAIN_H__ */

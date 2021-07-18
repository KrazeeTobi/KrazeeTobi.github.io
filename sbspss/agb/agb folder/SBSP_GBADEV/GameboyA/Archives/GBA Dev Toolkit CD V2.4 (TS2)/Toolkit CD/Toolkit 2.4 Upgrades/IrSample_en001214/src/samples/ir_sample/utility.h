/********************************************************************/
/*          utility.h                                               */
/*            Utility External Declaration                          */
/*                                                                  */
/*          Copyright (C) 1999-2000 NINTENDO Co.,Ltd.               */
/********************************************************************/
#ifndef __UTILITY_H_
#define __UTILITY_H_


#include <AgbTypes.h>

/*------------------------------------------------------*/
/*Dump and display momory area of arbitrary length to OBJ*/
/*------------------------------------------------------*/
#define DispCharSet( length, Oam, target)				\
{														\
	u8 i;												\
	u32 tmp;											\
	u8	current;										\
														\
	tmp = *target;										\
														\
	for( i=0; i<##length##/8; i++) {					\
		current = tmp & 0xff;							\
		DispCharSet8( (OamData*)Oam+(i*2), &current);	\
		tmp >>= 8;										\
	}													\
}
/*------------------------------------------------------*/
void DispCharSet8( OamData*, vu8*);




/*------------------------------------------------------*/
/*Dump and display momory area of arbitrary length to BG*/
/*------------------------------------------------------*/
#define DispCharSetBG( length, BGScr, target)			\
{														\
	u8 i;												\
	u32 tmp;											\
	u8	current;										\
														\
	tmp = *target;										\
														\
	for( i=0; i<##length##/8; i++) {					\
		current = tmp & 0xff;							\
		CharSet8BG( (vu8 *)(BGScr+((##length##/8-1)*4)-(i*4)), &current);	\
		tmp >>= 8;										\
	}													\
}
/*------------------------------------------------------*/
void CharSet8BG( vu8* BGScr, vu8* target);



#endif	/*__UTILITY_H_*/

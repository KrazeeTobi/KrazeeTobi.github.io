//======================================================
//    share.h                                           
//    Utilities
//                                                      
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.         
//======================================================

#ifndef	__SHARE__
#define	__SHARE__

#include <agb.h>

#undef	NULL
#define	NULL	((void *)0)

//-------------------- Initialization functions  ----------------------
void ClearRamAll( void );
void ClearWorkRam( void );
void ClearGraphicRam( void );
void ClearVram( void );
void ClearOamRam( void );
void ClearPaletteRam( void );
//-------------------- Fixed decimal point ----------------------
extern const short sin_cos_table[256+64];

#define	_Sin( a ) (sin_cos_table[(a)])
#define	_Cos( a ) (sin_cos_table[(a)+64])
s16 fix_mul( s16 a , s16 b );
s16 fix_div( s16 a , s16 b );
s16 fix_inverse( s16 b );
//------------------ Interrupt-related ----------------------
typedef void (*IntrFuncp)(void);

void InitVBlank( void );
void SetVBlankFunc( IntrFuncp fnc );
void V_Intr_Clear(void);
void V_Intr_Set(void);
void V_Wait(void);
//----------------- Controller process  -------------------
void KeyInit(void);
void KeyRead(void);
extern u16 Cont;
extern u16 Trg;

#endif	//  __SHARE__

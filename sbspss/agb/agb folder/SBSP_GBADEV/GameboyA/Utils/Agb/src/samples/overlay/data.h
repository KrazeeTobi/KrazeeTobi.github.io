/********************************************************************/
/*          data.h                                                  */
/*            Data External Declaration                             */
/*                                                                  */
/*          Copyright (C) 1999-2000 NINTENDO Co.,Ltd.               */
/********************************************************************/
#ifndef _DATA_H
#define _DATA_H

#include <Agb.h>
#include "types.h"


/*-------------------- Global Varialbles ----------------------------*/

extern u8           SceneNo;                    // Scene number

extern vu16         IntrCheck;                  // Check interrupt

extern u16          Cont, Trg;                  // Key input

extern IntrFuncp    IntrTableBuf[15];           // Interrupt table
extern u32          IntrMainBuf[0x200];         // Buffer for interrupt main routine

extern u16          BgBak[32*32];               // BG backup
extern OamData      OamBak[128];                // OAM backup


/*-------------------------- Data -------------------------------*/

extern LinkData LinkData_Title[2];

extern u32 CharData_Sample[8*0xe0];

extern u16 PlttData_Sample[16][16];

extern u16 BgScData_Title[32*20];
extern u16 BgScData_ObjMove[32*20];
extern u16 BgScData_BgMove0[32*20];
extern u16 BgScData_BgMove1[32*20];
extern u16 BgScData_BgMove2[32*20];
extern u16 BgScData_BgMove3[32*20];

extern u32 OamData_Sample[1][2];

#endif /* _DATA_H */

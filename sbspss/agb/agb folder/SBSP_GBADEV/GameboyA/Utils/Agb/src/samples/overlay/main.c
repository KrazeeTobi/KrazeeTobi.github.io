/********************************************************************/
/*          main.c                                                  */
/*            Main of overlay (Overlay Sample)                      */
/*                                                                  */
/*          Copyright (C) 1999-2000 NINTENDO Co.,Ltd.               */
/********************************************************************/
//#define CODE32
#include "overlay.h"


/*-------------------- Global Variables ----------------------------*/

    u8          SceneNo;                    // Scene number

    u16         Cont, Trg;                  // Key input

    IntrFuncp   IntrTableBuf[15];           // Interrupt table
    u32         IntrMainBuf[0x200];         // Buffer for interrupt main routine


    s32         DataSecDummy[4]={1,2,3,4};  // Data section sample data


/*==================================================================*/
/*                      Main Routine                                */
/*==================================================================*/
extern u8 __load_start_data[], __load_stop_data[];
extern void intr_main(void);

void AgbMain(void)
{
    u8    i;

    DmaClear(3, 0, EX_WRAM,  EX_WRAM_SIZE,           32);  // Clear CPU external work RAM
    DmaClear(3, 0, CPU_WRAM, CPU_WRAM_SIZE - 0x200,  32);  // Clear CPU internal work RAM
//  DmaClear(3, 0, VRAM,     VRAM_SIZE,              32);  //     VRAM clear
//  DmaClear(3, 0, OAM,      OAM_SIZE,               32);  //      OAM clear
//  DmaClear(3, 0, PLTT,     PLTT_SIZE,              32);  //  Palette clear

    DmaCopy(3, __load_start_data, EX_WRAM, 
               __load_stop_data - __load_start_data, 32);  // Initialize data section

    DmaCopy(3, intr_main, IntrMainBuf, sizeof(IntrMainBuf), 32);// Set interrupt main routine
    *(vu32 *)INTR_VECTOR_BUF = (vu32 )IntrMainBuf;

    DmaArrayCopy(3, CharData_Sample, BG_VRAM+0x8000, 32);  // Set BG character
    DmaArrayCopy(3, CharData_Sample, OBJ_MODE0_VRAM, 32);  // Set OBJ character
    DmaArrayCopy(3, PlttData_Sample, BG_PLTT,        32);  // Set BG palette
    DmaArrayCopy(3, PlttData_Sample, OBJ_PLTT,       32);  // Set OBJ palette

    *(vu16 *)REG_IME   = 1;                             // Set IME
    *(vu16 *)REG_STAT  = STAT_V_BLANK_IF_ENABLE;        // Permit V Blank interrupt

    *(vu16 *)REG_BG0CNT =                               // Set BG control
            BG_COLOR_16 | BG_SCREEN_SIZE_0 | BG_PRIORITY_0
            | 0 << BG_SCREEN_BASE_SHIFT | 2 << BG_CHAR_BASE_SHIFT ;
    *(vu16 *)REG_BG1CNT =
            BG_COLOR_16 | BG_SCREEN_SIZE_0 | BG_PRIORITY_0
            | 1 << BG_SCREEN_BASE_SHIFT | 2 << BG_CHAR_BASE_SHIFT ;
    *(vu16 *)REG_BG2CNT =
            BG_COLOR_16 | BG_SCREEN_SIZE_0 | BG_PRIORITY_0
            | 2 << BG_SCREEN_BASE_SHIFT | 2 << BG_CHAR_BASE_SHIFT ;
    *(vu16 *)REG_BG3CNT =
            BG_COLOR_16 | BG_SCREEN_SIZE_0 | BG_PRIORITY_0
            | 3 << BG_SCREEN_BASE_SHIFT | 2 << BG_CHAR_BASE_SHIFT ;

    KeyRead();
    while(1) {
        switch (SceneNo) {
            case 0: SceneNo = Title();      break;      // Title
            case 1: SceneNo = ObjMove();    break;      // Move OBJ
            case 2: SceneNo = BgMove();     break;      // Move BG
        }
    }
}



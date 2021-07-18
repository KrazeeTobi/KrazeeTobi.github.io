/********************************************************************/
/*          title.c                                                 */
/*            Title                                                 */
/*                                                                  */
/*          Copyright (C) 1999-2000 NINTENDO Co.,Ltd.               */
/********************************************************************/
//#define CODE32
#include "overlay.h"


/*------------------------------------------------------------------*/
/*                      Interrupt Table                             */
/*------------------------------------------------------------------*/
void TitleVBlankIntr(void);

const IntrFuncp TitleIntrTable[14] = {
    TitleVBlankIntr,    // V Blank interrupt
    IntrDummy,          // H Blank interrupt
    IntrDummy,          // V Counter interrupt
    IntrDummy,          // Timer 0 interrupt
    IntrDummy,          // Timer 1 interrupt
    IntrDummy,          // Timer 2 interrupt
    IntrDummy,          // Timer 3 interrupt
    IntrDummy,          // Serial communication interrupt
    IntrDummy,          // DMA 0 interrupt
    IntrDummy,          // DMA 1 interrupt
    IntrDummy,          // DMA 2 interrupt
    IntrDummy,          // DMA 2 interrupt
    IntrDummy,          // Key interrupt
    IntrDummy,          // Cassette interrupt
};


/*==================================================================*/
/*                      Title                                       */
/*==================================================================*/
u16           TitleBgBak[32*32];           // BG backup
OamData       TitleOamBak[128];            // OAM bakcup
u8            Cursolp;

u8 Title(void)
{
    DmaArrayCopy( 3, TitleIntrTable,  IntrTableBuf, 32);// Set interrupt table

    DmaArrayCopy( 3, BgScData_Title,  TitleBgBak,   32);// Set BG screen
    DmaArrayCopy( 3, TitleBgBak,      BG_VRAM,      32);
    DmaArrayClear(3, 0,               TitleOamBak,  32);// Clear OAM
    DmaArrayCopy( 3, OamData_Sample,  TitleOamBak,  32);// Set OAM
    DmaArrayCopy( 3, TitleOamBak,     OAM,          32);

    *(vu16 *)REG_IE = V_BLANK_INTR_FLAG;                // Permit V Blank interrupt

    *(vu16 *)REG_DISPCNT = DISP_MODE_0 | DISP_OBJ_ON | DISP_BG0_ON; // LCDC ON

    Cursolp = 0;
    while(1) {
        KeyRead();                                      // Key control
        if (Trg & (A_BUTTON | START_BUTTON)) {
            *(vu16 *)REG_IE ^= V_BLANK_INTR_FLAG;       // V Blank interrupt not permitted
            ((vl DispCnt *)REG_DISPCNT)->Lcdc_Off = 1;  // LCDC OFF
            return Cursolp + 1;
        }
        ObjCursolMove(TitleOamBak, LinkData_Title, &Cursolp);// Move cursor

        VBlankIntrWait();                               // Wait for V Blank
    }
}

/*==================================================================*/
/*                      Interrupt Routien                           */
/*==================================================================*/

/*------------------------------------------------------------------*/
/*                      V Blank Process                             */
/*------------------------------------------------------------------*/

void TitleVBlankIntr(void)
{
    DmaArrayCopy(3, TitleBgBak,  BG_VRAM, 16);      // Set BG screen
    DmaArrayCopy(3, TitleOamBak, OAM,     32);      // Set OAM
}


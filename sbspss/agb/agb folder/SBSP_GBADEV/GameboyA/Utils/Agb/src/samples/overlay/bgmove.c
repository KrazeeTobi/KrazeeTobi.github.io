/********************************************************************/
/*          bgmove.c                                                */
/*            BG Move Scene                                         */
/*                                                                  */
/*          Copyright (C) 1999-2000 NINTENDO Co.,Ltd.               */
/********************************************************************/
//#define CODE32
#include "overlay.h"


/*------------------------------------------------------------------*/
/*                      Interrupt Table                             */
/*------------------------------------------------------------------*/
void BgMoveVBlankIntr(void);

const IntrFuncp BgMoveIntrTable[14] = {
    BgMoveVBlankIntr,   // V Blank interrupt
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
    IntrDummy,          // DMA 3 interrupt
    IntrDummy,          // Key interrupt
    IntrDummy,          // Cassette interrupt
};


/*==================================================================*/
/*                      Move BG                                     */
/*==================================================================*/
void BgSnakeMove(void);
BgOffsetCnt        BgMoveOffsetBak[4];           // OAM backup
u16                BgMoveBgBak[4][32*32];        // BG backup

u8 BgMove(void)
{
    int        i;

    DmaArrayCopy(3, BgMoveIntrTable,  IntrTableBuf,    32);// Set interrupt table

    DmaArrayClear(3,0,                BgMoveBgBak,     32);// Clear BG screen
    DmaArrayCopy(3, BgScData_BgMove0, BgMoveBgBak[0],  32);// Set BG screen
    DmaArrayCopy(3, BgScData_BgMove1, BgMoveBgBak[1],  32);
    DmaArrayCopy(3, BgScData_BgMove2, BgMoveBgBak[2],  32);
    DmaArrayCopy(3, BgScData_BgMove3, BgMoveBgBak[3],  32);
    DmaArrayCopy(3, BgMoveBgBak[0],   BG_VRAM+0x800*0, 32);
    DmaArrayCopy(3, BgMoveBgBak[1],   BG_VRAM+0x800*1, 32);
    DmaArrayCopy(3, BgMoveBgBak[2],   BG_VRAM+0x800*2, 32);
    DmaArrayCopy(3, BgMoveBgBak[3],   BG_VRAM+0x800*3, 32);
    for (i=0; i<4; i++) {                               // Initialize BG scroll
        BgMoveOffsetBak[i].V = i<<2;
        BgMoveOffsetBak[i].H = i<<2;
    }
    DmaArrayCopy(3, BgMoveOffsetBak,  REG_BGOFS,       32);

    *(vu16 *)REG_IE = V_BLANK_INTR_FLAG;                // Permit V Blank interrupt

    *(vu16 *)REG_DISPCNT = DISP_MODE_0 | DISP_BG_ALL_ON;// LCDC ON

    while(1) {
        KeyRead();                                      // Control key
        if (Trg & SELECT_BUTTON) {                      // Return to title
            *(vu16 *)REG_IE ^= V_BLANK_INTR_FLAG;       // V Blank interrupt not permitted
            ((vl DispCnt *)REG_DISPCNT)->Lcdc_Off = 1;  // LCDC OFF
            DmaClear(3, 0, REG_BGOFS, 2*2*4, 32);       // Clear BG scroll
            return 0;
        }
        if (Cont & PLUS_KEY_MASK)    BgSnakeMove();     // Move BG

        VBlankIntrWait();                               // Waiting for V Blank 
    }
}


/*==================================================================*/
/*                      Interrupt Routine                           */
/*==================================================================*/

/*------------------------------------------------------------------*/
/*                      V Blank Process                             */
/*------------------------------------------------------------------*/

void BgMoveVBlankIntr(void)
{
    DmaArrayCopy(3, BgMoveOffsetBak, REG_BGOFS, 32);// Set BG screen
}


/*==================================================================*/
/*                      Subroutine                                  */
/*==================================================================*/

/*------------------------------------------------------------------*/
/*                      BG Move Routine                             */
/*------------------------------------------------------------------*/

void BgSnakeMove(void)
{
    u32        i;
    
    for (i=3; i>0; i--) {
        BgMoveOffsetBak[i].V = BgMoveOffsetBak[i-1].V;
        BgMoveOffsetBak[i].H = BgMoveOffsetBak[i-1].H;
    }
    if (Cont & U_KEY)    BgMoveOffsetBak[0].V += 4;
    if (Cont & D_KEY)    BgMoveOffsetBak[0].V -= 4;
    if (Cont & L_KEY)    BgMoveOffsetBak[0].H += 4;
    if (Cont & R_KEY)    BgMoveOffsetBak[0].H -= 4;

}



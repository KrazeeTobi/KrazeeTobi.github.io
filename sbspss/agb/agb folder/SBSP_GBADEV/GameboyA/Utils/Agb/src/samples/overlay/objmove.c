/********************************************************************/
/*          objmove.c                                               */
/*            OBJ Move Scene                                        */
/*                                                                  */
/*          Copyright (C) 1999-2000 NINTENDO Co.,Ltd.               */
/********************************************************************/
//#define CODE32
#include "overlay.h"


/*------------------------------------------------------------------*/
/*                      Interrupt Table                             */
/*------------------------------------------------------------------*/
void ObjMoveVBlankIntr(void);

const IntrFuncp ObjMoveIntrTable[14] = {
    ObjMoveVBlankIntr,  // V Blank interrupt
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
/*                      Move OBJ                                    */
/*==================================================================*/
void ObjSnakeMove(void);
OamData        ObjMoveOamBak[128];         // OAM backup
u16            ObjMoveBgBak[32*32];        // BG backup

u8 ObjMove(void)
{
    int        i;

    DmaArrayCopy( 3, ObjMoveIntrTable, IntrTableBuf, 32);// Set interrupt table

    DmaArrayCopy( 3, BgScData_ObjMove, ObjMoveBgBak, 32);// Set BG screen
    DmaArrayCopy( 3, ObjMoveBgBak,     BG_VRAM,      32);
    DmaArrayClear(3, 0,                ObjMoveOamBak,32);// Clear OAM
    DmaArrayCopy( 3, OamData_Sample,   ObjMoveOamBak,32);// Set OAM
    for (i=0; i<94; i++) {                               // Initialize OAM
        ObjMoveOamBak[i] = *(OamData *)OamData_Sample;
        ObjMoveOamBak[i].CharNo = '@' + DivRem(i, 64);
        ObjMoveOamBak[i].VPos += i<<2;
        ObjMoveOamBak[i].HPos += i<<2;
    }
    DmaArrayCopy( 3, ObjMoveOamBak,    OAM,          32);

    *(vu16 *)REG_IE = V_BLANK_INTR_FLAG;                 // Permit V Blank interrupt

    *(vu16 *)REG_DISPCNT = DISP_MODE_0 | DISP_OBJ_ON | DISP_BG0_ON; // LCDC ON

    while(1) {
        KeyRead();                                       // Control key
        if (Trg & SELECT_BUTTON) {                       // Return to title
            *(vu16 *)REG_IE ^= V_BLANK_INTR_FLAG;        // V Blank interrupt not permitted
            ((vl DispCnt *)REG_DISPCNT)->Lcdc_Off = 1;   // LCDC OFF
            return 0;
        }
        if (Trg & A_BUTTON)                              // Change character
            for (i=0; i<128; i++)    ObjMoveOamBak[i].CharNo++;
        if (Trg & B_BUTTON)
            for (i=0; i<128; i++)    ObjMoveOamBak[i].CharNo--;
        if (Cont & PLUS_KEY_MASK)                        // Move OBJ
            ObjSnakeMove();    

        VBlankIntrWait();                                // Wait for V Blank interrupt to complete
    }
}


/*==================================================================*/
/*                      Interrupt Routine                           */
/*==================================================================*/

/*------------------------------------------------------------------*/
/*                      V Blank Process                             */
/*------------------------------------------------------------------*/

void ObjMoveVBlankIntr(void)
{
    DmaArrayCopy(3, ObjMoveOamBak, OAM,     32);    // Set OAM
}


/*==================================================================*/
/*                      Subroutine                                  */
/*==================================================================*/

/*------------------------------------------------------------------*/
/*                      OBJ Move Routine                            */
/*------------------------------------------------------------------*/

void ObjSnakeMove(void)
{
    u32        i;
    
    for (i=127; i>0; i--) {
        ObjMoveOamBak[i].VPos = ObjMoveOamBak[i-1].VPos;
        ObjMoveOamBak[i].HPos = ObjMoveOamBak[i-1].HPos;
    }
    if (Cont & U_KEY)   ObjMoveOamBak[0].VPos -= 4;
    if (Cont & D_KEY)   ObjMoveOamBak[0].VPos += 4;
    if (Cont & L_KEY)   ObjMoveOamBak[0].HPos -= 4;
    if (Cont & R_KEY)   ObjMoveOamBak[0].HPos += 4;
}


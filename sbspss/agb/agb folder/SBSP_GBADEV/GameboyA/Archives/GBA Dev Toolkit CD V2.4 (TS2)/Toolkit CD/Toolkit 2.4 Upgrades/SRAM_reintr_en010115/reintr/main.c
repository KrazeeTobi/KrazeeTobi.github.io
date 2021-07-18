/********************************************************************/
/*          main.c                                                  */
/*            Source for reintr (Multiple Interrupt Sample)         */
/*                                                                  */
/*          Copyright (C) 1999-2001 Nintendo of America Inc.        */
/********************************************************************/
//#define CODE32
#include <Agb.h>
#include "data.h"


/*-------------------- Global Variables  ----------------------------*/

    u16      Cont, Trg;                  // Key input

    u32      IntrMainBuf[0x200];         // Buffer for interrupt main routine

    u16      BgBak[32*32];               // BG  backup
    OamData  OamBak[128];                // OAM  backup


/*---------------------- Subroutine -----------------------------*/

void KeyRead(void);
void ObjSnakeMove(void);


/*------------------------------------------------------------------*/
/*                      Interrupt Table                             */
/*------------------------------------------------------------------*/
typedef void (*IntrFuncp)(void);
void IntrDummy(void);
void VBlankIntr(void);

const IntrFuncp IntrTable[13] = {
    KeyRead,        // Timer 0 interrupt
    VBlankIntr,     // V Blank interrupt

    IntrDummy,      // H Blank interrupt
    IntrDummy,      // V Counter interrupt
    IntrDummy,      // Timer 1 interrupt
    IntrDummy,      // Timer 2 interrupt
    IntrDummy,      // Timer 3 interrupt
    IntrDummy,      // Serial communication interrupt
    IntrDummy,      // DMA 0 interrupt
    IntrDummy,      // DMA 1 interrupt
    IntrDummy,      // DMA 2 interrupt
    IntrDummy,      // DMA 3 interrupt
    IntrDummy,      // Key interrupt
};


/*==================================================================*/
/*                      Main Routine                                */
/*==================================================================*/
extern void intr_main(void);
#define DISP_OBJ_NUM    94

void AgbMain(void)
{
    u8    i;

    *(vu16 *)REG_WAITCNT = CST_ROM0_1ST_3WAIT | CST_ROM0_2ND_1WAIT
                         | CST_PREFETCH_ENABLE;            // 3-1 Set wait access

    DmaClear(3, 0,   EX_WRAM,  EX_WRAM_SIZE,         32);  // Clear external CPU work RAM
    DmaClear(3, 0,   CPU_WRAM, CPU_WRAM_SIZE - 0x200,32);  // Clear internal CPU work RAM
//  DmaClear(3, 0,   VRAM,     VRAM_SIZE,            32);  //     VRAM Clear
//  DmaClear(3, 160, OAM,      OAM_SIZE,             32);  //      OAM Clear
//  DmaClear(3, 0,   PLTT,     PLTT_SIZE,            32);  // Palette Clear


    DmaCopy(3, intr_main, IntrMainBuf, sizeof(IntrMainBuf), 32);// Set interrupt main routine
    *(vu32 *)INTR_VECTOR_BUF = (vu32 )IntrMainBuf;

    DmaArrayCopy(3, CharData_Sample, BG_VRAM+0x8000, 32);  // Set BG character
    DmaArrayCopy(3, CharData_Sample, OBJ_MODE0_VRAM, 32);  // Set OBJ character
    DmaArrayCopy(3, PlttData_Sample, BG_PLTT,        32);  // Set BG palette 
    DmaArrayCopy(3, PlttData_Sample, OBJ_PLTT,       32);  // Set OBJ palette

    DmaArrayCopy(3, BgScData_Sample, BgBak,          32);  // Set BG screen
    DmaArrayCopy(3, BgBak,           BG_VRAM,        32);
    
    DmaArrayClear(3,160,             OamBak,         32);  // Move undisplayed OBJ to outside of the screen
    DmaArrayCopy(3, OamData_Sample,  OamBak,         32);  // Initialize OAM
    for (i=0; i<DISP_OBJ_NUM; i++) {


        OamBak[i] = *(OamData *)OamData_Sample;
        OamBak[i].CharNo = '@' + DivRem(i, 64);
        OamBak[i].VPos += i<<2;
        OamBak[i].HPos += i<<2;
    }
    DmaArrayCopy(3, OamBak,          OAM,            32);

    *(vu16 *)REG_BG0CNT =                             // Set BG control
            BG_COLOR_16 | BG_SCREEN_SIZE_0 | BG_PRIORITY_0
            | 0 << BG_SCREEN_BASE_SHIFT | 2 << BG_CHAR_BASE_SHIFT ;

    *(vu16 *)REG_IME   = 1;                           // Set IME
    *(vu16 *)REG_IE    = V_BLANK_INTR_FLAG            // Permit V blank interrupt
                       | TIMER0_INTR_FLAG             // Permit timer 0 interrupt
                       | CASSETTE_INTR_FLAG;          // Permit cassette interrupt

    *(vu16 *)REG_STAT  = STAT_V_BLANK_IF_ENABLE;

    *(vu16 *)REG_DISPCNT = DISP_MODE_0 | DISP_OBJ_ON | DISP_BG0_ON;// LCDC ON

    *(u32 *)REG_TM0CNT = (0x10000-0x100) | TMR_PRESCALER_1024CK    // Start timer 0
            | TMR_IF_ENABLE | TMR_ENABLE;

    while(1) {
//      KeyRead();                                  // Key control
        if (Trg & A_BUTTON)                         // Change character
            for (i=0; i<DISP_OBJ_NUM; i++)    OamBak[i].CharNo++;
        if (Trg & B_BUTTON)
            for (i=0; i<DISP_OBJ_NUM; i++)    OamBak[i].CharNo--;
        if (Cont & PLUS_KEY_MASK)                   // Move OBJ
            ObjSnakeMove();    

        VBlankIntrWait();                           // Wait to complete V Blank interrupt process
    }
}


/*==================================================================*/
/*                      Interrupt Routine                           */
/*==================================================================*/

/*------------------------------------------------------------------*/
/*                      V Blank Process                             */
/*------------------------------------------------------------------*/

void VBlankIntr(void)
{
    DmaArrayCopy(3, BgBak,  BG_VRAM, 32);           // Set BG screen
    DmaArrayCopy(3, OamBak, OAM,     32);           // Set OAM

    *(u16 *)INTR_CHECK_BUF = V_BLANK_INTR_FLAG;     // Set V Blank interrupt check
}

/*------------------------------------------------------------------*/
/*                      Read in Key                                 */
/*------------------------------------------------------------------*/

void KeyRead(void)
{
    u16 ReadData = (*(vu16 *)REG_KEYINPUT ^ 0xffff);
    Trg  = ReadData & (ReadData ^ Cont);            // trigger input
    Cont = ReadData;                                //   beta input
}

/*------------------------------------------------------------------*/
/*                      Interrupt Dummy Routine                     */
/*------------------------------------------------------------------*/

void IntrDummy(void)
{
}

/*==================================================================*/
/*                      Subroutine                                  */
/*==================================================================*/

/*------------------------------------------------------------------*/
/*                      Move OBJ Routine                            */
/*------------------------------------------------------------------*/

void ObjSnakeMove(void)
{
    u8   i;
    for (i=DISP_OBJ_NUM-1; i>0; i--) {
        OamBak[i].VPos = OamBak[i-1].VPos;
        OamBak[i].HPos = OamBak[i-1].HPos;
    }
    if (Cont & U_KEY)    OamBak[0].VPos -= 4;
    if (Cont & D_KEY)    OamBak[0].VPos += 4;
    if (Cont & L_KEY)    OamBak[0].HPos -= 4;
    if (Cont & R_KEY)    OamBak[0].HPos += 4;
}


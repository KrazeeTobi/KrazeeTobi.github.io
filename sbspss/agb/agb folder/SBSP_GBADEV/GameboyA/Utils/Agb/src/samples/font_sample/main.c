/********************************************************************/
/*          main.c                                                  */
/*            Source for font_sample (font sample)                  */
/*                                                                  */
/*          Copyright (C) 1999-2000 NINTENDO Co.,Ltd.               */
/********************************************************************/
//#define CODE32
#include "data.h"


/*-------------------- Global Variables ----------------------------*/

    u16      Cont, Trg;                  // Key input

    u32      IntrMainBuf[0x200];         // Buffer for interrupt main routine

    u16      BgBak[32*32];               // BG backup
    OamData  OamBak[128];                // OAM backup
    
/*---------------------- Subroutine -----------------------------*/

void KeyRead(void);
void FontSpread(u32,u32);
void FontDisplay(void);

/*------------------------------------------------------------------*/
/*                      Interrupt Table                             */
/*------------------------------------------------------------------*/
typedef void (*IntrFuncp)(void);
void IntrDummy(void);
void VBlankIntr(void);

const IntrFuncp IntrTable[14] = {
    VBlankIntr,     // V Blank interrupt
    IntrDummy,      // H Blank interrupt
    IntrDummy,      // V Counter interrupt
    IntrDummy,      // Timer 0 interrupt
    IntrDummy,      // Timer 1 interrupt
    IntrDummy,      // Timter 2 interrupt
    IntrDummy,      // Timter 3 interrupt
    IntrDummy,      // Serial communication interrupt
    IntrDummy,      // DMA 0 interrupt
    IntrDummy,      // DMA 1 interrupt
    IntrDummy,      // DMA 2 interrupt
    IntrDummy,      // DMA 3 interrupt
    IntrDummy,      // Key interrupt
    IntrDummy,      // Cassette interrupt
};


/*==================================================================*/
/*                      Main Routine                                */
/*==================================================================*/
extern void intr_main(void);

void AgbMain(void)
{
    u16    i;

    DmaClear(3, 0, EX_WRAM,  EX_WRAM_SIZE,          32);   // Clear CPU external work RAM
    DmaClear(3, 0, CPU_WRAM, CPU_WRAM_SIZE - 0x200, 32);   // Clear CPU internal work RAM
//  DmaClear(3, 0, VRAM, VRAM_SIZE,                 32);   // VRAM clear
//  DmaClear(3, 0, OAM,  OAM_SIZE,                  32);   // OAM clear
//  DmaClear(3, 0, PLTT, PLTT_SIZE,                 32);   // Palette clear

    DmaCopy(3, intr_main, IntrMainBuf, sizeof(IntrMainBuf), 16);// Set interrupt main routine
    *(vu32 *)INTR_VECTOR_BUF = (vu32 )IntrMainBuf;

    DmaArrayCopy(3, PlttData_Sample, BG_PLTT,        16);   // Set BG palette
    DmaArrayCopy(3, BgScData_Sample, BgBak,          16);   // Set BG screen
    DmaArrayCopy(3, BgBak,           BG_VRAM,        16);

    FontDisplay();
                                                        
    *(vu16 *)REG_BG0CNT =   BG_COLOR_16                 // Select 16 colors
                          | BG_SCREEN_SIZE_0            // Screen size (256x256)
                          | BG_PRIORITY_1               // BG First Priority
                          | 0 << BG_SCREEN_BASE_SHIFT   // screen base block 0
                          | 2 << BG_CHAR_BASE_SHIFT ;   // character base block2

    *(vu16 *)REG_IME    = 1;                            // Set IME
    *(vu16 *)REG_IE     = V_BLANK_INTR_FLAG;            // Permit V blank interrupt
    *(vu16 *)REG_STAT   = STAT_V_BLANK_IF_ENABLE;

    *(vu16 *)REG_DISPCNT =   DISP_MODE_0                // BG mode0 
                           | DISP_BG0_ON;               // BG0 valid

    while(1) {
        KeyRead();                                      // key operation
        if (Trg & BUTTON_MASK) FontDisplay();           // display font
        
        VBlankIntrWait();                               // wait V blank interrupt to complete
    }
}

/*==================================================================*/
/*                      Interrupt routine                           */
/*==================================================================*/

/*------------------------------------------------------------------*/
/*                      V blank process                             */
/*------------------------------------------------------------------*/

void VBlankIntr(void)
{
    DmaArrayCopy(3, BgBak,  BG_VRAM, 16);           // Set BG screen
    DmaArrayCopy(3, OamBak, OAM,     32);           // Set OAM

    *(u16 *)INTR_CHECK_BUF = V_BLANK_INTR_FLAG;     // Set V blank interrupt check
}

/*------------------------------------------------------------------*/
/*                    Interrupt Dummy Routine                       */
/*------------------------------------------------------------------*/

void IntrDummy(void)
{
}

/*==================================================================*/
/*                      Subroutine                                  */
/*==================================================================*/

/*------------------------------------------------------------------*/
/*                      Read in Key                                 */
/*------------------------------------------------------------------*/

void KeyRead(void)
{
    u16 ReadData = (*(vu16 *)REG_KEYINPUT ^ 0xffff);
    Trg  = ReadData & (ReadData ^ Cont);            // input trigger
    Cont = ReadData;                                //   input beta
}

/*------------------------------------------------------------------*/
/*           Font Data 1 Character Expansion (8 dot Double-Byte 16 Colors)          */
/*------------------------------------------------------------------*/

void FontSpread(u32 FromAddress, u32 ToAddress)
{
    u8  i,j;                    // For Statement
    u8  Read;                   // For Read
    u32 Write;                  // For Write
    u32 Color = 0x00000001;     // Color Number 

    for (i=0;i<8;i++) {                                 // 8 vertical lines
        Write = 0x00000000;                             // Write Data Clear
        Read  = *(u8 *)(FromAddress + i);               // Read 8 bit    
        for (j=0;j<8;j++) {                             // 8 horizontal rows 
            if (Read & 0x80) Write |= (Color << (4*j)); // Expand from 1 bit to 4 bit (16 colors)
            Read <<= 1;
        }
        *(u32 *)(ToAddress + i*4) = Write;              // Write 32bit
    }
}

/*------------------------------------------------------------------*/
/*                      Font Screen Display                            */
/*------------------------------------------------------------------*/
#define SjisSize                      2                 // Sjis Code Size
#define FontInterval                 10                 // Character Interval
#define OffsetPlus   FontInterval*30*20                 // Data size of 1 screen
#define Limit        sizeof(_binary_Ld937728_dat_start)-OffsetPlus

void FontDisplay(void)
{
    static s32 Offset;
    u16 i;
        
    if (Trg & A_BUTTON) {
        Offset += OffsetPlus;
        if (Offset > Limit) Offset = Limit;
    }
    if (Trg & B_BUTTON) {
        Offset -= OffsetPlus;
        if (Offset <     0) Offset = 0;
    }
    
    for (i=0;i<30*20;i++) {
        FontSpread((u32)(_binary_Ld937728_dat_start + SjisSize + FontInterval*i + Offset),
                   (u32)(BG_VRAM+0x8000 + 32*i));
    }
}


/********************************************************************/
/*          demo_main.c                                             */
/*            multi_sio (Multi-play Communication Sample) Main      */
/*                                                                  */
/*          Copyright (C) 1999-2000 NINTENDO Co.,Ltd.               */
/********************************************************************/
//#define CODE32
#include "MultiSio.h"
#include "types.h"
#include "data.h"

//#define KEY_ON      // Flag that enables the key control OBJ


/*-------------------- Global Variables  ----------------------------*/

    u16      Cont, Trg;                  // Key input

    u32      IntrMainBuf[0x100];         // Interrupt main routine buffer

    u16      BgBak[32*32];               // BG backup
    OamData  OamBak[128];                // OAM backup

	u16		 UsrSendBuf[MULTI_SIO_BLOCK_SIZE/2];    // User send buffer
	u16		 UsrRecvBuf[4][MULTI_SIO_BLOCK_SIZE/2]; // User receive buffer

    u32      SioFlags;                              // Communication status

/*---------------------- Subroutine  -----------------------------*/

void KeyRead(void);


/*------------------------------------------------------------------*/
/*                      Interrupt Table                            */
/*------------------------------------------------------------------*/
void IntrDummy(void);
void VBlankIntr(void);

const IntrFuncp IntrTable[14] = {
    VBlankIntr,                 // V-blank interrupt
#ifdef MULTI_SIO_DI_FUNC_FAST   // Serial communication interrupt
    (IntrFuncp )IntrFuncBuf,
#else
    MultiSioIntr,
#endif
#ifdef MULTI_SIO_DI_FUNC_FAST   // Multi-play communication timer interrupt
    (IntrFuncp )IntrFuncBuf,
#else
    MultiSioIntr,
#endif

    IntrDummy,                  // H-blank interrupt
    IntrDummy,                  // V-counter match interrupt
    IntrDummy,                  // DMA 0 interrupt
    IntrDummy,                  // DMA 1 interrupt
    IntrDummy,                  // DMA 2 interrupt
    IntrDummy,                  // DMA 3 interrupt
    IntrDummy,                  // Key interrupt
    IntrDummy,                  // Game pak interrupt
};

IntrFuncp IntrTableBuf[14];


/*==================================================================*/
/*                      Main Routine                              */
/*==================================================================*/
extern void intr_main(void);

void DemoMain(void)
{
    s32    i;

	RegisterRamReset(RESET_CPU_WRAM_FLAG);                 // Clears CPU internal work RAM

    DmaCopy(3, IntrTable, IntrTableBuf,sizeof(IntrTableBuf),32);// Sets interrupt table
    DmaCopy(3, intr_main, IntrMainBuf, sizeof(IntrMainBuf), 32);// Sets interrupt main routine
    *(vu32 *)INTR_VECTOR_BUF = (vu32 )IntrMainBuf;

    DmaArrayCopy(3, CharData_Sample, BG_VRAM+0x8000, 32);  //  Sets BG characters
    DmaArrayCopy(3, CharData_Sample, OBJ_MODE0_VRAM, 32);  // Sets OBJ characters
    DmaArrayCopy(3, PlttData_Sample, BG_PLTT,        32);  //  Sets BG palette
    DmaArrayCopy(3, PlttData_Sample, OBJ_PLTT,       32);  // Sets OBJ palette

    DmaArrayCopy(3, BgScData_Sample, BgBak,          32);  // Sets BG screen
    DmaArrayCopy(3, BgBak,           BG_VRAM,        32);

    DmaArrayClear(3,160,             OamBak,         32);  // Moves OBJ that is not displayed to outside of the screen
    DmaArrayCopy(3, OamData_Sample,  OamBak,         32);  // Sets OAM
    DmaArrayCopy(3, OamBak,          OAM,            32);

    *(vu16 *)REG_BG0CNT =                                  // Sets BG control
            BG_COLOR_16 | BG_SCREEN_SIZE_0 | BG_PRIORITY_0
            | 0 << BG_SCREEN_BASE_SHIFT | 2 << BG_CHAR_BASE_SHIFT ;

    *(vu16 *)REG_IF    = 0xffff;                           // Resets interrupt
    *(vu16 *)REG_IE    = V_BLANK_INTR_FLAG;                // Enables V-blank interrupt
    *(vu16 *)REG_STAT  = STAT_V_BLANK_IF_ENABLE;
    *(vu16 *)REG_IME   = 1;                                // Sets IME

    *(vu16 *)REG_DISPCNT = DISP_MODE_0 | DISP_BG0_ON | DISP_OBJ_ON; // LCDC ON

    MultiSioInit();                                 // Initializes multi-play communication

	UsrSendBuf[0] = OamBak[((SioMultiCnt *)REG_SIOCNT)->ID].VPos;
	UsrSendBuf[1] = OamBak[((SioMultiCnt *)REG_SIOCNT)->ID].HPos;

    while(1) {
        VBlankIntrWait();                           // Waits for V-blank interrupt to end

        SioFlags = MultiSioMain(UsrSendBuf, UsrRecvBuf); // Multi-play communication main

		for (i=0; i<4; i++)
			if (SioFlags & (1 << i)) {
				OamBak[i].VPos = UsrRecvBuf[i][0];
				OamBak[i].HPos = UsrRecvBuf[i][1];
			}

        // DMA not used in order to enable SIO interrupt
        CpuFastArrayCopy(BgBak,  BG_VRAM);          // Sets BG screen
        CpuFastArrayCopy(OamBak, OAM    );          // Sets OAM


        KeyRead();                                  // Key control


		if (SioFlags & 0xe
		 && SioFlags & (1 << ((SioMultiCnt *)REG_SIOCNT)->ID)) {
#ifndef KEY_ON
            UsrSendBuf[1] -= 4;
#else
            if (Cont & U_KEY)    UsrSendBuf[0] -= 4;
            if (Cont & D_KEY)    UsrSendBuf[0] += 4;
            if (Cont & L_KEY)    UsrSendBuf[1] -= 4;
            if (Cont & R_KEY)    UsrSendBuf[1] += 4;
#endif
		}
    }
}


/*==================================================================*/
/*       Interrupt Routine (Makes process as easy as possible)      */
/*==================================================================*/

/*------------------------------------------------------------------*/
/*                      V-blank Process                              */
/*------------------------------------------------------------------*/

void VBlankIntr(void)
{
}

/*------------------------------------------------------------------*/
/*                      Interrupt Dummy Routine                     */
/*------------------------------------------------------------------*/

void IntrDummy(void)
{
}

/*==================================================================*/
/*                      Subroutine                                */
/*==================================================================*/

/*------------------------------------------------------------------*/
/*                      Key Read                                */
/*------------------------------------------------------------------*/

void KeyRead(void)
{
    u16 ReadData = (*(vu16 *)REG_KEYINPUT ^ 0xffff);
    Trg  = ReadData & (ReadData ^ Cont);            // Key pressed
    Cont = ReadData;                                //   Key held down
}


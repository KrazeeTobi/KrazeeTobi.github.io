/********************************************************************/
/*          main.c                                                  */
/*            multi_sio (Multi-Play Communication Sample) Main      */
/*                                                                  */
/*          Copyright (C) 1999-2000 NINTENDO Co.,Ltd.               */
/********************************************************************/
//#define CODE32
#include "MultiSio.h"
#include "data.h"
#include "MusyX.h"
#include "demo_snd.h"
//#define KEY_ON      // Flag that enables key control of OBJ


//===== For MusyX ===================================================//
	extern char _binary_demo_proj_start[];
	extern void	irqEnable(void);
	extern void irqDisable(void);
	static vs32	irqNest;
	static vs32	timerIrqNest;
	static u32	MusyXRam[0x1400];
//===================================================================//


/*-------------------- Global Variables  ----------------------------*/

	u16      Cont, Trg;                  // Key input

	u32      IntrMainBuf[0x100];         // Buffer for interrupt main routine

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
typedef void (*IntrFuncp)(void);
void IntrDummy(void);
void VBlankIntr(void);
void timerIRQ(void);

const IntrFuncp IntrTable[14] = {
	VBlankIntr,                 // V-Blank interrupt
#ifdef MULTI_SIO_DI_FUNC_FAST
	(IntrFuncp )IntrFuncBuf,    // Serial communication interrupt
#else                           // or Multi-play communication timer interrupt
	MultiSioIntr,
#endif
//===== For MusyX ===================================================//
	timerIRQ,					// Timer 1 interrupt
//===================================================================//
	IntrDummy,                  // H-Blank interrupt
	IntrDummy,                  // V-Counter match interrupt
	IntrDummy,                  // DMA 0 interrupt
	IntrDummy,                  // DMA 1 interrupt
	IntrDummy,                  // DMA 2 interrupt
	IntrDummy,                  // DMA 3 interrupt
	IntrDummy,                  // Key interrupt
	IntrDummy,                  // Game Pak interrupt
};

IntrFuncp IntrTableBuf[14];


/*==================================================================*/
/*                      Main Routine                              */
/*==================================================================*/
extern void intr_main(void);

void AgbMain(void)
{

//===== For MusyX ===================================================//
	MUSYXInitParam			p;
	MUSYXMemLocations		m;
	MUSYXMemRequirements	r;
//===================================================================//
	s32    i;

	RegisterRamReset(RESET_EX_WRAM_FLAG		// Clears CPU external work RAM
				   | RESET_CPU_WRAM_FLAG);	// Clears CPU internal work RAM

//===== For MusyX ===================================================//
	irqNest	= 0;
	timerIrqNest	= 0;
	p.desiredMixingRate		= 11025;
	p.mixingFlags			= 0;
	p.numberOfSampleVoices	= 4;
	p.delayInMSec			= 65;
	p.projectData			= (void *)_binary_demo_proj_start;
	if (musyxCalcMemUsage(&p, &r) > sizeof(MusyXRam))
		while(1);
	musyxCalcSimpleMemLayout(&r, MusyXRam, &m);
	musyxInit(&p, &m);
	musyxDelayParam(32767, 65535, 32767);
	musyxInitSong(0);
//===================================================================//


	DmaCopy(3, IntrTable, IntrTableBuf,sizeof(IntrTableBuf),32);// Sets interrupt table
	DmaCopy(3, intr_main, IntrMainBuf, sizeof(IntrMainBuf), 32);// Sets interrupt main routine
	*(vu32 *)INTR_VECTOR_BUF = (vu32 )IntrMainBuf;

	DmaArrayCopy(3, CharData_Sample, BG_VRAM+0x8000, 32);  //  Sets BG character
	DmaArrayCopy(3, CharData_Sample, OBJ_MODE0_VRAM, 32);  // Sets OBJ character
	DmaArrayCopy(3, PlttData_Sample, BG_PLTT,        32);  //  Sets BG palette
	DmaArrayCopy(3, PlttData_Sample, OBJ_PLTT,       32);  // Sets OBJ palette

	DmaArrayCopy(3, BgScData_Sample, BgBak,          32);  // Sets BG screen
	DmaArrayCopy(3, BgBak,           BG_VRAM,        32);

	DmaArrayClear(3,160,             OamBak,         32);  // Move undisplayed OBJ to outside of the screen
	DmaArrayCopy(3, OamData_Sample,  OamBak,         32);  //Sets OAM
	DmaArrayCopy(3, OamBak,          OAM,            32);

	*(vu16 *)REG_BG0CNT =                                  // Sets BG control
			BG_COLOR_16 | BG_SCREEN_SIZE_0 | BG_PRIORITY_0
			| 0 << BG_SCREEN_BASE_SHIFT | 2 << BG_CHAR_BASE_SHIFT ;

	*(vu16 *)REG_IE    = 0x0011;           					// V Blank & tim1 interrupt permission
	*(vu16 *)REG_STAT  = STAT_V_BLANK_IF_ENABLE;
	*(vu16 *)REG_IME   = 1;                                // Sets IME

	*(vu16 *)REG_DISPCNT = DISP_MODE_0 | DISP_BG0_ON | DISP_OBJ_ON; // LCDC ON

	MultiSioInit();                                 // Initializes multi-play communication

	UsrSendBuf[0] = OamBak[((SioMultiCnt *)REG_SIOCNT)->ID].VPos;
	UsrSendBuf[1] = OamBak[((SioMultiCnt *)REG_SIOCNT)->ID].HPos;
	
	
//===== For MusyX ===================================================//
	musyxStartSong();
	musyxFXKeyoffAll();
//===================================================================//
	
	
	while(1) {
		VBlankIntrWait();                           // Wait for V-Blank interrupt to end

		SioFlags = MultiSioMain(UsrSendBuf, UsrRecvBuf);// Multi-play communication main

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
/*      Interrupt Routine (optimize codes as much as possible)      */
/*==================================================================*/

/*------------------------------------------------------------------*/
/*                      V-Blank Process                              */
/*------------------------------------------------------------------*/

void VBlankIntr(void)
{
	if (irqNest++ == 0) {
		irqEnable();
		
		musyxHandle();
	}
	--irqNest;
	
    *(u16 *)INTR_CHECK_BUF = V_BLANK_INTR_FLAG;     // Set V Blank interrupt check
}

/*------------------------------------------------------------------*/
/*                      Timer Process                               */
/*------------------------------------------------------------------*/

void timerIRQ(void)
{
	if (timerIrqNest++ == 0) {
		irqEnable();
		
		musyxTimerIRQ();
	}
	
	--timerIrqNest;
}


/*------------------------------------------------------------------*/
/*                      Interrupt Dummy Routine                     */
/*------------------------------------------------------------------*/

void IntrDummy(void)
{
}

/*==================================================================*/
/*                     Subroutine                                */
/*==================================================================*/

/*------------------------------------------------------------------*/
/*                      Read Key                                */
/*------------------------------------------------------------------*/

void KeyRead(void)
{
	u16 ReadData = (*(vu16 *)REG_KEYINPUT ^ 0xffff);
	Trg  = ReadData & (ReadData ^ Cont);            // Key pressed
	Cont = ReadData;                                //   Key held down
}


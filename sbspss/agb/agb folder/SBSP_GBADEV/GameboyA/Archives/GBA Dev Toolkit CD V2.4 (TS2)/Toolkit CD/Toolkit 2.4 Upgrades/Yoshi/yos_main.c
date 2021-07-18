//======================================================
//    yos_main.c
//    Main Routine of Sample Yoshi
//
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

/////////////////////////////////////////////////////////////////////
//includes
#include <Agb.h>
#include <isagbprint.h>
#include "yos_main.h"

#include "yos_sound.h"
/////////////////////////////////////////////////////////////////////
//Function of Child Process
extern void yos_game();
extern void proc_0();

/////////////////////////////////////////////////////////////////////
//Global Function
void IntrDummy(void);

/////////////////////////////////////////////////////////////////////
//Local Function
static void KeyRead(void);
static void VBlankIntr(void);

/////////////////////////////////////////////////////////////////////
//Global Variable
gMainVal gMain;
IntrFuncp IntrTable[15];

/////////////////////////////////////////////////////////////////////
//Interrupt Table
const IntrFuncp IntrTable_0[14] = {
    VBlankIntr,     // V Blank interrupt
    IntrDummy,      // H Blank interrupt
    IntrDummy,      // V Blank interrupt
    IntrDummy,      // Timer 0 interrupt
    IntrDummy,      // Timer 1 interrupt
    IntrDummy,      // Timer 2 interrupt
    IntrDummy,      // Timer 3 interrupt
    IntrDummy,      // Serial communication interrupt
    IntrDummy,      // DMA 0 interrupt
    IntrDummy,      // DMA 1 interrupt
    IntrDummy,      // DMA 2 interrupt
    IntrDummy,      // DMA 3 interrupt
    IntrDummy,      // Key interrupt
    IntrDummy,      // Game Pak interrupt
};

/////////////////////////////////////////////////////////////////////
//Function table
void (*(proc_func_tbl[]))()=
{
	proc_0,
	yos_game,
};

/////////////////////////////////////////////////////////////////////
//Main Routine
extern void intr_main(void);

void AgbMain(void)
{
	s16 i;
//AGBPrintInit();
//AGBPrint("TEST \n");
#ifdef ENABLE_PREFETCH
	*(vu16 *)REG_WAITCNT=CST_ROM0_1ST_3WAIT | CST_ROM0_2ND_1WAIT | CST_PREFETCH_ENABLE;
#endif
	//The First Initialization
    DmaClear(3, 0,   EX_WRAM,  EX_WRAM_SIZE,         32);  // CPU exteral Work RAM clear
    DmaClear(3, 0,   CPU_WRAM, CPU_WRAM_SIZE - 0x200,32);  // CPU internal Work RAM clear
//  DmaClear(3, 0,   VRAM,     VRAM_SIZE,            32);  //     VRAM Clear
//  DmaClear(3, 160, OAM,      OAM_SIZE,             32);  //      OAM Clear
//  DmaClear(3, 0,   PLTT,     PLTT_SIZE,            32);  // Palette Clear

	for(i=0;i<15;i++)IntrTable[i]=IntrTable_0[i];
	DmaCopy(3, intr_main, gMain.IntrMainBuf, sizeof(gMain.IntrMainBuf), 16);// Set of interrupt Main Routine
	IntrAddrSet(gMain.IntrMainBuf);
	
	
	*(vu16 *)REG_BG0CNT = 					// Set BG Control
			BG_COLOR_256 | BG_SCREEN_SIZE_0 | BG_PRIORITY_0
			| 0 << BG_SCREEN_BASE_SHIFT | 1 << BG_CHAR_BASE_SHIFT ;

	*(vu16 *)REG_BG1CNT = 					// Set BG Control
			BG_COLOR_256 | BG_SCREEN_SIZE_0 | BG_PRIORITY_1
			| 1 << BG_SCREEN_BASE_SHIFT | 1 << BG_CHAR_BASE_SHIFT ;
	
	//Clear the pointer of function called during V blank
	gMain.pVBlankFunc = 0;
	
	*(vu16 *)REG_IE   &= 0x7fff;
	*(vu16 *)REG_IME  = 1;						// Set IME
//	*(vu16 *)REG_IE	  = IME_FLAG;				// Set IME
	*(vu16 *)REG_IE   |= V_BLANK_INTR_FLAG ;	// Set of V blank interrupt request flag
	*(vu16 *)REG_STAT  = STAT_V_BLANK_IF_ENABLE;
	
	*(vu16 *)REG_DISPCNT = DISP_MODE_0 | DISP_OBJ_ON | DISP_BG0_ON | DISP_BG1_ON | DISP_OBJ_CHAR_1D_MAP;	// LCDC ON
	
	gMain.main_status = 0;
	gMain.main_timer  = 0;
	gMain.proc_num = PROC_0;
#ifdef SOUND_ON
	m4aSoundInit(); // Sound Initialization
#endif
	//Main Loop
	while(1) {
		gMain.main_timer++;
		KeyRead();				// Key Operation
		
		proc_func_tbl[gMain.proc_num]();//Each Process
		
#ifdef SOUND_ON
//		*(vu16 *)BG_PLTT = 0xffe0;
		m4aSoundMain(); // Sound Main
//		*(vu16 *)BG_PLTT = 0xffff;
#endif

		gMain.IntrCheck &= V_BLANK_INTR_FLAG ^ 0xffff;
		while (1) {
//			Halt();				// CPU stop
			if (gMain.IntrCheck & V_BLANK_INTR_FLAG)	// V blank interrupt process completed
			{
				if(gMain.pVBlankFunc != 0)gMain.pVBlankFunc();
				break;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////
//Interrupt Dummy Routine
void IntrDummy(void)
{
}

/////////////////////////////////////////////////////////////////////
//V blank Interrupt Process
static void VBlankIntr(void)
{
#ifdef SOUND_ON
	m4aSoundVSync(); // Sound DMA Re-set
#endif
//	if(gMain.pVBlankFunc != 0)gMain.pVBlankFunc();
	
	gMain.IntrCheck	= V_BLANK_INTR_FLAG;		// Set V blank interrupt check flag
//	*(vu16 *)REG_IF	= V_BLANK_INTR_FLAG;		// Clear V blank interrupt request flag
}

/////////////////////////////////////////////////////////////////////
//Key Read
static void KeyRead(void)
{
	u16 ReadData = (*(vu16 *)REG_KEYINPUT ^ 0xffff);
	gMain.Trg  = ReadData & (ReadData ^ gMain.Cont);// Trigger input
	gMain.Cont = ReadData;							//Beta input
}


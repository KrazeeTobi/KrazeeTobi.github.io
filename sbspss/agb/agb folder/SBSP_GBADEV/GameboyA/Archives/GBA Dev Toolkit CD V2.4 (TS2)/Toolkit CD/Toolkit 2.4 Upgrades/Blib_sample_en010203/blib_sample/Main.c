/********************************************************************/
/*      Main.c      Ver.1.00                                        */
/*          AGB Backup Library Sample Main                          */
/*                                                                  */
/*              Copyright (C) 1999-2001 NINTENDO Co.,Ltd.           */
/********************************************************************/
//#define CODE32
#include <Agb.h>
#include "mylib.h"
#include "Main.h"

// define --------------------------------------
#define		BG0_SCBLK_1	20
#define		BG0_CHBLK_1	3

// extern --------------------------------------
extern void intr_main(void);

extern void InitSramTest(u8 c_p);
extern void SramTest();
extern void InitFlashTest(u8 c_p);
extern void FlashTest();
extern void InitEepromTest(u8 c_p);
extern void EepromTest();
extern void InitMemSelect(u8 c_p);
extern void MemSelect();

extern const u16 mychar[(0x180*32)*8/16];
extern const u16 textPaletteData[16][16];

// function's prototype ------------------------
void InitMainSequence(u8 c_p);
void MainSequence();
void VblankIntr();
void IntrDummy();

// const data  ---------------------------------
static const pos_obj posListMn[]={	{0x0002*8,0x0004*8},
					{0x0002*8,0x0006*8},
					{0x0002*8,0x0008*8},
					{0x0002*8,0x000d*8},
									};
static const u16 charListMn[]={		0x00a0,0x00a1,0x00a2,0x00a1};
static const csrDefine csr0={		posListMn,
					charListMn,
					4,
					127,
					OBJ_PLTT_WHITE,
									};
typedef struct fTableTag {
	void (*init)(u8 c_p);
	void (*func)();
}fTable;
static const fTable fTbl0[]={
					{InitSramTest,SramTest},
					{InitFlashTest,FlashTest},
					{InitEepromTest,EepromTest},
					{InitMemSelect,MemSelect},
					{0x00000000,0x00000000},
									};

// static variable -----------------------------
static	u32	IntrMainBuf[0x200];   		// Interrupt Main Routine Buffer
static	u16	Bg0Bak[32*32];	    		// BG0 Buffer
static	u16	OamBak[4*128];			// OAM Buffer
static	u8	numMain;		        // Hold main sequence cursor position

// global variable -----------------------------
void (*IntrTable[14])();			// Interrupt table
/*	* From crt0.s
	 0: Cassette interrupt
	 1: V-Blank interrupt
	 2: H-Blank interrupt
	 3: V-Counter interrupt
	 4: Timer 0 interrupt
	 5: Timer 1 interrupt
	 6: Timer 2 interrupt
	 7: Timer 3 interrupt
	 8: Serial communication interrupt
	 9: DMA0 interrupt
	10: DMA1 interrupt
	11: DMA2 interrupt
	12: DMA3 interrupt
	13: Key interrupt
*/
void (*ActiveProcess)();

/*==================================================================*/
/*                      Main Routine                                */
/*==================================================================*/

void AgbMain(void)
{
	u32 i;
	u16 result;
	
	RegisterRamReset(RESET_ALL_RAM_FLAG);	// Clear all RAM
	
	*(vu16 *)REG_WAITCNT=CST_ROM0_1ST_3WAIT|CST_ROM0_2ND_1WAIT;	// Set 3-1 wait access
	
	DmaCopy(3, intr_main, IntrMainBuf, sizeof(IntrMainBuf), 16);	// Set interrupt main routine
    *(vu32 *)INTR_VECTOR_BUF=(vu32)IntrMainBuf;
	
	// Initialize interrupt table
	for(i=0;i<14;i++)						
		IntrTable[i]=IntrDummy;
	IntrTable[1]=VblankIntr;
	
	// Initialize funtions you made (No functions in library)
	InitBg();
	
	// Set OBJ
	SetOamBuffer(OamBak,sizeof(OamBak));
	TrmCharData(selObj,mychar,sizeof(mychar),0);
	TrmPaletteData(selObj,(u16 *)textPaletteData,8,8);
	// Set BG
	*(vu16 *)REG_BG0CNT= BG_SCREEN_SIZE_0
						|BG0_SCBLK_1<<BG_SCREEN_BASE_SHIFT
						|BG_COLOR_16
						|BG_MOS_ON
						|BG0_CHBLK_1<<BG_CHAR_BASE_SHIFT
						|BG_PRIORITY_0;
	SetBgxBuffer(0,Bg0Bak,sizeof(Bg0Bak));
	TrmCharData(selBg,mychar,sizeof(mychar),BG0_CHBLK_1);
	TrmPaletteData(selBg,(u16 *)textPaletteData,8,8);
	
	// DISP ON
	*(vu16 *)REG_DISPCNT=DISP_MODE_0 | DISP_BG0_ON | DISP_OBJ_ON;
	
	// Set interrupt
    *(vu16 *)REG_IME=1;		// Set IME
    *(vu16 *)REG_IE=V_BLANK_INTR_FLAG | CASSETTE_INTR_FLAG;	
    					// Allow V-Blank & cassette interrupt
	*(vu16 *)REG_STAT=STAT_V_BLANK_IF_ENABLE;
	
	
	////////////////////////////////////////
	// Initial execution routine of device
	////////////////////////////////////////
#ifdef	__SRAM_FAST_SELECT	// Define with Main.h
	SetSramFastFunc();		// Set SRAM high speed access
#endif
	IdentifyFlash();		// FLASH device identify rountine
	/* * FLASH and SRAM are allocated to the same area so if
             the SRAM Sub-PCB is inserted, the device ID read command
             is issued for FLASH by the execution of this routine.  
	     The SRAM area (0x0e002aaa,0x0e005555) is destroyed.  
             Please be careful of this.
                       */
	
	
	////////////////////////////////////////
	// MAIN LOOP
	////////////////////////////////////////
	InitMainSequence(0);
	ActiveProcess=MainSequence;
	
	while(1) {
		VBlankIntrWait();
		ReadKeyPlus();
		ActiveProcess();
	}
}

void InitMainSequence(u8 c_p)
{
	*(vu16 *)REG_DISPCNT|=DISP_OBJ_ON;		// OBJ on
	
	if(c_p==0)
		numMain=0;
	SetCursorStatus(&csr0,numMain);			// Set cursor data
	
	ClearBgxBuffer(0,0x8000);				// Clear BG0 buffer
	DrawAsciiStringOnBgx(0,0x0021,BG_PLTT_BLUE,"Backup LIB sample");
	DrawAsciiStringOnBgx(0,0x0034,BG_PLTT_YELLOW,"V1.00");
	DrawAsciiStringOnBgx(0,0x0083,BG_PLTT_WHITE,"SRAM   Test");
	DrawAsciiStringOnBgx(0,0x00c3,BG_PLTT_WHITE,"FLASH  Test");
	DrawAsciiStringOnBgx(0,0x0103,BG_PLTT_WHITE,"EEPROM Test");
	DrawAsciiStringOnBgx(0,0x01a3,BG_PLTT_WHITE,"Memory Dump");
	
}

void MainSequence()
{
	if(key.Trg & U_KEY) {				// Move cursor
		if(--numMain& 0x80)
			numMain=csr0.member-1;
	}
	if(key.Trg & D_KEY) {
		if(++numMain == csr0.member)
			numMain=0;
	}
	MoveAndAnimeCursor(numMain);
	
	if(key.Trg & A_BUTTON) {		// To cursor position routine
		fTbl0[numMain].init(0);			// send processing
		ActiveProcess=fTbl0[numMain].func;
	}
}

void ReturnMain()
{
	InitMainSequence(1);
	ActiveProcess=MainSequence;
}


/*==================================================================*/
/*              Interrupt routine                                   */
/*==================================================================*/

void VblankIntr()
{
	DmaAllBgxBuffer();
	DmaOamBuffer();
}

void IntrDummy()
{
}

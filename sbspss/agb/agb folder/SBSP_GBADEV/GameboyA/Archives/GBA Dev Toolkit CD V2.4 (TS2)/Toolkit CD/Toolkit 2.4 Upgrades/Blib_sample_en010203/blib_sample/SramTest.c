/********************************************************************/
/*      SramTest.c                                                  */
/*          256Kbit SRAM Library Sample                             */
/*                                                                  */
/*              Copyright (C) 1999-2001 NINTENDO Co.,Ltd.           */
/********************************************************************/
#include <Agb.h>
#include "mylib.h"
#include "Main.h"


/*++++++++++++++++++++++++++++++++++++++++++++++
  * SetSramFastFunc()  when using AgbSramFast.h,
    is called in AgbMain().
+++++++++++++++++++++++++++++++++++++++++++++++*/


// function prototype --------------------------
void InitSramTest(u8 c_p);
void SramTest();
void WriteSramAllArea();
void SetSramWritePattern(u16 *buff);

// const data-----------------------------------
static const u16 value_wrpatt[]={	0x0000,		//  All  0x0000
					0xffff,		// All  0xffff
					0x0000,		// 2byte increment data
					0xffff,		// 2byte decrement data
					0x00ff,		// 0x00ff,0xff00 repeat
					0x55aa,		// 0x55aa,0xaa55 repeat
									};
static const u8 *const str_wrpatt[]={
					"0000",
					"FFFF",
					"INC ",
					"DEC ",
					"00FF",
					"55AA",
									};

// static variable -----------------------------
static u8 index_wrpatt;


// =============================================================
// =============================================================

void InitSramTest(u8 c_p)	// Executed once every time branch from 
							// main routine
{
	*(vu16 *)REG_DISPCNT&=~DISP_OBJ_ON;		// OBJ off
	
          ClearBgxBuffer(0,0x8000);			// Clear BG0 Buffer
	DrawAsciiStringOnBgx(0,0x0021,BG_PLTT_BLUE,"SRAM TEST");
	DrawAsciiStringOnBgx(0,0x0082,BG_PLTT_YELLOW,"Press(A) is WRITE START.");
	DrawAsciiStringOnBgx(0,0x00a2,BG_PLTT_YELLOW,"     (B) is RETURN.");
	DrawAsciiStringOnBgx(0,0x00c2,BG_PLTT_YELLOW,"     (#%)is PATTERN SELECT.");
	DrawAsciiStringOnBgx(0,0x0104,BG_PLTT_WHITE,"FUNC   :");
	DrawAsciiStringOnBgx(0,0x0124,BG_PLTT_WHITE,"PATTERN:");
#ifdef	__SRAM_FAST_SELECT
	DrawAsciiStringOnBgx(0,0x010c,BG_PLTT_WHITE,"FAST");
#else
	DrawAsciiStringOnBgx(0,0x010c,BG_PLTT_WHITE,"NORMAL");
#endif
	
	index_wrpatt=0;
}

void SramTest()
{
	if(key.Trg & U_KEY)				// Select write pattern
		if(--index_wrpatt & 0x80)
			index_wrpatt=5;
	if(key.Trg & D_KEY)
		if(++index_wrpatt>5)
			index_wrpatt=0;
	DrawAsciiStringOnBgx(0,0x012c,BG_PLTT_WHITE,str_wrpatt[index_wrpatt]);
	
	if(key.Trg & A_BUTTON)			// execute write
		WriteSramAllArea();
	
	if(key.Trg & B_BUTTON)			// return to main
		ReturnMain();
}

/* ** Carries out actual write in this routine ** */
void WriteSramAllArea()
{
	u16 i,phase;
	u32 result;
	const char *const str_phase[]={"WRITE","VERIFY"};
	
	ClearBgxScreenRect(0,0x0164,5,16);	// Clear previous progress and results
	
	SetSramWritePattern((u16 *)COMMON_BUFFER);    // Set write pattern
						    // * Define COMMON_BUFFER with Main.h
	// WRITE
	phase=0;
	DrawAsciiStringOnBgx(0,0x0164,BG_PLTT_WHITE,str_phase[phase]);
#ifdef	__SRAM_FAST_SELECT
	WriteSramFast((u8 *)COMMON_BUFFER,(u8 *)SRAM_ADR,SRAM_SIZE_256K);
#else
	WriteSram((u8 *)COMMON_BUFFER,(u8 *)SRAM_ADR,SRAM_SIZE_256K);
#endif
	
	// VERIFY
	phase=1;
	DrawAsciiStringOnBgx(0,0x0184,BG_PLTT_WHITE, "VERIFY");
#ifdef	__SRAM_FAST_SELECT
	result=VerifySramFast((u8 *)COMMON_BUFFER,(u8 *)SRAM_ADR,SRAM_SIZE_256K);
#else
	result=VerifySram((u8 *)COMMON_BUFFER,(u8 *)SRAM_ADR,SRAM_SIZE_256K);
#endif
	if(result)
		goto ERROR;
	
	// Write normal end message
	DrawAsciiStringOnBgx(0,0x01c4,BG_PLTT_GREEN,"WRITE COMPLETE.");
	return;
ERROR:
	// Write error generation message
	DrawAsciiStringOnBgx(0,0x01c4,BG_PLTT_RED,"VERIFY ERROR.");
	DrawHexOnBgx(0,0x01e4,BG_PLTT_RED,&result,8);
}

void SetSramWritePattern(u16 *buff)
{
	u16 wrdata;
	u32 i;
	
	wrdata=value_wrpatt[index_wrpatt];
	for(i=0;i<SRAM_SIZE_256K;i+=2) {
		*buff++=wrdata;
		if(index_wrpatt==2)		// Increment
			wrdata++;
		else if(index_wrpatt==3)	// Decrement
			wrdata--;
		else if((index_wrpatt==4)||(index_wrpatt==5))	// Flip
			wrdata^=0xffff;
	}
}


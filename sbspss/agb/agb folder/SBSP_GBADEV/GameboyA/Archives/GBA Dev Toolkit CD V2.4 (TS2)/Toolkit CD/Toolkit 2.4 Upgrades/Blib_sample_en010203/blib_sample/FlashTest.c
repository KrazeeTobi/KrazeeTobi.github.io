/********************************************************************/
/*      FlashTest.c                                                 */
/*          512Kbit FLASH Library Sample                            */
/*                                                                  */
/*              Copyright (C) 1999-2001 NINTENDO Co.,Ltd.           */
/********************************************************************/
#include <Agb.h>
#include "mylib.h"
#include "Main.h"

/*++++++++++++++++++++++++++++++++++++++++++++++
 *IdentifyFlash() is called in AgbMain()
+++++++++++++++++++++++++++++++++++++++++++++++*/

// function prototype --------------------------
void InitFlashTest(u8 c_p);
void FlashTest();
void ProgramFlashAllArea();
void SetFlashWritePattern(u16 *buff);

// const data-----------------------------------
static const u16 value_wrpatt[]={	0x0000,	   // All 0x0000
					0xffff,	   // All 0xffff
					0x0000,	   // 2byte  Increment Data
					0xffff,	   // 2byte  Decrement Data
					0x00ff,    // 0x00ff,0xff00 Repeat
					0x55aa,	   // 0x55aa,0xaa55 Repeat
									};
static const u8 *const str_wrpatt[]={   
					"0000",
					"FFFF",
					"INC ",
					"DEC ",
					"00FF",
					"55AA",
									};
static const u16 fdevice_id[]={		0xd4bf,		// LE39FW512
					0x3d1f,		// AT29LV512
					0x1cc2,		// MX29L512
					0x1b32,		// MN63F805MNP
					0x0000,		// UNKNOWN
									};
static const u8 *const str_fdevice[]={
					"LE39FW512",
					"AT29LV512",
					"MX29L512",
					"MN63F805MNP",
					"UNKNOWN",
					"NEW DEVICE",
									};
																	
// static variable--------------------------------------
static u8 index_wrpatt;


// =============================================================
// =============================================================

void InitFlashTest(u8 c_p)	// Executed once each time branch 
					// from main routine.
{
	u8 index;
	const u16 *id_listp;
	
	*(vu16 *)REG_DISPCNT&=~DISP_OBJ_ON;			// OBJ off
	
	ClearBgxBuffer(0,0x8000);			        // BG0 Buffer Clear
	DrawAsciiStringOnBgx(0,0x0021,BG_PLTT_BLUE,"FLASH TEST");
	DrawAsciiStringOnBgx(0,0x0082,BG_PLTT_YELLOW,"Press(A) is WRITE START.");
	DrawAsciiStringOnBgx(0,0x00a2,BG_PLTT_YELLOW,"     (B) is RETURN.");
	DrawAsciiStringOnBgx(0,0x00c2,BG_PLTT_YELLOW,"     (#%)is PATTERN SELECT.");
	DrawAsciiStringOnBgx(0,0x0104,BG_PLTT_WHITE,"DEVICE :");
	DrawAsciiStringOnBgx(0,0x0124,BG_PLTT_WHITE,"PATTERN:");
	
	// Display device name
	id_listp=fdevice_id;
	for(index=0;index<5;index++)
		if(*(u16*)&(flash->makerID)==*id_listp++)  //  Compare maker,device ID
			break;
	DrawAsciiStringOnBgx(0,0x0010c,BG_PLTT_WHITE,str_fdevice[index]);
	
	
	// Set Library Use Timer
	SetFlashTimerIntr(3,&IntrTable[4+3]);		// Use Timer 3
	
	index_wrpatt=0;
}

void FlashTest()
{
	if(key.Trg & U_KEY)				// Select write pattern
		if(--index_wrpatt & 0x80)
			index_wrpatt=5;
	if(key.Trg & D_KEY)
		if(++index_wrpatt>5)
			index_wrpatt=0;
	DrawAsciiStringOnBgx(0,0x012c,BG_PLTT_WHITE,str_wrpatt[index_wrpatt]);
	
	if(key.Trg & A_BUTTON)			// Execute write
		ProgramFlashAllArea();
	
	if(key.Trg & B_BUTTON)			// Return to main
		ReturnMain();
}

/* ** Actual write done with this routine. ** */
void ProgramFlashAllArea()
{
	u8 *src;
	u16 i,result,phase;
	u32 errAdr;
	const char *const str_phase[]={"WRITE","VERIFY"};
	
	ClearBgxScreenRect(0,0x0164,5,16);		// Clear previous progress and result
	
	SetFlashWritePattern((u16 *)COMMON_BUFFER);	// Set write pattern
	// WRITE
	phase=0;
	DrawAsciiStringOnBgx(0,0x0164,BG_PLTT_WHITE,str_phase[phase]);
	src=(u8 *)COMMON_BUFFER;
	for(i=0;i<flash->sector.count;i++) {
		DrawHexOnBgx(0,0x016c,BG_PLTT_WHITE,&i,2);	// Draw Write sector
		
		////////////////////////////////////////////////
		if(index_wrpatt!=1)
			result=ProgramFlashSector(i,src);	// Write
		else
			result=EraseFlashSector(i);		// Erase(Pattern is 0xFFFF)
		////////////////////////////////////////////////
		// *Prohibit direct sound in this section.
		// Also in this function there is a period when interrupts
                // are prohibited so be careful with operation of other  
		// interrupt processing.
		if(result)
			goto ERROR;
	}
	
	// VERIFY
	phase=1;
	DrawAsciiStringOnBgx(0,0x0184,BG_PLTT_WHITE, "VERIFY");
	src=(u8 *)COMMON_BUFFER;
	for(i=0;i<flash->sector.count;i++) {
		DrawHexOnBgx(0,0x018c,BG_PLTT_WHITE,&i,2);	// Draw Verify Sector
		if(errAdr=VerifyFlashSector(i,src))		// Verify
			goto ERROR;
	}
	//  Message for normal write end
	DrawAsciiStringOnBgx(0,0x01c4,BG_PLTT_GREEN,"WRITE COMPLETE.");
	return;
ERROR:
	// Error generation message
	DrawAsciiStringOnBgx(0,0x01c4,BG_PLTT_RED,str_phase[phase]);
	DrawAsciiStringOnBgx(0,0x01cb,BG_PLTT_RED,"ERROR.");
	if(phase==0)
		DrawHexOnBgx(0,0x01e4,BG_PLTT_RED,&result,0);
	else
		DrawHexOnBgx(0,0x01e4,BG_PLTT_RED,&errAdr,8);
}

void SetFlashWritePattern(u16 *buff)
{
	u16 i,wrdata;
	
	wrdata=value_wrpatt[index_wrpatt];
	for(i=0;i<flash->sector.size;i+=2) {
		*buff++=wrdata;
		if(index_wrpatt==2)			// Increment
			wrdata++;
		else if(index_wrpatt==3)	// Decrement
			wrdata--;
		else if((index_wrpatt==4)||(index_wrpatt==5))	// Flip
			wrdata^=0xffff;
	}
}

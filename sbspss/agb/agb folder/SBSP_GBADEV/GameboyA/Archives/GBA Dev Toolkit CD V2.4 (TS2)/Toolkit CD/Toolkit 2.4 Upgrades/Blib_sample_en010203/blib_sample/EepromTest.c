/********************************************************************/
/*      EepromTest.c                                                */
/*          4Kbit EEPROM Library Sample                             */
/*                                                                  */
/*              Copyright (C) 1999-2001 NINTENDO Co.,Ltd.           */
/********************************************************************/
#include <Agb.h>
#include "mylib.h"
#include "Main.h"

// function's prototype ------------------------
void InitEepromTest(u8 c_p);
void EepromTest();
void ProgramEepromAllArea();
void SetEepromWritePattern(u16 *buff);

// const data-----------------------------------
static const u16 value_wrpatt[]={     0x0000,	  // All  0x0000
				      0xffff,	  // All  0xffff
				      0x0000,	  // 2byte Increment Data
				      0xffff,	  // 2byte Decrement Data
				      0x00ff,	  // 0x00ff,0xff00 Repeat
				      0x55aa,	  // 0x55aa,0xaa55 Repeat
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

void InitEepromTest(u8 c_p)	// Executed once each time branch 
				//from main routine 
					
{
      *(vu16 *)REG_DISPCNT&=~DISP_OBJ_ON;			// OBJ off
	
    ClearBgxBuffer(0,0x8000);					// BG0 Buffer Clear
    DrawAsciiStringOnBgx(0,0x0021,BG_PLTT_BLUE,"EEPROM TEST");
    DrawAsciiStringOnBgx(0,0x0082,BG_PLTT_YELLOW,"Press(A) is WRITE START.");
    DrawAsciiStringOnBgx(0,0x00a2,BG_PLTT_YELLOW,"     (B) is RETURN.");
    DrawAsciiStringOnBgx(0,0x00c2,BG_PLTT_YELLOW,"     (#%)is PATTERN SELECT.");
    DrawAsciiStringOnBgx(0,0x0124,BG_PLTT_WHITE,"PATTERN:");
	
	// Set Library Use Timer
	SetEepromTimerIntr(3,&IntrTable[4+3]);		// Use Timer 3
	
	index_wrpatt=0;
}

void EepromTest()
{
	if(key.Trg & U_KEY)				// Select write pattern
		if(--index_wrpatt & 0x80)
			index_wrpatt=5;
	if(key.Trg & D_KEY)
		if(++index_wrpatt>5)
			index_wrpatt=0;
	DrawAsciiStringOnBgx(0,0x012c,BG_PLTT_WHITE,str_wrpatt[index_wrpatt]);
	
	if(key.Trg & A_BUTTON)			// Execute write
		ProgramEepromAllArea();
	
	if(key.Trg & B_BUTTON)			// Return to main
		ReturnMain();
}

/* ** Actual write done with this routine. ** */
void ProgramEepromAllArea()
{
	u16 i,result,*src,phase;
	u16 ep_Buffer[64*64/16];		// Write origin data buffer
					       // (*1declare with 6bit boundary)
	const char *const str_phase[]={"WRITE","VERIFY"};
	
	ClearBgxScreenRect(0,0x0164,5,16); // Clear previous progress and results
	
	SetEepromWritePattern(ep_Buffer);	// Set write pattern
	
	// WRITE
	phase=0;
	DrawAsciiStringOnBgx(0,0x0164,BG_PLTT_WHITE,str_phase[phase]);
	src=ep_Buffer;
	for(i=0;i<EEPROM_ADR_COUNT;i++) {
		DrawHexOnBgx(0,0x016c,BG_PLTT_WHITE,&i,2);  //Draw write address
		////////////////////////////////////////////////
		result=ProgramEepromDword(i,src);			// Write
		////////////////////////////////////////////////
		// *Prohibit direct sound in this section.
		// Also in this function there is a period when interrupts
                // are prohibited so be careful with operation of other  
		// interrupt processing.
		if(result)
			goto ERROR;
		src+=4;
	}
	
	// VERIFY
	phase=1;
	DrawAsciiStringOnBgx(0,0x0184,BG_PLTT_WHITE, "VERIFY");
	src=ep_Buffer;
	for(i=0;i<EEPROM_ADR_COUNT;i++) {
		DrawHexOnBgx(0,0x018c,BG_PLTT_WHITE,&i,2);  // Draw Verify address
		////////////////////////////////////////////////
		result=VerifyEepromDword(i,src);	              // Verify
		////////////////////////////////////////////////
	        // *Prohibit direct sound in this section.
		// Also in this function there is a period when interrupts
                // are prohibited so be careful with operation of other  
		// interrupt processing.
		if(result)
			goto ERROR;
		src+=4;
	}
	// Message for normal write end
	DrawAsciiStringOnBgx(0,0x01c4,BG_PLTT_GREEN,"WRITE COMPLETE.");
	return;
ERROR:
	// Error generation message
	DrawAsciiStringOnBgx(0,0x01c4,BG_PLTT_RED,str_phase[phase]);
	DrawAsciiStringOnBgx(0,0x01cb,BG_PLTT_RED,"ERROR.");
	DrawHexOnBgx(0,0x01e4,BG_PLTT_RED,&result,4);
}

void SetEepromWritePattern(u16 *buff)
{
	u16 i,wrdata;
	
	wrdata=value_wrpatt[index_wrpatt];
	for(i=0;i<EEPROM_SIZE;i+=2) {
		*buff++=wrdata;
		if(index_wrpatt==2)			// Increment
			wrdata++;
		else if(index_wrpatt==3)	// Decrement
			wrdata--;
		else if((index_wrpatt==4)||(index_wrpatt==5))	// Flip
			wrdata^=0xffff;
	}
}

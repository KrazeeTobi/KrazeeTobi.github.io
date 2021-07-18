/********************************************************************/
/*      MemDump.c                                                   */
/*          Backup Device Area Dump Routine                         */
/*                                                                  */
/*              Copyright (C) 1999-2001 NINTENDO Co.,Ltd.           */
/********************************************************************/
#include <Agb.h>
#include "mylib.h"
#include "Main.h"


/* **** Operations ****
   Left, Right  : Move cursor
   Up, Down	: Increase/Decrease dump address
   R Button	: Align data (1/2/4byte switch)
   L Button	: Speed up increase/decrease address
   B Button	: Return
   ***********************
*/

// function's prototype ------------------------
void InitMemSelect(u8 c_p);
void MemSelect();
void InitMemDump(u8 c_p);
void MemDump();
void DrawAdressLine(u32 adr);
void DumpData(u32 adr,u8 dsize);
void InitEepromDump(u8 c_p);

/*==============================================
	
	Memory Select
	
==============================================*/
// const data-----------------------------------
static const u8 *const memName[4]={
									"SRAM",
									"FLASH",
									"EEPROM",
									};

static const pos_obj posListMs[]={	{0x0002*8,0x0004*8},
									{0x0002*8,0x0006*8},
									{0x0002*8,0x0008*8},
									};
static const u16 charListMs[]={		0x00a0,0x00a1,0x00a2,0x00a1};
static const csrDefine csr1={		posListMs,
									charListMs,
									3,
									127,
									OBJ_PLTT_WHITE,
									};
// static variable------------------------------
static u8 numMemSel;

// function's description-----------------------
void InitMemSelect(u8 c_p)
{
	if(c_p==0)
		numMemSel=0;
	SetCursorStatus(&csr1,numMemSel);		// Set cursor data
	
	ClearBgxBuffer(0,0x8000);			// Clear BG0 buffer
	DrawAsciiStringOnBgx(0,0x0021,BG_PLTT_BLUE,"Dump Memory Select");
	DrawAsciiStringOnBgx(0,0x0083,BG_PLTT_WHITE,memName[0]);
	DrawAsciiStringOnBgx(0,0x00c3,BG_PLTT_WHITE,memName[1]);
	DrawAsciiStringOnBgx(0,0x0103,BG_PLTT_WHITE,memName[2]);
}

void MemSelect()
{
	if(key.Trg & U_KEY)			// Move cursor
		if(--numMemSel & 0x80)
			numMemSel=csr1.member-1;
	if(key.Trg & D_KEY)
		if(++numMemSel == csr1.member)
			numMemSel=0;
	MoveAndAnimeCursor(numMemSel);
	
	if(key.Trg & A_BUTTON) {		// Send process to memory dump
		InitMemDump(0);
		ActiveProcess=MemDump;
	}
	if(key.Trg & B_BUTTON)			// Return to main
		ReturnMain();
}

/*======================================================
	
	Memory Dump
	
======================================================*/
// static variable------------------------------
static inputHexDef inHexDefMd;
static u8 numMd,dumpSize,csrMax;
static u32 dumpAdr;
static u16 ep_rd_buffer[64*64/16];

// const data-----------------------------------
static const pos_obj posListMd[]={	{0x0007*8,0x0002*8},
					{0x0006*8,0x0002*8},
					{0x0005*8,0x0002*8},
					{0x0004*8,0x0002*8},
					{0x0003*8,0x0002*8},
					{0x0002*8,0x0002*8},
					{0x0001*8,0x0002*8},
					{0x0000*8,0x0002*8},
									};
static const u16 charListMd[]={		0x00b0,0x00b1,0x00b2,0x00b1};
static const csrDefine csr2={		posListMd,
					charListMd,
					8,
					127,
					OBJ_PLTT_WHITE,
									};
static const u8 unitMd[]={			0,8,1,1,1,1,1,1};
static const u32 range[]={			SRAM_ADR,               SRAM_ADR+SRAM_SIZE_256K,
									FLASH_ADR,		FLASH_ADR+0x10000,
									(u32)&ep_rd_buffer,(u32)&ep_rd_buffer+EEPROM_SIZE,
									};
static const u8 csrMaxArray[]={ 	4,4,3};

void InitMemDump(u8 c_p)
{
	u8 i;
	u16 *rdp;
	u32 dump_max;
	
	numMd=1;
	SetCursorStatus(&csr2,numMd);		// Set cursor data
	
	ClearBgxBuffer(0,0x8000);		// Clear BG0 buffer
	DrawAsciiStringOnBgx(0,0x0000,BG_PLTT_BLUE,memName[numMemSel]);
	
	inHexDefMd.value=&dumpAdr;	//   Set dump address input parameters
	inHexDefMd.unit=(u8 *)unitMd;
	inHexDefMd.max=range[(numMemSel<<1)+1];
	inHexDefMd.min=range[numMemSel<<1];
	inHexDefMd.pos=0x0020;
	inHexDefMd.attr=BG_PLTT_RED;
	inHexDefMd.size=4;
	inHexDefMd.bgNo=0;
	inHexDefMd.numMax=csrMaxArray[numMemSel]-1;
	inHexDefMd.numMin=1;
	inHexDefMd.range=true;
	inHexDefMd.finish=false;
	SetInputHexData(&inHexDefMd);
	
	dump_max=inHexDefMd.max-1;
	DrawHexOnBgx(0,0x0015,BG_PLTT_WHITE,&inHexDefMd.min,8);	// Draw dump range
	DrawHexOnBgx(0,0x0035,BG_PLTT_WHITE,&dump_max,8);
	
	dumpAdr=inHexDefMd.min;			// Set initial dump address
	
	if(numMemSel==2) {		// When selecting EEPROM, read data
		rdp=ep_rd_buffer;		// for all addresses in advance, and 
		for(i=0;i<EEPROM_ADR_COUNT;i++) {  // dump that content.
			////////////////////////////////////////////////
			ReadEepromDword(i,rdp);
			////////////////////////////////////////////////
			// *Prohibit direct sound in this section.
		        // Also in this function there is a period when 
                        // interrupts are prohibited so be careful with 
                        // operation of other interrupt processing.
			rdp+=4;
		}
	}
}

void MemDump()
{
	u16 temp;
	
	if(key.Rapid & L_KEY)		// Move cursor
		if(++numMd == csrMaxArray[numMemSel])
			numMd=1;
	if(key.Rapid & R_KEY) {
		if(--numMd == 0)
			numMd=csrMaxArray[numMemSel]-1;
	}
	MoveAndAnimeCursor(numMd);
	
	if(key.Trg & R_BUTTON) {     // Switch dump units (8/16/32bit)
		ClearBgxScreenRect(0,0x0065,16,23);
		dumpSize++;
		if(dumpSize>2)
			dumpSize=0;
	}
	
	// Memory dump
	InputHexData(&temp);
	DrawAdressLine(dumpAdr);
	DumpData(dumpAdr,dumpSize);
	
	if(key.Trg & B_BUTTON) {	// Return to master process (select memory)
		InitMemSelect(1);
		ActiveProcess=MemSelect;
	}
}

void DrawAdressLine(u32 adr)
{
	u8 i,top;
	u16 pos;
	
	top=(u8)adr;
	pos=0x0062;
	for(i=0;i<16;i++){
		DrawHexOnBgx(0,pos,BG_PLTT_WHITE,&top,2);
		top+=0x08;
		pos+=0x0020;
	}
}

void DumpData(u32 adr,u8 dsize)
{
	u8 i,j,length,row,addAdr,buffer[0x80];
	u16 pos,secNo;
	u32 offset;
	
	if(numMemSel==0x00) {		// SRAM dump
#ifdef	__AGB_SRAM_FAST_H__
		ReadSramFast((u8 *)adr,buffer,0x80);
#else
		ReadSram((u8 *)adr,buffer,0x80);
#endif
		adr=(u32)buffer;
	}
	else if(numMemSel==0x01) {	// FLASH dump
		secNo=(adr-FLASH_ADR)>>flash->sector.shift;
		offset=adr & (flash->sector.size-1);
		ReadFlash(secNo,offset,buffer,0x80);
		adr=(u32)buffer;
	}
	
	length=2<<dsize;			// Draw dump data
	row=8>>dsize;
	addAdr=1<<dsize;
	for(i=0;i<16;i++) {
		pos=0x0065+0x0020*i;
		for(j=0;j<row;j++){
			pos=DrawHexOnBgx(0,pos,BG_PLTT_WHITE,(u8 *)adr,length);
			pos++;
			adr+=addAdr;
		}
	}
}


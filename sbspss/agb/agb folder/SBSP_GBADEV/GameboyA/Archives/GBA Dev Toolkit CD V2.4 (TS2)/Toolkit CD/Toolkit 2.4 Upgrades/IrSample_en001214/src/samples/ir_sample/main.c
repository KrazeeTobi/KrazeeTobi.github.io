/********************************************************************/
/*					main.c											*/
/*      			AGB IR Communication Sample Program		    	*/
/*					ver1.0											*/
/*					Copyright (C) 2000 NINTENDO CO.,Ltd.			*/
/********************************************************************/

//#define CODE32
#include <Agb.h>
#include "ir_sample.h"
#include "utility.h"
#include "data.h"


/*-------------------- Global Variables ----------------------------*/

	vu16	Cont, Trg;						// Key input
	vu16	BAK_REG_DISPCNT;				// DISPLAY

	/*IR Communication*/
	vu16	EMImod;							// Consecutive communication mode flag
	vu16	ir_rate;							// Communication speed parameter

	vu16	scount;							// Count for successful communication
	vu16	fcount;							// Count for unsuccessful communication
	const	u16	IrId = 0xAC0F;				// Key code
	vu16	Data		[0xFF+1];			// Sending data (regardless of ROM or RAM)
	vu16	IrBuf		[0xFF+1];			// Receiving data buffer (RAM only)
	vu32	Ram_S_Buf	[IR_ARM_SEND_CORE_SIZE];	// Sending ARM core container buffer
	vu32	Ram_R_Buf	[IR_ARM_RECV_CORE_SIZE];	// Receiving ARM core container buffer

	vu16	coremode;						// To judge communication core

/*---------------------- Subroutine -----------------------------*/

void KeyRead(void);

/*------------------------------------------------------------------*/
/*              		Interrupt Table	                	 	    */
/*------------------------------------------------------------------*/
typedef void (*IntrFuncp)(void);
void VBlankIntr(void);

const IntrFuncp IntrTable[15] = {
	KeyRead, KeyRead, KeyRead, KeyRead, KeyRead,
	KeyRead, KeyRead, KeyRead, KeyRead, KeyRead,
	KeyRead, KeyRead, KeyRead, KeyRead, KeyRead
};


/*==================================================================*/
/*     				Main Routine				    				*/
/*==================================================================*/
extern void intr_main(void);


void AgbMain(void)
{
	int			i;
	u8			through;
	irResult	IrRS;

    DmaClear(3, 0, EX_WRAM ,  EX_WRAM_SIZE-0x200 , 32);	// CPU external work RAM clear
	DmaClear(3, 0, CPU_WRAM, CPU_WRAM_SIZE - 4*32, 32);	// Work RAM clear

	BAK_REG_DISPCNT		= DISP_MODE_0;
	*(vu16 *)REG_DISPCNT= BAK_REG_DISPCNT;

	DmaClear(3, 0, VRAM    , VRAM_SIZE           , 16);	// VRAM clear
	DmaClear(3, 0, OAM     , OAM_SIZE            , 32);	// OAM clear
	DmaClear(3, 0, PLTT    , PLTT_SIZE           , 16);	// Palette RAM clear

	DmaArrayCopy(3, CharData_Sample, BG_VRAM+0x8000,  16);	// BG character set
	DmaArrayCopy(3, CharData_Sample, OBJ_MODE0_VRAM,  16);	// OBJ character set
	DmaArrayCopy(3, PlttData_Sample, BG_PLTT,  16);	// BG palette set
	DmaArrayCopy(3, PlttData_Sample, OBJ_PLTT, 16);	// OBJ palette set

	*(vu16 *)REG_BG0CNT = 							// BG control set
			BG_COLOR_16 | BG_SCREEN_SIZE_0 | BG_PRIORITY_0
			| 0 << BG_SCREEN_BASE_SHIFT | 2 << BG_CHAR_BASE_SHIFT ;

	BAK_REG_DISPCNT |= DISP_OBJ_ON | DISP_BG0_ON;
 	*(vu16 *)REG_DISPCNT = BAK_REG_DISPCNT;			// LCDC ON

	scount = 0;
	fcount = 0;
	EMImod = 0;
	for( i=0; i<256; i++) {
		Data[i] = i;
	}

//	*(vu16 *)REG_WAITCNT |= 0x14;	// Game Pak ROM wait 3-1
//	ir_rate = IR_40kbps_RATE;		// Adjust comm speed setting depending on
//	ir_rate = IR_47kbps_RATE;		//  ROM wait and ROM/RAM behavior
	ir_rate = IR_104kbps_RATE;

	irBegin( 0, &IrRS, 1);
	irRamCopy( (u32*)Ram_S_Buf, (u32*)Ram_R_Buf);		// Copy ARM code RAM version
	irMountArmCore( (u32*)Ram_S_Buf, (u32*)Ram_R_Buf);	// Mount ARM code containing RAM
	coremode = 1;
//	irMountThumbCore();

	PrintMenu();				// Display menu

	while(1) {
		irInit();

		*(vu16 *)REG_IF &= SIO_INTR_FLAG;
		while(1) {
			if( (*(vu16 *)REG_IF & SIO_INTR_FLAG) != 0) {
				if( IR_RECV_CGB() == 1) { scount++; }else{ fcount++; }
				break;
			}
			KeyRead();								// Key operation
			/*** With arrow key <up>, mount ARM core ***/
			if( Trg & U_KEY) {
				ir_rate = IR_104kbps_RATE;
				irMountArmCore( (u32*)Ram_S_Buf, (u32*)Ram_R_Buf);
				coremode = 1;
			}
			/*** With arrow key <down>, mount THUMB core ***/
			if( Trg & D_KEY) {
				ir_rate = IR_40kbps_RATE;
				irMountThumbCore();
				coremode = 0;
			}
			if( Trg & START_BUTTON) { EMImod=1; }
			if( Trg & B_BUTTON)     { EMImod=0; }
			if( (Cont & A_BUTTON) | EMImod) {
				if( IR_SEND_CGB() == 1) { scount++; }else{ fcount++; }
				break;
			}
		}
		PrintParameter( &IrRS);		// Display comm parameter
	}
	irEnd();
}



/* Send */
u8 IR_SEND_CGB( void)
{
	vu8 i, err;
	err = 0;
	while(1) {
		if( irSendConnect(ir_rate)          == IR_FAILURE)	{err=1;break;}
		if( irSendPacket((u16 *)&IrId,  1) == IR_FAILURE)	{err=2;break;}

		irInit();
		if( irRecvPacket((u16 *)IrBuf, 1) == IR_FAILURE)	{err=5;break;}
		if( *(u16 *)IrBuf != ((u16)IrId ^ (u16)0xFFFF)) 	{err=7;break;}	// Check comm code
		irInit();
		if( irSendPacket((u16 *)Data, 0xFF) == IR_FAILURE)	{err=9;break;}
		return( 1);
	};
	return( 0);
}
/* Receive */
u8 IR_RECV_CGB( void)
{
	vu8	i, flag, err;
	err=0;
	while(1) {
		flag = irRecvConnect(ir_rate);
		if( flag == IR_FAILURE)								{ err=1; break;}
		
		if( irRecvPacket((u16 *)IrBuf, 1) == IR_FAILURE)	{ err=2; break;}
		if( *(u16 *)IrBuf != 0xAC0F)						{ err=4; break;}// Check comm code
		IrBuf[0] ^= (u16)0xFFFF;						// Modify comm code
		irInit();
		if( irSendPacket((u16 *)IrBuf, 1) == IR_FAILURE)	{ err=6; break;}

		irInit();
		if( irRecvPacket((u16 *)IrBuf, 0xFF) == IR_FAILURE)	{ err=9; break;}
		return( 1);
	};
	return( 0);
}


/* Display character string */
void putstr( char* str, vu16* dest)
{
	vu8		i;
	i=0;
	while(1) {
		if( str[i] == '\0') break;
		*(dest++) = (u16)str[i];
		i++;
	}
}

void PrintMenu( void)
{
	char	ircnt[]	= "SIODAT\0" ;
	char	stat []	= "STATUS\0" ;
	char	mode []	= "MODE\0"   ;
	char	csum []	= "SUM\0"    ;
	char	sccs []	= "SUCCESS\0";
	char	fail []	= "FAILURE\0";
	char	key  []	= "KEYCODE\0";
	char	rate [] = "RATE\0"   ;
	char	rbuf [] = "RECVBUF\0";
	char	core [] = "CORE\0"   ;
	
	putstr( ircnt, (vu16*)(VRAM+0x044));
	putstr( stat,  (vu16*)(VRAM+0x0C4));
	putstr( mode,  (vu16*)(VRAM+0x144));
	putstr( csum,  (vu16*)(VRAM+0x1C4));
	putstr( sccs,  (vu16*)(VRAM+0x244));
	putstr( fail,  (vu16*)(VRAM+0x284));	
	putstr( key,   (vu16*)(VRAM+0x304));
	putstr( rbuf,  (vu16*)(VRAM+0x344));
	putstr( rate,  (vu16*)(VRAM+0x3C4));
	putstr( core,  (vu16*)(VRAM+0x404));
}

void PrintParameter( irResult* IrRS)
{
	char	armcore  [] = "ARM  \0";
	char	thumbcore[] = "THUMB\0";

	DispCharSetBG( 16, VRAM+0x054, (vu16*)REG_RCNT)       ;// R register
	DispCharSetBG( 16, VRAM+0x0D4, (vu16*)&(IrRS->status));// Status code
	DispCharSetBG( 16, VRAM+0x154, (vu16*)&(IrRS->mode))  ;// Distinguish send/receive
	DispCharSetBG( 16, VRAM+0x1D4, (vu16*)&(IrRS->sum))   ;// Check sum value

	DispCharSetBG( 16, VRAM+0x254, (vu16*)&scount);	// Comm success count
	DispCharSetBG( 16, VRAM+0x294, (vu16*)&fcount);	// Comm failure count
	
	DispCharSetBG( 16, VRAM+0x314, (vu16*)&IrId);	// Comm key code
	DispCharSetBG( 16, VRAM+0x354, (vu16*)IrBuf);	// First 16bit in receiving buffer
													//  (Sender gets modified key code value)
	DispCharSetBG( 16, VRAM+0x3D4, (vu16*)&(IrRS->rate))  ;// Comm speed

	if( coremode == 1) {
		putstr( armcore, (vu16*)(VRAM+0x414));
	}else{
		putstr( thumbcore, (vu16*)(VRAM+0x414));
	}
}

/*==================================================================*/
/*     			Subroutine				    */
/*==================================================================*/

/*------------------------------------------------------------------*/
/*     		Key Reading					    */
/*------------------------------------------------------------------*/

void KeyRead(void)
{
	u16 ReadData = (*(vu16 *)REG_KEYINPUT ^ 0xffff);
	Trg  = ReadData & (ReadData ^ Cont);		// Key pressed
	Cont = ReadData;							// Key held down
}


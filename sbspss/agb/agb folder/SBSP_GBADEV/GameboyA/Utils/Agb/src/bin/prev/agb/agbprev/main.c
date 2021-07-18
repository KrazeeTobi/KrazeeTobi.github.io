//======================================================
//    main.c                          
//    Previewer Main Routine
//                                                     
//    Copyright (C) 1999, NINTENDO Co., Ltd.             
//======================================================

#include <agb.h>
#include <isagbprint.h>
#include <mpr.h>
#include <util.h>
#include <node.h>
#include <datatrans.h>
#include <controller.h>
#include "prevobj.h"
#include "prevbg.h"

extern const nodeHeaderChunk prev_node_header;

//  It is necessary to specify head address of node here.
#define	PREV_NODE_HEADER_ADDRESS	(&prev_node_header)

#define	APP_CONTROL_MODE_NUM	(2)

/*-------------------- Global Variables  ----------------------------*/

    u8		app_control_mode;	// Which BG,Obj is being moved
    vu16	IntrCheck;			// For interrupt check
    u32		IntrMainBuf[0x200];	// Buffer for interrupt main routine

/*---------------------- Sub-Routine  -----------------------------*/
extern void intr_main(void);
extern void ctrRead(void);
extern void dtDo(void);
extern void dtClear(void);
extern void ctrInit( void );
extern void omClear(void);
extern void bmClear(void);
extern void pobjInit( void );
extern void ndhcEvaluate( u32 nodeheaderchunk_address );
extern void pobjCreateObject( void );
extern void pbgLoopInit(void);
void appInit( void );
void appControl( void );

/*------------------------------------------------------------------*/
/*			Interrupt Table           	 	    */
/*------------------------------------------------------------------*/
typedef void (*IntrFuncp)(void);
void VBlankIntr(void);

const IntrFuncp IntrTable[15] = {
    VBlankIntr,
    ctrRead,
    ctrRead,
    ctrRead,
    ctrRead,
    ctrRead,
    ctrRead,
    ctrRead,
    ctrRead,
    ctrRead,
    ctrRead,
    ctrRead,
    ctrRead,
    ctrRead,
    ctrRead,
};
/*==================================================================*/
/*			Main Routine				    */
/*==================================================================*/
#ifdef	__GNUC__
int main(void)
#else
void AgbMain(void)
#endif
{
    DmaClear(3, 0, WRAM, USR_BUF_SIZE - 4*64, 32);	// Work RAM Clear
    DmaClear(3, 0, VRAM, VRAM_SIZE,	  16);		// VRAM Clear
    DmaClear(3, 0, OAM,  OAM_SIZE,	  32);		// OAM Clear
    DmaClear(3, 0, PLTT, PLTT_SIZE,	  16);		// Palette Clear

	// Set interrupt subroutine
    DmaCopy(3, intr_main, IntrMainBuf, sizeof(IntrMainBuf), 16);
    IntrAddrSet(IntrMainBuf);

	// Initialize application

    ctrInit();
    AGBPrintInit();
    appInit();

    *(vu16 *)REG_IE  = IME_FLAG;		// Set IME
    *(vu16 *)REG_IE |= V_BLANK_INTR_FLAG;	// Set V Blank interrupt permission flag
    *(vu16 *)REG_STAT  = STAT_V_BLANK_IF_ENABLE;
    app_control_mode = 0;

	// Main loop

    while(1)
    {

	pbgLoopInit();

	    //  Read in controller

	ctrRead();

	    //  Control

	appControl();

	    //  Evaluation

	pobjEvaluate();
	pbgEvaluate();

	    // Initialize V Blank interrupt flag

	IntrCheck &= V_BLANK_INTR_FLAG ^ 0xffff;

	while(1)
	{
		//  Pause CPU
	    Halt();
		//  Wait for V Blank interrupt process to complete
	    if (IntrCheck & V_BLANK_INTR_FLAG) break;
	}
    }
#ifdef	__GNUC__
    return 0;
#endif
}
/*==================================================================*/
/*			V Blank interrupt process		    */
/*==================================================================*/
void VBlankIntr(void)
{
    mprVBlankFnc();

    *(vu16 *)REG_IF	= V_BLANK_INTR_FLAG;
    IntrCheck		= V_BLANK_INTR_FLAG;
}
//----------------------------------------------------------------------
//			Initialization routine
//----------------------------------------------------------------------
void appInit(void)
{
    mprInitInfo initinfo;
    pobjInit();
    pbgInit();
    initinfo.nodeheaderchunk_address = (u32)PREV_NODE_HEADER_ADDRESS;
    initinfo.char_number_start = 0;
    initinfo.char_number_end = 255;
    initinfo.use_sort_key_flag = 0;
    mprInit( &initinfo );
    pobjCreateObject();
    mprVBlankFnc();
}
//----------------------------------------------------------------------
//			Control part
//----------------------------------------------------------------------
void appControl( void )
{
    if( Trg & SELECT_BUTTON )
    {
	++app_control_mode;
	_wrapUpperLimit( app_control_mode , 0 , APP_CONTROL_MODE_NUM );
    }
    if( nodeGetNumOfObjects() == 0 )
	app_control_mode = 1;
    if( nodeGetNumOfBGs() == 0 )
	app_control_mode = 0;

    switch( app_control_mode )
    {
	case 0 :
	    pobjControl();
	    break;
	case 1 :
	    pbgControl();
	    break;
	default :
	    break;
    }
}
//----------------------------------------------------------------------


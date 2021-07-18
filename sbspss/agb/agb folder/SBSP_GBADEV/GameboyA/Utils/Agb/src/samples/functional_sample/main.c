//======================================================
//    main.h                                           
//    Functional sample main routine
//                                                      
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.         
//======================================================

//#define CODE32
#include <agb.h>
#include "share.h"
#include "menu.h"
#include "menuitem.h"

//======================================================
//                     Main routine
//======================================================
void bgMain(void);

void AgbMain(void)
{

//	bgMain();

	//  Clear RAM
    ClearRamAll();

	//  Initialize V Blank 

    InitVBlank();

    *(vu16 *)REG_IE   = 0;                      // Reset IE  
    *(vu16 *)REG_IME  = 1;                      // Set IME 
    *(vu16 *)REG_STAT = STAT_V_BLANK_IF_ENABLE;	// V Blank interrupt request flag enabled 

	//  For debugging

    AGBPrintInit();

    MenuInit();
    KeyInit();
    KeyRead();

	//  Main loop
	//  After calling menu, each main routine is called according to mode.
 

    while(1)
    {
	(*(mitem[Menu()].call_back))();
    }
}



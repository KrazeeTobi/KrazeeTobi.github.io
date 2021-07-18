//======================================================
//    main.c                                           
//    Functional sample main routine
//                                                      
//    Copyright (C) 1999, NINTENDO Co., Ltd.             
//======================================================

//#define CODE32
#include <agb.h>
#include "share.h"
#include "bitmap.h"

//======================================================
//                 External routines
//======================================================
//extern const char* bm_title_str;
//extern const char** bm_expl_str_array[];
//extern void bm_Main(void);

//======================================================
//                   Main routine
//======================================================
void bgMain(void);

void AgbMain(void)
{
		
//  Clear RAM
    ClearRamAll();

//  Initialize V Blank 
    InitVBlank();

    *(vu16 *)REG_IE   = 0;			        	// Reset IE
	*(vu16 *)REG_IME  = V_BLANK_INTR_FLAG;      // Set IME
    *(vu16 *)REG_STAT = STAT_V_BLANK_IF_ENABLE;	// V Blank interrupt request flag enabled 

    KeyInit();
    KeyRead();

//  Main loop
//  Call the main routine for displaying the AVI file

    while(1)
    {
	bm_Main();
    }
}



//======================================================
//    window.c
//    Window function sample
//
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================
#include <agb.h>
#include "../share.h"
#include "sw_dat.h"

//--------------------    Data        ----------------------------
const u32 sw_OamData_Sample[1][2] =
{
	{ OAM_COLOR_256 | OAM_SIZE_32x64, 0},
};

//-------------------- Global variable  ----------------------------
OamData sw_OamBak[128];			// OAM backup

//---------------------- Subroutines -----------------------------
void sw_ObjMove(void);
void sw_v_blank_intr(void);

//==================================================================
//                       Main routine                             
//==================================================================
void swMain(void)
{
	u16 i;
	
	SetVBlankFunc( sw_v_blank_intr );// Set functions called in V blank
	
	DmaClear(3, 0,  OAM,     OAM_SIZE       , 32);//    OAM clear
	
	//Set display control register
	*(vu16 *)REG_DISPCNT = DISP_MODE_0		//BG mode 0
		| DISP_OBJ_ON | DISP_BG0_ON | DISP_BG1_ON | DISP_BG2_ON | DISP_BG3_ON //OBJ,BG0123 display
		| DISP_OBJ_CHAR_1D_MAP				//OBJ character 1D mapping 
		| DISP_WIN0_ON | DISP_WIN1_ON | DISP_OBJWIN_ON ;//Set window0, 1, OBJ window

	
	//Set BG control register
	*(vu16 *)REG_BG0CNT = BG_SCREEN_SIZE_0 | BG_PRIORITY_0
			| 7  << BG_SCREEN_BASE_SHIFT | 0 << BG_CHAR_BASE_SHIFT ;
	
	*(vu16 *)REG_BG1CNT = BG_SCREEN_SIZE_0 | BG_PRIORITY_1
			| 15 << BG_SCREEN_BASE_SHIFT | 1 << BG_CHAR_BASE_SHIFT ;
	
	*(vu16 *)REG_BG2CNT = BG_SCREEN_SIZE_0 | BG_PRIORITY_2
			| 23 << BG_SCREEN_BASE_SHIFT | 2 << BG_CHAR_BASE_SHIFT ;
	
	*(vu16 *)REG_BG3CNT = BG_SCREEN_SIZE_0 | BG_PRIORITY_3
			| 31 << BG_SCREEN_BASE_SHIFT | 3 << BG_CHAR_BASE_SHIFT ;
	
	DmaArrayCopy(3,   sw_bg0_Character, BG_VRAM       , 16);// Set BG character
	DmaArrayCopy(3,   sw_bg1_Character, BG_VRAM+0x4000, 16);// Set BG character
	DmaArrayCopy(3,   sw_bg2_Character, BG_VRAM+0x8000, 16);// Set BG character
	DmaArrayCopy(3,   sw_bg3_Character, BG_VRAM+0xc000, 16);// Set BG character
	DmaArrayCopy(3,         sw_bg0_Map, BG_VRAM+0x3800, 16);// Set screen data
	DmaArrayCopy(3,         sw_bg1_Map, BG_VRAM+0x7800, 16);// Set screen data
	DmaArrayCopy(3,         sw_bg2_Map, BG_VRAM+0xb800, 16);// Set screen data
	DmaArrayCopy(3,         sw_bg3_Map, BG_VRAM+0xf800, 16);// Set screen dataSet screen data
	DmaArrayCopy(3,     sw_bg0_Palette, BG_PLTT       , 16);// Set screen data
	
	DmaArrayCopy(3, sw_PS_hey5_Char,    OBJ_MODE0_VRAM, 16);// Set OBJ character
	DmaArrayCopy(3, sw_PS_hey5_Palette, OBJ_PLTT,       16);// Set OBJ palette
	
	for (i=0; i<128; i++) {// Initialize OAM
		sw_OamBak[i] = *(OamData *)sw_OamData_Sample;
		sw_OamBak[i].AffineMode=2;//No display
	}
	DmaArrayCopy(3, sw_OamBak,          OAM,            32);
	
	//OAM set
	//Use 1D mapping for OBJ character
	//Yoshi (32x64) is at the top
	sw_OamBak[0].CharNo = 0;
	sw_OamBak[0].VPos = 100;
	sw_OamBak[0].HPos = 50;
	sw_OamBak[0].Priority = 1;
	sw_OamBak[0].AffineMode = 0;
	sw_OamBak[0].ObjMode = 2;//OBJ window
	
	sw_OamBak[1].CharNo=0;
	sw_OamBak[1].VPos = 96;
	sw_OamBak[1].HPos = 184;
	sw_OamBak[1].Priority = 1;
	sw_OamBak[1].AffineMode = 0;
	
	DmaCopy(3, sw_OamBak, OAM,    (sizeof(OamData)*2), 32);// Set OAM
	
	*(vu16*)REG_WIN0H  = (112<<8)|(160);//Window0 horizontal coordinate
	*(vu16*)REG_WIN0V  = ( 88<<8)|(144);//Window0 vertical coordinate
	*(vu16*)REG_WIN1H  = (176<<8)|(232);//Window1 horizontal coordinate
	*(vu16*)REG_WIN1V  = ( 88<<8)|(144);//Window1 vertical coordinate
	*(vu16*)REG_WININ  = ((WIN_OBJ_ON|WIN_BG3_ON           )<<8)//Display inside Window1
						 |(WIN_OBJ_ON|WIN_BG3_ON|WIN_BG2_ON);//Display inside Window0
	
	*(vu16*)REG_WINOUT = ((WIN_OBJ_ON|WIN_BG3_ON|WIN_BG2_ON|WIN_BG1_ON)<<8)//Display inside Window0

						 |WIN_ALL_ON;//Display outside window
	
	*(vu16 *)REG_IME  = 1;						// Set IME
	*(vu16 *)REG_IE   = V_BLANK_INTR_FLAG;		// Set V blank interrupt flag
	*(vu16 *)REG_STAT = STAT_V_BLANK_IF_ENABLE;
	
	while(1) {
		KeyRead();				// Key operation
		
		sw_ObjMove();
		
		if(Trg & SELECT_BUTTON)return;
		
		V_Wait();
	}
}

//==================================================================
//                  V blank interrupt routine                                                  
//==================================================================
void sw_v_blank_intr(void)
{
	DmaCopy(3, sw_OamBak, OAM,    (sizeof(OamData)*2), 32);// Set OAM
}

//==================================================================
//                  Subroutine                                                 
//==================================================================
//------------------------------------------------------------------
//       OBJ move routine                                                      
//------------------------------------------------------------------
void sw_ObjMove(void)
{
	s16 n;
	//While A button is pressed, OBJ window moves    
	if(Cont & A_BUTTON)n=0;else n=1;
	
	if (Cont & U_KEY) sw_OamBak[n].VPos -= 4;
	if (Cont & D_KEY) sw_OamBak[n].VPos += 4;
	if (Cont & L_KEY) sw_OamBak[n].HPos -= 4;
	if (Cont & R_KEY) sw_OamBak[n].HPos += 4;
	
	if(Trg & START_BUTTON)
		sw_OamBak[1].Priority=(sw_OamBak[1].Priority+1)%4;
}

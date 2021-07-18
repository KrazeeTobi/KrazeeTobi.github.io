//======================================================
//    c_effect.c
//    Color special effects sample
//
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#include <agb.h>
#include "../share.h"

#include "ce_dat.h"

//-------------------- Global variables   ----------------------------
OamData ce_OamBak[128];// OAM backup
s16     ce_EVY_rate,ce_eff_type,ce_EVA_rate,ce_EVB_rate;
u16     ce_BgBak[32*32];// BG  backup
s16     ce_obj_mode;

//---------------------- Subroutines    -----------------------------
void ce_ObjMove(void);
void ce_v_blank_intr(void);
void ce_suji_pr(s16 x,s16 y,s32 suji,s16 keta);
void ce_moji_pr(s16 x,s16 y,char *str);


//==================================================================
//               Main routine                                                                          
//==================================================================
void ceMain(void)
{
	u16 i;
	
	SetVBlankFunc( ce_v_blank_intr );//Set functions called in V Blank
	
	DmaClear(3, 0, VRAM, VRAM_SIZE,		  16);		//   Clear VRAM
	DmaClear(3, 0, OAM,  OAM_SIZE,		  32);		//   Clear OAM
	DmaClear(3, 0, PLTT, PLTT_SIZE,		  16);		//  Clear palette
	
	//Set display control register
	*(vu16 *)REG_DISPCNT = DISP_MODE_0 //BG mode = 0
		| DISP_OBJ_ON | DISP_BG0_ON | DISP_BG1_ON | DISP_BG3_ON //OBJ,BG013 display
		| DISP_WIN0_ON //Use window 0
		| DISP_OBJ_CHAR_1D_MAP; //OBJ character 1D mapping
	

	
	*(vu16 *)REG_BG0CNT = BG_COLOR_256 | BG_SCREEN_SIZE_0 | BG_PRIORITY_1
			| 0 << BG_SCREEN_BASE_SHIFT | 1 << BG_CHAR_BASE_SHIFT ;
	
	*(vu16 *)REG_BG1CNT = BG_COLOR_256 | BG_SCREEN_SIZE_0 | BG_PRIORITY_2
			| 1 << BG_SCREEN_BASE_SHIFT | 2 << BG_CHAR_BASE_SHIFT ;
	
	*(vu16 *)REG_BG3CNT = BG_SCREEN_SIZE_0 | BG_PRIORITY_0
			| 31 << BG_SCREEN_BASE_SHIFT | 3 << BG_CHAR_BASE_SHIFT ;//Use BG3 to display characters

	
	DmaArrayCopy(3, ce_bg1_Character,   BG_VRAM+0x4000, 16);// Set BG character
	DmaArrayCopy(3, ce_bg3_Character,   BG_VRAM+0x8000, 16);// Set BG character
	DmaArrayCopy(3,ce_moji_Character,   BG_VRAM+0xc000, 16);// Set BG character
	DmaArrayCopy(3, ce_bg1_Map,         BG_VRAM,        16);// Set screen data
	DmaArrayCopy(3, ce_bg3_Map,         BG_VRAM+0x800,  16);// Set screen data
	DmaArrayCopy(3, ce_bg1_Palette,     BG_PLTT,        16);// Set BG palette
	
	DmaArrayCopy(3, ce_PS_hey5_Char,    OBJ_MODE0_VRAM, 16);// Set OBJ character
	DmaArrayCopy(3, ce_PS_hey5_Palette, OBJ_PLTT,       16);// Set OBJ palette
	

	
	for (i=0; i<128; i++) {// Initialize OAM
		ce_OamBak[i] = *(OamData *)ce_OamData_Sample;
		ce_OamBak[i].CharNo = 0;
		ce_OamBak[i].AffineMode=2;
	}
	for(i=0;i<32*32;i++)ce_BgBak[i]=0;
	
	//OAM setting (on buffer)
	//Use 1D mapping for OBJ character
	//"Yoshi" (32x64) is at the top
	ce_OamBak[0].VPos=0;
	ce_OamBak[0].HPos=0;
	ce_OamBak[1].VPos=0;
	ce_OamBak[1].HPos=64;
	ce_OamBak[2].VPos=0;
	ce_OamBak[2].HPos=128;
	
	ce_obj_mode=1;
	ce_OamBak[0].ObjMode=ce_obj_mode;
	ce_OamBak[1].ObjMode=ce_obj_mode;
	ce_OamBak[2].ObjMode=ce_obj_mode;
	
	ce_OamBak[0].Priority=1;//
	ce_OamBak[1].Priority=2;//
	ce_OamBak[2].Priority=3;//
	
	ce_OamBak[0].AffineMode=0;
	ce_OamBak[1].AffineMode=0;
	ce_OamBak[2].AffineMode=0;
	
	//Initialize variables
	ce_EVA_rate = 8;//alpha blend coefficient EVA
	ce_EVB_rate = 8;//alpha blend coefficient EVB
	ce_EVY_rate = 8;//  Brightness coefficient EVY
	ce_eff_type = 1;//Special effect type
	
	//Window setting
	*(vu16*)REG_WIN0H  = (100<<8)|(224);//Window 0 left, right coordinates
	*(vu16*)REG_WIN0V  = (100<<8)|(144);//Window 0 up, down coordinates
	*(vu16*)REG_WININ  = (0<<8)//Window 1 inside display
						 |(WIN_OBJ_ON|WIN_BG1_ON);//Window 0 inside display (color special effects OFF)
	*(vu16*)REG_WINOUT = (0<<8)//OBJ window inside display
						 |WIN_ALL_ON;//Window outside display
	
	//Color special effects setting
	//Second pixel, special effects type, first pixel
	*(vu16*)REG_BLDCNT = BLD_BG0_2ND|BLD_BG1_2ND|BLD_OBJ_2ND
		| BLD_A_BLEND_MODE | BLD_BG0_1ST|BLD_BG1_1ST|BLD_OBJ_1ST;//alpha
	*(vu16*)REG_BLDALPHA = (ce_EVB_rate<<8)|ce_EVA_rate;//Coefficient EVB EVA
	*(vu16*)REG_BLDY = ce_EVY_rate;//Coefficient EVY
	
	DmaCopy(3, ce_OamBak, OAM, (sizeof(OamData)*4), 32);// Set OAM
	
	*(vu16 *)REG_IME  = 1;						// Set IME
	*(vu16 *)REG_IE   = V_BLANK_INTR_FLAG;		// Set V Blank interrupt flag
	*(vu16 *)REG_STAT = STAT_V_BLANK_IF_ENABLE;
	
	ce_moji_pr(0,0,"EVA");
	ce_moji_pr(0,1,"EVB");
	ce_moji_pr(0,2,"EVY");
	ce_moji_pr(0,4,"BLEND MODE");
	ce_moji_pr(0,7,"OBJ MODE");
	
	while(1)
	{
		KeyRead();// Read key status (Cont, Trg store values)
		
		ce_ObjMove();//Process according to key
		
		//Display character on screen
		ce_suji_pr(4,0,ce_EVA_rate,2);
		ce_suji_pr(4,1,ce_EVB_rate,2);
		ce_suji_pr(4,2,ce_EVY_rate,2);
		ce_moji_pr(0,5,ce_type_tbl[ce_eff_type]);
		ce_moji_pr(0,8,ce_obj_mode==0? " NORMAL":" ALPHA ");
		
		if(Trg & SELECT_BUTTON)
		{
			*(vu16*)REG_BLDCNT = BLD_NORMAL_MODE;
			return;//to the menu
		}
		V_Wait();
	}
}

//==================================================================
//             V Blank interrupt process                                       
//==================================================================
void ce_v_blank_intr(void)
{
	DmaCopy(3, ce_OamBak, OAM,    (sizeof(OamData)*4), 32);// Set OAM
	DmaArrayCopy(3, ce_BgBak, BG_VRAM+0xf800, 16);//BG screen data set
}

//==================================================================
//                  Subroutines                                                
//==================================================================
//------------------------------------------------------------------
//            OBJ Move routine                                                 
//------------------------------------------------------------------
void ce_ObjMove(void)
{
	s16 num;
	
	if(Cont & A_BUTTON)num=2;//If A button is pressed, OBJ2
	else if(Cont & B_BUTTON)num=1;//If B button is pressed, OBJ1
	else num=0;//If no button is pressed, OBJ0
	
	//Move OBJ
	if(Cont & U_KEY)ce_OamBak[num].VPos -= 4;
	if(Cont & D_KEY)ce_OamBak[num].VPos += 4;
	if(Cont & L_KEY)ce_OamBak[num].HPos -= 4;
	if(Cont & R_KEY)ce_OamBak[num].HPos += 4;
	
	if(Trg & START_BUTTON)
	{
		if(Cont & B_BUTTON)
		{//Switch OBJ semi-transparent/normal
			ce_obj_mode^=1;
			ce_OamBak[0].ObjMode=ce_obj_mode;
			ce_OamBak[1].ObjMode=ce_obj_mode;
			ce_OamBak[2].ObjMode=ce_obj_mode;
		}else
		{//Change blend mode
			ce_eff_type = (ce_eff_type+1)&3;
			switch(ce_eff_type)
			{
			case 0:
				*(vu16*)REG_BLDCNT = BLD_NORMAL_MODE;//Normal
				break;
			case 1:
				*(vu16*)REG_BLDCNT = BLD_BG0_2ND|BLD_BG1_2ND|BLD_OBJ_2ND
									| BLD_A_BLEND_MODE //alpha blend

									| BLD_BG0_1ST|BLD_BG1_1ST|BLD_OBJ_1ST;
				break;
			case 2:
				*(vu16*)REG_BLDCNT = BLD_BG0_2ND|BLD_BG1_2ND|BLD_OBJ_2ND
									| BLD_UP_MODE //brightness up

									| BLD_BG0_1ST|BLD_BG1_1ST|BLD_OBJ_1ST;
				break;
			case 3:
				*(vu16*)REG_BLDCNT = BLD_BG0_2ND|BLD_BG1_2ND|BLD_OBJ_2ND
									| BLD_DOWN_MODE //brightness down
									| BLD_BG0_1ST|BLD_BG1_1ST|BLD_OBJ_1ST;
				break;
			}
		}
	}
	//Chage alpha blend coefficient (EVA,EVB) or brightness change coefficient 
	if(Trg & L_BUTTON)
	{
		if(Cont & B_BUTTON)
		{
			if(ce_EVY_rate > 0)ce_EVY_rate--;
			*(vu16*)REG_BLDY = ce_EVY_rate;//Coefficient EVY
		}else
		{
			if(ce_EVA_rate > 0)ce_EVA_rate--;
			if(ce_EVB_rate < 16)ce_EVB_rate++;
			*(vu16*)REG_BLDALPHA = (ce_EVB_rate<<8) | ce_EVA_rate;//alpha blend coefficient EVB EVA

		}
	}
	if(Trg & R_BUTTON)
	{
		if(Cont & B_BUTTON)
		{
			if(ce_EVY_rate < 16)ce_EVY_rate++;
			*(vu16*)REG_BLDY = ce_EVY_rate;//Coefficient EVY
		}else
		{
			if(ce_EVA_rate < 16)ce_EVA_rate++;
			if(ce_EVB_rate > 0)ce_EVB_rate--;
			*(vu16*)REG_BLDALPHA = (ce_EVB_rate<<8) | ce_EVA_rate;//alpha blend coefficient EVB EVA

		}
	}
}
//------------------------------------------------------------------
//       Character display routine                                             
//------------------------------------------------------------------
void ce_suji_pr(s16 x,s16 y,s32 suji,s16 keta)
{
	u16 *pv;
	s16 i,val;
	
	pv=&ce_BgBak[x+y*32];
	for(i=0;i<keta;i++)
	{
		val = (suji >> (keta-i-1)*4)&0xf;
		*pv = val + 1;
		pv++;
	}
}
//------------------------------------------------------------------
//       Number display routine                                                
//------------------------------------------------------------------
void ce_moji_pr(s16 x,s16 y,char *str)
{
	char *pt;
	u16 *pv;
	pt=str;
	pv=&ce_BgBak[x+y*32];
	while(*pt!=0)
	{
		if(*pt == ' ')
		{
			*pv = 0;
		}else if(*pt<='9')
		{
			*pv = *pt-'0'+1;
		}else
		{
			*pv = *pt-'A'+11;
		}
		pv++;pt++;
	}
}

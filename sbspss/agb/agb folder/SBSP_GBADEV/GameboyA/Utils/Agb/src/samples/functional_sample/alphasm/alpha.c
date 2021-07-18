//======================================================
//    alpha.c
//    Sample of alpha blend 
//
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================
#include <agb.h>
#include "../share.h"

extern const u16 ap_PS_hey5_Palette[256];
extern const u8 ap_PS_hey5_Char[8*8*(32/8/1/1)*(64/8) + 0];
extern const u16 ap_bg0_Palette[5];
extern const u8 ap_bg0_Character[8*8/2*56];
extern const u16 ap_bg0_Map[32*20];
extern const u8 ap_bg1_Character[8*8/2*54];
extern const u16 ap_bg1_Map[32*20];
extern const u8 ap_bg2_Character[8*8/2*54];
extern const u16 ap_bg2_Map[32*20];
extern const u32 ap_moji_Character[8*37];
extern const u32 ap_OamData_Sample[1][2];

//--------------------    Data        ----------------------------
char *ap_eff_tbl[]={"ALPHA    ","ALPHA OBJ","NORMAL2ND","NORMAL   "};


//-------------------- Global variables    ----------------------------
u16     ap_BgBak[32*32];// BG  buffer
OamData ap_OamBak[128]; // OAM buffer
s16     ap_eff_type,ap_obj_alpha,ap_eva,ap_evb;

//---------------------- Subroutine   -----------------------------
void ap_ObjMove(void);
void ap_v_blank_intr(void);
void ap_moji_pr(s16 x,s16 y,char *str);
void ap_suji_pr(s16 x,s16 y,s32 suji,s16 keta);


//==================================================================
//                       Main routine                             
//==================================================================
void apMain(void)
{
	u16 i;
	
	SetVBlankFunc( ap_v_blank_intr );
	
	DmaClear(3, 0,  OAM,     OAM_SIZE       , 32);//    OAM Clear
	
	//Set display control register

	*(vu16 *)REG_DISPCNT = DISP_MODE_0 //BG mode 0
		| DISP_OBJ_ON | DISP_BG0_ON | DISP_BG1_ON | DISP_BG2_ON | DISP_BG3_ON  //OBJ,BG0123 display
		| DISP_OBJ_CHAR_1D_MAP; //OBJ character 1D mapping
	
	//Set BG control register
	*(vu16 *)REG_BG0CNT = BG_SCREEN_SIZE_0 | BG_PRIORITY_0
			| 7  << BG_SCREEN_BASE_SHIFT | 0 << BG_CHAR_BASE_SHIFT ;
	
	*(vu16 *)REG_BG1CNT = BG_SCREEN_SIZE_0 | BG_PRIORITY_1
			| 15 << BG_SCREEN_BASE_SHIFT | 1 << BG_CHAR_BASE_SHIFT ;
	
	*(vu16 *)REG_BG2CNT = BG_SCREEN_SIZE_0 | BG_PRIORITY_2
			| 23 << BG_SCREEN_BASE_SHIFT | 2 << BG_CHAR_BASE_SHIFT ;
	
	*(vu16 *)REG_BG3CNT = BG_SCREEN_SIZE_0 | BG_PRIORITY_3
			| 31 << BG_SCREEN_BASE_SHIFT | 3 << BG_CHAR_BASE_SHIFT ;
	
	DmaArrayCopy(3,   ap_bg0_Character, BG_VRAM       , 16);// Set BG character
	DmaArrayCopy(3,   ap_bg1_Character, BG_VRAM+0x4000, 16);// Set BG character
	DmaArrayCopy(3,   ap_bg2_Character, BG_VRAM+0x8000, 16);// Set BG character
	DmaArrayCopy(3,  ap_moji_Character, BG_VRAM+0xc000, 16);// Set BG character
	DmaArrayCopy(3,         ap_bg0_Map, BG_VRAM+0x3800, 16);// Set screen data
	DmaArrayCopy(3,         ap_bg1_Map, BG_VRAM+0x7800, 16);// Set screen data
	DmaArrayCopy(3,         ap_bg2_Map, BG_VRAM+0xb800, 16);// Set screen data
	DmaArrayCopy(3,     ap_bg0_Palette, BG_PLTT       , 16);// Set BG palette
	
	DmaArrayCopy(3, ap_PS_hey5_Char,    OBJ_MODE0_VRAM, 16);// Set OBJ character
	DmaArrayCopy(3, ap_PS_hey5_Palette, OBJ_PLTT,       16);// Set OBJ palette
	
	for (i=0; i<128; i++) {// Initialize OAM  
		ap_OamBak[i] = *(OamData *)ap_OamData_Sample;
		ap_OamBak[i].AffineMode=2;
	}
	DmaArrayCopy(3, ap_OamBak, OAM, 32);//Set OAM 
	
	for(i=0;i<32*32;i++)ap_BgBak[i]=0;//Clear BG buffer
	
	//Initialize variables
	ap_eva = 8;//EVA
	ap_evb = 8;//EVB
	ap_obj_alpha = 0;//OBJ semi-transparent OFF
	ap_eff_type =0;
	
	//Second pixel, special effect types, first pixel
	*(vu16*)REG_BLDCNT = BLD_BG0_2ND|BLD_BG1_2ND|BLD_BG2_2ND|BLD_OBJ_2ND //Second pixel
		| BLD_A_BLEND_MODE //Alpha blend
		| BLD_BG0_1ST|BLD_BG1_1ST|BLD_BG2_1ST|BLD_OBJ_1ST;//First pixel
	*(vu16*)REG_BLDALPHA = (ap_evb<<8)|ap_eva;//Coefficient EVB EVA
	
	//Set OAM (on the buffer)
	//Use 1 D mapping for OBJ character
	//"Yoshi" (32x64) is at the top

	ap_OamBak[0].CharNo=0;
	ap_OamBak[0].VPos=50;
	ap_OamBak[0].HPos=112;
	ap_OamBak[0].Priority=1;//
	ap_OamBak[0].AffineMode=0;
	ap_OamBak[0].ObjMode=ap_obj_alpha;//
	
	ap_OamBak[1].CharNo=0;
	ap_OamBak[1].VPos=12;
	ap_OamBak[1].HPos=112;
	ap_OamBak[1].Priority=2;
	ap_OamBak[1].AffineMode=0;
	ap_OamBak[1].ObjMode=ap_obj_alpha;
	
	DmaCopy(3, ap_OamBak, OAM, (sizeof(OamData)*2), 32);// Set OAM

	
	*(vu16 *)REG_IME  = 1;						// Set IME
	*(vu16 *)REG_IE   = V_BLANK_INTR_FLAG;		// Set V Blank interrupt flag 
	*(vu16 *)REG_STAT = STAT_V_BLANK_IF_ENABLE;
	
	//Display screen
	ap_moji_pr(0,0,"EVA");
	ap_moji_pr(0,1,"EVB");
	ap_moji_pr(0,3,"BLENDMODE");
	ap_moji_pr(0,6,"OBJ");
	
	while(1)
	{
		KeyRead();// Read key state (values held in Cont, Trg)
		
		ap_ObjMove();//Process according to key
		
		ap_moji_pr(0,4,ap_eff_tbl[ap_eff_type]);//Display special color effect setting 
		ap_moji_pr(0,7,ap_obj_alpha==1?"ALPHA ":"NORMAL");//Display OBJ semi-transparent/noraml 
 
		ap_suji_pr(4,0,ap_eva,2);
		ap_suji_pr(4,1,ap_evb,2);
		
		if(Trg & SELECT_BUTTON)
		{
			*(vu16*)REG_BLDCNT = BLD_NORMAL_MODE;
			return;//To menu
		}
		V_Wait();//Wait for V Blank
	}
}

//==================================================================
//                  V Blank interrupt process                                              
//==================================================================
void ap_v_blank_intr(void)
{
	DmaCopy(3, ap_OamBak, OAM, (sizeof(OamData)*2), 32);		// Set OAM
	DmaArrayCopy(3, ap_BgBak, BG_VRAM+0xf800, 16);
}

//==================================================================
//                  Subroutine                                    
//==================================================================
//------------------------------------------------------------------
//       OBJ move routine                                                                            
//------------------------------------------------------------------
void ap_ObjMove(void)
{
	s16 n;
	//While A_BUTTON is pressed and held, the 0th "Yoshi" moves   
	if(Cont & A_BUTTON)n=0;else n=1;
	if(Cont & U_KEY) ap_OamBak[n].VPos -= 4;
	if(Cont & D_KEY) ap_OamBak[n].VPos += 4;
	if(Cont & L_KEY) ap_OamBak[n].HPos -= 4;
	if(Cont & R_KEY) ap_OamBak[n].HPos += 4;
	
	if(Trg & START_BUTTON)
	{
		if(Cont & B_BUTTON)
		{//Switch OBJ semi-transparent/normal when START button pressed with B button
			ap_obj_alpha^=1;
			ap_OamBak[0].ObjMode=ap_obj_alpha;//
			ap_OamBak[1].ObjMode=ap_obj_alpha;//
		}else
		{//Change color special effect with START button
			ap_eff_type = (ap_eff_type +1)%4;
			switch(ap_eff_type)
			{
			case 0:
				*(vu16*)REG_BLDCNT = BLD_BG0_2ND|BLD_BG1_2ND|BLD_BG2_2ND|BLD_OBJ_2ND //Second pixel
								| BLD_A_BLEND_MODE //alpha blend
								| BLD_BG0_1ST|BLD_BG1_1ST|BLD_BG2_1ST|BLD_OBJ_1ST;//First pixel
				break;
			case 1:
				*(vu16*)REG_BLDCNT = BLD_BG0_2ND|BLD_BG1_2ND|BLD_BG2_2ND|BLD_OBJ_2ND //Second pixel
								| BLD_A_BLEND_MODE //alpha blend
								| BLD_OBJ_1ST;//First pixel, OBJ only

				break;
			case 2://Set only second pixel with normal
				*(vu16*)REG_BLDCNT = BLD_BG0_2ND|BLD_BG1_2ND|BLD_BG2_2ND|BLD_OBJ_2ND //Second pixel
								| BLD_NORMAL_MODE ;//Normal
				break;
			case 3:
				*(vu16*)REG_BLDCNT = BLD_NORMAL_MODE;//Normal
				break;
			}
		}
	}
	//Change coefficient for alpha blending with L-R button 
	if(Trg & L_BUTTON)
	{
		if(ap_eva>0)ap_eva--;
		if(ap_evb<16)ap_evb++;
		*(vu16*)REG_BLDALPHA = (ap_evb<<8)|ap_eva;//Coefficient EVB EVA
	}
	if(Trg & R_BUTTON)
	{
		if(ap_eva<16)ap_eva++;
		if(ap_evb>0)ap_evb--;
		*(vu16*)REG_BLDALPHA = (ap_evb<<8)|ap_eva;//Coefficient EVB EVA
	}
}

//------------------------------------------------------------------
//       Character display routine                                                                          
//------------------------------------------------------------------
void ap_moji_pr(s16 x,s16 y,char *str)
{
	char *pt;
	u16 *pv;
	pt=str;
	pv=&ap_BgBak[x+y*32];
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
//------------------------------------------------------------------
//       Number display routine                                                
//------------------------------------------------------------------
void ap_suji_pr(s16 x,s16 y,s32 suji,s16 keta)
{
	u16 *pv;
	s16 i,val;
	
	pv=&ap_BgBak[x+y*32];
	for(i=0;i<keta;i++)
	{
		val = (suji >> (keta-i-1)*4)&0xf;
		*pv = val + 1;
		pv++;
	}
}

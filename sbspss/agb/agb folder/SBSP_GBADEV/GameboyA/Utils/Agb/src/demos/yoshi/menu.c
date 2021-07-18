//======================================================
//    menu.c
//    Main Routine of Sample Yoshi
//
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

/////////////////////////////////////////////////////////////////////
//includes
#include "agb.h"
#include "yos_main.h"
#include "yos_main.ext"
#include "yos_type.h"
#include "oam_proc.h"
#include "isle_bmp.h"
#include "menu_bmp.h"
#include "menu_dat.h"
#include "yos_main_dat.h"
#include "yos_sound.h"


/////////////////////////////////////////////////////////////////////
//
#define JIMEN_POS (72)
#define SORA_POS (64)
enum
{
	P0_ST_INIT,
	P0_ST_ZOOM_1,
	P0_ST_NORMAL,
	P0_ST_END,
	P0_ST_END_W,
};


/////////////////////////////////////////////////////////////////////
//Local Funtion
static void p0_VIntrFunc(void);
#ifndef USE_HDMA
static void p0_HBlankIntr(void);
#else
static void p0_VCountIntr(void);
#endif
/////////////////////////////////////////////////////////////////////
//Global Variable
s16 p0_isle_frm;
s16 p0_count;

s16 p0_h_org_b[228];//Following LineXMove Initial-Value
s16 p0_h_tmp_b[228];//Following LineXMove Buffer

s16 p0_h_bg2p[256][4];//BG2PA,BG2PB,BG2PC,BG2PD
u8	p0_BgBak[32*32];// BG  backup
s32 p0_hsy_org;


/////////////////////////////////////////////////////////////////////
//
void p0_set_umi_sora(void)
{
	s16 i;
	for(i=64;i<160;i++)
	{
		p0_h_tmp_b[i] = p0_h_org_b[i]+fix_cos[(i+gMain.main_timer)&0xff]/4;
	}
//	p0_h_bg2p[227][3]=(gMain.main_timer&0x1ff)*16;//Set Cloud Scroll 
//	p0_h_bg2p[SORA_POS-1][3]=p0_hsy_org-(gMain.main_timer&0x1ff)*16;
}

/////////////////////////////////////////////////////////////////////
//Main Funtion
void proc_0()
{
	s16 i,j;
	s32 sd,zoom_,zoom;
	s32 scr_h,scr_l;
	
	switch(gMain.main_status)
	{
	case P0_ST_INIT://init
#ifdef BGM_ON
	m4aSongNumStart(YOS_BGM_TITLE);//BGM Start
#endif
		
		*(vu16 *)REG_BG3CNT=BG_PRIORITY_2|BG_COLOR_256|BG_MOS_OFF| BG_SCREEN_SIZE_1 
					| 0 << BG_SCREEN_BASE_SHIFT | 2 << BG_CHAR_BASE_SHIFT ;
		*(vu16 *)REG_BG2CNT=BG_PRIORITY_3|BG_COLOR_256|BG_MOS_OFF|BG_LOOP_ON| BG_SCREEN_SIZE_1 
					| 1 << BG_SCREEN_BASE_SHIFT | 3 << BG_CHAR_BASE_SHIFT ;
//		*(vu16 *)REG_DISPCNT = DISP_BG3_ON | DISP_MODE_2 |DISP_OBJ_CHAR_1D_MAP
		*(vu16 *)REG_DISPCNT = DISP_BG2_ON | DISP_BG3_ON | DISP_MODE_2 |DISP_OBJ_CHAR_1D_MAP
#ifdef USE_HDMA
//					|DISP_OBJ_HOFF
#endif
					;
		
		DmaClear(3, 0, VRAM, VRAM_SIZE,		  16);		//   VRAM Clear
		DmaClear(3, 0, OAM,  OAM_SIZE,		  32);		//    OAM Clear
		
		DmaArrayCopy(3, p0_yoshi_island_Palette, BG_PLTT, 16);	// Set BG Palette
		DmaCopy(3, _binary_umi64_imb_start, BG_VRAM+0xc000,64*64      , 16);	//  Set BG Character
		DmaCopy(3,  _binary_kumo_imb_start, BG_VRAM+0xc000+64*64,32*32, 16);	//  Set BG Character
		DmaCopy(3, _binary_grade_imb_start, BG_VRAM+0xc000+64*64*2,8*8, 16);	//  Set BG Character
		p0_isle_frm = 0;
		
		*(vu16 *)REG_BG2X_L = 0x0;
		*(vu16 *)REG_BG2X_H = 0x0;
		*(vu16 *)REG_BG2Y_L = 0x0;
		*(vu16 *)REG_BG2Y_H = 0x0;

		*(vu16 *)REG_BG2PA = 0x100;
		*(vu16 *)REG_BG2PB = 0;
		*(vu16 *)REG_BG2PC = 0;
		*(vu16 *)REG_BG2PD = 0x100;
		
		*(vu16 *)REG_BG3X_L = 0x0;
		*(vu16 *)REG_BG3X_H = 0x0;
		*(vu16 *)REG_BG3Y_L = 0x0;
		*(vu16 *)REG_BG3Y_H = 0x0;

		*(vu16 *)REG_BG3PA = 0x100;
		*(vu16 *)REG_BG3PB = 0;
		*(vu16 *)REG_BG3PC = 0;
		*(vu16 *)REG_BG3PD = 0x100;
		
		//Ocean
		for(i=0; i<32; i++)
			for(j=0; j<32; j++)p0_BgBak[i*32+j] = (i%8)*8+j%8;
		
		//Sky
		for(i=0; i<8; i++)
			for(j=0; j<32; j++)p0_BgBak[i*32+j] = 64+(i%4)*4+j%4;
		
		//Area between Sky and Ocean
		for(j=0; j<32; j++)p0_BgBak[8*32+j] = 64*2;
		
		DmaArrayCopy(3, p0_BgBak, BG_VRAM+0x800, 16);
		
		for(i=0; i<80; i++)
		{
			p0_h_bg2p[i][0] = 0x100;
			p0_h_bg2p[i][1] = 0;
			p0_h_bg2p[i][2] = 0;
			p0_h_bg2p[i][3] = 0x100;
			p0_h_org_b[i]   = 0;
		}
		
		//Ground Perspective
		for(i=JIMEN_POS,sd=0; i<228; i++)
		{
			s32 _x,_mx,_my,n;
			
			n = -JIMEN_POS+10+i;
			scr_h=100; scr_l=100;
			_x  =  scr_h *0x100 / n;
			_mx = (scr_h *0x100 /(n-1) - scr_h*0x100/n) * 120;
			_my =  scr_h*scr_l*0x100 / n / (n-1);//0x.00
			p0_h_bg2p[i][0] = _x;
			p0_h_bg2p[i][1] = _mx;
			p0_h_bg2p[i][2] = 0;
			p0_h_bg2p[i][3] = _my;
			p0_h_org_b[i]   = _mx;
			sd += p0_h_bg2p[i][3];
			if(sd > (255-JIMEN_POS)<<8)
			{
				p0_h_bg2p[i][3] -= (255-JIMEN_POS)<<8;
				sd -= (255-JIMEN_POS)<<8;
			}
		}
		//Sky Perspective
		for(i=0,sd=0; i<SORA_POS-1; i++)
		{
			s32 _x,_mx,_my,n;
			n = 20+SORA_POS-i;
			scr_h = 100;scr_l=100;
			_x  =  scr_h *0x100 / n;
			_mx = (scr_h *0x100 /(n) - scr_h*0x100/(n-1)) * 120;
			_my =  scr_h*scr_l*0x100 / n / (n-1);//0x.00
			p0_h_bg2p[i][0] = _x;
			p0_h_bg2p[i][1] = _mx;
			p0_h_bg2p[i][2] = 0;
			p0_h_bg2p[i][3] = _my;
			p0_h_org_b[i]   = _mx;
			sd += p0_h_bg2p[i][3];
			while(sd >= 32<<8)
			{
				p0_h_bg2p[i][3] -= 32<<8;
				sd -= 32<<8;
			}
		}

		p0_h_bg2p[SORA_POS-1][0] = 0x100;
		p0_h_bg2p[SORA_POS-1][1] = 0;
		p0_h_bg2p[SORA_POS-1][2] = 0;
		p0_h_bg2p[SORA_POS-1][3] = (SORA_POS-1)*0x100-sd;
		p0_h_org_b[SORA_POS-1]   = 0;
		p0_hsy_org = p0_h_bg2p[SORA_POS-1][3];
		
		p0_h_bg2p[227][0] = 0x100;
		p0_h_bg2p[227][1] = 0;
		p0_h_bg2p[227][2] = 0;
		p0_h_bg2p[227][3] = 0x100;
		p0_h_org_b[227]   = 0;
		
		for(i=0; i<160; i++)
			p0_h_tmp_b[i] = p0_h_org_b[i];
		
		//The Second Pixel, Type of Special Effect, The First Pixel
		*(vu16*)REG_BLDCNT   = BLD_2ND_ALL|BLD_NORMAL_MODE|BLD_ALL;//No Special Effects
		*(vu16*)REG_BLDALPHA = 0x0808;//Coefficient EVB EVA
		*(vu16*)REG_BLDY     = 8;//Coefficient EVY
		
#ifndef USE_HDMA
		IntrTable[1] = p0_HBlankIntr;
		*(vu16 *)REG_IE   |= H_BLANK_INTR_FLAG;
		*(vu16 *)REG_STAT |= STAT_H_BLANK_IF_ENABLE;
#else
		IntrTable[2] = p0_VCountIntr;
		
		*(vu16 *)REG_IE   |= V_COUNT_INTR_FLAG;
		*(vu16 *)REG_STAT |= (0<<STAT_VCOUNT_CMP_SHIFT)|STAT_V_COUNT_IF_ENABLE;
#endif
		p0_count = 0;
		gMain.main_status = P0_ST_ZOOM_1;
		gMain.pVBlankFunc = p0_VIntrFunc;
		break;
	case P0_ST_ZOOM_1:
		p0_count++;
		zoom_ = 0x100+(0x40-p0_count)*0x10;
		zoom  = 0x10000/zoom_;
		*(vu16 *)REG_BG3PA = zoom_;
		*(vu16 *)REG_BG3PB = 0;
		*(vu16 *)REG_BG3PC = 0;
		*(vu16 *)REG_BG3PD = zoom_;
		
		sd = -120*(zoom_)+120*0x100;
		*(vu16 *)REG_BG3X_L = sd&0xffff;
		*(vu16 *)REG_BG3X_H = sd>>16;
		sd = -80*(zoom_)+80*0x100;
		*(vu16 *)REG_BG3Y_L = sd&0xffff;
		*(vu16 *)REG_BG3Y_H = sd>>16;
		
		p0_set_umi_sora();
		
		if(p0_count >= 0x40)
		{
			gMain.main_status = P0_ST_NORMAL;
		}
		break;
	case P0_ST_NORMAL:
		if((gMain.main_timer&3) == 0)p0_isle_frm=(p0_isle_frm+1)%60;
		p0_set_umi_sora();
		if((gMain.Trg & START_BUTTON) != 0)
		{
#ifdef SOUND_ON
			m4aSongNumStart(YOS_SE_START);
#endif
			p0_count = 0;
			gMain.main_status = P0_ST_END;
			*(vu16 *)REG_MOSAIC  = 0;
			*(vu16 *)REG_BG2CNT |= BG_MOS_ON;
			*(vu16 *)REG_BG3CNT |= BG_MOS_ON;
			*(vu16*)REG_BLDY = 0;
			*(vu16*)REG_BLDCNT = BLD_2ND_ALL|BLD_DOWN_MODE|BLD_ALL;//Decrease Brightness
		}
		break;
	case P0_ST_END:
		p0_count++;//1~
		*(vu16*)REG_BLDY  = p0_count>>2;//Increase Brightness Down
		p0_set_umi_sora();
		zoom  = 0x100+0x100*(p0_count)/0x20;
		zoom_ = 0x10000/zoom;
		*(vu16 *)REG_BG3PA = zoom_;
		*(vu16 *)REG_BG3PB = 0;
		*(vu16 *)REG_BG3PC = 0;
		*(vu16 *)REG_BG3PD = zoom_;
		
		sd = -120*(zoom_)+120*0x100;
		*(vu16 *)REG_BG3X_L = sd&0xffff;
		*(vu16 *)REG_BG3X_H = sd>>16;
		sd = -80*(zoom_)+80*0x100;
		*(vu16 *)REG_BG3Y_L = sd&0xffff;
		*(vu16 *)REG_BG3Y_H = sd>>16;
		i = p0_count/5;
		*(vu16 *)REG_MOSAIC = (i<<4)|i;//Add Mosaic 
		if(p0_count > 0x40)
		{
#ifdef BGM_ON
//			MPlayStop(&music);
#endif
#ifndef USE_HDMA
			*(vu16 *)REG_IE   &= ~H_BLANK_INTR_FLAG;
			*(vu16 *)REG_STAT &= ~STAT_H_BLANK_IF_ENABLE;
			IntrTable[1] = IntrDummy;
#else
			*(vu16 *)REG_IE   &= ~V_COUNT_INTR_FLAG;
			*(vu16 *)REG_STAT &= ~STAT_V_COUNT_IF_ENABLE;
			IntrTable[2] = IntrDummy;
#endif
			gMain.pVBlankFunc = 0;
			*(vu16 *)REG_DMA0CNT_H = 0;
			p0_count = 0;
			gMain.main_status = P0_ST_END_W;
		}
		break;
	case P0_ST_END_W:
		p0_count++;//1~
		if(p0_count > 1)
		{
			gMain.proc_num = 1;
			gMain.main_status = 0;
			*(vu16 *)REG_MOSAIC = 0;
			*(vu16 *)REG_BG2CNT &= ~BG_MOS_ON;
			*(vu16 *)REG_BG3CNT &= ~BG_MOS_ON;
			*(vu16 *)REG_DMA0CNT_H = 0;
			
			*(vu16 *)REG_BG2PA = 0x100;
			*(vu16 *)REG_BG2PB = 0;
			*(vu16 *)REG_BG2PC = 0;
			*(vu16 *)REG_BG2PD = 0x100;
			
			*(vu16 *)REG_BG3X_L = 0x0;
			*(vu16 *)REG_BG3X_H = 0x0;
			*(vu16 *)REG_BG3Y_L = 0x0;
			*(vu16 *)REG_BG3Y_H = 0x0;
			
			*(vu16 *)REG_BG3PA = 0x100;
			*(vu16 *)REG_BG3PB = 0;
			*(vu16 *)REG_BG3PC = 0;
			*(vu16 *)REG_BG3PD = 0x100;
		}
		break;
	}
}

////////////////////////////////////////////////////////////////
//Process after V Blank Interrupt
static void p0_VIntrFunc(void)
{
	u16 i;
#ifdef USE_HDMA
	*(vu16 *)REG_DMA0CNT_H = 0;
#endif
	
	DmaCopy(3, p0_isle_tbl[p0_isle_frm], BG_VRAM+0x8000,p0_size_tbl[p0_isle_frm]*64, 16);//  Set BG Character
	for(i=0; i< 20; i++)DmaCopy(3,p0_map_tbl[p0_isle_frm]+i*30,(BG_VRAM+i*32),30,16);
//	for(i=0; i<228; i++)p0_h_bg2p[i][1] = p0_h_tmp_b[i];
	for(i=0; i<160; i++)p0_h_bg2p[i][1] = p0_h_tmp_b[i];
	
//	p0_h_bg2p[227][3] = (gMain.main_timer&0x1ff)*16;//Set Cloud Scroll
	p0_h_bg2p[0][3] = (gMain.main_timer&0x1ff)*16;//Set Cloud Scroll
	p0_h_bg2p[SORA_POS-1][3] = p0_hsy_org-(gMain.main_timer&0x1ff)*16;
}

#ifndef USE_HDMA
/////////////////////////////////////////////////////////////////////
//Process of H Blank Interrupt
static void p0_HBlankIntr(void)
{
	u8 line = *(u8*)REG_VCOUNT;
	u16 *BgParamTmpp  = (u16 *)REG_BG2PA;
	u16 *SrcParamTmpp = (u16 *)p0_h_bg2p[line];
	
	BgParamTmpp[0] = SrcParamTmpp[0];// REG_BG2PA
	BgParamTmpp[1] = SrcParamTmpp[1];// REG_BG2PB
	BgParamTmpp[2] = SrcParamTmpp[2];// REG_BG2PC
	BgParamTmpp[3] = SrcParamTmpp[3];// REG_BG2PD
}
#endif

#ifdef USE_HDMA
/////////////////////////////////////////////////////////////////////
//V Counter Match Interrupt Process
static void p0_VCountIntr(void)
{
	u32 *RegTmpp = (u32 *)REG_DMA0SAD;
	
	*(vu16 *)REG_DMA0CNT_H = 0;  //DMA0 Stop
	
	RegTmpp[0] = (u32)p0_h_bg2p; //REG_DMA0SAD
	RegTmpp[1] = REG_BG2PA;      //REG_DMA0DAD
	RegTmpp[2] = DMA_ENABLE
							| DMA_TIMMING_H_BLANK
							| DMA_16BIT_BUS
							| DMA_CONTINUOUS_ON
							| DMA_SRC_INC
							| DMA_DEST_RELOAD
							| 4; //REG_DMA0CNT
}
#endif

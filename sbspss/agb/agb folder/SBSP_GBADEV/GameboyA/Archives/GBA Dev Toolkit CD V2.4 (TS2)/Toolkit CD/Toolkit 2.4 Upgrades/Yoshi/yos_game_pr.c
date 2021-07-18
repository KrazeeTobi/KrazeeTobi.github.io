//======================================================
//    yos_game_pr.c
//    Sample Yoshi Character Display Routine
//
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#include <Agb.h>
#include "yos_main.h"
#include "yos_main.ext"
#include "yos_type.h"
#include "yos_game.h"
#include "yos_bmp.h"
#include "etc_bmp.h"
#include "oam_proc.h"
#include "yos_anm.h"
#include "yos_game_dat.h"
#include "yos_main_dat.h"
#include "yos_game_sub.h"
#include "yos_game_pr.h"

#include "yos_game.ext"

////////////////////////////////////////////////////////////////////////////
//Display of Yoshi
void p1_yoshiPrint(void)
{
	OamData *pOamDat;
	xyPos zoom;
	AffineParamWork *pAf;
	u8 rot,flip;
	
	pAf = &affineWork[AFN_WORK_YOS];
	
	if((p1_yoshiWork.muteki_timer>0) && (p1_gGame.game_timer&0x8))return;//Blink while invincible
	
	//Check if it is in the screen
	if((p1_yoshiWork.pos.x < -DISP_X-32*0x10000+p1_gGame.disp_x)
	 ||(p1_yoshiWork.pos.x > +DISP_X+32*0x10000+p1_gGame.disp_x)
	 ||(p1_yoshiWork.pos.y < -DISP_Y-64*0x10000+p1_gGame.disp_y)
	 ||(p1_yoshiWork.pos.y > +DISP_Y+64*0x10000+p1_gGame.disp_y))return;//Outside of screen area
	
//	pOamDat=new_OamData(p1_charSpecData[CHR_TYPE_YOSHI].priority);
	pOamDat=new_OamData(3);
	if(pOamDat == 0)return;
	
	zoom.x = (p1_yoshiWork.zoom.x>>8) * (p1_gGame.zoom >>8);
	zoom.y = (p1_yoshiWork.zoom.y>>8) * (p1_gGame.zoom >>8);
	
	*( u32*)pOamDat    = p1_charSpecData[CHR_TYPE_YOSHI].oam01;
	*((u16*)pOamDat+2) = p1_charSpecData[CHR_TYPE_YOSHI].oam2;
	pOamDat->HPos = ((((p1_yoshiWork.pos.x-p1_gGame.disp_x)>>8)*(p1_gGame.zoom>>8)-(16*0x20000)+DISP_X))>>16;
	pOamDat->VPos = ((((p1_yoshiWork.pos.y-p1_gGame.disp_y-p1_tatenobi_tbl[p1_yoshiWork.tatenobi]*32)>>8)*(p1_gGame.zoom>>8)-(32*0x20000)+DISP_Y))>>16;
	//Set affineWork.param
	flip = pAf->Hflip;
	if(anmWork[ANM_WORK_YOSHI].pTbl->dir < 0)flip ^= 1;
	if(p1_yoshiWork.rot != 0)//Rotating
	{
		rot = p1_yoshiWork.rot;
		if(zoom.x == 0)zoom.x = 1;//
		if(zoom.y == 0)zoom.y = 1;
		if(flip == 0)
		{
			pAf->param[0] = fix_cos[rot]*0x10000/(zoom.x);
			pAf->param[1] =-fix_sin[rot]*0x10000/(zoom.x);
			pAf->param[2] = fix_sin[rot]*0x10000/(zoom.y);
			pAf->param[3] = fix_cos[rot]*0x10000/(zoom.y);
		}else
		{
			pAf->param[0] =-fix_cos[rot]*0x10000/(zoom.x);
			pAf->param[1] = fix_sin[rot]*0x10000/(zoom.x);
			pAf->param[2] = fix_sin[rot]*0x10000/(zoom.y);
			pAf->param[3] = fix_cos[rot]*0x10000/(zoom.y);
		}
	}else
	{
		if(zoom.x <= 0x100)zoom.x = 0x100;//
		if(zoom.y <= 0x100)zoom.y = 0x100;
		pAf->param[0] = (flip == 0) ? (0x1000000/zoom.x) : -(0x1000000/zoom.x);
		pAf->param[1] = 0x0;
		pAf->param[2] = 0x0;
		pAf->param[3] = 0x1000000/zoom.y;
	}
}
////////////////////////////////////////////////////////////////////////////
//Shadow
void p1_yoshiKagePrint(void)
{
	s32 mapY,dis,zoom,zoom_;
	OamData *pOamDat;
	zoom_=p1_gGame.zoom>>8;
	mapY = p1_getMap(p1_yoshiWork.pos.x);
	
	dis = mapY - (p1_yoshiWork.pos.y+(p1_yoshiWork.col[1].y<<16));
	if(dis < 0) dis = 0;
	if(dis > (32-2)*0x10000)return;
	zoom = (32*0x10000-dis)/32;
	zoom = (zoom>>8) * (p1_gGame.zoom >>8);
	if(zoom <= 100)return;
	pOamDat = new_OamData(8);
	if(pOamDat == 0)return;
	*( u32*)pOamDat    = p1_charSpecData[CHR_TYPE_KAGE0].oam01|OAM_OBJ_BLEND|(AFN_WORK_KAGE<<OAM_AFFINE_NO_SHIFT);
	*((u16*)pOamDat+2) = p1_charSpecData[CHR_TYPE_KAGE0].oam2;
	pOamDat->HPos = ((((p1_yoshiWork.pos.x-p1_gGame.disp_x             )>>8)*(zoom_)-(8*0x20000)+DISP_X))>>16;
	pOamDat->VPos = ((((mapY-p1_gGame.disp_y-(4<<16))>>8)*(zoom_)-(4*0x20000)+DISP_Y))>>16;
	
	affineWork[AFN_WORK_KAGE].param[0] = 
	affineWork[AFN_WORK_KAGE].param[3] = 0x1000000/zoom;
	affineWork[AFN_WORK_KAGE].param[1] = 0x0;
	affineWork[AFN_WORK_KAGE].param[2] = 0x0;
}

////////////////////////////////////////////////////////////////////////////
//Display of egg
void p1_eggPrint(void)
{
	OamData *pOamDat;
	s32 bias,posx,zoom_,posy;
	s16 i,j;
	
	zoom_ = p1_gGame.zoom>>8;
	
	p1_gGame.egg_bias_count = (p1_gGame.egg_bias_count + 1) % EGG_BIAS_COUNT;
	bias = (fix_sin[p1_gGame.egg_bias_count * 0x80 / EGG_BIAS_COUNT])*EGG_BIAS*0x100;
	
	//Egg
	for(i=0; i<EGG_WORK_MAX; i++)
	{
		switch(p1_eggWork[i].status)
		{
		case EGG_ST_SURI:
			//Disregard with Y Coordinate
			j = (p1_yoshiWork.history_cur + YOS_HISTORY_MAX - (p1_eggWork[i].work0+1)*YOS_EGG_DIFF) % YOS_HISTORY_MAX;
			if(p1_yoshiWork.pos_history[j].y > 0x900)
				posy = (p1_yoshiWork.pos_history[j].y-0x1000)*0x10000-p1_gGame.disp_y;//Floating
			else
				posy = (p1_yoshiWork.pos_history[j].y)*0x10000-p1_gGame.disp_y;//On the ground
			
			if(posy+16<(-80<<16) || posy-16>(80<<16))continue;//Outside of screen area
			
			pOamDat=new_OamData(p1_charSpecData[CHR_TYPE_EGG].priority);
			if(pOamDat == 0)return;
			*( u32*)pOamDat    = p1_charSpecData[CHR_TYPE_EGG].oam01;
			*((u16*)pOamDat+2) = p1_charSpecData[CHR_TYPE_EGG].oam2;
			posx = p1_get_rel_pos(p1_yoshiWork.pos_history[j].x*0x10000);
			pOamDat->HPos = ((posx>>8)*(zoom_)-p1_charSpecData[CHR_TYPE_EGG].mid.x*2+DISP_X)>>16;
			if(p1_yoshiWork.pos_history[j].y > 0x900)
				pOamDat->VPos = ((((p1_yoshiWork.pos_history[j].y-0x1000)*0x10000-p1_gGame.disp_y)>>8)*(zoom_)-p1_charSpecData[CHR_TYPE_EGG].mid.y*2+DISP_Y)>>16;//Floating
			else
				pOamDat->VPos = ((((p1_yoshiWork.pos_history[j].y)*0x10000-p1_gGame.disp_y)>>8)*(zoom_)-p1_charSpecData[CHR_TYPE_EGG].mid.y*2+DISP_Y+bias)>>16;//On the ground
			break;
		case EGG_ST_NORMAL:
			posx=p1_get_rel_pos(p1_eggWork[i].pos.x);
			if(posx < ((-120-8)<<16) || posx>((120+8)<<16))continue;//Limitation of Display area
			if(((p1_eggWork[i].pos.y+(8<<16)-p1_gGame.disp_y)>>8)*(zoom_)<(-80<<16)
			 ||((p1_eggWork[i].pos.y-(8<<16)-p1_gGame.disp_y)>>8)*(zoom_)>( 80<<16))continue;
			pOamDat = new_OamData(p1_charSpecData[CHR_TYPE_EGG].priority);
			if(pOamDat == 0)return;
			*( u32*)pOamDat    = p1_charSpecData[CHR_TYPE_EGG].oam01;
			*((u16*)pOamDat+2) = p1_charSpecData[CHR_TYPE_EGG].oam2;
			pOamDat->HPos = ((           posx              >>8)*(zoom_)-p1_charSpecData[CHR_TYPE_EGG].mid.x*2+DISP_X)>>16;
			pOamDat->VPos = (((p1_eggWork[i].pos.y-p1_gGame.disp_y)>>8)*(zoom_)-p1_charSpecData[CHR_TYPE_EGG].mid.y*2+DISP_Y)>>16;
			break;
		}
	}
}
////////////////////////////////////////////////////////////////////////////
//Display of characters other than Yoshi
//As the whole screen zooms, it is necessary to calculate the display coordinate from the zoom value of screen
//As map is looped, when Yoshi comes to the edge of the map, characters on the opposite edge are also displayed.
void p1_charPrint(void)
{
	OamData *pOamDat;
	xyPos pos;
	s32 zoom_;
	s16 i,j;
	s8 char_type,dir;
	u8 rot;
	
	//Set of Affine Parameter
	//Box's
	rot = affineWork[AFN_WORK_HAKO].rot;
	affineWork[AFN_WORK_HAKO].param[0] =
	affineWork[AFN_WORK_HAKO].param[3] = fix_cos[rot]*0x10000/(p1_gGame.zoom);
	affineWork[AFN_WORK_HAKO].param[2] = fix_sin[rot]*0x10000/(p1_gGame.zoom);
	affineWork[AFN_WORK_HAKO].param[1] =-affineWork[AFN_WORK_HAKO].param[2];
	
	//Flower's
	rot = affineWork[AFN_WORK_HANA].rot;
	affineWork[AFN_WORK_HANA].param[0] =
	affineWork[AFN_WORK_HANA].param[3] = fix_cos[rot]*0x10000/(p1_gGame.zoom);
	affineWork[AFN_WORK_HANA].param[2] = fix_sin[rot]*0x10000/(p1_gGame.zoom);
	affineWork[AFN_WORK_HANA].param[1] =-affineWork[AFN_WORK_HANA].param[2];
	
	//left rotation of thorn
	rot = affineWork[AFN_WORK_TOGE_L].rot;
	affineWork[AFN_WORK_TOGE_L].param[0] =
	affineWork[AFN_WORK_TOGE_L].param[3] = fix_cos[rot]*0x10000/(p1_gGame.zoom);
	affineWork[AFN_WORK_TOGE_L].param[2] = fix_sin[rot]*0x10000/(p1_gGame.zoom);
	affineWork[AFN_WORK_TOGE_L].param[1] =-affineWork[AFN_WORK_TOGE_L].param[2];
	
	//Right rotation of thorn
	rot = affineWork[AFN_WORK_TOGE_R].rot;
	affineWork[AFN_WORK_TOGE_R].param[0] =
	affineWork[AFN_WORK_TOGE_R].param[3] = fix_cos[rot]*0x10000/(p1_gGame.zoom);
	affineWork[AFN_WORK_TOGE_R].param[2] = fix_sin[rot]*0x10000/(p1_gGame.zoom);
	affineWork[AFN_WORK_TOGE_R].param[1] =-affineWork[AFN_WORK_TOGE_R].param[2];
	
	//Balloon's
	zoom_ = (p1_gGame.zoom>>8) * (affineWork[AFN_WORK_BALLOON].zoom.x>>8);
	rot = affineWork[AFN_WORK_BALLOON].rot;
	affineWork[AFN_WORK_BALLOON].param[0] =
	affineWork[AFN_WORK_BALLOON].param[3] = fix_cos[rot]*0x10000/zoom_;
	affineWork[AFN_WORK_BALLOON].param[2] = fix_sin[rot]*0x10000/zoom_;
	affineWork[AFN_WORK_BALLOON].param[1] =-affineWork[AFN_WORK_BALLOON].param[2];
	
	//On Left
	affineWork[AFN_WORK_GL].param[0] =
	affineWork[AFN_WORK_GL].param[3] = 0x1000000/p1_gGame.zoom;
	affineWork[AFN_WORK_GL].param[1] = 0x0;
	affineWork[AFN_WORK_GL].param[2] = 0x0;
	
	//On Right
	affineWork[AFN_WORK_GR].param[1] = 0x0;
	affineWork[AFN_WORK_GR].param[2] = 0x0;
	affineWork[AFN_WORK_GR].param[3] = 0x1000000/p1_gGame.zoom;
	affineWork[AFN_WORK_GR].param[0] =-affineWork[AFN_WORK_GR].param[3];
	
	zoom_ = p1_gGame.zoom>>8;
	for(i=0; i<CHARACTER_WORK_MAX; i++)
	{
		if(p1_charWork[i].status <= 0)continue; //when it is non-active, status==0, so it is disregardedhere
		char_type=p1_charWork[i].char_type;
		
		//Correct to the coordinate that has the center of screen as origin (wrap the opposite edge)
		pos.x = p1_get_rel_pos(p1_charWork[i].pos.x);
		
		//move the display position when the ground shakes
		if(char_type == CHR_TYPE_HEIHO)
		{//Shy guy jumps
			pos.y = p1_charWork[i].pos.y - p1_gGame.disp_y-fix_sin[p1_gGame.gnd_bias_count*0x80/GND_BIAS_FRM]*30*100;
		}else
		{//move normally
			pos.y = p1_charWork[i].pos.y - p1_gGame.disp_y - p1_gGame.gnd_bias;
		}
		
		//Check if it is in valid area
		if( (pos.x+p1_charSpecData[char_type].mid.x*2 < -120*0x10000)
		 || (pos.x-p1_charSpecData[char_type].mid.x*2 >  120*0x10000))continue;
		
//		if( (pos.y+p1_charSpecData[char_type].mid.y*2 < -80*0x10000)
//		 || (pos.y-p1_charSpecData[char_type].mid.y*2 >  80*0x10000))continue;
		if( (((pos.y+p1_charSpecData[char_type].mid.y*2) >>8)*(zoom_) < -80*0x10000)
		 || (((pos.y-p1_charSpecData[char_type].mid.y*2) >>8)*(zoom_) >  80*0x10000))continue;
		//display
		pOamDat = new_OamData(p1_charSpecData[char_type].priority);
		if(pOamDat == 0)return;
		*( u32*)pOamDat    = p1_charSpecData[char_type].oam01;
		*((u16*)pOamDat+2) = p1_charSpecData[char_type].oam2;
		
		if(char_type == CHR_TYPE_HAKO)
		{//box
			if(p1_charWork[i].status == HAKO_ST_ROT)
			{//When head-butted
				pOamDat->HPos = ((((p1_charWork[i].a.x-p1_gGame.disp_x)>>8)*zoom_- p1_charSpecData[char_type].mid.x*2+DISP_X) >> 16);
				pOamDat->VPos = ((((p1_charWork[i].a.y-p1_gGame.disp_y)>>8)*zoom_- p1_charSpecData[char_type].mid.y*2+DISP_Y) >> 16);
			}else
			{
				pOamDat->HPos = (((pos.x>>8) * zoom_- p1_charSpecData[char_type].mid.x*2+DISP_X) >> 16);
				pOamDat->VPos = (((pos.y>>8) * zoom_- p1_charSpecData[char_type].mid.y*2+DISP_Y) >> 16);
			}
		}else
		{//Other than box
			*( u32*)pOamDat &= ~(0x1f<<OAM_AFFINE_NO_SHIFT);
			pOamDat->HPos = (((pos.x>>8) * zoom_- p1_charSpecData[char_type].mid.x*2+DISP_X) >> 16);
			pOamDat->VPos = (((pos.y>>8) * zoom_- p1_charSpecData[char_type].mid.y*2+DISP_Y) >> 16);
			switch(char_type)
			{
			case CHR_TYPE_HEIHO://shy guy
				pOamDat->CharNo = CNUM_HEIHO0+p1_charWork[i].work2*(16*OBJ_COLOR);
				j = AFN_WORK_HEIHO0+p1_charWork[i].work2;
				*( u32*)pOamDat |= j<<OAM_AFFINE_NO_SHIFT;
				dir=((p1_charWork[i].dir<0) ? 0:1);
				if(anmWork[ANM_WORK_HEIHO0+p1_charWork[i].work2].pTbl->dir < 0)dir ^= 1;
				affineWork[j].param[0] = ((dir==0) ? 1:-1)*0x1000000/((p1_charWork[i].a.x>>8)*zoom_);
				affineWork[j].param[1] = 0x0;
				affineWork[j].param[2] = 0x0;
				affineWork[j].param[3] = 0x1000000/((p1_charWork[i].a.y>>8)*zoom_);
				if(p1_charWork[i].status==HEIHO_ST_NORMAL)p1_heiKagePrint(pos,i);//Display shadow
				break;
			case CHR_TYPE_HEIHOL://Large Shy Guy
				pOamDat->CharNo = CNUM_HEIHOL;
				j = AFN_WORK_HEIHOL;
				*( u32*)pOamDat |= j<<OAM_AFFINE_NO_SHIFT;
				dir=((p1_charWork[i].dir<0) ? 0:1);
				if(anmWork[ANM_WORK_HEIHOL].pTbl->dir < 0)dir ^= 1;
				affineWork[j].param[0] = ((dir==0) ? 1:-1)*0x1000000/((p1_charWork[i].a.x>>8)*zoom_);
				affineWork[j].param[1] = 0x0;
				affineWork[j].param[2] = 0x0;
				affineWork[j].param[3] = 0x1000000/((p1_charWork[i].a.y>>8)*zoom_);
				if(p1_charWork[i].status == HEIHO_ST_NORMAL)p1_heiKagePrintL(pos);//Display shadow
				break;
			case CHR_TYPE_BALLOON://Balloon
				*( u32*)pOamDat |= AFN_WORK_BALLOON<<OAM_AFFINE_NO_SHIFT;
				break;
			case CHR_TYPE_BOMB://Bob-omb
				if(p1_charWork[i].dir < 0)
					*( u32*)pOamDat |= AFN_WORK_GL<<OAM_AFFINE_NO_SHIFT;
				else
					*( u32*)pOamDat |= AFN_WORK_GR<<OAM_AFFINE_NO_SHIFT;
				p1_bombKagePrint(pos);//Display shadow
				break;
			case CHR_TYPE_HANA://Flower on the ground (rotates)
				*( u32*)pOamDat |= AFN_WORK_HANA<<OAM_AFFINE_NO_SHIFT;
				break;
			case CHR_TYPE_KOKAMEK0://
				if(p1_charWork[i].dir > 0)//Reversal
					*( u32*)pOamDat |= AFN_WORK_GL<<OAM_AFFINE_NO_SHIFT;
				else
					*( u32*)pOamDat |= AFN_WORK_GR<<OAM_AFFINE_NO_SHIFT;
				break;
			case CHR_TYPE_TOGE://thorn
				if(p1_charWork[i].work1)
				{
					if(p1_charWork[i].dir < 0)
						*( u32*)pOamDat |= AFN_WORK_TOGE_L<<OAM_AFFINE_NO_SHIFT;
					else
						*( u32*)pOamDat |= AFN_WORK_TOGE_R<<OAM_AFFINE_NO_SHIFT;
				}else
				{
//					*( u32*)pOamDat |= AFN_WORK_GR<<OAM_AFFINE_NO_SHIFT;
					*( u32*)pOamDat |= AFN_WORK_HANA<<OAM_AFFINE_NO_SHIFT;
				}
				break;
			default://character that is normally facing either right or left
				if(p1_charWork[i].dir < 0)
					*( u32*)pOamDat |= AFN_WORK_GL<<OAM_AFFINE_NO_SHIFT;
				else
					*( u32*)pOamDat |= AFN_WORK_GR<<OAM_AFFINE_NO_SHIFT;
				break;
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////
//Display of sunflower gauge
void p1_gagePrint(void)
{
	OamData *pOamDat;
	s8 i,anm_ptn;
	
	// Select Animation
	anm_ptn = p1_yoshiWork.egg_num+2;
	if(anm_ptn < 0)anm_ptn = 0;
	else if(anm_ptn > SUN_ANM_SP)anm_ptn = SUN_ANM_SP;
	
	if(gMain.main_status == GMAIN_ST_GAME_OVER0)anm_ptn = SUN_ANM_D;
	if(anmWork[ANM_WORK_SUN].anm_ptn != anm_ptn)
	{
		anmWork[ANM_WORK_SUN].anm_ptn = anm_ptn;
		anmWork[ANM_WORK_SUN].flg = ANM_FLG_NEW;
	}
	//Display
	pOamDat = new_OamData(p1_charSpecData[CHR_TYPE_SUN].priority);
	if(pOamDat == 0)return;
	*( u32*)pOamDat    = p1_charSpecData[CHR_TYPE_SUN].oam01;
	*((u16*)pOamDat+2) = p1_charSpecData[CHR_TYPE_SUN].oam2;
	pOamDat->HPos = 16;
	pOamDat->VPos = 16;
	pOamDat->HFlip = (p1_gGame.game_timer & 0x100)>>8;
	
	anm_ptn = (p1_gGame.game_timer>>3) % 3;
	for(i=0; i<8; i++)
	{
		if(p1_hanabiraWork[i].status <= 0)continue;
		if((p1_hanabiraWork[i].status == HANABIRA_ST_FALL) && (p1_hanabiraWork[i].work1 == 0))//during fall
		{
			pOamDat = new_OamData(PRI_KAGE);//lower part
			if(pOamDat == 0)return;
			*( u32*)pOamDat    = p1_charSpecData[CHR_TYPE_HANABIRA8].oam01|OAM_OBJ_BLEND|((AFN_WORK_HANABIRA0+i)<<OAM_AFFINE_NO_SHIFT)|OAM_AFFINE_NORMAL;
			*((u16*)pOamDat+2) = p1_charSpecData[CHR_TYPE_HANABIRA8].oam2;
			pOamDat->CharNo    = pOamDat->CharNo + (4*OBJ_COLOR)*anm_ptn;
		}else
		{
			pOamDat = new_OamData(PRI_GAGE);//same as gauge
			if(pOamDat == 0)return;
			*( u32*)pOamDat    = p1_charSpecData[CHR_TYPE_HANABIRA0+i].oam01;
			*((u16*)pOamDat+2) = p1_charSpecData[CHR_TYPE_HANABIRA0+i].oam2;
			pOamDat->CharNo    = pOamDat->CharNo + (4*OBJ_COLOR)*anm_ptn;
		}
		
		pOamDat->HPos = p1_hanabiraWork[i].pos.x>>16;
		pOamDat->VPos = p1_hanabiraWork[i].pos.y>>16;
	}
}
////////////////////////////////////////////////////////////////////////////
//Display of Shy Guy's Shadow
void p1_heiKagePrint(xyPos pos,s8 num)
{
	s32 mapY,dis,zoom,zoom_;
	OamData *pOamDat;
	
	zoom_=p1_gGame.zoom>>8;
	mapY = p1_getMap(pos.x+p1_gGame.disp_x);
	
	dis = mapY - (pos.y+p1_gGame.disp_y+(p1_charSpecData[CHR_TYPE_HEIHO].col[1].y<<16));
	if(dis < 0) dis = 0;
	if(dis > (32-2)*0x10000)return;
	zoom = (32*0x10000-dis)/32;
	zoom = (zoom>>8) * (p1_gGame.zoom >>8);
	if(zoom <= 100)return;
	pOamDat = new_OamData(8);
	if(pOamDat == 0)return;
	*( u32*)pOamDat    = p1_charSpecData[CHR_TYPE_KAGE0].oam01|OAM_OBJ_BLEND|(AFN_WORK_HEI_K0<<OAM_AFFINE_NO_SHIFT);
	*((u16*)pOamDat+2) = p1_charSpecData[CHR_TYPE_KAGE0].oam2;
	pOamDat->HPos = ((((pos.x                    )>>8)*(zoom_)-(8*0x20000)+DISP_X))>>16;
	pOamDat->VPos = ((((mapY-p1_gGame.disp_y-(4<<16))>>8)*(zoom_)-(4*0x20000)+DISP_Y))>>16;
	
	affineWork[AFN_WORK_HEI_K0].param[0] = 
	affineWork[AFN_WORK_HEI_K0].param[3] = 0x1000000/zoom;
	affineWork[AFN_WORK_HEI_K0].param[1] = 0x0;
	affineWork[AFN_WORK_HEI_K0].param[2] = 0x0;
}

////////////////////////////////////////////////////////////////////////////
//Display of Large Shy Guy's shadow
void p1_heiKagePrintL(xyPos pos)
{
	OamData *pOamDat;
	pOamDat = new_OamData(8);
	if(pOamDat == 0)return;
	
	*( u32*)pOamDat    = p1_charSpecData[CHR_TYPE_KAGEL].oam01|OAM_OBJ_BLEND;
	*((u16*)pOamDat+2) = p1_charSpecData[CHR_TYPE_KAGEL].oam2;
	pOamDat->HPos = ((((pos.x         )>>8)*(p1_gGame.zoom>>8)-(16*0x20000)+DISP_X))>>16;
	pOamDat->VPos = ((((pos.y+(27<<16))>>8)*(p1_gGame.zoom>>8)-( 4*0x20000)+DISP_Y))>>16;
}

////////////////////////////////////////////////////////////////////////////
//Display of Bob-omb's shadow
void p1_bombKagePrint(xyPos pos)
{
	OamData *pOamDat;
	pOamDat = new_OamData(8);
	if(pOamDat == 0)return;
	
	*( u32*)pOamDat    = p1_charSpecData[CHR_TYPE_KAGE0].oam01|OAM_OBJ_BLEND|(AFN_WORK_GL<<OAM_AFFINE_NO_SHIFT);
	*((u16*)pOamDat+2) = p1_charSpecData[CHR_TYPE_KAGE0].oam2;
	pOamDat->HPos = ((((pos.x         )>>8)*(p1_gGame.zoom>>8)-(8*0x20000)+DISP_X))>>16;
	pOamDat->VPos = ((((pos.y+(14<<16))>>8)*(p1_gGame.zoom>>8)-(4*0x20000)+DISP_Y))>>16;
}
////////////////////////////////////////////////////////////////////////////
//Display of effect
void p1_effectPrint(void)
{
	OamData *pOamDat;
	xyPos pos;
	s32 zoom_;
	s16 i,j,k;
	s16 char_type;
	
	zoom_ = p1_gGame.zoom>>8;
	for(i=0; i<EFF_WORK_MAX; i++)
	{
		if(p1_effWork[i].status == 0)continue;
		switch(p1_effWork[i].eff_type)
		{
		case EFF_TYPE_DASH://Dash Smoke
			pOamDat=new_OamData(1);
			if(pOamDat == 0)return;
			k = (40-p1_effWork[i].time)/5;
			if(k > 7)k = 7;
			char_type = CHR_TYPE_BATABATA;
			*( u32*)pOamDat    = p1_charSpecData[char_type].oam01;
			*((u16*)pOamDat+2) = p1_charSpecData[char_type].oam2|(CNUM_BATABATA0+(OBJ_COLOR*4)*k);
			pos.x = p1_get_rel_pos(p1_effWork[i].pos.x);
			pOamDat->HPos = (((            pos.x              >>8)*zoom_-p1_charSpecData[char_type].mid.x+DISP_X)>>16);
			pOamDat->VPos = ((((p1_effWork[i].pos.y-p1_gGame.disp_y)>>8)*zoom_-p1_charSpecData[char_type].mid.y+DISP_Y)>>16);
			break;
		case EFF_TYPE_SMOKE://Ground Pound Smoke
			pOamDat = new_OamData(1);
			if(pOamDat == 0)return;
			char_type = CHR_TYPE_KURUKEMU;
//			*( u32*)pOamDat    = p1_charSpecData[char_type].oam01;//Opaque
			*( u32*)pOamDat    = p1_charSpecData[char_type].oam01|OAM_OBJ_BLEND;//Semi-transparent
			*((u16*)pOamDat+2) = p1_charSpecData[char_type].oam2;
			pos.x = p1_get_rel_pos(p1_effWork[i].pos.x);
			pOamDat->HPos = (((            pos.x              >>8)*zoom_-p1_charSpecData[char_type].mid.x+DISP_X)>>16);
			pOamDat->VPos = ((((p1_effWork[i].pos.y-p1_gGame.disp_y)>>8)*zoom_-p1_charSpecData[char_type].mid.y+DISP_Y)>>16);
			break;
		case EFF_TYPE_HEIS://Star that comes out when stepping on Shy Guy
			k = (40-p1_effWork[i].time)/5;
			if(k > 7)k = 7;
			char_type = CHR_TYPE_HOSI;
			for(j=0; j<HOSI_MAX; j++)//For the number of stars it has
			{
				pOamDat = new_OamData(1);
				if(pOamDat == 0)return;
				pos.x = p1_effWork[i].pos.x + HOSI_R_*fix_cos[0x100*j/HOSI_MAX]*fix_cos[p1_effWork[i].time];
				pos.y = p1_effWork[i].pos.y + HOSI_R_*fix_sin[0x100*j/HOSI_MAX]*fix_cos[p1_effWork[i].time];
				*( u32*)pOamDat    = p1_charSpecData[char_type].oam01;
				*((u16*)pOamDat+2) = p1_charSpecData[char_type].oam2|(CNUM_HOSI+k*OBJ_COLOR);
				pos.x = p1_get_rel_pos(pos.x);
				pOamDat->HPos = (( pos.x              >>8)*zoom_-p1_charSpecData[char_type].mid.x+DISP_X)>>16;
				pOamDat->VPos = (((pos.y-p1_gGame.disp_y)>>8)*zoom_-p1_charSpecData[char_type].mid.y+DISP_Y)>>16;
			}
			break;
		}
	}
}
////////////////////////////////////////////////////////////////////////////
//Display of Kokamek (when withdraws and taken into castle)
void p1_kokamekPrint(void)
{
	s16 i;
	OamData *pOamDat;
	affineWork[AFN_WORK_KOKAMEK_L].param[0] =
	affineWork[AFN_WORK_KOKAMEK_L].param[3] = 0x1000000/p1_kokamekWork[0].v.x;
	affineWork[AFN_WORK_KOKAMEK_L].param[1] = 0x0;
	affineWork[AFN_WORK_KOKAMEK_L].param[2] = 0x0;
	
	affineWork[AFN_WORK_KOKAMEK_R].param[0] =-0x1000000/p1_kokamekWork[0].v.x;
	affineWork[AFN_WORK_KOKAMEK_R].param[1] = 0x0;
	affineWork[AFN_WORK_KOKAMEK_R].param[2] = 0x0;
	affineWork[AFN_WORK_KOKAMEK_R].param[3] = 0x1000000/p1_kokamekWork[0].v.x;
	
	//Display
	for(i=0; i<4; i++)
	{
		//check of screen area
		if(p1_kokamekWork[i].pos.y-32*0x10000 > p1_gGame.disp_y+DISP_Y)continue;
		if(p1_kokamekWork[i].pos.y+32*0x10000 < p1_gGame.disp_y-DISP_Y)continue;
		
		pOamDat = new_OamData((i<2)?5:1);//Two on the top are over Yoshi
		if(pOamDat == 0)return;
		*( u32*)pOamDat    = p1_charSpecData[p1_kokamekWork[i].char_type].oam01;
		*((u16*)pOamDat+2) = p1_charSpecData[p1_kokamekWork[i].char_type].oam2;
		pOamDat->HPos = ((p1_kokamekWork[i].pos.x-p1_gGame.disp_x)-32*0x10000+DISP_X)>>16;
		pOamDat->VPos = ((p1_kokamekWork[i].pos.y-p1_gGame.disp_y)-32*0x10000+DISP_Y)>>16;
		if(p1_kokamekWork[i].dir < 0)
			*( u32*)pOamDat |= AFN_WORK_KOKAMEK_L<<OAM_AFFINE_NO_SHIFT;
		else
			*( u32*)pOamDat |= AFN_WORK_KOKAMEK_R<<OAM_AFFINE_NO_SHIFT;
	}
}

////////////////////////////////////////////////////////////////////////////
//Display of cloud
void p1_kumoPrint()
{
	OamData *pOamDat;
	pOamDat = new_OamData(PRI_KAGE);
	if(pOamDat == 0)return;
	*( u32*)pOamDat    = p1_charSpecData[CHR_TYPE_KUMO0].oam01|OAM_OBJ_BLEND;
	*((u16*)pOamDat+2) = p1_charSpecData[CHR_TYPE_KUMO0].oam2;
	pOamDat->HPos = p1_gGame.kumo_x>>8;
	pOamDat->VPos = 10;
	
	pOamDat=new_OamData(PRI_KAGE);
	if(pOamDat == 0)return;
	*( u32*)pOamDat    = p1_charSpecData[CHR_TYPE_KUMO1].oam01|OAM_OBJ_BLEND;
	*((u16*)pOamDat+2) = p1_charSpecData[CHR_TYPE_KUMO1].oam2;
	pOamDat->HPos = (p1_gGame.kumo_x>>8)+64;
	pOamDat->VPos = 10;

	pOamDat = new_OamData(PRI_KAGE);
	if(pOamDat == 0)return;
	*( u32*)pOamDat    = p1_charSpecData[CHR_TYPE_KUMO0].oam01|OAM_OBJ_BLEND;
	*((u16*)pOamDat+2) = p1_charSpecData[CHR_TYPE_KUMO0].oam2;
	pOamDat->HPos = (p1_gGame.kumo_x>>8)+40;
	pOamDat->VPos = 96;
	
	pOamDat=new_OamData(PRI_KAGE);
	if(pOamDat == 0)return;
	*( u32*)pOamDat    = p1_charSpecData[CHR_TYPE_KUMO1].oam01|OAM_OBJ_BLEND;
	*((u16*)pOamDat+2) = p1_charSpecData[CHR_TYPE_KUMO1].oam2;
	pOamDat->HPos = (p1_gGame.kumo_x>>8)+64+40;
	pOamDat->VPos = 96;
}
////////////////////////////////////////////////////////////////////////////
//Display of Bat
void p1_koumoriPrint(void)
{
	s8 i;
	OamData *pOamDat;
	
	for(i=0; i<KOUMORI_NUM; i++)
	{
		affineWork[AFN_WORK_KOUMORI0+i].param[0] = 0x1000000/p1_koumoriDat[i][2];
		affineWork[AFN_WORK_KOUMORI0+i].param[1] = 0x0;
		affineWork[AFN_WORK_KOUMORI0+i].param[2] = 0x0;
		if(((gMain.main_timer+i*13)&0x8) > 0)
			affineWork[AFN_WORK_KOUMORI0+i].param[3] = 0x1000000/p1_koumoriDat[i][2];
		else
			affineWork[AFN_WORK_KOUMORI0+i].param[3] =-0x1000000/p1_koumoriDat[i][2];
		
		pOamDat = new_OamData(PRI_OT);
		if(pOamDat == 0)return;
		*( u32*)pOamDat    = p1_charSpecData[CHR_TYPE_KOUMORI].oam01|((AFN_WORK_KOUMORI0+i)<<OAM_AFFINE_NO_SHIFT);
		*((u16*)pOamDat+2) = p1_charSpecData[CHR_TYPE_KOUMORI].oam2;
		pOamDat->HPos  = p1_koumoriDat[i][0];
		pOamDat->VPos  = p1_koumoriDat[i][1];
//		pOamDat->VFlip = ((gMain.main_timer+i*13)&0x8) > 0 ? 1:0 ;
	}
}

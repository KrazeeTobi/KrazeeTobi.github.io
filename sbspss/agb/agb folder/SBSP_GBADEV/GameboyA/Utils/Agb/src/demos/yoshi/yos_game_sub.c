//======================================================
//    yos_game_sub.c
//    Sample Yoshi Miscellaneous Sub-Routine
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
#include "yos_main_dat.h"
#include "yos_anm.h"
#include "yos_game_dat.h"
#include "yos_game_sub.h"
#include "yos_game.ext"

#include "yos_sound.h"

////////////////////////////////////////////////////////////////////////////
//Affine Parameter Work Initialization 
void p1_workInit0(void)
{
	u32 rot;
	s16 i;
	p1_affineWorkInit0();//Affine Parameter Work Initialization
	
	p1_charWorkInit0();//Create Characters in character work
	
	p1_gGame.disp_x = 0;//Position of screen at the time of start
	p1_gGame.disp_y = DISP_Y;
	p1_gGame.zoom   = ZOOM_1;//Set the zoom of screen to x1
	
	p1_gGame.siro_flg=-1;
	
	//Initialization of Yoshi
	p1_yoshiWork.col[0]  = p1_charSpecData[0].col[0];
	p1_yoshiWork.col[1]  = p1_charSpecData[0].col[1];
	p1_yoshiWork.mid     = p1_charSpecData[0].mid;
	p1_yoshiWork.egg_num = EGG_WORK_MAX;//Number of eggs
	
	//Initialization of Animation Work
	for(i=0; i<ANM_WORK_G_MAX; i++)
	{
		anmWork[i].flg     = -1;
		anmWork[i].pTbl    = 0;
		anmWork[i].anm_ptn = 0;
		anmWork[i].pPixTbl = p1_anmInfo_def[i].pPixTbl;
		anmWork[i].ppTbl   = p1_anmInfo_def[i].ppTbl;
		anmWork[i].chr     = p1_anmInfo_def[i].chr;
		anmWork[i].size    = p1_anmInfo_def[i].size;
	}

	//Initialization of Eggs
	for(i=0; i<EGG_WORK_MAX; i++)
	{
		p1_eggWork[i].status = EGG_ST_SURI;//
		p1_eggWork[i].work0  = i;//The numbers Yoshi has
	}
	
	//Initialization of petals
	for(i=0; i<HANABIRA_MAX; i++)
	{
		p1_hanabiraWork[i].status=1;
		p1_hanabiraWork[i].work0=0;
		p1_hanabiraWork[i].v.y=0;
		p1_hanabiraWork[i].pos=p1_hanabira_pos[i];
		
		rot = p1_hanabira_rot_tbl[i] & 0xff;
		affineWork[AFN_WORK_HANABIRA0+i].param[0] =
		affineWork[AFN_WORK_HANABIRA0+i].param[3] = fix_cos[rot];
		affineWork[AFN_WORK_HANABIRA0+i].param[1] =-fix_sin[rot];
		affineWork[AFN_WORK_HANABIRA0+i].param[2] = fix_sin[rot];
	}
}

////////////////////////////////////////////////////////////////////////////
//Affine Parameter Work Initialization
void p1_affineWorkInit0(void)
{
	s16 i;
	
	for(i=0; i<32; i++)
	{
		affineWork[i].param[0] = 0x100;
		affineWork[i].param[1] = 0x0;
		affineWork[i].param[2] = 0x0;
		affineWork[i].param[3] = 0x100;
		affineWork[i].rot      = 0;
		affineWork[i].Hflip    = 0;
		affineWork[i].zoom.x   = 0x10000;
		affineWork[i].zoom.y   = 0x10000;
	}
}
////////////////////////////////////////////////////////////////////////////
//Compose Characters on Character work
void p1_charWorkInit0(void)
{
	s16 i;
	
	for(i=0; i<CHARACTER_WORK_MAX; i++)p1_charWork[i].status = -1;//Clear Character work
	//Create Characters in character work
	for(i=0; i<CHARACTER_WORK_MAX; i++)
	{
		if(p1_charMapData[i].char_type == -1)break;//Complete
		p1_charWork[i].status    = p1_charMapData[i].status;
		p1_charWork[i].pos.x     = p1_charMapData[i].start_pos.x<<16;
		p1_charWork[i].pos.y     = p1_charMapData[i].start_pos.y<<16;
		p1_charWork[i].v.x       = 0;
		p1_charWork[i].v.y       = 0;
		p1_charWork[i].char_type = p1_charMapData[i].char_type;
		p1_charWork[i].dir       = CHR_DIR_L;
		p1_charWork[i].hit_flg   = p1_charSpecData[p1_charWork[i].char_type].hit_flg;
		p1_charWork[i].work0     = p1_charMapData[i].dat0;
		p1_charWork[i].work1     = p1_charMapData[i].dat1;
		p1_charWork[i].work2     = p1_charMapData[i].dat2;
		p1_charWork[i].work3     = p1_charMapData[i].dat3;
		p1_charWork[i].work4     = 0;
	}
}

////////////////////////////////////////////////////////////////////////////
//Check to see if Yoshi hits (when moving sideways)
//It does not get on while moving sideways
s16 p1_yos_hit_yoko(xyPos pos_old,s16 *chr_num)
{
	s8 hit;
	xyPos yos_col[2],teki_col[2],pos;
	s16 i;
	u8 char_type;
	
	hit=0;
	yos_col[0].x = p1_yoshiWork.pos.x + ((s32)p1_yoshiWork.col[0].x<<16);
	yos_col[0].y = p1_yoshiWork.pos.y + ((s32)p1_yoshiWork.col[0].y<<16);
	yos_col[1].x = p1_yoshiWork.pos.x + ((s32)p1_yoshiWork.col[1].x<<16);
	yos_col[1].y = p1_yoshiWork.pos.y + ((s32)p1_yoshiWork.col[1].y<<16);
	
	for(i=0; i<CHARACTER_WORK_MAX; i++)
	{
		//Is it a character that hits?
		if(p1_charWork[i].status <= 0)continue;//None or non-active
		char_type = p1_charWork[i].char_type;
		if(!(p1_charWork[i].hit_flg & (HIT_LR)))continue;//character that doesn't hit
//		if((p1_charSpecData[char_type].hit_flg & HIT_YLR) && p1_yoshiWork.muteki_timer>0)continue;//It does not hit when invincible
		if((p1_charWork[i].hit_flg & HIT_YLR) && p1_yoshiWork.muteki_timer>0)continue;//It does not hit when invincible
		if((char_type == CHR_TYPE_5T) && p1_yoshiWork.muteki_timer>0)continue;//It does not hit when invincible
		//Check screen area
//		pos.x = get_rel_pos(p1_charWork[i].pos.x)+p1_gGame.disp_x;
		pos.x = p1_get_lap_pos(p1_charWork[i].pos.x);
		
		teki_col[0].x =             pos.x + ((s32)p1_charSpecData[char_type].col[0].x<<16);
		teki_col[0].y = p1_charWork[i].pos.y + ((s32)p1_charSpecData[char_type].col[0].y<<16);
		teki_col[1].x =             pos.x + ((s32)p1_charSpecData[char_type].col[1].x<<16);
		teki_col[1].y = p1_charWork[i].pos.y + ((s32)p1_charSpecData[char_type].col[1].y<<16);
		if( (teki_col[0].x < yos_col[1].x) && (teki_col[1].x > yos_col[0].x) &&
			(teki_col[0].y < yos_col[1].y) && (teki_col[1].y > yos_col[0].y) )
		{//hit
			if(i == p1_yoshiWork.on_old)continue;//it does not hit the character it is on
			*chr_num = i;
			hit=1;
//			return 1;//It returns if it hits even one
			if(p1_charWork[i].hit_flg & HIT_YLR)
			{
				if(char_type == CHR_TYPE_HEIHO)
				{
					//check to see if it is coming from above
					if(p1_charWork[i].pos.y>p1_yoshiWork.pos.y+(16<<16) && p1_yoshiWork.status==YOSHI_ST_JUMPING)
					{//from the top
						p1_charWork[i].status = HEIHO_ST_DYING;//Kill Shy Guy
						p1_charWork[i].work4  = 0;//timer
						p1_charWork[i].hit_flg =0;//It does not hit when it dies
						p1_effectSet(EFF_TYPE_HEIS,p1_charWork[i].pos,0);
						if(p1_yoshiWork.status == YOSHI_ST_KURURIN )
						{
							p1_yoshiWork.kururin_se = 0;
#ifdef SOUND_ON
							m4aSongNumStart(YOS_SE_HA);//"Hah!"
#endif
							continue;//If Ground Pound can go through
						}else
						{
#ifdef SOUND_ON
							m4aSongNumStart(YOS_SE_PAKON);
#endif
							p1_yoshi_jump_set(YOSHI_HANE_SPEED_U);
							return 1;
						}
						return 1;
					}
				}
				
				p1_yoshi_dead_set();
				p1_yoshiWork.rot = 0;
				return 5;//Death
			}else if(p1_charWork[i].hit_flg & HIT_LR)
			{
				if(char_type == CHR_TYPE_BALLOON)
				{
					if(pos.x < p1_yoshiWork.pos.x)
					{
						p1_charWork[i].v.x = -BALLOON_HANE_SPEED;
						p1_yoshiWork.v.x =  YOSHI_HANE_SPEED_LR;
					}else
					{
						p1_charWork[i].v.x =  BALLOON_HANE_SPEED;
						p1_yoshiWork.v.x = -YOSHI_HANE_SPEED_LR;
					}
				}
			}
		}
	}
	return hit;
}
////////////////////////////////////////////////////////////////////////////
//Check to see if Yoshi hits (while moving vertically)
s16 p1_yos_hit_tate(xyPos pos_old,s16 *chr_num)
{
	s8 hit_flg;
	xyPos yos_col[2],teki_col[2],pos;
	s16 i;
	u8 rot,rotr,char_type;
	
	hit_flg = 0;
	yos_col[0].x = p1_yoshiWork.pos.x + ((s32)p1_yoshiWork.col[0].x<<16);
	yos_col[0].y = p1_yoshiWork.pos.y + ((s32)p1_yoshiWork.col[0].y<<16);
	yos_col[1].x = p1_yoshiWork.pos.x + ((s32)p1_yoshiWork.col[1].x<<16);
	yos_col[1].y = p1_yoshiWork.pos.y + ((s32)p1_yoshiWork.col[1].y<<16);
	
	for(i=0; i<CHARACTER_WORK_MAX; i++)
	{
		if(p1_charWork[i].status <= 0)continue;//None or non-active
		//is it a character that hits?
		char_type = p1_charWork[i].char_type;
		if(!(p1_charWork[i].hit_flg & (HIT_T | HIT_B)))continue;//character that does not hit
		
		pos.x = p1_get_lap_pos(p1_charWork[i].pos.x);
		pos.y = p1_charWork[i].pos.y;
		
		teki_col[0].x = pos.x + ((s32)p1_charSpecData[char_type].col[0].x<<16);
		teki_col[0].y = pos.y + ((s32)p1_charSpecData[char_type].col[0].y<<16);
		teki_col[1].x = pos.x + ((s32)p1_charSpecData[char_type].col[1].x<<16);
		teki_col[1].y = pos.y + ((s32)p1_charSpecData[char_type].col[1].y<<16);
		
		//decide large area
		
		if(char_type ==CHR_TYPE_HAKO)
		{//box
			xyPos post,pos_foot;
			
			if(i == p1_yoshiWork.on_old)continue;//it does not hit the character it is on
			
			rot  = p1_charWork[i].rot;//Rotation angle of the character it is riding
			rotr = (0x100-rot)&0xff;
			
			//evaluation of area
			if( (pos.x + ((s32)p1_charSpecData[char_type].col[0].x<<16) < yos_col[1].x) &&
				(pos.x + ((s32)p1_charSpecData[char_type].col[1].x<<16) > yos_col[0].x) &&
				(pos.y + ((s32)p1_charSpecData[char_type].col[0].y<<16) < yos_col[1].y) &&
				(pos.y + ((s32)p1_charSpecData[char_type].col[1].y<<16) > yos_col[0].y)    )
			{//Hit
				hit_flg=1;
				*chr_num = i;
				//evaluate whether if it overlaps from above
				if( p1_yoshiWork.pos.y - pos_old.y > 0 
				 && p1_yoshiWork.pos.y < p1_charWork[i].pos.y)//From above
				{//gets on it as it is from above
					hit_flg=3;//from above
					p1_yoshiWork.status = YOSHI_ST_MOUNT;
					p1_yoshiWork.on=i;//character it is riding
#ifdef SOUND_ON
					m4aSongNumStart(YOS_SE_JMPST);
#endif
					
					//Rotating the position of feet
					post.x = p1_yoshiWork.pos.x                              -p1_charWork[i].pos.x;//Find the coordinate that has the center of rotation as origin
					post.y = p1_yoshiWork.pos.y+((s32)p1_yoshiWork.col[1].y<<16)-p1_charWork[i].pos.y;
					pos_foot.x =( fix_cos[rotr]*post.x + fix_sin[rotr]*post.y)>>8;//Reversal rotation
					pos_foot.y =(-fix_sin[rotr]*post.x + fix_cos[rotr]*post.y)>>8;
					
					//Use X on Rotational coordinate of the location
					p1_yoshiWork.posOn.x = pos_foot.x;
					p1_yoshiWork.posOn.y = (-(s32)p1_yoshiWork.col[1].y<<16)+((s32)p1_charSpecData[char_type].col[0].y<<16);//(Center of Yoshi<->Feet)+(Center of Box<->Top)
					
					p1_yoshiWork.pos.x = (( fix_cos[rot]*p1_yoshiWork.posOn.x + fix_sin[rot]*p1_yoshiWork.posOn.y)>>8)+p1_charWork[i].pos.x;
					p1_yoshiWork.pos.y = ((-fix_sin[rot]*p1_yoshiWork.posOn.x + fix_cos[rot]*p1_yoshiWork.posOn.y)>>8)+p1_charWork[i].pos.y;
				}else if( p1_yoshiWork.pos.y - pos_old.y < 0 //Moving upwards
				 && p1_yoshiWork.pos.y > p1_charWork[i].pos.y)//Center is at the bottom
				{//push up as it is from bottom
					if(p1_charWork[i].status == HAKO_ST_NORMAL)//when it is normal
					{
#ifdef SOUND_ON
						m4aSongNumStart(YOS_SE_GAONN);
#endif
						p1_charWork[i].status=HAKO_ST_ROT;
						p1_charWork[i].work0=0;
						p1_charWork[i].a.x = p1_charWork[i].pos.x;
						p1_charWork[i].a.y = p1_charWork[i].pos.y;
						if(p1_charWork[i].pos.x < p1_yoshiWork.pos.x)
							p1_charWork[i].work1=-1;//from left
						else
							p1_charWork[i].work1= 1;//from right
						
						p1_yoshiWork.v.y = YOSHI_HANE_SPEED_D;//Rising speed of Yoshi
						p1_yoshiWork.jump_timer = 0;
						p1_yoshiWork.funbari_timer = 0;
					}
				}
				return hit_flg;
			}//hit
		}else
		{//normal character that does not rotate
			if(i == p1_yoshiWork.on)continue;//it does not hit the character that is currently riding
			if( (teki_col[0].x < yos_col[1].x) &&
				(teki_col[1].x > yos_col[0].x) &&
				(teki_col[0].y < yos_col[1].y) &&
				(teki_col[1].y > yos_col[0].y)    )
			{//hit
				if(	  (pos_old.y+(p1_yoshiWork.col[1].y<<16) <= teki_col[0].y+8 )
					||(p1_yoshiWork.status == YOSHI_ST_KURURIN)//From above at the time of KURURINHA
					)hit_flg=3;//from above
				else hit_flg=1;
				
				//Ride or Kick
				if(hit_flg == 3)
				{//it is hit from above
					if(!(p1_charWork[i].hit_flg & HIT_T))continue;//the type that does not get hit from above
					
					*chr_num = i;
					switch(char_type)
					{
					case CHR_TYPE_BOMB:
						if(p1_charWork[i].status != CHAR_ST_NORMAL)continue;//it does not hit
						p1_charWork[i].hit_flg =0;//it does not get hit when it dies
						p1_charWork[i].status = BOMB_ST_DYING;//Kill the killer
						p1_charWork[i].work4  = 0;//timer
						p1_effectSet(EFF_TYPE_HEIS,p1_charWork[i].pos,0);
						if(p1_yoshiWork.status == YOSHI_ST_KURURIN )
						{
							p1_yoshiWork.kururin_se = 0;
#ifdef SOUND_ON
							m4aSongNumStart(YOS_SE_HA);
#endif
							continue;//If Ground Pound can go through
						}else
						{
#ifdef SOUND_ON
							m4aSongNumStart(YOS_SE_PAKON);
#endif
							p1_yoshi_jump_set(YOSHI_HANE_SPEED_U);
							return hit_flg;
						}
						break;
#if 1
					case CHR_TYPE_5T:
						p1_yoshi_jump_set(YOSHI_HANE_SPEED_U);//Jump
						hit_flg=4;
						return hit_flg;
						break;
#endif
					case CHR_TYPE_BALLOON:
						if(p1_yoshiWork.status == YOSHI_ST_KURURIN )
						{//Ground Pound can break
							p1_yoshiWork.kururin_se = 0;
#ifdef SOUND_ON
							m4aSongNumStart(YOS_SE_WARE);
#endif
							p1_charWork[i].status  = BALLOON_ST_HARETU;//
							p1_charWork[i].hit_flg = 0;//It does not get hit when it dies
							p1_charWork[i].work0   = 0;//timer
							p1_effectSet(EFF_TYPE_HEIS,p1_charWork[i].pos,0);
							p1_yoshi_jump_set(YOSHI_HANE_SPEED_U);
							return hit_flg;
						}else
						{//Normal jump does not break it and it flips
#ifdef SOUND_ON
							m4aSongNumStart(YOS_SE_ATAR);
#endif
							p1_charWork[i].v.y = BALLOON_HANE_SPEED;
							p1_yoshi_jump_set(YOSHI_HANE_SPEED_U);
							return hit_flg;
						}
						break;
					case CHR_TYPE_HEIHO:
					case CHR_TYPE_HEIHOL:
						if(p1_charWork[i].status != HEIHO_ST_NORMAL)continue;//it does not hit
						p1_charWork[i].status = HEIHO_ST_DYING;//Kill shy guy
						p1_charWork[i].hit_flg =0;//it does not get hit when it dies
						p1_charWork[i].work4  = 0;//timer
						p1_effectSet(EFF_TYPE_HEIS,p1_charWork[i].pos,0);
#ifdef SOUND_ON
						if(p1_yoshiWork.status == YOSHI_ST_KURURIN)
							p1_yoshiWork.kururin_se = 0;
						if(char_type == CHR_TYPE_HEIHO)
						{
							if(p1_yoshiWork.status == YOSHI_ST_KURURIN)
								m4aSongNumStart(YOS_SE_HA);//"Hah!"
							else
								m4aSongNumStart(YOS_SE_PAKON);
						}else
						{//Large shy guy
							m4aSongNumStart(YOS_SE_KAITN);
						}
#endif
						if(p1_yoshiWork.status == YOSHI_ST_KURURIN && char_type == CHR_TYPE_HEIHO)
						{
							continue;//Ground Pound can go through
						}else
						{
							p1_yoshi_jump_set(YOSHI_HANE_SPEED_U);
							return hit_flg;
						}
						break;
					case CHR_TYPE_KILLER_S:
						if(p1_charWork[i].status != KILLERS_ST_NORMAL)continue;//It does not get hit
						p1_charWork[i].hit_flg =0;//It does not get hit when it dies
						p1_charWork[i].status = KILLERS_ST_DYING;//Kill the killer
						p1_charWork[i].work0  = 0;//timer
						p1_effectSet(EFF_TYPE_HEIS,p1_charWork[i].pos,0);
#ifdef SOUND_ON
						m4aSongNumStart(YOS_SE_SID2);
#endif
						if(p1_yoshiWork.status == YOSHI_ST_KURURIN )
						{
							p1_yoshiWork.kururin_se = 0;
#ifdef SOUND_ON
							m4aSongNumStart(YOS_SE_HA);//"Hah!"
#endif
							continue;//If Ground Pound can go through
						}else
						{
							p1_yoshi_jump_set(YOSHI_HANE_SPEED_U);
#ifdef SOUND_ON
							m4aSongNumStart(YOS_SE_PAKON);
#endif
							return hit_flg;
						}
						break;
					default:
						//Get on
#ifdef SOUND_ON
						m4aSongNumStart(YOS_SE_JMPST);
#endif
						p1_yoshiWork.pos.y = p1_charWork[i].pos.y+((s32)p1_charSpecData[char_type].col[0].y<<16)
									-((s32)p1_yoshiWork.col[1].y<<16);//Get on
						p1_yoshiWork.status = YOSHI_ST_MOUNT;
						p1_yoshiWork.on=i;//Character that is on
						return hit_flg;
						//break;
					}
				}else
				{//Get hit from underneath
					if(!(p1_charWork[i].hit_flg & HIT_B))continue;//Type that does not get hit from underneath
					if((p1_charWork[i].hit_flg & HIT_YLR) && p1_yoshiWork.muteki_timer>0)continue;//It does not get hit because invincible
					
					if(char_type == CHR_TYPE_BALLOON)
					{
						p1_charWork[i].v.y =-BALLOON_HANE_SPEED;
						
						p1_yoshiWork.v.y = YOSHI_HANE_SPEED_D;//rising speed of yoshi
						p1_yoshiWork.jump_timer = 0;
						p1_yoshiWork.funbari_timer = 0;
					}else if(p1_charWork[i].hit_flg & HIT_D_H)
					{
						p1_yoshiWork.v.y = YOSHI_HANE_SPEED_D;//Rising Speed of Yoshi
						p1_yoshiWork.jump_timer = 0;
						p1_yoshiWork.funbari_timer = 0;
					}
					*chr_num = i;
					return hit_flg;
				}
			}
		}
	}
	*chr_num = -1;
	return 0;
}
////////////////////////////////////////////////////////////////////////////
//Cross check of the ground
s8 p1_jimen_cross_chk_yoko(xyPos p0, xyPos p1)
{
	p0.y += ((s32)p1_yoshiWork.col[1].y << 16);
	p1.y += ((s32)p1_yoshiWork.col[1].y << 16);
	return p1_jimen_cross_chk(p0,p1);
}
////////////////////////////////////////////////////////////////////////////
//Cross check of the ground
s8 p1_jimen_cross_chk(xyPos p0, xyPos p1)
{
	xyPos xy0;
	xyPos xy1;
	const xyPos *pMap;
	s8 rval;
	
	pMap=p1_mapALine;
	xy0.x = (pMap->x)<<16;
	xy0.y = (pMap->y)<<16;
	pMap++;
	while(1)
	{
		xy1.x = (pMap->x)<<16;
		xy1.y = (pMap->y)<<16;
		if(p0.x != p1.x)
		{
			rval = p1_line_cross_chk_yoko(p0,p1,xy0,xy1);//Horizontal Direction
			if(rval !=0)return 1;
		}
		rval = p1_line_cross_chk_tate(p0,p1,xy0,xy1);//Vertical direction
		if(rval !=0)return 1;
		pMap++;
		if(pMap->x == -1)break;//end
		xy0 = xy1;
	}
	return 0;
}
////////////////////////////////////////////////////////////////////////////
//Cross check of half line (exclusively used for vertical move)
// (p0-p1)  (p2-p3)
// (p0-p1)is near as it is a moving line
// Return Value: 0 if not crossing
//       1 if crossing
// Suppose (p0-p1) is same as X coordinate and disregard p1.x --> vertical line
s8 p1_line_cross_chk_tate(xyPos p0, xyPos p1, xyPos p2, xyPos p3)
{
	s32 dx0,dy0,t;
	
	//disregard the ones without hope
	if( (p0.x<p2.x && p0.x<p3.x)
	  ||(p0.x>p2.x && p0.x>p3.x))return 0;
	if(p0.y<p1.y)
	{
		if(p2.y<p3.y)
		{
			if(p1.y<p2.y)return 0;
		}else if(p1.y<p3.y)return 0;
	}else
	{
		if(p2.y<p3.y)
		{
			if(p0.y<p2.y)return 0;
		}else if(p0.y<p3.y)return 0;
	}
	
	if(p2.x == p3.x)return 0;//it does not cross vertical line
	
	if(p2.y == p3.y)
	{//horizontal line
		if((p0.y<p2.y && p1.y<p2.y)
		 ||(p0.y>p2.y && p1.y>p2.y))return 0;
		
		if((p0.x >= p2.x && p0.x <= p3.x)
		 ||(p0.x <= p2.x && p0.x >= p3.x))return 1;
		return 0;
	}else
	{//Diagonal line
		dx0 = p3.x - p2.x;
		dy0 = p3.y - p2.y;
		
		if((dx0>>8)==0)
			t = (dy0/0x100) * ((p0.x - p2.x)/0x100) / (dx0)+ p2.y;
		else
			t = (dy0/0x100) * ((p0.x - p2.x)/0x100)*0x100 / (dx0/0x100)+ p2.y;
		if( (t<p0.y && t<p1.y) || (t>p0.y && t>p1.y))return 0;//not crossing
		return 1;
	}
	return 0;//decoration
}

////////////////////////////////////////////////////////////////////////////
//Find Y Coordinate of Map from X Coordinate
u32 p1_getMap(long posx)
{
	xyPos xy0;
	xyPos xy1;
	long posy;
	const xyPos *pMap;
	pMap=p1_mapALine;
	xy0.x=0;
	xy0.y=0;
	while(1)
	{
		if((pMap->x << 16) == posx)
		{
			posy = pMap->y<<16;
			if(((pMap+1)->x << 16) == posx)
			{
				if(((pMap+1)->y<<16)<posy)return (pMap+1)->y<<16;
//				else return posy;
			}
			return posy;
		}
		if((pMap->x << 16) > posx)break;
		xy0 = *pMap;
		pMap++;
		if(pMap->x == -1)break;//No good
	}
	xy1=*pMap;
	posy=xy0.y + (xy1.y-xy0.y)*((posx>>16)-xy0.x)/(xy1.x-xy0.x);
	return posy<<16;
}

////////////////////////////////////////////////////////////////////////////
//Cross check of half line (exclusively used for horizontal move)
// (p0-p1)  (p2-p3)
// (p0-p1) is near as it is the moving line of Yoshi
// Return Value : 0 is not crossing
//       1 if crossing
// (p0-p1) is same in Y coordinate
s8 p1_line_cross_chk_yoko(xyPos p0, xyPos p1, xyPos p2, xyPos p3)
{
	s32 dx0,dy0,t;
	
	//flip the ones without hope
	if(  (p0.y<p2.y && p0.y<p3.y)
	   ||(p0.y>p2.y && p0.y>p3.y))return 0;
	if(p0.x<p1.x)
	{
		if(p2.x<p3.x)
		{
			if(p1.x<p2.x)return 0;
		}else if(p1.x<p3.x)return 0;
	}else
	{
		if(p2.x<p3.x)
		{
			if(p0.x<p2.x)return 0;
		}else if(p0.x<p3.x)return 0;
	}
	if(p2.y == p3.y)return 0;//it does not cross horizontal line
	
	if(p2.x == p3.x)
	{
		if( (p0.x<p2.x && p1.x<p2.x)
		  ||(p0.x>p2.x && p1.x>p2.x))return 0;
		
		if( (p0.y >= p2.y && p0.y <= p3.y)
		  ||(p0.y <= p2.y && p0.y >= p3.y))return 1;
		return 0;
	}else
	{
		dx0 = p3.x - p2.x;
		dy0 = p3.y - p2.y;
		if((dy0>>8)==0)
			t = (dx0/0x100) * ((p0.y - p2.y)/0x100) / (dy0) + p2.x;
		else
			t = (dx0/0x100) * ((p0.y - p2.y)/0x100)*0x100 / (dy0>>8)+ p2.x;
		
		if( (t<p0.x && t<p1.x) || (t>p0.x && t>p1.x))return 0;//not crossing
		return 1;
	}
	return 0;//decoration
}

////////////////////////////////////////////////////////////////////////////
//Find the relative coordinate from the center of the screen which has been wrap-revised
//x absolute coordinate
s32 p1_get_rel_pos(s32 x)
{
	if(     p1_gGame.disp_x<      240 *0x10000 && x>(BG_L-240)*0x10000)x -= BG_L*0x10000;
	else if(p1_gGame.disp_x>(BG_L-240)*0x10000 && x<      240 *0x10000)x += BG_L*0x10000;
	
	x -= p1_gGame.disp_x;
	
	return x;
}

////////////////////////////////////////////////////////////////////////////
//Find absolute coordinate that has been wrap-revised
//x Absolute coordinate
s32 p1_get_lap_pos(s32 x)
{
	if(     p1_gGame.disp_x<      240 *0x10000 && x>(BG_L-240)*0x10000)x -= BG_L*0x10000;
	else if(p1_gGame.disp_x>(BG_L-240)*0x10000 && x<      240 *0x10000)x += BG_L*0x10000;
	
	return x;
}

////////////////////////////////////////////////////////////////////////////
//Set death of Yoshi
void p1_yoshi_dead_set(void)
{
	s16 i;
	p1_yoshiWork.status = YOSHI_ST_DIE;//Death
	p1_yoshiWork.work0  = 0;
	//Set falling petals
	if(p1_yoshiWork.egg_num > 0 && p1_yoshiWork.egg_num <= 4)
	{
		p1_hanabiraWork[(p1_yoshiWork.egg_num-1) * 3    ].status = HANABIRA_ST_FALL;
		p1_hanabiraWork[(p1_yoshiWork.egg_num-1) * 3    ].v.y    = 0;
		p1_hanabiraWork[(p1_yoshiWork.egg_num-1) * 3    ].work0  = 0;
		p1_hanabiraWork[(p1_yoshiWork.egg_num-1) * 3    ].work1  = 0x18;//wait count
		p1_hanabiraWork[(p1_yoshiWork.egg_num-1) * 3 + 1].status = HANABIRA_ST_FALL;
		p1_hanabiraWork[(p1_yoshiWork.egg_num-1) * 3 + 1].v.y    = 0;
		p1_hanabiraWork[(p1_yoshiWork.egg_num-1) * 3 + 1].work0  = 0;
		p1_hanabiraWork[(p1_yoshiWork.egg_num-1) * 3 + 1].work1  = 0;
		if(p1_yoshiWork.egg_num > 1)
		{
			p1_hanabiraWork[(p1_yoshiWork.egg_num-1) * 3 - 1].status = HANABIRA_ST_FALL;
			p1_hanabiraWork[(p1_yoshiWork.egg_num-1) * 3 - 1].v.y    = 0;
			p1_hanabiraWork[(p1_yoshiWork.egg_num-1) * 3 - 1].work0  = 0;
			p1_hanabiraWork[(p1_yoshiWork.egg_num-1) * 3 - 1].work1  = 0x30;//wait count
#ifdef SOUND_ON
			m4aSongNumStart(YOS_SE_DMGN1);
#endif
		}else
		{
#ifdef SOUND_ON
			m4aSongNumStart(YOS_SE_DMGN2);
#endif
		}
	}
	p1_yoshiWork.egg_num--;
	if(p1_yoshiWork.egg_num<-1)p1_yoshiWork.egg_num=-1;
	for(i=0; i<EGG_WORK_MAX; i++)
	{
		if(p1_eggWork[i].status != EGG_ST_SURI)continue;
		if(p1_eggWork[i].work0 <= 0)
		{
			p1_eggWork[i].status = EGG_ST_NONE;//Decrease eggs
		}else
		{
			p1_eggWork[i].work0 --;
		}
	}
}

////////////////////////////////////////////////////////////////////////////
//Set Yoshi's jump
void p1_yoshi_jump_set(s32 vy)
{
	p1_yoshiWork.on            = YOS_ON_NONE;
	p1_yoshiWork.v.y           = vy;//Initial speed of jump
	p1_yoshiWork.status        = YOSHI_ST_JUMPING;
	p1_yoshiWork.jump_timer    = YOSHI_JMP_TIME;
	p1_yoshiWork.funbari_timer = FUNBARI_TIME;
	p1_yoshiWork.funbari_flg   = 0;
	p1_yoshiWork.anm_ptn_new   = YOS_ANM_JUMP;
	p1_yoshiWork.fall_timer    = 0;
	anmWork[ANM_WORK_YOSHI].flg = ANM_FLG_NEW;
}

////////////////////////////////////////////////////////////////////////////
//Effect Set
void p1_effectSet(s8 type, xyPos pos, xyPos *v0)
//static EffectWork* p1_effectSet(s8 type, xyPos pos, xyPos v0)
{
	s16 i;
	
	for(i=0; i<EFF_WORK_MAX; i++)
	{
		if(p1_effWork[i].status != 0)continue;
		
		//Use this since it is open
		p1_effWork[i].status = 1;
		p1_effWork[i].eff_type = type;
		p1_effWork[i].pos  = pos;
		p1_effWork[i].v    = *v0;
		switch(type)
		{
		case EFF_TYPE_DASH://Dash Smoke
			p1_effWork[i].time = 40;
			p1_effWork[i].chr  = CHR_TYPE_BATABATA;
			break;
		case EFF_TYPE_SMOKE://KURURINHA Smoke
			p1_effWork[i].time = 40;
			p1_effWork[i].chr  = CHR_TYPE_KURUKEMU;
			break;
		case EFF_TYPE_HEIS://Star
			p1_effWork[i].time = 40;
			p1_effWork[i].chr  = CHR_TYPE_HOSI;
			break;
		}
		break;
	}
}
////////////////////////////////////////////////////////////////////////////
//When the character changed from balloon disappear
void p1_balloon_dead(s16 chr_num)
{
	p1_charWork[chr_num].status    = BALLOON_ST_NA;
	p1_charWork[chr_num].pos       = p1_balloon_pos[0];
	p1_charWork[chr_num].hit_flg   = 0;
	p1_charWork[chr_num].char_type = CHR_TYPE_BALLOON;
}


////////////////////////////////////////////////////////////////////////////
//Animation Process
void p1_anim_work_proc(void)
{
	s16 i;
	AnmWork *pAw;
	
	for(i=0; i<ANM_WORK_G_MAX; i++)
	{
		if(anmWork[i].flg == -1)continue;
		pAw = &anmWork[i];
		if(pAw->flg==ANM_FLG_NEW)//Set new animation when flag which indicates the switch of animation is out
		{
			pAw->pTbl = (AnmTbl*)pAw->ppTbl[pAw->anm_ptn];
			pAw->time = pAw->pTbl->time;
			pAw->flg  = 0;
			dmaReqSet(pAw->pPixTbl[pAw->pTbl->anm_ptn], pAw->chr, pAw->size);//rewrite VRAM
		}else if(pAw->flg==ANM_FLG_PIX_CHG)//Only Pixel table changed
		{
			pAw->pTbl = (AnmTbl*)pAw->ppTbl[pAw->anm_ptn];
			pAw->flg  = 0;
			dmaReqSet(pAw->pPixTbl[pAw->pTbl->anm_ptn], pAw->chr, pAw->size);//rewrite VRAM
		}
		pAw->time--;
		if(pAw->time <= 0)//when time is up, it moves to the next pattern
		{
			pAw->pTbl++;
			pAw->time = pAw->pTbl->time;
			if(pAw->pTbl->time == -1)//Loop
			{
				pAw->pTbl = (AnmTbl*)pAw->ppTbl[pAw->anm_ptn];
				pAw->time = pAw->pTbl->time;
			}else if(pAw->pTbl->time == -2)//End
			{
				pAw->pTbl--;
				pAw->time = 0;
				pAw->anm_ptn = 0;
				pAw->flg = -1;
			}
			if(pAw->flg >= 0)
				dmaReqSet(pAw->pPixTbl[pAw->pTbl->anm_ptn], pAw->chr, pAw->size);//Rewrite VRAM
		}
	}
}

////////////////////////////////////////////////////////////////////////////
//Set the coordinate of Kokamek and Yoshi when taken into a castle and the zoom value
//Coordinate which converted its fluoroscopy by rotating
s8 p1_turekomi_fly_pos_set(s32 timer)
{
	#define POS_H (100)
	#define SIRO_POS_X ( 50*0x10000)
	#define SIRO_POS_Y (-50*0x10000)
	s16 i;
	s32 z;
	if(timer < 0)timer = 0;
	if(timer > 0x180)return -1;
	
	i = 0;
	z = 100+((timer*timer>>8)*timer>>8);//z(depth)
	
	p1_yoshiWork.zoom.x = //zoom of Yoshi
	p1_yoshiWork.zoom.y = (POS_H*0x10000)/z;
	p1_kokamekWork[0].v.x = (POS_H*0x10000)/z;//zoom of Kokamek
	
	//Fluoroscopy conversion
	p1_yoshiWork.pos.x = (fix_cos[timer&0xff]*0x80)*POS_H/z*0x100+p1_gGame.disp_x+SIRO_POS_X;
	p1_yoshiWork.pos.y = (fix_sin[timer&0xff]*0x80)*POS_H/z*0x100+p1_gGame.disp_y+SIRO_POS_Y;
	
	//Kokamek
	for(i=0; i<4; i++)
	{
		p1_kokamekWork[i].pos.x = p1_yoshiWork.pos.x+(p1_kokamekPos[i].x>>8)*(p1_kokamekWork[0].v.x>>8);
		p1_kokamekWork[i].pos.y = p1_yoshiWork.pos.y+(p1_kokamekPos[i].y>>8)*(p1_kokamekWork[0].v.x>>8);
	}
	return 0;
}

////////////////////////////////////////////////////////////////////////////
//Stop all the animation
void p1_clear_anm(void)
{
	s16 i;
	for(i=0; i<ANM_WORK_MAX; i++)
	{
		anmWork[i].flg = -1;
	}
}

////////////////////////////////////////////////////////////////////////////
//Key check
void p1_key_chk(void)
{
	//Pushed
	if(gMain.Cont & R_KEY)p1_gGame.contKey  =1;else p1_gGame.contKey=0;
	if(gMain.Cont & U_KEY)p1_gGame.contKey |=2;
	if(gMain.Cont & L_KEY)p1_gGame.contKey |=4;
	if(gMain.Cont & D_KEY)p1_gGame.contKey |=8;
}

////////////////////////////////////////////////////////////////////////////
//calculate the center location of screen
//Update the center location of screen from the location and zoom value of Yoshi, Current center location of screen, Standing Yoshi and the direction Yoshi is facing
void p1_calcDispPosition(void)
{
	s32 dd;
	
	//Limitation to area of X direction
	dd = p1_yoshiWork.pos.x-p1_gGame.disp_x;
	if(dd > D_LIMIT_X)
		p1_gGame.disp_x = p1_yoshiWork.pos.x - D_LIMIT_X;
	else if(dd < - D_LIMIT_X)
		p1_gGame.disp_x = p1_yoshiWork.pos.x + D_LIMIT_X;
	
	dd = p1_yoshiWork.pos.x-p1_gGame.disp_x;
	if(p1_gGame.zoom > ZOOM_1)
	{//Make sure that Yoshi is in the center while zooming
		if(dd > 0x10000)
			p1_gGame.disp_x += 0x10000;
		else if(dd < 0x10000)
			p1_gGame.disp_x -= 0x10000;
	}else
	{//Request to set aside for front view
		if((dd >-D_LIMIT_X) && (p1_yoshiWork.dir > 0))
		{
			p1_gGame.disp_x += 0x18000;
		}else if((dd <D_LIMIT_X) && (p1_yoshiWork.dir<0))
		{
			p1_gGame.disp_x -= 0x18000;
		}
	}
	//Y direction
	if(   p1_yoshiWork.status == YOSHI_ST_NORMAL
	   || p1_yoshiWork.status == YOSHI_ST_MOUNT)
	{//when feet are touching ground
		if(abs(p1_gGame.disp_y-p1_yoshiWork.pos.y) <= 1*0x10000)
			p1_gGame.disp_y = p1_yoshiWork.pos.y;
		
		if(p1_gGame.disp_y < p1_yoshiWork.pos.y)
			p1_gGame.disp_y += 0x10000;
		else if(p1_gGame.disp_y > p1_yoshiWork.pos.y)
			p1_gGame.disp_y -= 0x10000;
	}else
	{//when floating
		dd = p1_yoshiWork.pos.y - p1_gGame.disp_y;
		if(p1_yoshiWork.pos.y - p1_gGame.disp_y > 0 )//it is likely to go down
			p1_gGame.disp_y = p1_yoshiWork.pos.y;//maintain
		else if(dd < - D_LIMIT_Y)
			p1_gGame.disp_y = p1_yoshiWork.pos.y + D_LIMIT_Y;
	}
	//Absolute limitation for Y direction
	if(p1_gGame.disp_y < BG_LIMIT_Y_TOP)
	{
		p1_gGame.disp_y = BG_LIMIT_Y_TOP;
	}else if(p1_gGame.disp_y > BG_LIMIT_Y_BOTTOM)
	{
		p1_gGame.disp_y = BG_LIMIT_Y_BOTTOM;
	}
	
	//Shake control of the ground
	if(p1_gGame.gnd_bias_count > 0)
	{
		if(++p1_gGame.gnd_bias_count > GND_BIAS_FRM)
		{
			p1_gGame.gnd_bias_count = 0;
			p1_gGame.gnd_bias = 0;
		}else
		{
			p1_gGame.gnd_bias = fix_sin[p1_gGame.gnd_bias_count*16 %0x100]*100*6;
		}
	}
}

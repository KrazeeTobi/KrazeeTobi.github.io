//======================================================
//    yos_game_mov.c
//    Sample Yoshi Character Move Sub-routine
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
#include "yos_game_mov.h"

#include "yos_game.ext"
#include "yos_sound.h"


s16 p1_egg_se_tbl[3]=
{
	YOS_SE_ONPP1, YOS_SE_ONPP2, YOS_SE_ONPP3
};

////////////////////////////////////////////////////////////////////////////
//Local Function
static void p1_yos_histry_set(void);

////////////////////////////////////////////////////////////////////////////
//Initialization of Yoshi1
void p1_yoshi_init1(void)
{
	s16 i;
	
	p1_yoshiWork.pos        = p1_yoshi_start_pos;//Position of Yoshi
	p1_yoshiWork.pos_old    = p1_yoshiWork.pos;
	p1_yoshiWork.v.x        = 0;//Speed of Yoshi
	p1_yoshiWork.v.y        = 0;
	p1_yoshiWork.kururin_se = 0;
	p1_yoshiWork.fall_timer = 0;
	//Yoshi Coordinate(For Coordinate of Egg) History Initialization
	for(i=0; i<YOS_HISTORY_MAX; i++)
	{
		p1_yoshiWork.pos_history[i].x = p1_yoshiWork.pos.x >> 16;
		p1_yoshiWork.pos_history[i].y = p1_yoshiWork.pos.y >> 16;
	}
	p1_yoshiWork.history_cur    = 0;//Egg History Ring BuggerHead position
	p1_yoshiWork.status         = YOSHI_ST_NORMAL;
	p1_yoshiWork.dir            = CHR_DIR_R;//Facing Right
	p1_yoshiWork.zoom.x         = ZOOM_1;
	p1_yoshiWork.zoom.y         = ZOOM_1;
	p1_yoshiWork.funbari_timer  = FUNBARI_TIME;
	p1_yoshiWork.on             = YOS_ON_NONE;
	p1_yoshiWork.on_old         = YOS_ON_NONE;
	p1_yoshiWork.muteki_timer   = 0;
	p1_yoshiWork.koutyoku_timer = 0;
	p1_yoshiWork.tyouhatu_flg   = 0;
	p1_yoshiWork.tatenobi       = 0;
	affineWork[AFN_WORK_YOS].Hflip = 1;
}
#ifdef SOUND_ON
void p1_jump_se_set(void)
{
	if((p1_gGame.game_timer&1)==0)
		m4aSongNumStart(YOS_SE_JUMP0);
	else
		m4aSongNumStart(YOS_SE_JUMP1);
}
#endif
////////////////////////////////////////////////////////////////////////////
//Move of Yoshi
void p1_yoshiMove(void)
{
	xyPos pos_old,yos_pos,pos_on;
	xyPos yos_col[2],effv,effp;
	s32 mapY,d0;
	s16 rval,hit_chr_num;
	u8 char_on,char_type,rot;
	
	if(gMain.Trg & SELECT_BUTTON)p1_yoshi_dead_set();//Dies when select button is pressed
	
	pos_old.x = p1_yoshiWork.pos.x;
	pos_old.y = p1_yoshiWork.pos.y;
	yos_pos = p1_yoshiWork.pos;
	p1_yoshiWork.on_old=p1_yoshiWork.on;
	
	p1_yoshiWork.anm_ptn_new = anmWork[ANM_WORK_YOSHI].anm_ptn;
	
	if( (p1_yoshiWork.status==YOSHI_ST_NORMAL || p1_yoshiWork.status==YOSHI_ST_MOUNT)
	  &&(gMain.Cont & L_BUTTON))
	{
		p1_yoshiWork.tyouhatu_flg=1;//Provocation
	}else p1_yoshiWork.tyouhatu_flg=0;//No Provocation
	
	if(p1_yoshiWork.koutyoku_timer>0)p1_yoshiWork.koutyoku_timer--;//Process of Stiffness Timer
	if(p1_yoshiWork.muteki_timer  >0)p1_yoshiWork.muteki_timer--;//Process of Invincible Timer 
	
#ifdef SOUND_ON
	//Turn around SE
	if(anmWork[ANM_WORK_YOSHI].anm_ptn == YOS_ANM_NORMAL)
	{
		AnmTbl *pTbl;
		
		pTbl = anmWork[ANM_WORK_YOSHI].pTbl;
		if((pTbl == anmWork[ANM_WORK_YOSHI].ppTbl[YOS_ANM_NORMAL])
			&& (anmWork[ANM_WORK_YOSHI].time == 3))
				m4aSongNumStart(YOS_SE_KUBIFURI);
		else if((pTbl == anmWork[ANM_WORK_YOSHI].ppTbl[YOS_ANM_NORMAL]+46)
			&& (anmWork[ANM_WORK_YOSHI].time == 1))
			m4aSongNumStart(YOS_SE_STPH1);
		else if((pTbl == anmWork[ANM_WORK_YOSHI].ppTbl[YOS_ANM_NORMAL]+30)
			&& (anmWork[ANM_WORK_YOSHI].time == 1))
			m4aSongNumStart((p1_gGame.game_timer&8)? YOS_SE_TONT1:YOS_SE_TONT2);
		else if((pTbl == anmWork[ANM_WORK_YOSHI].ppTbl[YOS_ANM_NORMAL]+39)
			&& (anmWork[ANM_WORK_YOSHI].time == 1))
			m4aSongNumStart((p1_gGame.game_timer&16)?YOS_SE_TONT1:YOS_SE_TONT2);
	}
#endif
	
	switch( p1_yoshiWork.status )
	{
	case YOSHI_ST_NORMAL:
		//Cannot move to the side while turning around (able to turn around)
		p1_yoshiWork.rot = 0;
		if( (gMain.Cont & (L_KEY|R_KEY) ) != (L_KEY|R_KEY) 
		    && (gMain.Cont & (L_KEY|R_KEY))
			&& p1_yoshiWork.koutyoku_timer==0
			&&(!p1_yoshiWork.tyouhatu_flg)//unable to move while provoking
			)
		{
			if (gMain.Cont & L_KEY)
			{
				if(p1_yoshiWork.dir == CHR_DIR_R)//
				{
					//Turn Around
					p1_yoshiWork.dir = CHR_DIR_L;
					affineWork[AFN_WORK_YOS].Hflip = 0;
					p1_yoshiWork.v.x = 0;
					//Set of turn-around Animation
					p1_yoshiWork.anm_ptn_new = YOS_ANM_L2R;
				}else if(anmWork[ANM_WORK_YOSHI].anm_ptn != YOS_ANM_L2R)
				{//Go forward
					if(gMain.Cont & B_BUTTON)
					{
						p1_yoshiWork.v.x = -YOSHI_MOV_MAX_SPEED;
						p1_yoshiWork.anm_ptn_new = YOS_ANM_RUN;
						if((p1_gGame.game_timer&0x7)==0)
						{
							effv.x = 0x6000;
							effv.y =-0x3000;
							effp = yos_pos;
							effp.y += 13<<16;
							p1_effectSet(EFF_TYPE_DASH, effp, &effv);
						}
					}else
					{
						p1_yoshiWork.v.x = -YOSHI_MOV_SPEED;
						p1_yoshiWork.anm_ptn_new = YOS_ANM_WALK;
					}
				}
			}else if (gMain.Cont & R_KEY)//temp
			{
				if(p1_yoshiWork.dir == CHR_DIR_L)//
				{
					//Turn around
					p1_yoshiWork.dir = CHR_DIR_R;
					affineWork[AFN_WORK_YOS].Hflip = 1;
					p1_yoshiWork.v.x = 0;
					//Set of turn-around Animation
					p1_yoshiWork.anm_ptn_new = YOS_ANM_L2R;
				}else if(anmWork[ANM_WORK_YOSHI].anm_ptn != YOS_ANM_L2R)
				{//Go forward
					if(gMain.Cont & B_BUTTON)
					{
						if((p1_gGame.game_timer&0x7) == 0)
						{
							effv.x = -0x6000;
							effv.y = -0x3000;
							effp = yos_pos;
							effp.y += 13<<16;
							p1_effectSet(EFF_TYPE_DASH,effp,&effv);
						}
						p1_yoshiWork.v.x = YOSHI_MOV_MAX_SPEED;
						p1_yoshiWork.anm_ptn_new = YOS_ANM_RUN;
					}else
					{
						p1_yoshiWork.v.x = YOSHI_MOV_SPEED;
						p1_yoshiWork.anm_ptn_new = YOS_ANM_WALK;
					}
				}
			}
		}else
		{//while stopping or stop walking
			p1_yoshiWork.v.x = 0;
			if(anmWork[ANM_WORK_YOSHI].anm_ptn != YOS_ANM_L2R)//not a turn-around
			{
				if(p1_gGame.zoom == ZOOM_1)
				{
					p1_yoshiWork.anm_ptn_new = YOS_ANM_NORMAL;
				}
			}
		}
		yos_pos.x = p1_yoshiWork.pos.x + p1_yoshiWork.v.x;
		
		mapY = p1_getMap(yos_pos.x);
		//Move along road since he is on the ground
		yos_pos.y = mapY - ((s32)p1_yoshiWork.col[1].y << 16);
		if(yos_pos.y - pos_old.y < -0x40000)yos_pos = pos_old;//cannot go up
		if(yos_pos.y - pos_old.y >  0x40000)
		{//Fall
			yos_pos.y = pos_old.y;
			p1_yoshi_jump_set(0);
		}
		//Jump?
		if ((gMain.Trg & A_BUTTON) && p1_yoshiWork.koutyoku_timer == 0
			&&(!p1_yoshiWork.tyouhatu_flg)//Cannot move while provoking
			)
		{
			yos_pos.x = pos_old.x;
			p1_yoshi_jump_set(YOSHI_JMP_SPEED);
			//Dash Smoke
			effv.y = -0x3000;
			if(p1_yoshiWork.dir < 0)effv.x = 0x3000;else effv.x = -0x3000;
			effp = yos_pos;
			effp.y += 13<<16;
			p1_effectSet(EFF_TYPE_DASH,effp,&effv);
#ifdef SOUND_ON
			p1_jump_se_set();
#endif
		}
		//Hit Decision
		//Try moving to the side
		p1_yoshiWork.pos.x=yos_pos.x;
		//Hit other characters
		rval = p1_yos_hit_yoko(pos_old, &hit_chr_num);//Hit decision
		if(rval == 5)break;//Death
		if(rval != 0)//hitting
		{
			d0=p1_yoshiWork.pos.x;
			p1_yoshiWork.pos.x = pos_old.x;//Cancel to move to side
			rval = p1_yos_hit_yoko(pos_old, &hit_chr_num);//Hit Decision
			if(rval!=0)p1_yoshiWork.pos.x=d0;//Move since hit before moving
		}
		//Move vertically
		p1_yoshiWork.pos.y = yos_pos.y;
		rval = p1_yos_hit_tate(pos_old, &hit_chr_num);//Check
		if(rval != 0 )
		{
			p1_yoshiWork.pos.y = pos_old.y;//
			p1_yoshiWork.v.y = 0;//
		}
		break;
	case YOSHI_ST_MOUNT://Mounting on other character
		char_on = p1_yoshiWork.on;
		char_type = p1_charWork[char_on].char_type;
		pos_on = p1_yoshiWork.posOn;
		if(char_type == CHR_TYPE_HAKO)
		{//Get on box
			p1_yoshiWork.rot =
			rot = p1_charWork[char_on].rot;
			
			//Provocation?
			if( (gMain.Cont & (L_KEY|R_KEY) ) != (L_KEY|R_KEY) 
			    && (gMain.Cont & (L_KEY|R_KEY))
				&& p1_yoshiWork.koutyoku_timer == 0
				&&(!p1_yoshiWork.tyouhatu_flg)//unable to move while provoking
				)
			{
				if (gMain.Cont & L_KEY)//pressed --> direction
				{
					if(p1_yoshiWork.dir == CHR_DIR_R)//faced right
					{
						//Turn around
						p1_yoshiWork.dir = CHR_DIR_L;
						affineWork[AFN_WORK_YOS].Hflip = 0;
						p1_yoshiWork.v.x = 0;
						//Set of turn-around animation
						p1_yoshiWork.anm_ptn_new = YOS_ANM_L2R;
					}else if(anmWork[ANM_WORK_YOSHI].anm_ptn != YOS_ANM_L2R)
					{//Go forward
						if(gMain.Cont & B_BUTTON)
						{
							p1_yoshiWork.v.x = -YOSHI_MOV_MAX_SPEED;
							p1_yoshiWork.anm_ptn_new = YOS_ANM_RUN;
						}else
						{
							p1_yoshiWork.v.x = -YOSHI_MOV_SPEED;
							p1_yoshiWork.anm_ptn_new = YOS_ANM_WALK;
						}
					}
				}else if (gMain.Cont & R_KEY)//In case
				{
					if(p1_yoshiWork.dir == CHR_DIR_L)//
					{
						//Turn around
						p1_yoshiWork.dir = CHR_DIR_R;
						affineWork[AFN_WORK_YOS].Hflip = 1;
						p1_yoshiWork.v.x = 0;
						//Set of turn-around animation
						p1_yoshiWork.anm_ptn_new = YOS_ANM_L2R;
					}else if(anmWork[ANM_WORK_YOSHI].anm_ptn != YOS_ANM_L2R)
					{//go forward
						if(gMain.Cont & B_BUTTON)
						{
							p1_yoshiWork.v.x = YOSHI_MOV_MAX_SPEED;
							p1_yoshiWork.anm_ptn_new = YOS_ANM_RUN;
						}else
						{
							p1_yoshiWork.v.x = YOSHI_MOV_SPEED;
							p1_yoshiWork.anm_ptn_new = YOS_ANM_WALK;
						}
					}
				}
			}else
			{//while stopping or stop walking
				p1_yoshiWork.v.x = 0;
				if(anmWork[ANM_WORK_YOSHI].anm_ptn != YOS_ANM_L2R)//not a turn-around
				{
					p1_yoshiWork.anm_ptn_new = YOS_ANM_NORMAL;
				}
			}
			p1_yoshiWork.posOn.x = p1_yoshiWork.posOn.x + p1_yoshiWork.v.x;
			
			//Revolve(From coordinate of item to normal coordinate)
			yos_pos.x = (( fix_cos[rot]*p1_yoshiWork.posOn.x+fix_sin[rot]*p1_yoshiWork.posOn.y)>>8)+p1_charWork[char_on].pos.x;
			yos_pos.y = ((-fix_sin[rot]*p1_yoshiWork.posOn.x+fix_cos[rot]*p1_yoshiWork.posOn.y)>>8)+p1_charWork[char_on].pos.y;
			
			yos_col[0].x = p1_yoshiWork.posOn.x + ((s32)p1_yoshiWork.col[0].x<<16);
			yos_col[1].x = p1_yoshiWork.posOn.x + ((s32)p1_yoshiWork.col[1].x<<16);
			
			//Hit Decision
			//Move sideways
			p1_yoshiWork.pos.x = yos_pos.x;
			//Hit ground
			rval = p1_jimen_cross_chk_yoko(pos_old,p1_yoshiWork.pos);
			if(rval == 1)p1_yoshiWork.pos.x = pos_old.x;
			//Hit other characters
			rval = p1_yos_hit_yoko(pos_old, &hit_chr_num);//Hit Decision
			if(rval == 5)break;//Yoshi dies
			if(rval == 0)
			{
				//Move vertically
				p1_yoshiWork.pos.y = yos_pos.y;
				rval = p1_yos_hit_tate(pos_old, &hit_chr_num);//Check
			}
			//Move is cancelled when hit either one
			if(rval != 0)
			{
				p1_yoshiWork.posOn=pos_on;
				//Revolve
				p1_yoshiWork.pos.x =(( fix_cos[rot]*p1_yoshiWork.posOn.x + fix_sin[rot]*p1_yoshiWork.posOn.y)>>8)+p1_charWork[char_on].pos.x;
				p1_yoshiWork.pos.y =((-fix_sin[rot]*p1_yoshiWork.posOn.x + fix_cos[rot]*p1_yoshiWork.posOn.y)>>8)+p1_charWork[char_on].pos.y;
			}
			
			//Decide screen(whether riding on or not)
			if(!( ( (((s32)p1_charSpecData[char_type].col[0].x-3)<<16) < yos_col[1].x) &&
				  ( (((s32)p1_charSpecData[char_type].col[1].x+3)<<16) > yos_col[0].x)) )
			{//Fall after missing
				p1_yoshi_jump_set(0);
			}
			//Jump?
			if((gMain.Trg & A_BUTTON)
			 &&(!p1_yoshiWork.tyouhatu_flg))//unable to move while provoking
			{
				yos_pos.x = pos_old.x;
				p1_yoshi_jump_set(YOSHI_JMP_SPEED);
				p1_yoshiWork.pos.y += p1_yoshiWork.v.y;//Avoid being caught on
#ifdef SOUND_ON
			p1_jump_se_set();
#endif
			}
		}else
		{//Getting on something that does not revolve
			p1_yoshiWork.rot =0;
			if( (gMain.Cont & (L_KEY|R_KEY) ) != (L_KEY|R_KEY) 
			    && (gMain.Cont & (L_KEY|R_KEY)))
			{
				if (gMain.Cont & L_KEY)
				{
					if(p1_yoshiWork.dir == CHR_DIR_R)//
					{
						//Turn around
						p1_yoshiWork.dir = CHR_DIR_L;
						affineWork[AFN_WORK_YOS].Hflip = 0;
						p1_yoshiWork.v.x = 0;
						//Set of turn-around animation
						p1_yoshiWork.anm_ptn_new = YOS_ANM_L2R;
					}else if(anmWork[ANM_WORK_YOSHI].anm_ptn != YOS_ANM_L2R)
					{//Go forward
						if(gMain.Cont & B_BUTTON)
						{
							p1_yoshiWork.v.x = -YOSHI_MOV_MAX_SPEED;
							p1_yoshiWork.anm_ptn_new = YOS_ANM_RUN;
						}else
						{
							p1_yoshiWork.v.x = -YOSHI_MOV_SPEED;
							p1_yoshiWork.anm_ptn_new = YOS_ANM_WALK;
						}
					}
				}else if (gMain.Cont & R_KEY)//
				{
					if(p1_yoshiWork.dir == CHR_DIR_L)//
					{
						//Turn around
						p1_yoshiWork.dir = CHR_DIR_R;
						affineWork[AFN_WORK_YOS].Hflip = 1;
						p1_yoshiWork.v.x = 0;
						//Set of turn-around animation
						p1_yoshiWork.anm_ptn_new = YOS_ANM_L2R;
					}else if(anmWork[ANM_WORK_YOSHI].anm_ptn != YOS_ANM_L2R)
					{//Go forward
						if(gMain.Cont & B_BUTTON)
						{
							p1_yoshiWork.v.x = YOSHI_MOV_MAX_SPEED;
							p1_yoshiWork.anm_ptn_new = YOS_ANM_RUN;
						}else
						{
							p1_yoshiWork.v.x = YOSHI_MOV_SPEED;
							p1_yoshiWork.anm_ptn_new = YOS_ANM_WALK;
						}
					}
				}
			}else
			{//stopping or stop walking
				p1_yoshiWork.v.x = 0;
				if(anmWork[ANM_WORK_YOSHI].anm_ptn != YOS_ANM_L2R)//not a turn around
				{
					p1_yoshiWork.anm_ptn_new = YOS_ANM_NORMAL;
				}
			}
			yos_pos.x = p1_yoshiWork.pos.x + p1_yoshiWork.v.x;
			
			yos_col[0].x = p1_yoshiWork.pos.x + ((s32)p1_yoshiWork.col[0].x<<16);
			yos_col[1].x = p1_yoshiWork.pos.x + ((s32)p1_yoshiWork.col[1].x<<16);
			// Decide screen
			if( (p1_charWork[char_on].pos.x + ((s32)p1_charSpecData[char_type].col[0].x<<16) < yos_col[1].x) &&
				(p1_charWork[char_on].pos.x + ((s32)p1_charSpecData[char_type].col[1].x<<16) > yos_col[0].x) )
			{//within screen
				yos_pos.y = p1_charWork[char_on].pos.y + ((s32)p1_charSpecData[char_type].col[0].y<<16) - ((s32)p1_yoshiWork.col[1].y<<16);
				//move vertically
				p1_yoshiWork.pos.y = yos_pos.y;
				rval=p1_yos_hit_tate(pos_old, &hit_chr_num);//Check
				if(rval != 0 )
				{
					p1_yoshiWork.pos.y = pos_old.y;//
					p1_yoshiWork.v.y = 0;//
				}
			}else
			{//Fall after missing
				p1_yoshi_jump_set(0);
			}
			//Jump?
			if (gMain.Trg & A_BUTTON)
			{
				p1_yoshi_jump_set(YOSHI_JMP_SPEED);
#ifdef SOUND_ON
				p1_jump_se_set();
#endif
				
//				p1_yoshiWork.pos.y -=0x10000;//5t
			}
			//Move sideways
			p1_yoshiWork.pos.x = yos_pos.x;
			//hit Ground
			rval = p1_jimen_cross_chk_yoko(pos_old, p1_yoshiWork.pos);
			if(rval == 1)p1_yoshiWork.pos.x = pos_old.x;
			//Hit other characters
			rval = p1_yos_hit_yoko(pos_old, &hit_chr_num);//Hit Decision
			if(rval == 5)break;
			if(rval == 1)p1_yoshiWork.pos.x = pos_old.x;//horizontal move cancel if hit
		}
		break;
	case YOSHI_ST_JUMPING:
		p1_yoshiWork.rot = 0;
		if(p1_gGame.contKey == 8)
		{//becomes Ground Pound when press down button
			p1_yoshiWork.status = YOSHI_ST_KURUN;
			p1_yoshiWork.work0 = 0;
#ifdef SOUND_ON
			m4aSongNumStart(YOS_SE_KURURIN);
#endif
		}
		//
		p1_yoshiWork.v.y += YOSHI_FALL_ACC;
		if(p1_yoshiWork.v.y > YOSHI_FALL_MAX_SPEED)
			p1_yoshiWork.v.y = YOSHI_FALL_MAX_SPEED;
		
		if(p1_yoshiWork.jump_timer > 0)
		{
			p1_yoshiWork.jump_timer--;
			if(p1_yoshiWork.v.y > FUNBARI_LIMIT)
			{//Falling speed is fast enough for flutter jump
				
				p1_yoshiWork.jump_timer = 0;
			}
		}
		if(p1_yoshiWork.funbari_flg == 0 && p1_yoshiWork.v.y > FUNBARI_LIMIT)
		{
			p1_yoshiWork.funbari_flg = 1;
		}
		//Move sideways
		yos_pos.x+=p1_yoshiWork.v.x;
		if(abs(p1_yoshiWork.v.x) < YOSHI_MASATU_ACC)p1_yoshiWork.v.x = 0;
		if(p1_yoshiWork.v.x < 0)p1_yoshiWork.v.x += YOSHI_MASATU_ACC;
		if(p1_yoshiWork.v.x > 0)p1_yoshiWork.v.x -= YOSHI_MASATU_ACC;
		
		if (gMain.Cont & L_KEY) yos_pos.x -= YOSHI_JUMP_MOV_SPEED;
		if (gMain.Cont & R_KEY) yos_pos.x += YOSHI_JUMP_MOV_SPEED;
		if (gMain.Cont & A_BUTTON)//pressing jump button
		{
			if(p1_yoshiWork.jump_timer > 0)
			{//still can rise higher
				p1_yoshiWork.v.y += YOSHI_JMP_ACC;//rising
			}else if(p1_yoshiWork.funbari_timer > 0 && p1_yoshiWork.funbari_flg)
			{//able to flutter jump
#ifdef SOUND_ON
				if(p1_yoshiWork.funbari_timer==FUNBARI_TIME)
					m4aSongNumStart(YOS_SE_FUN);
#endif
				
				p1_yoshiWork.funbari_timer--;
				if(p1_yoshiWork.v.y>0)
				{//It works better than flutter jump while falling
					if(gMain.Cont & U_KEY)
						p1_yoshiWork.v.y += FUNBARI_ACC2-p1_yoshiWork.v.y/8;
					else
						p1_yoshiWork.v.y += FUNBARI_ACC-p1_yoshiWork.v.y/8;
				}else
				{//Up
					if(gMain.Cont & U_KEY)
						p1_yoshiWork.v.y += FUNBARI_ACC2;
					else
						p1_yoshiWork.v.y += FUNBARI_ACC;
				}
				p1_yoshiWork.anm_ptn_new = YOS_ANM_FUNBARI;
			}else if(anmWork[ANM_WORK_YOSHI].anm_ptn == YOS_ANM_FUNBARI)
			{
				p1_yoshiWork.anm_ptn_new = YOS_ANM_JUMP;
			}
		}else
		{
			if(anmWork[ANM_WORK_YOSHI].anm_ptn == YOS_ANM_FUNBARI)
			{
				p1_yoshiWork.anm_ptn_new = YOS_ANM_JUMP;
			}
		}
		if(p1_yoshiWork.fall_timer >= 0)
		{
			if(p1_yoshiWork.v.y <= 0)p1_yoshiWork.fall_timer = 0;
			p1_yoshiWork.fall_timer++;
			if(p1_yoshiWork.fall_timer > 54)
			{
#ifdef SOUND_ON
				m4aSongNumStart(YOS_SE_AWAWA);//AWAWA
#endif
				p1_yoshiWork.anm_ptn_new = YOS_ANM_JUMP;
				p1_yoshiWork.fall_timer = -1;
			}
		}
		//Move Vertically
		yos_pos.y += p1_yoshiWork.v.y;
		
		//Hit Decision
		p1_yoshiWork.pos.x = yos_pos.x;//horizontal move
		//hit ground
		rval = p1_jimen_cross_chk_yoko(pos_old,p1_yoshiWork.pos);
		if(rval != 0)p1_yoshiWork.pos.x = pos_old.x;
		//Hit other characters
		rval = p1_yos_hit_yoko(pos_old, &hit_chr_num);//Hit Decision
		if(rval == 5)break;//Death
		if(rval != 0)
		{
//			p1_yoshiWork.pos.x = pos_old.x;//horizontal move is cancelled if hit
			d0=p1_yoshiWork.pos.x;
			p1_yoshiWork.pos.x = pos_old.x;//Move to sideways is cancelled
			rval = p1_yos_hit_yoko(pos_old, &hit_chr_num);//Hit Decision
			if(rval != 0)p1_yoshiWork.pos.x=d0;//Move since it was hit before moving
		}
		p1_yoshiWork.pos.y = yos_pos.y;//Move Vertically
		rval=p1_yos_hit_tate(pos_old, &hit_chr_num);//Check
		if(rval != 0 && rval !=4 )
		{
			p1_yoshiWork.pos.y = pos_old.y;//
		}
		mapY = p1_getMap(p1_yoshiWork.pos.x);
		if(mapY < p1_yoshiWork.pos.y + ((s32)p1_yoshiWork.col[1].y << 16) )
		{//land on the ground if gone in deeper than the ground surface
#ifdef SOUND_ON
			m4aSongNumStart(YOS_SE_JMPST);
#endif
			p1_yoshiWork.v.y = 0;
			p1_yoshiWork.status = YOSHI_ST_NORMAL;
			p1_yoshiWork.on = YOS_ON_NONE;//land
			p1_yoshiWork.pos.y = mapY - ((s32)p1_yoshiWork.col[1].y << 16);
			p1_yoshiWork.tatenobi = 10;
			//Dash Smoke
			effv.y = -0x3000;
			if(p1_yoshiWork.dir < 0)effv.x = 0x3000;else effv.x = -0x3000;
			effp = yos_pos;
			effp.y += 13<<16;
			p1_effectSet(EFF_TYPE_DASH, effp, &effv);
		}
		//dies if fall further than limit
		if(p1_yoshiWork.pos.y > YOSHI_DEAD_LIMIT)p1_yoshi_dead_set();
		
		//Setting of reversing left and right
		if(p1_yoshiWork.pos.x > pos_old.x)
		{
			p1_yoshiWork.dir = CHR_DIR_R;
			affineWork[AFN_WORK_YOS].Hflip = 1;
		}else if(p1_yoshiWork.pos.x < pos_old.x)
		{
			p1_yoshiWork.dir = CHR_DIR_L;
			affineWork[AFN_WORK_YOS].Hflip = 0;
		}
		break;
	case YOSHI_ST_KURUN://KURUN (move before Ground Pound)
		p1_yoshiWork.anm_ptn_new = YOS_ANM_KURURINHA;
		p1_yoshiWork.rot = (p1_yoshiWork.rot + 12 )&0xff;
		p1_yoshiWork.work0++;
		if(p1_yoshiWork.work0 > 32)
		{
			p1_yoshiWork.status = YOSHI_ST_KURURIN;
			p1_yoshiWork.kururin_se = 1;
		}
		break;
	case YOSHI_ST_KURURIN://Ground Pound
		p1_yoshiWork.rot = 0x80;
		p1_yoshiWork.v.y = YOSHI_KURU_FALL_SPEED;
		yos_pos.y += p1_yoshiWork.v.y;
		p1_yoshiWork.pos.y = yos_pos.y;//Move vertically
		rval=p1_yos_hit_tate(pos_old, &hit_chr_num);//Check
		if(rval != 0 )
		{
			p1_yoshiWork.pos.y = pos_old.y;//
		}
		mapY = p1_getMap(p1_yoshiWork.pos.x);
		if(mapY < p1_yoshiWork.pos.y + ((s32)p1_yoshiWork.col[1].y << 16) )
		{//Land on the ground if gone in deeper than the ground surface
#ifdef SOUND_ON
			if(p1_yoshiWork.kururin_se != 0)
				m4aSongNumStart(YOS_SE_HA);//"Hah!"
#endif
			p1_yoshiWork.kururin_se = 0;
			p1_yoshiWork.v.y = 0;
			p1_yoshiWork.status = YOSHI_ST_NORMAL;
			p1_yoshiWork.on = YOS_ON_NONE;//land
			p1_yoshiWork.pos.y = mapY - ((s32)p1_yoshiWork.col[1].y << 16);
			p1_yoshiWork.koutyoku_timer=KURURINHA_KOTYOKU_TIME;
			p1_yoshiWork.rot = 0;
			
			anmWork[ANM_WORK_KURUKEMU].anm_ptn = 1;
			anmWork[ANM_WORK_KURUKEMU].flg = ANM_FLG_NEW;
			
			//Set Ground Pound Smoke
			effp.x = pos_old.x;
			effp.y = pos_old.y + (16<<16);
			effv.y = -0x4000;
			effv.x = 0x8000;
			p1_effectSet(EFF_TYPE_SMOKE, effp, &effv);
			effv.x = -0x8000;
			p1_effectSet(EFF_TYPE_SMOKE, effp, &effv);
			effv.y = -0x8000;
			effv.x = 0x4000;
			p1_effectSet(EFF_TYPE_SMOKE, effp, &effv);
			effv.x = -0x4000;
			p1_effectSet(EFF_TYPE_SMOKE, effp, &effv);
			
			p1_gGame.gnd_bias_count = 1;
		}
		//dies if fell further than limit
		if(p1_yoshiWork.pos.y > YOSHI_DEAD_LIMIT)p1_yoshi_dead_set();
		
		break;
	case YOSHI_ST_DIE:
		p1_yoshiWork.rot = (p1_yoshiWork.rot + 8 )&0xff;
		p1_yoshiWork.work0++;
		if(p1_yoshiWork.work0 > 30)//time
		{
			p1_yoshiWork.status = YOSHI_ST_NORMAL;//normal
			p1_yoshiWork.muteki_timer = YOSHI_MUTEKI_TIME;//set the invincible time after death
			p1_yoshiWork.rot = 0;
			p1_yoshiWork.v.x = 0;
			p1_yoshiWork.v.y = 0;
			if(p1_yoshiWork.egg_num < 0)
			{//Game over if died with no eggs
				gMain.main_status = GMAIN_ST_GAME_OVER0;
				p1_sub_status = 0;
				p1_yoshiWork.muteki_timer = 0;
				p1_yoshiWork.anm_ptn_new  = YOS_ANM_DIE;
#ifdef SOUND_ON
				m4aSongNumStart(YOS_SE_ARRA);
#endif
			}else if(p1_yoshiWork.pos.y>YOSHI_DEAD_LIMIT)//if yoshi gets killed in crash, re-start from the home position
			{
				gMain.main_status = GMAIN_ST_INIT1;
				p1_sub_status = 0;
				*(vu16*)REG_BLDCNT = BLD_2ND_ALL|BLD_DOWN_MODE|BLD_ALL;//Brightness down
				*(vu16*)REG_BLDY = 16;
			}
		}
		break;
	}
	
	//stretch vertically during Ground Pound
	if(p1_yoshiWork.status == YOSHI_ST_KURURIN)
	{
		p1_yoshiWork.zoom.x = 0xc000;
		p1_yoshiWork.zoom.y = 0x14000;
	}else if(p1_yoshiWork.tatenobi > 0)
	{//Vertical Stretch Process (after landing)
		p1_yoshiWork.tatenobi--;
		p1_yoshiWork.zoom.y = ZOOM_1+p1_tatenobi_tbl[p1_yoshiWork.tatenobi];
	}else
	{
		p1_yoshiWork.zoom.x = 0x10000;
		p1_yoshiWork.zoom.y = 0x10000;
	}
	
	//Screen Zoom Process
	if(p1_yoshiWork.tyouhatu_flg)
	{
		if(gMain.Cont & L_BUTTON)
		{//pressing down button && provoking
#ifdef SOUND_ON
		if(anmWork[ANM_WORK_YOSHI].anm_ptn != YOS_ANM_TYOUHATU)
		{
			m4aSongNumStart(YOS_SE_UPUP);
		}
#endif
			p1_yoshiWork.anm_ptn_new = YOS_ANM_TYOUHATU;
			p1_gGame.zoom += ZOOM_SPEED;//zoom in
			if(p1_gGame.zoom >ZOOM_MAX)
				p1_gGame.zoom = ZOOM_MAX;
		}else
		{//button is not pressed
			p1_gGame.zoom -= 0x100;//zoom out
			if(p1_gGame.zoom < ZOOM_1)p1_gGame.zoom = ZOOM_1;
		}
	}else if(p1_gGame.zoom > ZOOM_1)//zooming
	{
		p1_gGame.zoom -= ZOOM_SPEED;//zoom out
		if(p1_gGame.zoom < ZOOM_1)p1_gGame.zoom = ZOOM_1;
	}
	
	if(anmWork[ANM_WORK_YOSHI].anm_ptn != p1_yoshiWork.anm_ptn_new)
	{
		anmWork[ANM_WORK_YOSHI].anm_ptn = p1_yoshiWork.anm_ptn_new;
		anmWork[ANM_WORK_YOSHI].flg = ANM_FLG_NEW;
	}
	//When reached an edge, warp to the other edge
	if(p1_yoshiWork.pos.x >(BG_L)*0x10000)
	{
		p1_yoshiWork.pos.x -= BG_L*0x10000;
		p1_gGame.disp_x -= BG_L*0x10000;
	}
	if(p1_yoshiWork.pos.x <(0)*0x10000)
	{
		p1_yoshiWork.pos.x += BG_L*0x10000;
		p1_gGame.disp_x += BG_L*0x10000;
	}
	p1_yos_histry_set();
	p1_yoshiWork.pos_old=p1_yoshiWork.pos;
}

void p1_yos_histry_set(void)
{
	s16 i,j,pos_old[3];
	
	for(i=0;i<3;i++)
	{
		if(i >= p1_yoshiWork.egg_num)break;
		j = (p1_yoshiWork.history_cur + YOS_HISTORY_MAX - (i+1)*YOS_EGG_DIFF) % YOS_HISTORY_MAX;
		pos_old[i] = p1_yoshiWork.pos_history[j].y;
	}
	
	//History for the position of egg
	if(   p1_yoshiWork.pos.x != p1_yoshiWork.pos_old.x
	   || p1_yoshiWork.pos.y != p1_yoshiWork.pos_old.y)
	{
		//move
		p1_yoshiWork.history_cur = (p1_yoshiWork.history_cur+1) % YOS_HISTORY_MAX;
		p1_yoshiWork.pos_history[p1_yoshiWork.history_cur].x = p1_yoshiWork.pos.x >> 16;
		if( p1_yoshiWork.pos.y + (p1_yoshiWork.col[1].y<<16) < p1_getMap(p1_yoshiWork.pos.x) )
//			p1_yoshiWork.pos_history[p1_yoshiWork.history_cur].y = ((p1_yoshiWork.pos.y>> 16)+16-4)|0x8000;//floating
			p1_yoshiWork.pos_history[p1_yoshiWork.history_cur].y = ((p1_yoshiWork.pos.y>>16)+p1_yoshiWork.col[1].y-p1_charSpecData[CHR_TYPE_EGG].col[1].y)+0x1000;//floating
		else
//			p1_yoshiWork.pos_history[p1_yoshiWork.history_cur].y = ((p1_yoshiWork.pos.y>>16)+p1_yoshiWork.col[1].y-p1_charSpecData[CHR_TYPE_EGG].col[1].y);//
			p1_yoshiWork.pos_history[p1_yoshiWork.history_cur].y = (p1_yoshiWork.pos.y>>16);//
	}else
	{//move 1 if floating
		for(i=1; i<YOS_HISTORY_MAX; i++)
		{
//			if(p1_yoshiWork.pos_history[(p1_yoshiWork.history_cur+i) % YOS_HISTORY_MAX].y & 0x8000)
			if(p1_yoshiWork.pos_history[(p1_yoshiWork.history_cur+i) % YOS_HISTORY_MAX].y > 0x900)
			{//slide 1 because floating
				j = (p1_yoshiWork.history_cur+1) % YOS_HISTORY_MAX;
				p1_yoshiWork.pos_history[j] = p1_yoshiWork.pos_history[p1_yoshiWork.history_cur];
				p1_yoshiWork.history_cur = j;
				break;
			}
		}
	}
#ifdef SOUND_ON
	for(i=0;i<3;i++)
	{
		if(i>=p1_yoshiWork.egg_num)break;
		j = (p1_yoshiWork.history_cur + YOS_HISTORY_MAX - (i+1)*YOS_EGG_DIFF) % YOS_HISTORY_MAX;
		if(pos_old[i]>0x900 && p1_yoshiWork.pos_history[j].y < 0x900)
		{//Egg landed now
			m4aSongNumStart(p1_egg_se_tbl[i]);
		}
	}
#endif
}
////////////////////////////////////////////////////////////////////////////
//Move of Shy Guy
//Number of chr_num p1_charWork
void p1_heiho_move(u8 chr_num)
{
	xyPos pos,pos_old;
	s8 anm_w;
	CharacterWork *pChr;
	
	pChr = &p1_charWork[chr_num];
//	anm_w = ANM_WORK_HEIHO0+p1_charMapData[chr_num].dat2;
	anm_w = ANM_WORK_HEIHO0+pChr->work2;
	
	switch(pChr->status)
	{
	case HEIHO_ST_NA://
		//Make active if enter the screen
		pos.x = p1_get_rel_pos(pChr->pos.x);
		
		if( (pos.x + p1_charSpecData[CHR_TYPE_HEIHO].mid.x > -120*0x10000)
		 && (pos.x - p1_charSpecData[CHR_TYPE_HEIHO].mid.x <  120*0x10000))
		{//Make active because within screen 
			pChr->status = HEIHO_ST_NORMAL;
			pChr->dir = CHR_DIR_L;
			pChr->a.x = ZOOM_1;
			pChr->a.y = ZOOM_1;
			anmWork[anm_w].anm_ptn = HEIHO_ANM_WALK;
			anmWork[anm_w].flg = ANM_FLG_NEW;
//			pChr->work3=1;
			anmWork[anm_w].pPixTbl = p1_heiho_pix_tbl[pChr->work3];
//			anmWork[anm_w].pPixTbl = (u8**)heiho_b_pixel_tbl;
		}else break;
		
	case HEIHO_ST_NORMAL://normal condition
		if(p1_gGame.gnd_bias_count == GND_BIAS_FRM_2)
		{
			pChr->work3 = (pChr->work3+1) % HEIHO_COLOR_NUM;
			anmWork[anm_w].pPixTbl = p1_heiho_pix_tbl[pChr->work3];
			anmWork[anm_w].flg = ANM_FLG_PIX_CHG;
		}
		if(p1_gGame.gnd_bias_count>0)break;//no move while shaking
		//fix to the coordinate that has the center of screen as origin (wrap the opposite edge)
		pos.x = p1_get_rel_pos(pChr->pos.x);
		
		if( (pos.x + p1_charSpecData[CHR_TYPE_HEIHO].mid.x < -120*0x10000)
		 || (pos.x - p1_charSpecData[CHR_TYPE_HEIHO].mid.x >  120*0x10000))
		{//Makes it non-active since it was outside screen
			anmWork[anm_w].flg = -1;
			if(p1_charMapData[chr_num].char_type == CHR_TYPE_BALLOON)
			{//character changed from balloon
				p1_balloon_dead(chr_num);
			}else
			{
				pChr->status = HEIHO_ST_NA;
			}
			break;
		}
		switch(pChr->dir)
		{
		case CHR_DIR_L://facing left
		case CHR_DIR_R://facing right
			pos_old=pChr->pos;
			pChr->pos.x += (pChr->dir>0)? HEIHO_MOV_SPEED : -HEIHO_MOV_SPEED;
			pChr->pos.y = p1_getMap(pChr->pos.x)-(p1_charSpecData[CHR_TYPE_HEIHO].col[1].y<<16);
			if( ((pChr->dir>0)&&(pChr->pos.x > (pChr->work1<<16)))
			 || ((pChr->dir<0)&&(pChr->pos.x < (pChr->work0<<16))) )
			{//came to the edge
				pChr->pos=pos_old;
				pChr->dir   = (pChr->dir>0)? CHR_DIR_TL0:CHR_DIR_TR0;
				pChr->work4 = 0;
				anmWork[anm_w].anm_ptn  = HEIHO_ANM_TURN;
				anmWork[anm_w].flg = ANM_FLG_NEW;
			}
			break;
		case CHR_DIR_TL0://
		case CHR_DIR_TR0://
			if(++pChr->work4 > 24)
			{
				pChr->dir = (pChr->dir>0)? CHR_DIR_L:CHR_DIR_R;
				anmWork[anm_w].anm_ptn = HEIHO_ANM_WALK;
				anmWork[anm_w].flg = ANM_FLG_NEW;
			}
			break;
		}
		break;
	case HEIHO_ST_DYING://die after stomped on
		if(pChr->work4 == 0)
		{//Save Feet Y coordinate to Initialization v
			pChr->v.y = pChr->pos.y+(16<<16);
		}
		pChr->work4++;
		pChr->a.x = ZOOM_1+ZOOM_1*(pChr->work4)/0x20;//stretch sideways
		pChr->a.y = ZOOM_1*(0x20-pChr->work4)/0x20;//smash vertically
		pChr->pos.y = pChr->v.y - 16*pChr->a.y;//smash
		if(pChr->work4 >= 0x20)
		{
			anmWork[anm_w].flg = -1;//animation complete
			if(p1_charMapData[chr_num].char_type == CHR_TYPE_BALLOON)
			{//character changed from balloon
				p1_balloon_dead(chr_num);
			}else
			{
				pChr->status = HEIHO_ST_NONE;//none
			}
		}
		break;
	}
}
////////////////////////////////////////////////////////////////////////////
//Move of shy guy
//Number of chr_num p1_charWork
void p1_heihoL_move(u8 chr_num)
{
	xyPos pos,pos_old;
	s8 anm_w;
	CharacterWork *pChr;
	
	pChr = &p1_charWork[chr_num];
	
	switch(pChr->status)
	{
	case HEIHO_ST_NA://
		//Make active if enter screen
		pos.x = p1_get_rel_pos(pChr->pos.x);
		
		if( (pos.x + p1_charSpecData[CHR_TYPE_HEIHOL].mid.x > -120*0x10000)
		 && (pos.x - p1_charSpecData[CHR_TYPE_HEIHOL].mid.x <  120*0x10000))
		{//Makes active because within screen
			pChr->status = HEIHO_ST_NORMAL;
			pChr->dir = CHR_DIR_L;
			pChr->a.x = ZOOM_1;
			pChr->a.y = ZOOM_1;
			anmWork[ANM_WORK_HEIHOL].anm_ptn = HEIHO_ANM_WALK;
			anmWork[ANM_WORK_HEIHOL].flg = ANM_FLG_NEW;
		}else break;
		
	case HEIHO_ST_NORMAL://normal condition
		if(p1_gGame.gnd_bias_count > 0)break;//does not move while shaking
		
		//Makes it non-active when out of screen
		
		//fix to the coordinate with the center of screen as origin (wrap the opposite edge)
		pos = pChr->pos;
		pos.x = p1_get_rel_pos(pos.x);
		
		if( (pos.x + p1_charSpecData[CHR_TYPE_HEIHO].mid.x < -120*0x10000)
		 || (pos.x - p1_charSpecData[CHR_TYPE_HEIHO].mid.x >  120*0x10000))
		{//Make it non-active since it is outside of the area
			pChr->status = HEIHO_ST_NA;
			anmWork[ANM_WORK_HEIHOL].flg = -1;//Stop Animation
			break;
		}
		switch(pChr->dir)
		{
		case CHR_DIR_L://Facing left
		case CHR_DIR_R://facing right
			pos_old=pChr->pos;
			pChr->pos.x += (pChr->dir>0)? HEIHO_MOV_SPEED : -HEIHO_MOV_SPEED;
			pChr->pos.y = p1_getMap(pChr->pos.x)-(p1_charSpecData[CHR_TYPE_HEIHOL].col[1].y<<16);
			if( ((pChr->dir>0)&&(pChr->pos.x > (pChr->work1<<16)))
			 || ((pChr->dir<0)&&(pChr->pos.x < (pChr->work0<<16))) )
			{//came to the edge
				pChr->pos=pos_old;
				pChr->dir   = (pChr->dir>0)? CHR_DIR_TL0:CHR_DIR_TR0;
				pChr->work4 = 0;
				anmWork[ANM_WORK_HEIHOL].anm_ptn  = HEIHO_ANM_TURN;
				anmWork[ANM_WORK_HEIHOL].flg = ANM_FLG_NEW;
			}
			break;
		case CHR_DIR_TL0://
		case CHR_DIR_TR0://
			if(++pChr->work4 > 24)//turn-around animation complete
			{
				pChr->dir = (pChr->dir>0)? CHR_DIR_L:CHR_DIR_R;
				anmWork[ANM_WORK_HEIHOL].anm_ptn = HEIHO_ANM_WALK;
				anmWork[ANM_WORK_HEIHOL].flg = ANM_FLG_NEW;
			}
			break;
		}
		break;
	case HEIHO_ST_DYING://die after stamped
		if(pChr->work4 == 0)
		{//Save Feet Y coordinate to Initialization v
			pChr->v.y = pChr->pos.y+(32<<16);
		}
		pChr->work4++;
		
		pChr->a.x = ZOOM_1*(0x40-pChr->work4)/0x40;//stretch sideways
		pChr->a.y = ZOOM_1*(0x40-pChr->work4)/0x40;//smashed vertically
		pChr->pos.y = pChr->v.y - (32)*pChr->a.y;//Keep the location of feet by moving the amount it is smashed
		if(pChr->work4 >= 0x20)
		{
//			pChr->status = HEIHO_ST_NONE;//none
			anmWork[ANM_WORK_HEIHOL].flg=-1;//animation complete
			
			pChr->char_type = CHR_TYPE_HEIHO;//change into Shy Guy (small)
			pChr->status    = HEIHO_ST_NORMAL;//
			pChr->hit_flg   = p1_charSpecData[CHR_TYPE_HEIHO].hit_flg;
			pChr->dir = CHR_DIR_L;
			pChr->a.x = ZOOM_1;
			pChr->a.y = ZOOM_1;
//			anm_w=ANM_WORK_HEIHO0+p1_charMapData[chr_num].dat2;
			anm_w=ANM_WORK_HEIHO0+pChr->work2;
			anmWork[anm_w].anm_ptn = HEIHO_ANM_WALK;
			anmWork[anm_w].flg = ANM_FLG_NEW;
		}
		break;
	}
}
////////////////////////////////////////////////////////////////////////////
//Move of Killer S
//Number of chr_num p1_charWork
void p1_killerS_move(u8 chr_num)
{
	xyPos pos;
	s8 dir;
	CharacterWork *pChr;
	
	pChr = &p1_charWork[chr_num];
	
	switch(pChr->status)
	{
	case KILLERS_ST_NA://not active
		//makes active when enter screen
		pos = pChr->pos;
		
//		if( (pos.x + p1_charSpecData[CHR_TYPE_KILLER_S].mid.x > p1_gGame.disp_x-120*0x10000)
//		 && (pos.x - p1_charSpecData[CHR_TYPE_KILLER_S].mid.x < p1_gGame.disp_x+120*0x10000))
		if(((pos.x + p1_charSpecData[CHR_TYPE_KILLER_S].mid.x > p1_gGame.disp_x-120*0x10000)
		  &&(pos.x + p1_charSpecData[CHR_TYPE_KILLER_S].mid.x < p1_gGame.disp_x-118*0x10000))
		 ||((pos.x - p1_charSpecData[CHR_TYPE_KILLER_S].mid.x < p1_gGame.disp_x+120*0x10000)
		  &&(pos.x - p1_charSpecData[CHR_TYPE_KILLER_S].mid.x > p1_gGame.disp_x+118*0x10000))
		 )
		{//Makes active since within screen
			pChr->status = KILLERS_ST_NORMAL;
			if(p1_yoshiWork.pos.x < pChr->pos.x)dir = CHR_DIR_L;else dir = CHR_DIR_R;
			pChr->v.x = KILLER_MOV_SPEED * dir;
			pChr->dir = dir;
#ifdef SOUND_ON
			m4aSongNumStart(YOS_SE_SID1);
#endif
		}else break;
		
	case KILLERS_ST_NORMAL://normal condition
		pChr->pos.x += pChr->v.x;
		//warp
		if(pChr->pos.x < 0)pChr->pos.x += BG_L*0x10000;
		if(pChr->pos.x > BG_L*0x10000)pChr->pos.x -= BG_L*0x10000;
		
		pos.x = p1_get_rel_pos(pChr->pos.x);
		
		if((pos.x < -240*0x10000)
		 ||(pos.x >  240*0x10000))
		{//disappeared because went too far
			if(p1_charMapData[chr_num].char_type == CHR_TYPE_BALLOON)
			{//character changed from balloon
				p1_balloon_dead(chr_num);
			}else
			{
				pChr->status = KILLERS_ST_NA;
			}
		}
		break;
	case KILLERS_ST_DYING://die when stomped on
		if(pChr->work0 == 0)
		{
			pChr->v.y = 0;
		}
		pChr->work0++;
		pChr->v.y += KILLERS_FALL_ACC;
		pChr->pos.x += pChr->v.x;
		pChr->pos.y +=pChr->v.y;
		if(pChr->pos.y-p1_gGame.disp_y-32*0x10000 > (80<<16))
		{
			if(p1_charMapData[chr_num].char_type == CHR_TYPE_BALLOON)
			{//characters changed from balloon
				p1_balloon_dead(chr_num);
			}else
			{
				pChr->status = KILLERS_ST_NONE;//none
			}
		}
		break;
	}
}
////////////////////////////////////////////////////////////////////////////
//Move of balloon
//Number of chr_num p1_charWork
void p1_balloon_move(u8 chr_num)
{
	xyPos pos,effv,effp;
	s32 r_,mapY,dir;
	s16 i,d0;
	CharacterWork *pChr;
	
	pChr = &p1_charWork[chr_num];
	
	switch(pChr->status)
	{
	case BALLOON_ST_NORMAL://Normal condition
		pChr->pos.x += pChr->v.x;//Move
		pChr->pos.y += pChr->v.y;//Move
		if(abs(pChr->v.x) < BALLOON_MASATU_ACC)pChr->v.x = 0;
		if(     pChr->v.x>0)pChr->v.x -= BALLOON_MASATU_ACC;
		else if(pChr->v.x<0)pChr->v.x += BALLOON_MASATU_ACC;
		
		if(abs(pChr->v.y) < BALLOON_MASATU_ACC)pChr->v.y = 0;
		if(     pChr->v.y>0)pChr->v.y -=BALLOON_MASATU_ACC;
		else if(pChr->v.y<0)pChr->v.y +=BALLOON_MASATU_ACC;
		
		//warp
		if(pChr->pos.x < 0)pChr->pos.x += BG_L*0x10000;
		if(pChr->pos.x > BG_L*0x10000)pChr->pos.x -= BG_L*0x10000;
		pos.x = p1_get_rel_pos(pChr->pos.x);
		
		if((pos.x < -240*0x10000) ||(pos.x >  240*0x10000))
		{//Disappeared because it went too far
			pChr->status = BALLOON_ST_NA;
		}
		break;
	case BALLOON_ST_HARETU://Burst after stomped on
 		if(pChr->work0 == 0)
		{
			pChr->v = pChr->pos;
		}
		r_ = pChr->work0;
		pChr->pos.x = pChr->v.x + r_*fix_sin[pChr->work0*4 & 0xff]*0x100;
		pChr->pos.y = pChr->v.y + r_*fix_sin[pChr->work0*8 & 0xff]*0x100;
//		p1_charWork[chr_num].pos.x = p1_get_rel_pos(p1_charWork[chr_num].pos.x)+p1_gGame.disp_x;
		pChr->pos.x = p1_get_lap_pos(pChr->pos.x);
		affineWork[AFN_WORK_BALLOON].rot = (0xd0+pChr->work0*8) & 0xff;
		affineWork[AFN_WORK_BALLOON].zoom.x = 0x10000 * (0x80 - pChr->work0)/0x60;//leave it a little bit big
		pChr->work0++;
		mapY = p1_getMap(pChr->pos.x);
		if(pChr->work0 > 0x80 || mapY < pChr->pos.y)
		{
			pos.x = p1_get_lap_pos(pChr->pos.x);
//			pos.y = p1_charWork[chr_num].pos.y;
			pChr->pos.x=pos.x;
			r_=p1_gGame.game_timer&1;
			if(mapY < pChr->pos.y)
			{//land
				pChr->pos.y = mapY;
				effp.x = pChr->pos.x;
				effp.y = pChr->pos.y;
				effv.y = -0x4000;
				effv.x = 0x8000;
				p1_effectSet(EFF_TYPE_SMOKE, effp, &effv);
				effv.x = -0x8000;
				p1_effectSet(EFF_TYPE_SMOKE, effp, &effv);
				effv.x = 0x3000;
				effv.y = -0x3000;
				p1_effectSet(EFF_TYPE_DASH, effp, &effv);
				
				//Check to see if there is space in egg
				for(i=0,d0=-1; i<EGG_WORK_MAX; i++)
				{
					if(p1_eggWork[i].status == EGG_ST_NONE)
					{
						d0 = i;
						break;
					}
				}
				
//				if(r_ == 0 && d0 != -1)
				if(d0 != -1)
				{//Egg
					p1_eggWork[d0].status = EGG_ST_NORMAL;
					p1_eggWork[d0].pos = pChr->pos;
					p1_eggWork[d0].v.x = 0;
					p1_eggWork[d0].v.y = 0;
					p1_balloon_dead(chr_num);
#ifdef SOUND_ON
					m4aSongNumStart(YOS_SE_DERUP);// Egg acquisition sound
#endif
				}else
				{//Shy Guy
					pChr->char_type = CHR_TYPE_HEIHO;//Change to Small Shy Guy
					pChr->status    = HEIHO_ST_NORMAL;//
					pChr->hit_flg   = p1_charSpecData[CHR_TYPE_HEIHO].hit_flg;
					pChr->pos.y = p1_getMap(pChr->pos.x)-(p1_charSpecData[CHR_TYPE_HEIHO].col[1].y<<16);
					pChr->dir   = CHR_DIR_L;
					pChr->a.x   = ZOOM_1;
					pChr->a.y   = ZOOM_1;
					pChr->work0 = p1_charWork[chr_num].pos.x>>16;//Move screen
					pChr->work1 = p1_charWork[chr_num].work0+10;
					pChr->work3 = 0;//color
					if(pChr->work1 > BG_L)pChr->work1 = pChr->work0-20;
					
					if(p1_getMap(pChr->work0<<16) != p1_getMap(pChr->work1<<16))
					{
						pChr->work1=pChr->work0;
					}
					pChr->work2 = 5;//Work of Animation
					anmWork[ANM_WORK_HEIHO0+5].pPixTbl = p1_heiho_pix_tbl[pChr->work3];
					anmWork[ANM_WORK_HEIHO0+5].anm_ptn = HEIHO_ANM_WALK;
					anmWork[ANM_WORK_HEIHO0+5].flg     = ANM_FLG_NEW;
				}
			}else
			{//In the air
				//Killer
				pChr->char_type = CHR_TYPE_KILLER_S;//Change to Killer S
				pChr->status    = KILLERS_ST_NORMAL;//
				pChr->hit_flg   = p1_charSpecData[CHR_TYPE_KILLER_S].hit_flg;
				pChr->dir       = CHR_DIR_L;
				if(p1_yoshiWork.pos.x < pChr->pos.x)dir = CHR_DIR_L;else dir = CHR_DIR_R;
				pChr->v.x = KILLER_MOV_SPEED * dir;
				pChr->dir = dir;
			}
		}
		break;
	}
}
////////////////////////////////////////////////////////////////////////////
//Move of 5t
//Number of chr_num p1_charWork
void p1_omori_move(u8 chr_num)
{
	xyPos pos;
	CharacterWork *pChr;
	pChr = &p1_charWork[chr_num];
	
	switch(pChr->status)
	{
	case CHAR_ST_NA://Not Active
		//Make active when in screen
		pos = pChr->pos;
		pos.x=p1_get_lap_pos(pos.x);
		if((pos.x + p1_charSpecData[CHR_TYPE_5T].mid.x > p1_gGame.disp_x-120*0x10000)
		 &&(pos.x - p1_charSpecData[CHR_TYPE_5T].mid.x < p1_gGame.disp_x+120*0x10000)
		 )
		{//Make active since within screen
			pChr->status = CHAR_ST_NORMAL;
			pChr->dir = CHR_DIR_L;//in case
			pChr->work4 = 0;//
			pChr->v.y = 0;
			pChr->pos.y = p1_charMapData[chr_num].start_pos.y<<16;
		}else break;
		
	case CHAR_ST_NORMAL://Normal Condition
		switch(pChr->work4)
		{
		case 0:
			pChr->v.y += 0x2000;
			pChr->pos.y += pChr->v.y;
			//May overlap with Yoshi
			if(	p1_yoshiWork.pos.x+((s32)p1_yoshiWork.col[0].x<<16) < pChr->pos.x+((s32)p1_charSpecData[CHR_TYPE_5T].col[1].x<<16)
			&&	p1_yoshiWork.pos.x+((s32)p1_yoshiWork.col[1].x<<16) > pChr->pos.x+((s32)p1_charSpecData[CHR_TYPE_5T].col[0].x<<16)
			&&	p1_yoshiWork.pos.y+((s32)p1_yoshiWork.col[0].y<<16) < pChr->pos.y+((s32)p1_charSpecData[CHR_TYPE_5T].col[1].y<<16)
//			&&	p1_yoshiWork.pos.y+((s32)p1_yoshiWork.col[1].y<<16) > pChr->pos.y+((s32)p1_charSpecData[CHR_TYPE_5T].col[0].y<<16)
			&&	p1_yoshiWork.pos.y+((s32)p1_yoshiWork.col[1].y<<16) > pChr->pos.y
			)
			{
//				p1_yoshiWork.pos.y = pChr->pos.y+((s32)p1_charSpecData[CHR_TYPE_5T].col[0].y<<16)
//									-((s32)p1_yoshiWork.col[1].y<<16);//Exit to the top
				if(p1_yoshiWork.status!=YOSHI_ST_DIE && p1_yoshiWork.muteki_timer==0) p1_yoshi_dead_set();
			}
			pos.y=p1_getMap(pChr->pos.x)-(p1_charSpecData[CHR_TYPE_5T].col[1].y<<16);
			if(pChr->pos.y>pos.y)
			{
				pChr->pos.y = pos.y;
				pChr->v.y = -0x8000;
				p1_gGame.gnd_bias_count = 1;
				pChr->work3 = 0;//
				pChr->work4++;
#ifdef SOUND_ON
				m4aSongNumStart(YOS_SE_DSIN);
#endif
			}
			break;
		case 1://WAIT
			if(pChr->work3++>0x40)
			{
				pChr->v.y = -0x8000;
				pChr->work4++;
			}
			break;
		case 2://pull up
			pChr->pos.y += pChr->v.y;
			//may overlap yoshi
			if(	p1_yoshiWork.pos.x+((s32)p1_yoshiWork.col[0].x<<16) < pChr->pos.x+((s32)p1_charSpecData[CHR_TYPE_5T].col[1].x<<16)
			&&	p1_yoshiWork.pos.x+((s32)p1_yoshiWork.col[1].x<<16) > pChr->pos.x+((s32)p1_charSpecData[CHR_TYPE_5T].col[0].x<<16)
//			&&	p1_yoshiWork.pos.y+((s32)p1_yoshiWork.col[0].y<<16) < pChr->pos.y+((s32)p1_charSpecData[CHR_TYPE_5T].col[1].y<<16)
			&&	p1_yoshiWork.pos.y+(16<<16)< pChr->pos.y
			&&	p1_yoshiWork.pos.y+((s32)p1_yoshiWork.col[1].y<<16) > pChr->pos.y+((s32)p1_charSpecData[CHR_TYPE_5T].col[0].y<<16)
			)
			{
				p1_yoshiWork.pos.y = pChr->pos.y+((s32)p1_charSpecData[CHR_TYPE_5T].col[0].y<<16)
									-((s32)p1_yoshiWork.col[1].y<<16);//exit to the top
			}
			pos.y=p1_charMapData[chr_num].start_pos.y<<16;
			if(pChr->pos.y<pos.y)
			{
				pChr->pos.y = pos.y;
				pChr->v.y = 0;
				pChr->work4 = 0;
			}
			break;
		}
		//warp
		pos.x = p1_get_rel_pos(pChr->pos.x);
		
		if((pos.x < -240*0x10000)
		 ||(pos.x >  240*0x10000))
		{//disappeared since it went too far
			pChr->status = CHAR_ST_NA;
		}
		break;
	}
}
////////////////////////////////////////////////////////////////////////////
//Move of Bob-Omb
//Number of chr_num p1_charWork
void p1_bomb_move(u8 chr_num)
{
	xyPos pos;
	s8 anm_w;
	CharacterWork *pChr;
	
	pChr = &p1_charWork[chr_num];
	anm_w = ANM_WORK_BOMB;
	
	switch(pChr->status)
	{
	case CHAR_ST_NA://
		//make active if enter screen
		pos.x = p1_get_rel_pos(pChr->pos.x);
		
		if( (pos.x + p1_charSpecData[CHR_TYPE_BOMB].mid.x > -120*0x10000)
		 && (pos.x - p1_charSpecData[CHR_TYPE_BOMB].mid.x <  120*0x10000))
		{//Make it active if within screen
			pChr->status = CHAR_ST_NORMAL;
			pChr->dir = CHR_DIR_L;
			pChr->a.x = ZOOM_1;
			pChr->a.y = ZOOM_1;
			anmWork[anm_w].anm_ptn = 1;
			anmWork[anm_w].flg = ANM_FLG_NEW;
		}else break;
		
	case CHAR_ST_NORMAL://normal condition
		if(p1_gGame.gnd_bias_count>0)break;//do not move while shaking
		//Fix to the coordinate that has the center of the screen as origin (wrap the opposite edge)
		pos.x = p1_get_rel_pos(pChr->pos.x);
		
		if( (pos.x + p1_charSpecData[CHR_TYPE_BOMB].mid.x < -120*0x10000)
		 || (pos.x - p1_charSpecData[CHR_TYPE_BOMB].mid.x >  120*0x10000))
		{//Make non-active as it is outside screen
			anmWork[anm_w].flg = -1;
			pChr->status = CHAR_ST_NA;
			break;
		}
		switch(pChr->dir)
		{
		case CHR_DIR_R://facing Right
			pChr->pos.x += HEIHO_MOV_SPEED;
			pChr->pos.y = p1_getMap(pChr->pos.x)-(p1_charSpecData[CHR_TYPE_BOMB].col[1].y<<16);
			if(pChr->pos.x > (pChr->work1<<16))
			{//came to the right edge
				pChr->dir   = CHR_DIR_L;
			}
			break;
		case CHR_DIR_L://facing left
			pChr->pos.x -= HEIHO_MOV_SPEED;
			pChr->pos.y = p1_getMap(pChr->pos.x)-(p1_charSpecData[CHR_TYPE_BOMB].col[1].y<<16);
			
			if(pChr->pos.x < (pChr->work0<<16))
			{//came to the left edge
				pChr->dir   = CHR_DIR_R;
			}
			break;
		}
		break;
	case BOMB_ST_DYING://die when stomped on
		if(pChr->work4 == 0)
		{//Save Feet Y Coordinate in Initialization v
			pChr->v.y = pChr->pos.y+(16<<16);
		}
		pChr->work4++;
		if(pChr->work4 >= 0x10)
		{
			anmWork[anm_w].flg = -1;//Animation Complete
			pChr->status = CHAR_ST_NONE;//None
		}
		break;
	}
}
////////////////////////////////////////////////////////////////////////////
//Move of Kokamek (during game)
//Number of chr_num p1_charWork
void p1_kokamek_move(u8 chr_num)
{
	xyPos pos;
	CharacterWork *pChr;
	
	pChr = &p1_charWork[chr_num];
	
	switch(pChr->status)
	{
	case CHAR_ST_NA://
		//Make active if in screen
		pos.x = p1_get_rel_pos(pChr->pos.x);
		
		if(p1_charWork[chr_num+1].status>0)break;//if hanging thorn is active, send its appearance
#if 0
		if( (pos.x + p1_charSpecData[CHR_TYPE_KOKAMEK0].mid.x > -120*0x10000)
		 && (pos.x - p1_charSpecData[CHR_TYPE_KOKAMEK0].mid.x <  120*0x10000))
#else
		if(((pos.x + p1_charSpecData[CHR_TYPE_KOKAMEK0].mid.x > -120*0x10000)
		  &&(pos.x + p1_charSpecData[CHR_TYPE_KOKAMEK0].mid.x < -118*0x10000))
		 ||((pos.x - p1_charSpecData[CHR_TYPE_KOKAMEK0].mid.x <  120*0x10000)
		  &&(pos.x - p1_charSpecData[CHR_TYPE_KOKAMEK0].mid.x >  118*0x10000)))
#endif
		{//Make active as it is within screen
			pChr->status = CHAR_ST_NORMAL;
			pChr->dir = CHR_DIR_R;
			
			{
				p1_charWork[chr_num+1].status = CHAR_ST_NORMAL;
				p1_charWork[chr_num+1].pos    = pChr->pos;
				p1_charWork[chr_num+1].work0  = 1;//hanging
				p1_charWork[chr_num+1].work1  = 0;//Revolving Flag
				p1_charWork[chr_num+1].work2  = 1;//Flag to first check if it touched the ground
				p1_charWork[chr_num+1].v.y    = 0;
				p1_charWork[chr_num+1].dir    = CHR_DIR_R;
				pChr->work2 = 1;
			}
#ifdef SOUND_ON
			m4aSongNumStart(YOS_SE_UKUU);
#endif
		}else break;
	case CHAR_ST_NORMAL://Normal condition
		//Fix to the coordinate that has the center of screen as origin (wrap the opposite edge)
		pos.x = p1_get_rel_pos(pChr->pos.x);
		
		if( (pos.x + p1_charSpecData[CHR_TYPE_KOKAMEK0].mid.x < -(200<<16))
		 || (pos.x - p1_charSpecData[CHR_TYPE_KOKAMEK0].mid.x >  (200<<16))
		 )
		{//Make it non-active as it is outside of the screen
			if(pChr->work2==0)
			{//not hanging
				pChr->status = CHAR_ST_NA;
			}else
			{//hanging
				pChr->status = CHAR_ST_NA;
				(pChr+1)->status = CHAR_ST_NA;
			}
			break;
		}
		if(pChr->work2==0)//hanging
		{
			pChr->pos.y-=0x10000;
			if(pChr->pos.y-p1_gGame.disp_y<-(160<<16))
			{
				pChr->status = CHAR_ST_NA;
				pChr->pos.y = p1_charMapData[chr_num].start_pos.y;
			}
		}else
		{//hanging
			if(p1_yoshiWork.pos.y < pChr->pos.y)
			{//Yoshi is on top
				pChr->pos.y-=0x10000;
			}else if(p1_getMap(pChr->pos.x)<pChr->pos.y+(60<<16))
			{
				pChr->pos.y-=0x10000;
			}else if(p1_yoshiWork.pos.y > pChr->pos.y+(60<<16))
			{//too low
				if(p1_getMap(pChr->pos.x) >= pChr->pos.y+(61<<16))pChr->pos.y+=0x10000;
			}
		}
		switch(pChr->dir)
		{
		case CHR_DIR_R://facing right
			pChr->pos.x += HEIHO_MOV_SPEED;
			if(pChr->pos.x > (pChr->work1<<16))
			{//came to the right edge
				pChr->dir   = CHR_DIR_L;
#ifdef SOUND_ON
			m4aSongNumStart(YOS_SE_UKUU);
#endif
			}
			break;
		case CHR_DIR_L://direction to left
			pChr->pos.x -= HEIHO_MOV_SPEED;
			
			if(pChr->pos.x < (pChr->work0<<16))
			{//came to left end
				pChr->dir   = CHR_DIR_R;
#ifdef SOUND_ON
			m4aSongNumStart(YOS_SE_UKUU);
#endif
			}
			break;
		}
		break;
	}
	
	if(pChr->work2 == 1)//hanging
	{
		p1_charWork[chr_num+1].pos.x=pChr->pos.x;
		p1_charWork[chr_num+1].pos.y=pChr->pos.y+(8<<16);
		if(abs(p1_yoshiWork.pos.x-pChr->pos.x)<(16<<16)
			&& p1_yoshiWork.pos.y>pChr->pos.y)
		{//drop when near
			pChr->work2 = 0;//not hanging
			p1_charWork[chr_num+1].work0 = 0;//not hanging
			p1_charWork[chr_num+1].work2 = 1;//flag to first check if it touched the ground
			p1_charWork[chr_num+1].work1 = 0;//Revolving flag
		}
	}
	
}

////////////////////////////////////////////////////////////////////////////
//Move of thorn
//Number of chr_num p1_charWork
void p1_toge_move(u8 chr_num)
{
	xyPos pos;
	s32 mapY;
	CharacterWork *pChr;
	
	pChr = &p1_charWork[chr_num];
	
	switch(pChr->status)
	{
	case CHAR_ST_NORMAL://Normal Condition
		//Fix to the coordinate that has the center of screen as origin (wrap the opposite edge)
		pos.x = p1_get_rel_pos(pChr->pos.x);
		pos.y = pChr->pos.y;
		if( (pos.x + p1_charSpecData[CHR_TYPE_TOGE].mid.x < -200*0x10000)
		 || (pos.x - p1_charSpecData[CHR_TYPE_TOGE].mid.x >  200*0x10000)
		 || (pos.y > YOSHI_DEAD_LIMIT)
		 )
		{//Make non-active as it is outside screen
			if(pChr->work0 == 1)
			{//hanging
//				pChr->status = CHAR_ST_NA;
			}else
			{
				pChr->status = CHAR_ST_NONE;
			}
			break;
		}
		//may overlap yoshi
		if(	p1_yoshiWork.pos.x+((s32)p1_yoshiWork.col[0].x<<16) < pChr->pos.x+((s32)p1_charSpecData[CHR_TYPE_TOGE].col[1].x<<16)
		&&	p1_yoshiWork.pos.x+((s32)p1_yoshiWork.col[1].x<<16) > pChr->pos.x+((s32)p1_charSpecData[CHR_TYPE_TOGE].col[0].x<<16)
		&&	p1_yoshiWork.pos.y+((s32)p1_yoshiWork.col[0].y<<16) < pChr->pos.y+((s32)p1_charSpecData[CHR_TYPE_TOGE].col[1].y<<16)
		&&	p1_yoshiWork.pos.y+((s32)p1_yoshiWork.col[1].y<<16) > pChr->pos.y+((s32)p1_charSpecData[CHR_TYPE_TOGE].col[0].y<<16)
			)
		{
			if(p1_yoshiWork.status!=YOSHI_ST_DIE && p1_yoshiWork.muteki_timer==0) p1_yoshi_dead_set();
		}
		if(pChr->work0 == 1)break;//hanging
		//fall if there is some space at the bottom
		mapY = p1_getMap(pChr->pos.x)-(p1_charSpecData[CHR_TYPE_TOGE].col[1].y<<16);
		if(mapY > pChr->pos.y+(2<<16))
		{
			pChr->v.y   += 0x1000;//acceleration
			if(pChr->v.y>0x40000)pChr->v.y=0x40000;
			pChr->pos.y += pChr->v.y;
			pChr->work1  = 0;
			if(pChr->pos.y+(2<<16) >= mapY)//whether it landed after moving
			{
#ifdef SOUND_ON
				m4aSongNumStart(YOS_SE_RAKA);
#endif
				pChr->pos.y = mapY;
				pChr->v.y = 0;
				if(pChr->work2 > 0)//deciding the direction when it touches the ground for the first time
				{
					if(p1_yoshiWork.pos.x < pChr->pos.x)
						pChr->dir = CHR_DIR_L;
					else
						pChr->dir = CHR_DIR_R;
					
					pChr->work2 = 0;//
				}
			}
		}else
		{
			switch(pChr->dir)
			{
			case CHR_DIR_R://facing Right
				pChr->pos.x += TOGE_MOV_SPEED;
				//Warp
				if(pChr->pos.x > (BG_L<<16))pChr->pos.x-=BG_L<<16;
//				pChr->pos.y = p1_getMap(pChr->pos.x)-(p1_charSpecData[CHR_TYPE_TOGE].col[1].y<<16);
				pChr->pos.y = mapY;//with one previous
				break;
			case CHR_DIR_L://facing left
				pChr->pos.x -= TOGE_MOV_SPEED;
				//warp
				if(pChr->pos.x < 0)pChr->pos.x+=BG_L*0x10000;
//				pChr->pos.y = p1_getMap(pChr->pos.x)-(p1_charSpecData[CHR_TYPE_TOGE].col[1].y<<16);
				pChr->pos.y = mapY;//with one previous
				break;
			}
			pChr->work1 = 1;//revolving flag
		}
		break;
	}
}

////////////////////////////////////////////////////////////////////////////
//Move of box
void p1_hakoMove(u8 char_num)
{
	xyPos pos0;
	s32 w0;
	s16 rot;
	
	if(p1_charWork[char_num].status == HAKO_ST_ROT)//it revolves after pushed up
	{
		p1_charWork[char_num].work0++;
		w0 = p1_charWork[char_num].work0;
		
		if(w0 >= 0x15)
		{
			p1_charWork[char_num].status = HAKO_ST_NORMAL;
//			return;
			goto lab_ret_;
		}else if(w0 < 0x5)
			rot = w0*8;
		else
			rot = 0x40-(w0-5)*4;
		
		if(p1_charWork[char_num].work1 < 0)
		{//rotation to left
			affineWork[AFN_WORK_HAKO].rot = rot/4;
		}else
		{//rotation to right
			affineWork[AFN_WORK_HAKO].rot = (0x100-rot/4)&0xff;
		}
		
		pos0.x = (0x80000 - fix_cos[rot]*0x800)*p1_charWork[char_num].work1;
		pos0.y =-fix_sin[rot]*0x800;
		
		p1_charWork[char_num].a.x = p1_charWork[char_num].pos.x+pos0.x;
		p1_charWork[char_num].a.y = p1_charWork[char_num].pos.y+pos0.y;
		
		if(w0 == 5 && p1_charWork[CHR_WORK_BALLOON].status == 0)//NA
		{//Balloon appears
#ifdef SOUND_ON
			m4aSongNumStart(YOS_SE_APIR);
#endif
			if(p1_charWork[char_num].pos.x<p1_gGame.disp_x)
				p1_charWork[CHR_WORK_BALLOON].pos.x = p1_get_lap_pos(p1_charWork[char_num].pos.x+(80<<16));
			else
				p1_charWork[CHR_WORK_BALLOON].pos.x = p1_get_lap_pos(p1_charWork[char_num].pos.x-(80<<16));
			p1_charWork[CHR_WORK_BALLOON].pos.y    = p1_charWork[char_num].pos.y;
			p1_charWork[CHR_WORK_BALLOON].status   = BALLOON_ST_NORMAL;
			p1_charWork[CHR_WORK_BALLOON].v.x      = 0;
			p1_charWork[CHR_WORK_BALLOON].v.y      = 0;
			p1_charWork[CHR_WORK_BALLOON].dir      = CHR_DIR_L;//in case
			p1_charWork[CHR_WORK_BALLOON].hit_flg  = HIT_LR | HIT_T | HIT_B;
			anmWork[ANM_WORK_BALLOON].anm_ptn   = 1;
			anmWork[ANM_WORK_BALLOON].flg       = ANM_FLG_NEW;
			affineWork[AFN_WORK_BALLOON].rot    = 0;
			affineWork[AFN_WORK_BALLOON].zoom.x = 0x10000;
		}
	}
	
lab_ret_:
	p1_charWork[char_num].rot = affineWork[AFN_WORK_HAKO].rot;//Riding yoshi references

}

////////////////////////////////////////////////////////////////////////////
//Move of characters other than Yoshi
void p1_charMove(void)
{
	s16 i;
	s16 rota;
	
	//Rotation of box
	affineWork[AFN_WORK_HAKO].work0 = (affineWork[AFN_WORK_HAKO].work0+3)&0xff;
	rota = affineWork[AFN_WORK_HAKO].work0;
	if(rota < 0x40)rota = rota * HAKO_ROT_ANGLE/0x40;
	else if(rota < 0x80)rota = -(rota-0x40)*HAKO_ROT_ANGLE/0x40+HAKO_ROT_ANGLE;
	else if(rota < 0xc0)rota = -(rota-0x80)*HAKO_ROT_ANGLE/0x40;
	else rota = (rota-0xc0)*HAKO_ROT_ANGLE/0x40-HAKO_ROT_ANGLE;
	affineWork[AFN_WORK_HAKO].rot = (u8)rota;
	
	//Rotation of flower
	affineWork[AFN_WORK_HANA].work0 = (affineWork[AFN_WORK_HANA].work0+3)&0xff;
	rota = affineWork[AFN_WORK_HANA].work0;
	if(rota < 0x40)rota = rota * HAKO_ROT_ANGLE/0x40;
	else if(rota < 0x80)rota = -(rota-0x40)*HAKO_ROT_ANGLE/0x40+HAKO_ROT_ANGLE;
	else if(rota < 0xc0)rota = -(rota-0x80)*HAKO_ROT_ANGLE/0x40;
	else rota = (rota-0xc0)*HAKO_ROT_ANGLE/0x40-HAKO_ROT_ANGLE;
	affineWork[AFN_WORK_HANA].rot = (u8)rota;
	
	//Rotation of thorn
	affineWork[AFN_WORK_TOGE_L].rot = (affineWork[AFN_WORK_TOGE_L].rot+3)%0xff;
	affineWork[AFN_WORK_TOGE_R].rot = (affineWork[AFN_WORK_TOGE_R].rot+(0x100-3))%0xff;
	
	for(i=0; i<CHARACTER_WORK_MAX; i++)
	{
		if(p1_charWork[i].status <= -1)continue;//-1 None or Complete (when it is 0, process although non-active)
		
		//Process per character
		switch(p1_charWork[i].char_type)
		{
		case CHR_TYPE_HAKO:
			p1_hakoMove(i);
			break;
		case CHR_TYPE_HEIHO:
			p1_heiho_move(i);
			break;
		case CHR_TYPE_HEIHOL:
			p1_heihoL_move(i);
			break;
		case CHR_TYPE_KILLER_S:
			p1_killerS_move(i);
			break;
		case CHR_TYPE_BALLOON:
			p1_balloon_move(i);
			break;
		case CHR_TYPE_5T:
			p1_omori_move(i);
			break;
		case CHR_TYPE_BOMB:
			p1_bomb_move(i);
			break;
		case CHR_TYPE_TOGE:
			p1_toge_move(i);
			break;
		case CHR_TYPE_KOKAMEK0:
			p1_kokamek_move(i);
			break;
		}
	}
}

////////////////////////////////////////////////////////////////////////////
//Move of petals
void p1_hanabiraMove(void)
{
	s16 rot;
	s8 i;
	
	for(i=0; i<8; i++)
	{
		//Revival
		if(p1_hanabiraWork[i].status!=HANABIRA_ST_NORMAL && i<=(p1_yoshiWork.egg_num-1)*3+1)
		{
			p1_hanabiraWork[i].status = HANABIRA_ST_NORMAL;
			p1_hanabiraWork[i].pos    = p1_hanabira_pos[i];
		}
		if(p1_hanabiraWork[i].status <= 0)continue;
		if(p1_hanabiraWork[i].status == HANABIRA_ST_FALL)
		{//Fall
			if(p1_hanabiraWork[i].work1 > 0)
			{
				p1_hanabiraWork[i].work1--;//while waiting
				continue;
			}
			
			p1_hanabiraWork[i].v.y  += HANABIRA_FALL_ACC;  //Acceleration
			p1_hanabiraWork[i].pos.y+= p1_hanabiraWork[i].v.y;//Move
			p1_hanabiraWork[i].work0++;                    //Timer Addition
			
			rot = (p1_hanabiraWork[i].work0 * 8 + p1_hanabira_rot_tbl[i]) & 0xff;//Rotation Angle
			affineWork[AFN_WORK_HANABIRA0+i].param[0] =
			affineWork[AFN_WORK_HANABIRA0+i].param[3] = fix_cos[rot];
			affineWork[AFN_WORK_HANABIRA0+i].param[1] =-fix_sin[rot];
			affineWork[AFN_WORK_HANABIRA0+i].param[2] = fix_sin[rot];
			
			if(p1_hanabiraWork[i].work0 > HANABIRA_FALL_TIME)p1_hanabiraWork[i].status = -1;//complete when time is up
		}
	}
}
////////////////////////////////////////////////////////////////////////////
//Move of egg
void p1_eggMove(void)
{
	u16 i,j,k;
	u32 mapY;
	xyPos pos;
	
	for(i=0; i<EGG_WORK_MAX; i++)
	{
		if(p1_eggWork[i].status == EGG_ST_NONE)continue;
		switch(p1_eggWork[i].status)
		{
		case EGG_ST_JUMP:
			p1_eggWork[i].v.y   += YOSHI_FALL_ACC;
			p1_eggWork[i].pos.x += p1_eggWork[i].v.x;
			p1_eggWork[i].pos.y += p1_eggWork[i].v.y;
			
			//hit ground
			mapY = p1_getMap(p1_eggWork[i].pos.x);
			if(p1_eggWork[i].pos.y >=mapY)
			{
				p1_eggWork[i].pos.y = mapY;
				p1_eggWork[i].status = EGG_ST_NORMAL;
			}
			break;
		case EGG_ST_NORMAL://it gets picked up when overlaps yoshi while falling to the ground
			pos.x=p1_get_rel_pos(p1_eggWork[i].pos.x);
			if(pos.x<(-160  <<16)||pos.x>(160  <<16))//extra time
			{//Disappear when it goes off the screen
				p1_eggWork[i].status=EGG_ST_NONE;
				break;
			}
			pos.x=p1_get_lap_pos(p1_eggWork[i].pos.x);
			if(   p1_yoshiWork.pos.x + (p1_yoshiWork.col[0].x<<16) < pos.x + 0x40000
			   && p1_yoshiWork.pos.x + (p1_yoshiWork.col[1].x<<16) > pos.x - 0x40000
			   && p1_yoshiWork.pos.y + (p1_yoshiWork.col[0].y<<16) < p1_eggWork[i].pos.y + 0x40000
			   && p1_yoshiWork.pos.y + (p1_yoshiWork.col[1].y<<16) > p1_eggWork[i].pos.y - 0x40000 )
			{//Overlapping
				//Check to see how many eggs it has
				for(j=0,k=0;j<EGG_WORK_MAX;j++)
				{
					if(p1_eggWork[j].status == EGG_ST_SURI)
					{
						k++;
					}
				}
				p1_eggWork[i].work0=k;//set a order for this egg
				p1_eggWork[i].status = EGG_ST_SURI;
				p1_yoshiWork.egg_num++;
#ifdef SOUND_ON
				m4aSongNumStart(YOS_SE_TORUP);
#endif
			}
			break;
		}
	}
}

////////////////////////////////////////////////////////////////////////////
//Effect Process
void p1_effectMove(void)
{
	s16 i;
	
	for(i=0; i<EFF_WORK_MAX; i++)
	{
		if(p1_effWork[i].status == 0)continue;
		switch(p1_effWork[i].eff_type)
		{
		case EFF_TYPE_DASH://Dash Smoke
			p1_effWork[i].time--;
			if(p1_effWork[i].time<0){p1_effWork[i].status = 0;break;}
			if(p1_effWork[i].v.x > 0)p1_effWork[i].v.x += 0x400;else p1_effWork[i].v.x -= 0x400;
			p1_effWork[i].pos.x += p1_effWork[i].v.x;
			p1_effWork[i].pos.y += p1_effWork[i].v.y;
			break;
		case EFF_TYPE_SMOKE://Ground Pound smoke
			p1_effWork[i].time--;
			if(p1_effWork[i].time < 0){p1_effWork[i].status = 0;break;}
			p1_effWork[i].pos.x += p1_effWork[i].v.x;
			p1_effWork[i].pos.y += p1_effWork[i].v.y;
			break;
		case EFF_TYPE_HEIS:
			p1_effWork[i].time--;
			if(p1_effWork[i].time < 0){p1_effWork[i].status = 0;break;}
			break;
		}
	}
}


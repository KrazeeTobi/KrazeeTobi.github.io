//======================================================
//    yos_game_sub.h
//    Sample Yoshi Game Miscellaneous Sub-Routine Header
//
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#ifndef YOS_GAME_SUB_H
#define YOS_GAME_SUB_H

s16 p1_yos_hit_yoko(xyPos pos_old,s16 *chr_num);
s16 p1_yos_hit_tate(xyPos pos_old,s16 *chr_num);
s32 p1_get_rel_pos(s32 x);
s32 p1_get_lap_pos(s32 x);
void p1_yoshi_dead_set(void);
void p1_yoshi_jump_set(s32 vy);
void p1_effectSet(s8 type, xyPos pos, xyPos *v0);
s8 p1_jimen_cross_chk_yoko(xyPos p0, xyPos p1);
s8 p1_jimen_cross_chk(xyPos p0, xyPos p1);
s8 p1_line_cross_chk_tate(xyPos p0, xyPos p1, xyPos p2, xyPos p3);
s8 p1_line_cross_chk_yoko(xyPos p0, xyPos p1, xyPos p2, xyPos p3);
u32 p1_getMap(long posx);
void p1_balloon_dead(s16 chr_num);
void p1_anim_work_proc(void);
s8 p1_turekomi_fly_pos_set(s32 timer);
void p1_clear_anm(void);
void p1_key_chk(void);
void p1_calcDispPosition(void);	//Calculation of the center location of the screen
void p1_charWorkInit0(void);
void p1_affineWorkInit0(void);
void p1_workInit0(void);

#endif

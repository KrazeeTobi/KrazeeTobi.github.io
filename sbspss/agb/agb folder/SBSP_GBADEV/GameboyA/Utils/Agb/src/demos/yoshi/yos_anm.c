//======================================================
//    yos_anm.c
//    Animation Data for Sample Yoshi
//
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#include <Agb.h>
#include "yos_game.h"
#include "oam_proc.h"
#include "yos_bmp.h"
#include "etc_bmp.h"

//Animation Table
enum
{
	PS_HEY1,
	PS_HEY2,
	PS_HEY3,
	PS_HEY4,
	PS_HEY5,
	PS_HEY6,
	PS_HEY7,
	PS_HEY8,

	PS_JUMP1,
	PS_JUMP2,
	PS_JUMP3,
	PS_JUMP4,
	PS_JUMP5,
	PS_JUMP6,
	PS_JUMP7,
	PS_JUMP8,

	PS_KIHON_M,
	PS_KIHON_Y,

	PS_KYORO_B,
	PS_KYORO_B10,
	PS_KYORO_B11,
	PS_KYORO_B2,
	PS_KYORO_B3,
	PS_KYORO_B4,
	PS_KYORO_B5,
	PS_KYORO_B6,
	PS_KYORO_B7,
	PS_KYORO_B8,
	PS_KYORO_B9,

	PS_KYORO_M10,
	PS_KYORO_M11,
	PS_KYORO_M2,
	PS_KYORO_M3,
	PS_KYORO_M4,
	PS_KYORO_M5,
	PS_KYORO_M6,
	PS_KYORO_M7,
	PS_KYORO_M8,
	PS_KYORO_M9,

	PS_KYORO_Y10,
	PS_KYORO_Y11,
	PS_KYORO_Y2,
	PS_KYORO_Y3,
	PS_KYORO_Y4,
	PS_KYORO_Y5,
	PS_KYORO_Y6,
	PS_KYORO_Y7,
	PS_KYORO_Y8,
	PS_KYORO_Y9,

	PS_KYORO_YR10,
	PS_KYORO_YR11,
	PS_KYORO_YR2,
	PS_KYORO_YR3,
	PS_KYORO_YR4,
	PS_KYORO_YR5,
	PS_KYORO_YR6,
	PS_KYORO_YR7,
	PS_KYORO_YR8,
	PS_KYORO_YR9,

	PS_MEPACHI_B2,
	PS_MEPACHI_B3,
	PS_MEPACHI_B4,
	PS_MEPACHI_B5,
	PS_MEPACHI_B6,

	PS_MEPACHI_M2,
	PS_MEPACHI_M3,
	PS_MEPACHI_M4,
	PS_MEPACHI_M5,
	PS_MEPACHI_M6,

	PS_MEPACHI_Y2,
	PS_MEPACHI_Y3,
	PS_MEPACHI_Y4,
	PS_MEPACHI_Y5,
	PS_MEPACHI_Y6,

	PS_TURN_BACK1,
	PS_TURN_BACK2,
	PS_TURN_BACK3,
	PS_TURN_BACK4,
	PS_TURN_BACK5,
	PS_TURN_BACK6,
	PS_TURN_BACK7,

	PS_TURN_L1,
	PS_TURN_L2,
	PS_TURN_L3,
	PS_TURN_L4,
	PS_TURN_L5,
	PS_TURN_L6,
	PS_TURN_L7,

	PS_TURN_MAE1,
	PS_TURN_MAE2,
	PS_TURN_MAE3,
	PS_TURN_MAE4,
	PS_TURN_MAE5,
	PS_TURN_MAE6,
	PS_TURN_MAE7,

	PS_TURN1,
	PS_TURN2,
	PS_TURN3,
	PS_TURN4,
	PS_TURN5,
	PS_TURN6,
	PS_TURN7,

	PS_U_TURN1,
	PS_U_TURN2,
	PS_U_TURN3,
	PS_U_TURN4,
	PS_U_TURN5,
	PS_U_TURN6,
	PS_U_TURN7,
	PS_U_TURN8,

	PS_WALK_B1,
	PS_WALK_B10,
	PS_WALK_B11,
	PS_WALK_B12,
	PS_WALK_B13,
	PS_WALK_B14,
	PS_WALK_B15,
	PS_WALK_B16,
	PS_WALK_B2,
	PS_WALK_B3,
	PS_WALK_B4,
	PS_WALK_B5,
	PS_WALK_B6,
	PS_WALK_B7,
	PS_WALK_B8,
	PS_WALK_B9,

	PS_WALK_M1,
	PS_WALK_M10,
	PS_WALK_M11,
	PS_WALK_M12,
	PS_WALK_M13,
	PS_WALK_M14,
	PS_WALK_M15,
	PS_WALK_M16,
	PS_WALK_M2,
	PS_WALK_M3,
	PS_WALK_M4,
	PS_WALK_M5,
	PS_WALK_M6,
	PS_WALK_M7,
	PS_WALK_M8,
	PS_WALK_M9,

	PS_WALK_Y1,
	PS_WALK_Y2,
	PS_WALK_Y3,
	PS_WALK_Y4,
	PS_WALK_Y5,
	PS_WALK_Y6,
	PS_WALK_Y7,
	PS_WALK_Y8,
	PS_WALK_Y9,
	PS_WALK_Y10,
	PS_WALK_Y11,
	PS_WALK_Y12,
	PS_WALK_Y13,
	PS_WALK_Y14,
	PS_WALK_Y15,
};

const u8 *p1_yoshi_pixel_tbl[]=
{
	_binary_PS_hey1_imb_start,
	_binary_PS_hey2_imb_start,
	_binary_PS_hey3_imb_start,
	_binary_PS_hey4_imb_start,
	_binary_PS_hey5_imb_start,
	_binary_PS_hey6_imb_start,
	_binary_PS_hey7_imb_start,
	_binary_PS_hey8_imb_start,

	_binary_PS_jump1_imb_start,
	_binary_PS_jump2_imb_start,
	_binary_PS_jump3_imb_start,
	_binary_PS_jump4_imb_start,
	_binary_PS_jump5_imb_start,
	_binary_PS_jump6_imb_start,
	_binary_PS_jump7_imb_start,
	_binary_PS_jump8_imb_start,

	_binary_PS_kihon_M_imb_start,
	_binary_PS_kihon_Y_imb_start,

	_binary_PS_kyoro_B_imb_start,
	_binary_PS_kyoro_B10_imb_start,
	_binary_PS_kyoro_B11_imb_start,
	_binary_PS_kyoro_B2_imb_start,
	_binary_PS_kyoro_B3_imb_start,
	_binary_PS_kyoro_B4_imb_start,
	_binary_PS_kyoro_B5_imb_start,
	_binary_PS_kyoro_B6_imb_start,
	_binary_PS_kyoro_B7_imb_start,
	_binary_PS_kyoro_B8_imb_start,
	_binary_PS_kyoro_B9_imb_start,

	_binary_PS_kyoro_M10_imb_start,
	_binary_PS_kyoro_M11_imb_start,
	_binary_PS_kyoro_M2_imb_start,
	_binary_PS_kyoro_M3_imb_start,
	_binary_PS_kyoro_M4_imb_start,
	_binary_PS_kyoro_M5_imb_start,
	_binary_PS_kyoro_M6_imb_start,
	_binary_PS_kyoro_M7_imb_start,
	_binary_PS_kyoro_M8_imb_start,
	_binary_PS_kyoro_M9_imb_start,

	_binary_PS_kyoro_Y10_imb_start,
	_binary_PS_kyoro_Y11_imb_start,
	_binary_PS_kyoro_Y2_imb_start,
	_binary_PS_kyoro_Y3_imb_start,
	_binary_PS_kyoro_Y4_imb_start,
	_binary_PS_kyoro_Y5_imb_start,
	_binary_PS_kyoro_Y6_imb_start,
	_binary_PS_kyoro_Y7_imb_start,
	_binary_PS_kyoro_Y8_imb_start,
	_binary_PS_kyoro_Y9_imb_start,

	_binary_PS_kyoro_YR10_imb_start,
	_binary_PS_kyoro_YR11_imb_start,
	_binary_PS_kyoro_YR2_imb_start,
	_binary_PS_kyoro_YR3_imb_start,
	_binary_PS_kyoro_YR4_imb_start,
	_binary_PS_kyoro_YR5_imb_start,
	_binary_PS_kyoro_YR6_imb_start,
	_binary_PS_kyoro_YR7_imb_start,
	_binary_PS_kyoro_YR8_imb_start,
	_binary_PS_kyoro_YR9_imb_start,

	_binary_PS_MEPACHI_B2_imb_start,
	_binary_PS_MEPACHI_B3_imb_start,
	_binary_PS_MEPACHI_B4_imb_start,
	_binary_PS_MEPACHI_B5_imb_start,
	_binary_PS_MEPACHI_B6_imb_start,

	_binary_PS_MEPACHI_M2_imb_start,
	_binary_PS_MEPACHI_M3_imb_start,
	_binary_PS_MEPACHI_M4_imb_start,
	_binary_PS_MEPACHI_M5_imb_start,
	_binary_PS_MEPACHI_M6_imb_start,

	_binary_PS_MEPACHI_Y2_imb_start,
	_binary_PS_MEPACHI_Y3_imb_start,
	_binary_PS_MEPACHI_Y4_imb_start,
	_binary_PS_MEPACHI_Y5_imb_start,
	_binary_PS_MEPACHI_Y6_imb_start,

	_binary_PS_turn_back1_imb_start,
	_binary_PS_turn_back2_imb_start,
	_binary_PS_turn_back3_imb_start,
	_binary_PS_turn_back4_imb_start,
	_binary_PS_turn_back5_imb_start,
	_binary_PS_turn_back6_imb_start,
	_binary_PS_turn_back7_imb_start,

	_binary_PS_turn_L1_imb_start,
	_binary_PS_turn_L2_imb_start,
	_binary_PS_turn_L3_imb_start,
	_binary_PS_turn_L4_imb_start,
	_binary_PS_turn_L5_imb_start,
	_binary_PS_turn_L6_imb_start,
	_binary_PS_turn_L7_imb_start,

	_binary_PS_turn_mae1_imb_start,
	_binary_PS_turn_mae2_imb_start,
	_binary_PS_turn_mae3_imb_start,
	_binary_PS_turn_mae4_imb_start,
	_binary_PS_turn_mae5_imb_start,
	_binary_PS_turn_mae6_imb_start,
	_binary_PS_turn_mae7_imb_start,

	_binary_PS_turn1_imb_start,
	_binary_PS_turn2_imb_start,
	_binary_PS_turn3_imb_start,
	_binary_PS_turn4_imb_start,
	_binary_PS_turn5_imb_start,
	_binary_PS_turn6_imb_start,
	_binary_PS_turn7_imb_start,

	_binary_PS_U_turn1_imb_start,
	_binary_PS_U_turn2_imb_start,
	_binary_PS_U_turn3_imb_start,
	_binary_PS_U_turn4_imb_start,
	_binary_PS_U_turn5_imb_start,
	_binary_PS_U_turn6_imb_start,
	_binary_PS_U_turn7_imb_start,
	_binary_PS_U_turn8_imb_start,

	_binary_PS_walk_B1_imb_start,
	_binary_PS_walk_B10_imb_start,
	_binary_PS_walk_B11_imb_start,
	_binary_PS_walk_B12_imb_start,
	_binary_PS_walk_B13_imb_start,
	_binary_PS_walk_B14_imb_start,
	_binary_PS_walk_B15_imb_start,
	_binary_PS_walk_B16_imb_start,
	_binary_PS_walk_B2_imb_start,
	_binary_PS_walk_B3_imb_start,
	_binary_PS_walk_B4_imb_start,
	_binary_PS_walk_B5_imb_start,
	_binary_PS_walk_B6_imb_start,
	_binary_PS_walk_B7_imb_start,
	_binary_PS_walk_B8_imb_start,
	_binary_PS_walk_B9_imb_start,

	_binary_PS_walk_M1_imb_start,
	_binary_PS_walk_M10_imb_start,
	_binary_PS_walk_M11_imb_start,
	_binary_PS_walk_M12_imb_start,
	_binary_PS_walk_M13_imb_start,
	_binary_PS_walk_M14_imb_start,
	_binary_PS_walk_M15_imb_start,
	_binary_PS_walk_M16_imb_start,
	_binary_PS_walk_M2_imb_start,
	_binary_PS_walk_M3_imb_start,
	_binary_PS_walk_M4_imb_start,
	_binary_PS_walk_M5_imb_start,
	_binary_PS_walk_M6_imb_start,
	_binary_PS_walk_M7_imb_start,
	_binary_PS_walk_M8_imb_start,
	_binary_PS_walk_M9_imb_start,

	_binary_PS_walk_Y1_imb_start,
	_binary_PS_walk_Y2_imb_start,
	_binary_PS_walk_Y3_imb_start,
	_binary_PS_walk_Y4_imb_start,
	_binary_PS_walk_Y5_imb_start,
	_binary_PS_walk_Y6_imb_start,
	_binary_PS_walk_Y7_imb_start,
	_binary_PS_walk_Y8_imb_start,
	_binary_PS_walk_Y9_imb_start,
	_binary_PS_walk_Y10_imb_start,
	_binary_PS_walk_Y11_imb_start,
	_binary_PS_walk_Y12_imb_start,
	_binary_PS_walk_Y13_imb_start,
	_binary_PS_walk_Y14_imb_start,
	_binary_PS_walk_Y15_imb_start,
};

static const AnmTbl yoshi_anm_normal[]=
{//ptn, time, dir
	{  0,    30,    0},
	{  1,    30,    0},
	{  0,    -1,    0},
	
};
static const AnmTbl yoshi_anm_walk[]=
{//        ptn    ,  time, dir
	{  PS_WALK_Y1 ,     4,    0},
	{  PS_WALK_Y2 ,     4,    0},
	{  PS_WALK_Y3 ,     4,    0},
	{  PS_WALK_Y4 ,     4,    0},
	{  PS_WALK_Y5 ,     4,    0},
	{  PS_WALK_Y6 ,     4,    0},
	{  PS_WALK_Y7 ,     4,    0},
	{  PS_WALK_Y8 ,     4,    0},
	{  PS_WALK_Y9 ,     4,    0},
	{  PS_WALK_Y10,     4,    0},
	{  PS_WALK_Y11,     4,    0},
	{  PS_WALK_Y12,     4,    0},
	{  PS_WALK_Y13,     4,    0},
	{  PS_WALK_Y14,     4,    0},
	{  PS_WALK_Y15,     4,    0},
	{            0,    -1,    0},
};
static const AnmTbl yoshi_anm_run[]=
{//        ptn    ,  time, dir
	{  PS_WALK_Y1 ,     2,    0},
	{  PS_WALK_Y2 ,     2,    0},
	{  PS_WALK_Y3 ,     2,    0},
	{  PS_WALK_Y4 ,     2,    0},
	{  PS_WALK_Y5 ,     2,    0},
	{  PS_WALK_Y6 ,     2,    0},
	{  PS_WALK_Y7 ,     2,    0},
	{  PS_WALK_Y8 ,     2,    0},
	{  PS_WALK_Y9 ,     2,    0},
	{  PS_WALK_Y10,     2,    0},
	{  PS_WALK_Y11,     2,    0},
	{  PS_WALK_Y12,     2,    0},
	{  PS_WALK_Y13,     2,    0},
	{  PS_WALK_Y14,     2,    0},
	{  PS_WALK_Y15,     2,    0},
	{            0,    -1,    0},
};
static const AnmTbl yoshi_anm_l2r[]=
{//        ptn   ,  time, dir
	{  PS_U_TURN1,     2,    0},
	{  PS_U_TURN2,     2,    0},
	{  PS_U_TURN3,     2,    0},
	{  PS_U_TURN4,     2,    0},
	{  PS_U_TURN5,     2,    0},
	{  PS_U_TURN6,     2,    0},
	{  PS_U_TURN7,     2,    0},
	{  PS_U_TURN8,     2,    0},
	{           0,    -2,    0},//Truncation
};
static const AnmTbl yoshi_anm_jump[]=
{//      ptn   ,  time, dir
	{  PS_JUMP1,     2,    0},
	{  PS_JUMP2,     2,    0},
	{  PS_JUMP3,     2,    0},
	{  PS_JUMP4,     2,    0},
	{  PS_JUMP5,     2,    0},
	{  PS_JUMP4,     2,    0},
	{  PS_JUMP5,     2,    0},
	{  PS_JUMP4,     2,    0},
	{  PS_JUMP5,     2,    0},
	{  PS_JUMP4,     2,    0},
	{  PS_JUMP5,     2,    0},
	{  PS_JUMP4,     2,    0},
	{  PS_JUMP5,     2,    0},
	{  PS_JUMP4,     2,    0},
	{  PS_JUMP5,     2,    0},
//	{  PS_JUMP6,     2,    0},
//	{  PS_JUMP7,     2,    0},
//	{  PS_JUMP8,     2,    0},
	{         0,    -2,    0},//Truncation
};
static const AnmTbl yoshi_anm_kyoro[]=
{//        ptn      ,  time, dir
	{  PS_KIHON_Y   ,    60,    0},//0
	{  PS_KYORO_Y2  ,     2,    0},
	{  PS_KYORO_Y3  ,     2,    0},
	{  PS_KYORO_Y4  ,     2,    0},
	{  PS_KYORO_Y5  ,     2,    0},
	{  PS_KYORO_Y6  ,     2,    0},
	{  PS_KYORO_Y7  ,     2,    0},
	{  PS_KYORO_Y8  ,     2,    0},
	{  PS_KYORO_Y9  ,     2,    0},
	{  PS_KYORO_Y10 ,     2,    0},
	{  PS_KYORO_Y11 ,    30,    0},
	{  PS_KYORO_Y10 ,     2,    0},
	{  PS_KYORO_Y9  ,     2,    0},
	{  PS_KYORO_Y8  ,     2,    0},
	{  PS_KYORO_Y7  ,     2,    0},
	{  PS_KYORO_Y6  ,     2,    0},
	{  PS_KYORO_Y5  ,     2,    0},
	{  PS_KYORO_Y4  ,     2,    0},
	{  PS_KYORO_Y3  ,     2,    0},//18

	{  PS_KIHON_Y   ,     8,    0},//19
	{  PS_MEPACHI_Y2,     2,    0},
	{  PS_MEPACHI_Y3,     2,    0},
	{  PS_MEPACHI_Y4,     2,    0},
	{  PS_MEPACHI_Y5,     2,    0},
	{  PS_MEPACHI_Y6,     2,    0},
	{  PS_MEPACHI_Y5,     2,    0},
	{  PS_MEPACHI_Y4,     2,    0},
	{  PS_MEPACHI_Y3,     2,    0},
	{  PS_MEPACHI_Y2,     2,    0},
	
	{  PS_KIHON_Y   ,     8,    0},//29
	
	{  PS_WALK_Y5   ,     4,    0},//30
	{  PS_WALK_Y6   ,     4,    0},
	{  PS_WALK_Y7   ,     4,    0},
	{  PS_WALK_Y8   ,     4,    0},
	{  PS_WALK_Y9   ,     4,    0},
	{  PS_WALK_Y10  ,     4,    0},
	{  PS_WALK_Y11  ,     4,    0},
	{  PS_WALK_Y12  ,     4,    0},
	{  PS_WALK_Y13  ,     4,    0},
	{  PS_WALK_Y14  ,     4,    0},//39
	{  PS_WALK_Y15  ,     4,    0},
	{  PS_WALK_Y1   ,     4,    0},
	{  PS_WALK_Y2   ,     4,    0},
	{  PS_WALK_Y3   ,     4,    0},
	{  PS_WALK_Y4   ,     4,    0},
	{  PS_KIHON_Y   ,    10,    0},//45
	
	{  PS_KYORO_YR2 ,     2,    0},//46
	{  PS_KYORO_YR3 ,     2,    0},
	{  PS_KYORO_YR4 ,     2,    0},
	{  PS_KYORO_YR5 ,     2,    0},
	{  PS_KYORO_YR6 ,     2,    0},
	{  PS_KYORO_YR7 ,     2,    0},
	{  PS_KYORO_YR8 ,     2,    0},
	{  PS_KYORO_YR9 ,     2,    0},
	{  PS_KYORO_YR10,     2,    0},
	{  PS_KYORO_YR11,    30,    0},
	{  PS_KYORO_YR10,     2,    0},
	{  PS_KYORO_YR9 ,     2,    0},
	{  PS_KYORO_YR8 ,     2,    0},
	{  PS_KYORO_YR7 ,     2,    0},
	{  PS_KYORO_YR6 ,     2,    0},
	{  PS_KYORO_YR5 ,     2,    0},
	{  PS_KYORO_YR4 ,     2,    0},
	{  PS_KYORO_YR3 ,     2,    0},
	{             0,    -1,    0},//Truncation
};
static const AnmTbl yoshi_anm_tyouhatu[]=
{//        ptn   ,  time, dir
	{  PS_HEY1,     2,    0},
	{  PS_HEY2,     2,    0},
	{  PS_HEY3,     2,    0},
	{  PS_HEY4,     2,    0},
	{  PS_HEY5,     2,    0},
	{  PS_HEY6,     2,    0},
	{  PS_HEY7,     2,    0},
	{  PS_HEY8,     2,    0},
	{  PS_HEY7,     2,    0},
	{  PS_HEY6,     2,    0},
	{  PS_HEY5,     2,    0},
	{  PS_HEY4,     2,    0},
	{  PS_HEY3,     2,    0},
	{  PS_HEY2,     2,    0},
	{  PS_HEY1,     2,    0},
	{        0,    -1,    0},//Loop
};
static const AnmTbl yoshi_anm_funbari[]=
{//        ptn    ,  time, dir
	{  PS_WALK_Y1 ,     1,    0},
	{  PS_WALK_Y2 ,     1,    0},
	{  PS_WALK_Y3 ,     1,    0},
	{  PS_WALK_Y4 ,     1,    0},
	{  PS_WALK_Y5 ,     1,    0},
	{  PS_WALK_Y6 ,     1,    0},
	{  PS_WALK_Y7 ,     1,    0},
	{  PS_WALK_Y8 ,     1,    0},
	{  PS_WALK_Y9 ,     1,    0},
	{  PS_WALK_Y10,     1,    0},
	{  PS_WALK_Y11,     1,    0},
	{  PS_WALK_Y12,     1,    0},
	{  PS_WALK_Y13,     1,    0},
	{  PS_WALK_Y14,     1,    0},
	{  PS_WALK_Y15,     1,    0},
	{            0,    -1,    0},
};
static const AnmTbl yoshi_anm_kururinha[]=
{//      ptn   ,  time, dir
	{  PS_JUMP5,     2,    0},
	{         0,    -2,    0},//Truncation
};
static const AnmTbl yoshi_anm_die[]=
{//      ptn        ,  time, dir
	{  PS_KYORO_M2  ,     2,    0},
	{  PS_KYORO_M3  ,     2,    0},
	{  PS_KYORO_M4  ,     2,    0},
	{  PS_KYORO_M5  ,     2,    0},
	{  PS_KYORO_M6  ,     2,    0},
	{  PS_KYORO_M7  ,     2,    0},
	{  PS_KYORO_M8  ,     2,    0},
	{  PS_KYORO_M9  ,     2,    0},
	{  PS_KYORO_M10 ,     2,    0},
	{  PS_KYORO_M11 ,     2,    0},
	{  PS_KYORO_M10 ,     2,    0},
	{  PS_KYORO_M9  ,     2,    0},
	{  PS_KYORO_M8  ,     2,    0},
	{  PS_KYORO_M7  ,     2,    0},
	{  PS_KYORO_M6  ,     2,    0},
	{  PS_KYORO_M5  ,     2,    0},
	{  PS_KYORO_M4  ,     2,    0},
	{  PS_KYORO_M3  ,     2,    0},
	{  PS_KYORO_M2  ,     2,    0},
	{  PS_KIHON_M   ,     2,    0},
	{  PS_KYORO_M2  ,     2,   -1},
	{  PS_KYORO_M3  ,     2,   -1},
	{  PS_KYORO_M4  ,     2,   -1},
	{  PS_KYORO_M5  ,     2,   -1},
	{  PS_KYORO_M6  ,     2,   -1},
	{  PS_KYORO_M7  ,     2,   -1},
	{  PS_KYORO_M8  ,     2,   -1},
	{  PS_KYORO_M9  ,     2,   -1},
	{  PS_KYORO_M10 ,     2,   -1},
	{  PS_KYORO_M11 ,     2,   -1},
	{  PS_KYORO_M10,      2,   -1},
	{  PS_KYORO_M9  ,     2,   -1},
	{  PS_KYORO_M8  ,     2,   -1},
	{  PS_KYORO_M7  ,     2,   -1},
	{  PS_KYORO_M6  ,     2,   -1},
	{  PS_KYORO_M5  ,     2,   -1},
	{  PS_KYORO_M4  ,     2,   -1},
	{  PS_KYORO_M3  ,     2,   -1},
	{  PS_KYORO_M2  ,     2,   -1},
#if 0
	{  PS_TURN1     ,     4,    0},
	{  PS_TURN2     ,     4,    0},
	{  PS_TURN3     ,     4,    0},
	{  PS_TURN4     ,     4,    0},
	{  PS_TURN5     ,     4,    0},
	{  PS_TURN6     ,     4,    0},
	{  PS_TURN7     ,     4,    0},
	{  PS_TURN_BACK1,     4,    0},
	{  PS_TURN_BACK2,     4,    0},
	{  PS_TURN_BACK3,     4,    0},
	{  PS_TURN_BACK4,     4,    0},
	{  PS_TURN_BACK5,     4,    0},
	{  PS_TURN_BACK6,     4,    0},
	{  PS_TURN_BACK7,     4,    0},
	{  PS_TURN_L1   ,     4,    0},
	{  PS_TURN_L2   ,     4,    0},
	{  PS_TURN_L3   ,     4,    0},
	{  PS_TURN_L4   ,     4,    0},
	{  PS_TURN_L5   ,     4,    0},
	{  PS_TURN_L6   ,     4,    0},
	{  PS_TURN_L7   ,     4,    0},
#endif
//	{        0,    -1,    0},//Loop
	{         0,    -2,    0},//Truncation
};
static const AnmTbl yoshi_anm_bring1[]=
{//        ptn      ,  time, dir
	{  PS_MEPACHI_M2,     2,    0},
	{  PS_MEPACHI_M3,     2,    0},
	{  PS_MEPACHI_M4,     2,    0},
	{  PS_MEPACHI_M5,     2,    0},
	{  PS_MEPACHI_M6,     2,    0},
	{  PS_MEPACHI_M5,     2,    0},
	{  PS_MEPACHI_M4,     2,    0},
	{  PS_MEPACHI_M3,     2,    0},
	{        0,    -1,    0},//Loop
};
static const AnmTbl yoshi_anm_bring2[]=
{//        ptn   ,  time, dir
	{  PS_HEY1,     2,    0},
	{  PS_HEY2,     2,    0},
	{  PS_HEY3,     2,    0},
	{  PS_HEY4,     2,    0},
	{  PS_HEY5,     2,    0},
	{  PS_HEY6,     2,    0},
	{  PS_HEY7,     2,    0},
	{  PS_HEY8,     2,    0},
	{  PS_HEY7,     2,    0},
	{  PS_HEY6,     2,    0},
	{  PS_HEY5,     2,    0},
	{  PS_HEY4,     2,    0},
	{  PS_HEY3,     2,    0},
	{  PS_HEY2,     2,    0},
	{  PS_HEY1,     2,    0},
	{        0,    -1,    0},//Loop
};

const AnmTbl *p1_yoshi_anm_patern[]=
{
	yoshi_anm_kyoro,//none
	yoshi_anm_kyoro,//normal
	yoshi_anm_walk,//walk
	yoshi_anm_l2r,//l2r
	yoshi_anm_jump,//
	yoshi_anm_run,//run
	yoshi_anm_tyouhatu,//Provocation
	yoshi_anm_funbari,
	yoshi_anm_kururinha,
	yoshi_anm_die,
	yoshi_anm_bring1,
	yoshi_anm_bring2,
};

//Shy Guy Animation
static const AnmTbl hei_anm_walk[]=
{//ptn, time, dir
	{  0,     6,    0},
	{  1,     6,    0},
	{  2,     6,    0},
	{  3,     6,    0},
	{  4,     6,    0},
	{  5,     6,    0},
	{  6,     6,    0},
	{  7,     6,    0},
	{  0,    -1,    0},
};
static const AnmTbl hei_anm_turn[]=
{//ptn, time, dir
	{  8,      6,    0},
	{  9,      6,    0},
	{  9,      6,   -1},
	{  8,      6,   -1},
	{  0,    -2,    0},
};

const u8 *p1_heiho_pixel_tbl[]=
{
	_binary_HEIHO929_001_imb_start,//0
	_binary_HEIHO929_003_imb_start,
	_binary_HEIHO929_005_imb_start,
	_binary_HEIHO929_007_imb_start,
	_binary_HEIHO929_009_imb_start,
	_binary_HEIHO929_011_imb_start,
	_binary_HEIHO929_013_imb_start,
	_binary_HEIHO929_015_imb_start,//7
	_binary_HEIHO_normal_walk_turn_002_imb_start,//8
	_binary_HEIHO_normal_walk_turn_003_imb_start,//9

};
const u8 *p1_heiho_b_pixel_tbl[]=
{
	_binary_HEIHO929_001_b_imb_start,//0
	_binary_HEIHO929_003_b_imb_start,
	_binary_HEIHO929_005_b_imb_start,
	_binary_HEIHO929_007_b_imb_start,
	_binary_HEIHO929_009_b_imb_start,
	_binary_HEIHO929_011_b_imb_start,
	_binary_HEIHO929_013_b_imb_start,
	_binary_HEIHO929_015_b_imb_start,//7
	_binary_HEIHO_normal_walk_turn_002_b_imb_start,//8
	_binary_HEIHO_normal_walk_turn_003_b_imb_start,//9
};
const u8 *p1_heiho_g_pixel_tbl[]=
{
	_binary_HEIHO929_001_g_imb_start,//0
	_binary_HEIHO929_003_g_imb_start,
	_binary_HEIHO929_005_g_imb_start,
	_binary_HEIHO929_007_g_imb_start,
	_binary_HEIHO929_009_g_imb_start,
	_binary_HEIHO929_011_g_imb_start,
	_binary_HEIHO929_013_g_imb_start,
	_binary_HEIHO929_015_g_imb_start,//7
	_binary_HEIHO_normal_walk_turn_002_g_imb_start,//8
	_binary_HEIHO_normal_walk_turn_003_g_imb_start,//9
};
const u8 *p1_heiho_y_pixel_tbl[]=
{
	_binary_HEIHO929_001_y_imb_start,//0
	_binary_HEIHO929_003_y_imb_start,
	_binary_HEIHO929_005_y_imb_start,
	_binary_HEIHO929_007_y_imb_start,
	_binary_HEIHO929_009_y_imb_start,
	_binary_HEIHO929_011_y_imb_start,
	_binary_HEIHO929_013_y_imb_start,
	_binary_HEIHO929_015_y_imb_start,//7
	_binary_HEIHO_normal_walk_turn_002_y_imb_start,//8
	_binary_HEIHO_normal_walk_turn_003_y_imb_start,//9
};
const u8 *p1_heihoL_pixel_tbl[]=
{
	_binary_HEIHO_l_001_imb_start,
	_binary_HEIHO_l_003_imb_start,
	_binary_HEIHO_l_005_imb_start,
	_binary_HEIHO_l_007_imb_start,
	_binary_HEIHO_l_009_imb_start,
	_binary_HEIHO_l_011_imb_start,
	_binary_HEIHO_l_013_imb_start,
	_binary_HEIHO_l_015_imb_start,
	_binary_HEIHO_l_turn_002_imb_start,
	_binary_HEIHO_l_turn_003_imb_start
};
const AnmTbl *p1_heiho_anm_patern[]=
{
	hei_anm_walk,//none
	hei_anm_walk,//walk
	hei_anm_turn,//turn
};
//Message BOX Animation
static const AnmTbl mbox_anm_normal[]=
{//ptn, time, dir
	{  0,    30,    0},
	{  1,    30,    0},
	{  0,    -1,    0},
};
const u8 *p1_mbox_pixel_tbl[]=
{
	_binary_mBOX1_imb_start,
	_binary_mBOX2_imb_start,
};
const AnmTbl *p1_mbox_anm_patern[]=
{
	mbox_anm_normal,//none
	mbox_anm_normal,//normal
};
//Sunflower gauge Animation
static const AnmTbl sun_anm_d[]=
{//ptn, time, dir
	{  0,     5,    0},
	{  1,     5,    0},
	{  2,     5,    0},
	{  0,    -1,    0},
};
static const AnmTbl sun_anm_c[]=
{//ptn, time, dir
	{  3,     5,    0},
	{  4,     5,    0},
	{  5,     5,    0},
	{  0,    -1,    0},
};
static const AnmTbl sun_anm_normal[]=
{//ptn, time, dir
	{  6,     5,    0},
	{  7,     5,    0},
	{  8,     5,    0},
	{  0,    -1,    0},
};
static const AnmTbl sun_anm_s[]=
{//ptn, time, dir
	{  9,     5,    0},
	{ 10,     5,    0},
	{ 11,     5,    0},
	{  0,    -1,    0},
};
static const AnmTbl sun_anm_sp[]=
{//ptn, time, dir
	{ 12,     5,    0},
	{ 13,     5,    0},
	{ 14,     5,    0},
	{  0,    -1,    0},
};
const u8 *p1_sun_pixel_tbl[]=
{
	_binary_DDDD_A_imb_start,//0
	_binary_DDDD_B_imb_start,
	_binary_DDDD_C_imb_start,
	_binary_CCCC_A_imb_start,//3
	_binary_CCCC_B_imb_start,
	_binary_CCCC_C_imb_start,
	_binary_NNNN_A_imb_start,//6
	_binary_NNNN_B_imb_start,
	_binary_NNNN_C_imb_start,
	_binary_SSSS_A_imb_start,//9
	_binary_SSSS_B_imb_start,
	_binary_SSSS_C_imb_start,
	_binary_sPPPP_A_imb_start,//12
	_binary_sPPPP_B_imb_start,
	_binary_sPPPP_C_imb_start,
};
const AnmTbl *p1_sun_anm_patern[]=
{
	sun_anm_normal,//none
	sun_anm_d,//
	sun_anm_c,//
	sun_anm_normal,//normal
	sun_anm_s,//
	sun_anm_sp,//
};
//Killer S
static const AnmTbl killerS_anm_normal[]=
{//ptn, time, dir
	{  0,     5,    0},
	{  1,     5,    0},
	{  2,     5,    0},
	{  3,     5,    0},
	{  4,     5,    0},
	{  5,     5,    0},
	{  6,     5,    0},
	{  7,     5,    0},
	{  8,     5,    0},
	{  7,     5,    0},
	{  6,     5,    0},
	{  0,    -1,    0},
};
const u8 *p1_killerS_pixel_tbl[]=
{
	_binary_killer_s1_imb_start,//0
	_binary_killer_s2_imb_start,
	_binary_killer_s3_imb_start,
	_binary_killer_sA_imb_start,
	_binary_killer_sAA_imb_start,
	_binary_killer_sB_imb_start,
	_binary_killer_sC_imb_start,
	_binary_killer_sD_imb_start,
	_binary_killer_sE_imb_start,//8
};
const AnmTbl *p1_killerS_anm_patern[]=
{
	killerS_anm_normal,//none
	killerS_anm_normal,//normal
};
#if 0
//Killer L
static const AnmTbl killerL_anm_normal[]=
{//ptn, time, dir
	{  0,     5,    0},
	{  1,     5,    0},
	{  2,     5,    0},
	{  3,     5,    0},
	{  4,     5,    0},
	{  5,     5,    0},
	{  6,     5,    0},
	{  7,     5,    0},
	{  8,     5,    0},
	{  7,     5,    0},
	{  6,     5,    0},
	{  0,    -1,    0},
};
const u8 *p1_killerL_pixel_tbl[]=
{
	killer_l1_Char,//0
	killer_l2_Char,
	killer_l3_Char,
	killer_lA_Char,
	killer_lAA_Char,
	killer_lB_Char,
	killer_lC_Char,
	killer_lD_Char,
	killer_lE_Char,//8
};
const AnmTbl *p1_killerL_anm_patern[]=
{
	killerL_anm_normal,//none
	killerL_anm_normal,//normal
};
#endif
//Kokamek
static const AnmTbl kokamek_anm_normal[]=
{//ptn, time, dir
	{  0,     5,    0},
	{  2,     5,    0},
	{  0,     5,    0},
	{  2,     5,    0},
	{  0,    -1,    0},
};
static const AnmTbl kokamek_anm_ura[]=
{//ptn, time, dir
	{  1,     5,    0},
	{  3,     5,    0},
	{  1,     5,    0},
	{  3,     5,    0},
	{  0,    -1,    0},
};
const u8 *p1_kokamek_pixel_tbl[]=
{
	_binary_kokamek_a_imb_start,//0
	_binary_kokamek_c_imb_start,
	_binary_kokamek_d_imb_start,
	_binary_kokamek_e_imb_start,
};
const AnmTbl *p1_kokamek_anm_patern[]=
{
	kokamek_anm_normal,//none
	kokamek_anm_normal,//normal
	kokamek_anm_ura,//normal
};

//Star
static const AnmTbl hosi_anm_normal[]=
{//ptn, time, dir
#if 1
	{  0,     5,    0},
	{  1,     5,    0},
	{  2,     5,    0},
	{  3,     5,    0},
	{  4,     5,    0},
	{  5,     5,    0},
	{  6,     5,    0},
	{  7,     5,    0},
#endif
//	{  3,     5,    0},
	{  0,    -2,    0},
};
const u8 *p1_hosi_pixel_tbl[]=
{
	_binary_hosi1_imb_start,//0
	_binary_hosi2_imb_start,
	_binary_hosi3_imb_start,
	_binary_hosi4_imb_start,
	_binary_hosi5_imb_start,
	_binary_hosi6_imb_start,
	_binary_hosi7_imb_start,
	_binary_hosi8_imb_start,
};
const AnmTbl *p1_hosi_anm_patern[]=
{
	hosi_anm_normal,//none
	hosi_anm_normal,//normal
};
//Hip Drop Smoke
static const AnmTbl kurukemu_anm_normal[]=
{//ptn, time, dir
	{  0,     5,    0},
	{  1,     5,    0},
	{  2,     5,    0},
	{  3,     5,    0},
	{  4,     5,    0},
	{  5,     5,    0},
	{  6,     5,    0},
	{  7,     5,    0},
	{  0,    -2,    0},
};
const u8 *p1_kurukemu_pixel_tbl[]=
{
	_binary_kururi1_imb_start,//0
	_binary_kururi2_imb_start,
	_binary_kururi3_imb_start,
	_binary_kururi4_imb_start,
	_binary_kururi5_imb_start,
	_binary_kururi6_imb_start,
	_binary_kururi7_imb_start,
	_binary_kururi8_imb_start,
};
const AnmTbl *p1_kurukemu_anm_patern[]=
{
	kurukemu_anm_normal,//none
	kurukemu_anm_normal,//normal
};
//Balloon
static const AnmTbl balloon_anm_normal[]=
{//ptn, time, dir
	{  1,     5,    0},
	{  2,     5,    0},
	{  3,     5,    0},
	{  4,     5,    0},
	{  5,     5,    0},
	{  6,     5,    0},
	{  7,     5,    0},
	{  8,     5,    0},
	{  9,     5,    0},
	{ 10,     5,    0},
	{ 11,     5,    0},
	{ 12,     5,    0},
	{ 13,     5,    0},
	{  0,     5,    0},
	{  0,    -2,    0},
};
const u8 *p1_balloon_pixel_tbl[]=
{
	_binary_balloon_imb_start,//0
	_binary_balloon01_imb_start,
	_binary_balloon02_imb_start,
	_binary_balloon03_imb_start,
	_binary_balloon04_imb_start,
	_binary_balloon05_imb_start,
	_binary_balloon06_imb_start,
	_binary_balloon07_imb_start,
	_binary_balloon08_imb_start,
	_binary_balloon09_imb_start,
	_binary_balloon10_imb_start,
	_binary_balloon11_imb_start,
	_binary_balloon12_imb_start,
	_binary_balloon13_imb_start,
};
const AnmTbl *p1_balloon_anm_patern[]=
{
	balloon_anm_normal,//none
	balloon_anm_normal,//normal
};

//Bob-omb
static const AnmTbl bomb_anm_normal[]=
{//ptn, time, dir
	{  0,     5,    0},
	{  1,     5,    0},
	{  2,     5,    0},
	{  3,     5,    0},
	{  4,     5,    0},
	{  3,     5,    0},
	{  2,     5,    0},
	{  1,     5,    0},
	{  0,    -1,    0},
};
const u8 *p1_bomb_pixel_tbl[]=
{
	_binary_bomb_1_imb_start,//0
	_binary_bomb_2_imb_start,
	_binary_bomb_3_imb_start,
	_binary_bomb_4_imb_start,
	_binary_bomb_5_imb_start,
};
const AnmTbl *p1_bomb_anm_patern[]=
{
	bomb_anm_normal,//none
	bomb_anm_normal,//normal
};

/********************************************************************/
/*          player_dat.c                                            */
/*                 dolphin source                                   */
/*                                                                  */
/*          Copyright (C) 2000 NINTENDO Co.,Ltd.                    */
/********************************************************************/
#include <Agb.h>
#include "main.h"
#include "player.h"
#include "enemy.h"

//------------------------------------------------------------------//
//		Basic Graphics Table of Dolphin			    //
//------------------------------------------------------------------//

const u8 *r_kihon_pixel_tbl[]=
{
	r_up8_Char,
	r_up7_Char,
	r_up6_Char,
	r_up2_Char,
	r_up1_Char,
	r_down7_Char,
};


//------------------------------------------------------------------//
//		Operation Stand-by Graphics Table of Dolphin 	    //
//------------------------------------------------------------------//
const u8 *r_kihon_idle_pixel_tbl[]=
{
	r_kihon0_Char,
	r_kihon1_Char,
	r_kihon2_Char,
	r_kihon3_Char,
	r_kihon4_Char,
	r_kihon5_Char,
	r_kihon6_Char,
	r_kihon7_Char,
};


//------------------------------------------------------------------//
//		Attack Graphics Table of Dolphin 		    //
//------------------------------------------------------------------//
const u8 *r_attack_pixel_tbl[]=
{
	r_attack1_Char,
	r_attack2_Char,
//	r_attack3_Char,
	r_attack4_Char,
	r_attack5_Char,
	r_attack6_Char,
	r_attack7_Char,
};

//------------------------------------------------------------------//
//		Downward Graphics Table of Dolphin 		    //
//------------------------------------------------------------------//
const u8 *r_down_pixel_tbl[]=
{
	r_down0_Char,
	r_down1_Char,
	r_down2_Char,
	r_down3_Char,
	r_down4_Char,
	r_down5_Char,
	r_down6_Char,
	r_down7_Char,
	r_down8_Char,
};


//------------------------------------------------------------------//
//		Upward/Downward Graphics Table of Dolphin 	    //
//------------------------------------------------------------------//
const u8 *r_up_down_pixel_tbl[]=
{
	r_up8_Char,
	r_up7_Char,
	r_up6_Char,
	r_up5_Char,
	r_go_up7_Char,
	r_go_up6_Char,
	r_go_up5_Char,
	r_go_up4_Char,
	r_go_up3_Char,
	r_go_up2_Char,
	r_go_up1_Char,
	r_go_up0_Char,
	r_up3_Char,
	r_up2_Char,
	r_up1_Char,
	r_up0_Char,
	r_down1_Char,
	r_down2_Char,
	r_down3_Char,
	r_go_down2_Char,
	r_go_down3_Char,
	r_go_down4_Char,
	r_go_down5_Char,
	r_go_down6_Char,
	r_down4_Char,
	r_down5_Char,
	r_down6_Char,
	r_down7_Char,
	r_down8_Char,
};

//------------------------------------------------------------------//
//		Jump Graphics Table of Dolphin  		    //
//------------------------------------------------------------------//
const u8 *r_jump_pixel_tbl[]=
{
	r_go_up1_Char,
	r_go_up3_Char,
	r_go_up7_Char,
	r_up4_Char,
	r_up5_Char,
	r_up6_Char,
	r_down1_Char,
	r_down2_Char,
	r_down3_Char,
	r_go_down2_Char,
	r_go_down3_Char,
	r_go_down4_Char,
	r_go_down5_Char,
	r_go_down6_Char,
	r_down4_Char,
	r_down5_Char,
	r_down6_Char,
	r_down7_Char,
	r_down8_Char,
};

//------------------------------------------------------------------//
//		Animation Pattern Data of Dolphin		    //
//------------------------------------------------------------------//


// animation pattern of normal move 
AnmTable2 rick_normal_move_pat[] =
{
//   pat      img       time
	{ 0, r_up8_Char,   8},
	{ 1, r_up7_Char,   8},
	{ 2, r_up6_Char,   8},
	{ 3, r_up2_Char,   8},
	{ 4, r_up1_Char,   8},
	{ 5, r_down7_Char, 8},
	{ 0,           0, -1},
};


// animation pattern of operation stand-by  
AnmTable2 rick_kihon_idle_pat[] =
{
//   pat      img       time
	{  0, r_kihon0_Char,  8},
	{  1, r_kihon1_Char,  8},
	{  2, r_kihon2_Char,  8},
	{  3, r_kihon4_Char,  8},
	{  4, r_kihon5_Char,  8},
	{  5, r_kihon6_Char,  8},
	{  6, r_kihon0_Char,  8},
	{  0,             0, -1},
};

#define JUMP_INTERVAL 4
// animation pattern of jump  
AnmTable2 rick_jump_anm_pat[] =
{
	{ 0, r_go_up1_Char,    JUMP_INTERVAL},
	{ 1, r_go_up3_Char,    JUMP_INTERVAL},
	{ 2, r_go_up7_Char,    JUMP_INTERVAL},
	{ 3, r_up4_Char,       JUMP_INTERVAL},
	{ 4, r_up5_Char,       JUMP_INTERVAL},
	{ 5, r_up6_Char,       JUMP_INTERVAL},
	{ 6, r_down1_Char,     JUMP_INTERVAL},
	{ 7, r_down2_Char,     JUMP_INTERVAL},
	{ 8, r_down3_Char,     JUMP_INTERVAL},
	{ 9, r_go_down2_Char,  JUMP_INTERVAL},
	{ 10, r_go_down3_Char, JUMP_INTERVAL},
	{ 11, r_go_down4_Char, JUMP_INTERVAL},
	{ 12, r_go_down5_Char, JUMP_INTERVAL},
	{ 13, r_go_down6_Char, JUMP_INTERVAL},
	{ 14, r_down4_Char,    JUMP_INTERVAL},
	{ 15, r_down5_Char,    JUMP_INTERVAL},
	{ 16, r_down6_Char,    JUMP_INTERVAL},
	{ 17, r_down7_Char,    JUMP_INTERVAL},
	{ 18, r_down8_Char,    JUMP_INTERVAL},
};

// switch direction and attack animation patterns 
/*
AnmTable2 rick_attack_pat[] =
{
//   pat      img       time
	{ 0, r_attack1_Char,  2},
	{ 1, r_attack2_Char,  4},
	{ 2, r_attack4_Char,  6},
	{ 3, r_attack5_Char,  6},
	{ 4, r_attack6_Char,  6},
	{ 0,              0, -1},
	{ 5, r_attack7_Char,  8},
};
*/
AnmTable rick_attack_pat[] =
{
//   pat      img       time
	{ 0,  2},
	{ 1,  8},
	{ 2,  8},
	{ 3,  8},
	{ 4,  8},
	{ 5,  8},

};


// up/down move animation patterns  

AnmTable rick_kihon_fast_pat[] =
{
	{  0,     2},
	{  1,     2},
	{  2,     2},
	{  3,     2},
	{  4,     2},
	{  5,     2},
	{  6,     2},
	{  7,     2},
	{  8,     2},
	{  9,     2},
	{  0,    -1},
};



AnmTable rick_jump_pat[] =
{
	{  0,     4},
	{  1,     4},
	{  2,     4},
	{  3,     4},
	{  4,     4},
	{  5,     4},
	{  6,     4},
	{  7,     4},
	{  8,     4},
	{  9,     4},
	{ 10,     4},
	{ 11,     4},
	{ 12,     4},
	{ 13,     4},
	{ 14,     4},
	{ 15,     4},
	{ 16,     4},
	{ 17,     4},
	{ 18,     4},
	{ 19,     4},
	{ 20,     4},
	{ 21,     4},
	{ 22,     4},
	{ 23,     4},
	{ 24,     4},
};



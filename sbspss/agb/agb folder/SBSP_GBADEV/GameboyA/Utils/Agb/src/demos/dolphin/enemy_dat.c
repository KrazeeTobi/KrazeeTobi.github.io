/********************************************************************/
/*          enemy_dat.c                                             */
/*                 dolphin source                                   */
/*                                                                  */
/*          Copyright (C) 2000 NINTENDO Co.,Ltd.                    */
/********************************************************************/
#include <Agb.h>
#include "main.h"
#include "player.h"
#include "enemy.h"


// Basic graphics table for Nautilus 
const u8 *shell_base_pix_tbl[]=
{
	o_kihon001_Char,	o_kihon002_Char,
	o_kihon003_Char,	o_kihon004_Char,
	o_kihon005_Char,	o_kihon006_Char,
	o_kihon007_Char,	o_kihon008_Char,
	o_kihon009_Char,	o_kihon010_Char,
};

// Basic animation pattern table for Nautilus 
Anmpat shell_base_anm_pat[] =
{
//  pat delay action
	{0, 16,   SHELL_MOVE},
	{1, 16,   SHELL_MOVE},
	{2, 16,   SHELL_AWA},
	{3, 16,   SHELL_AWA},
	{4, 16,   SHELL_AWA},
	{5, 16,   SHELL_MOVE},
	{6, 16,   SHELL_AWA},
	{7, 16,   SHELL_MOVE},
	{8, 16,   SHELL_MOVE},
	{0, -1,   SHELL_MOVE},
};

// Attack graphics table for Nautilus 
const u8 *shell_attack_pix_tbl[] =
{
	o_kougeki000_Char,	o_kougeki001_Char,	o_kougeki002_Char,
	o_kougeki003_Char,	o_kougeki004_Char,	o_kougeki005_Char,
	o_kougeki006_Char,	o_kougeki007_Char,	o_kougeki008_Char,
	o_kougeki009_Char,	o_kougeki010_Char,	o_kougeki011_Char,
	o_kougeki012_Char,	o_kougeki013_Char,	o_kougeki014_Char,
	o_kougeki015_Char,	o_kougeki016_Char,	o_kougeki017_Char,
	o_kougeki018_Char,	o_kougeki019_Char,	o_kougeki020_Char,
};

// Attack animation pattern table for Nautilus 
Anmpat shell_attack_anm_pat[] =
{
//  pat delay action
	{0, 8,   SHELL_MOVE},
	{1, 8,   SHELL_MOVE},
	{2, 8,   SHELL_MOVE},
	{3, 8,   SHELL_MOVE},
	{4, 8,   SHELL_MOVE},
	{5, 8,   SHELL_MOVE},
	{6, 8,   SHELL_ATTACK},
	{7, 8,   SHELL_ATTACK},
	{8, 8,   SHELL_MOVE},
	{9, 8,   SHELL_ATTACK},
	{10, 8,  SHELL_MOVE},
	{11, 8,  SHELL_ATTACK},
	{0, -1,  SHELL_MOVE},
};

// Rotating graphics table for Nautilus 
const u8 *shell_yarare_pix_tbl[] =
{
	o_yarare000_Char, o_yarare001_Char, o_yarare002_Char,
	o_yarare003_Char, o_yarare004_Char, o_yarare005_Char,
	o_yarare006_Char, o_yarare007_Char, o_yarare008_Char,
	o_yarare009_Char, o_yarare010_Char, o_yarare011_Char,
	o_yarare012_Char, o_yarare013_Char, o_yarare014_Char,
	o_yarare015_Char, o_yarare016_Char, o_yarare017_Char,
	o_yarare018_Char, o_yarare019_Char, o_yarare020_Char,
};

// Rotating animation pattern table for Nautilus 
Anmpat shell_yarare_anm_pat[] =
{
//  pat delay action
	{0, 8,   SHELL_MOVE},
	{1, 8,   SHELL_MOVE},
	{2, 8,   SHELL_MOVE},
	{3, 8,   SHELL_MOVE},
	{4, 8,   SHELL_MOVE},
	{5, 8,   SHELL_MOVE},
	{6, 8,   SHELL_MOVE},
	{7, 8,   SHELL_MOVE},
	{8, 8,   SHELL_MOVE},
	{9, 8,   SHELL_MOVE},
	{10, 8,  SHELL_MOVE},
	{11, 8,  SHELL_MOVE},
	{12, 8,  SHELL_MOVE},
	{13, 8,  SHELL_MOVE},
	{14, 8,  SHELL_MOVE},
	{15, 8,  SHELL_MOVE},
	{16, 8,  SHELL_MOVE},
	{17, 8,  SHELL_MOVE},
	{18, 8,  SHELL_MOVE},
	{19, 8,  SHELL_MOVE},
	{20, 8,  SHELL_MOVE},
};

// Map data of enemy   
CharMapData shell_map_dat[] =
{
	{  556, 396, SHELL, 0,  SHELL_1_VRAM_POS, SHELL1_CHAR_NO},
	{  686, 440, SHELL, 0,  SHELL_2_VRAM_POS, SHELL2_CHAR_NO},
	{  728, 160, SHELL, 0,  SHELL_3_VRAM_POS, SHELL3_CHAR_NO},
	{  800, 356, SHELL, 0,  SHELL_4_VRAM_POS, SHELL4_CHAR_NO},

	{ 1456, 396, SHELL, 0,  SHELL_5_VRAM_POS, SHELL5_CHAR_NO},
	{ 1626, 240, SHELL, 0,  SHELL_6_VRAM_POS, SHELL6_CHAR_NO},
	{ 2028, 460, SHELL, 0,  SHELL_7_VRAM_POS, SHELL7_CHAR_NO},
	{ 2100, 356, SHELL, 0,  SHELL_8_VRAM_POS, SHELL8_CHAR_NO},

	{ 2700, 396, SHELL, 0,  SHELL_9_VRAM_POS, SHELL9_CHAR_NO},
	{ 2956, 440, SHELL, 0, SHELL_10_VRAM_POS, SHELL10_CHAR_NO},
	{ 3000, 160, SHELL, 0, SHELL_11_VRAM_POS, SHELL11_CHAR_NO},
	{ 3320, 356, SHELL, 0, SHELL_12_VRAM_POS, SHELL12_CHAR_NO},
};


Enemy_Oam_Data enemy_Oam_Data[ENEMY_OAM_NUM_MAX] =
{
	{  SHELL_1_VRAM_POS,  SHELL1_CHAR_NO},
	{  SHELL_2_VRAM_POS,  SHELL2_CHAR_NO},
	{  SHELL_3_VRAM_POS,  SHELL3_CHAR_NO},
	{  SHELL_4_VRAM_POS,  SHELL4_CHAR_NO},
	{  SHELL_5_VRAM_POS,  SHELL5_CHAR_NO},

	{  SHELL_6_VRAM_POS,  SHELL6_CHAR_NO},
	{  SHELL_7_VRAM_POS,  SHELL7_CHAR_NO},
	{  SHELL_8_VRAM_POS,  SHELL8_CHAR_NO},
	{  SHELL_9_VRAM_POS,  SHELL9_CHAR_NO},
	{  SHELL_10_VRAM_POS, SHELL10_CHAR_NO},
};

//======================================================
//    yos_anm.h
//    Header of Animation Data for Sample Yoshi
//
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#ifndef YOS_ANM_H
#define YOS_ANM_H

extern const AnmTbl *p1_yoshi_anm_patern[];
extern const AnmTbl *p1_heiho_anm_patern[];
extern const AnmTbl *p1_mbox_anm_patern[];
extern const AnmTbl *p1_sun_anm_patern[];
extern const AnmTbl *p1_killerS_anm_patern[];
extern const AnmTbl *p1_kokamek_anm_patern[];
extern const AnmTbl *p1_hosi_anm_patern[];
extern const AnmTbl *p1_kurukemu_anm_patern[];
extern const AnmTbl *p1_balloon_anm_patern[];
extern const AnmTbl *p1_bomb_anm_patern[];

extern const u8 *p1_yoshi_pixel_tbl[];
extern const u8 *p1_heiho_pixel_tbl[];
extern const u8 *p1_heiho_b_pixel_tbl[];
extern const u8 *p1_heiho_g_pixel_tbl[];
extern const u8 *p1_heiho_y_pixel_tbl[];
extern const u8 *p1_heihoL_pixel_tbl[];
extern const u8 *p1_mbox_pixel_tbl[];
extern const u8 *p1_sun_pixel_tbl[];
extern const u8 *p1_killerS_pixel_tbl[];
extern const u8 *p1_kokamek_pixel_tbl[];
extern const u8 *p1_hosi_pixel_tbl[];
extern const u8 *p1_kurukemu_pixel_tbl[];
extern const u8 *p1_balloon_pixel_tbl[];
extern const u8 *p1_bomb_pixel_tbl[];

//Yoshi Animation
enum
{
	YOS_ANM_NONE,
	YOS_ANM_NORMAL,
	YOS_ANM_WALK,//Walk
	YOS_ANM_L2R,//Turn Around
//	YOS_ANM_R2L,
	YOS_ANM_JUMP,
	YOS_ANM_RUN,
	YOS_ANM_TYOUHATU,
	YOS_ANM_FUNBARI,
	YOS_ANM_KURURINHA,
	YOS_ANM_DIE,
	YOS_ANM_BRING1,
	YOS_ANM_BRING2,
};

//Shy Guy Animation
enum
{
	HEIHO_ANM_NONE,
	HEIHO_ANM_WALK,
	HEIHO_ANM_TURN,
};

enum
{
	KILLERS_ANM_NONE,
	KILLERS_ANM_NORMAL,
};
enum
{
	SUN_ANM_NONE,
	SUN_ANM_D,
	SUN_ANM_C,
	SUN_ANM_NORMAL,
	SUN_ANM_S,
	SUN_ANM_SP,
};

#endif

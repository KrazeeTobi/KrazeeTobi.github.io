//======================================================
//    yos_game_dat.c
//    Sample Yoshi Game Data
//
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================
#include <Agb.h>
#include "yos_type.h"
#include "yos_game.h"
#include "etc_bmp.h"
#include "oam_proc.h"
#include "yos_bmp.h"
#include "yos_anm.h"

//Map of Appearing Characters
//       dat0, dat1, dat2, dat3
//heiho  minx, maxx, anmw, color
//heihoL minx, maxx, anmw
//killer   vx,   vy, dir
//5t      
//bomb   minx, maxx,
const CharMapData p1_charMapData[]=
{//xy,                 type           ,     status     , dat0,  dat1, dat2, dat3
//	{{ 100,100},   CHR_TYPE_YOSHI     ,               1,    0              },
#ifdef SPEED_CHK
	{{  90,230},   CHR_TYPE_EGG       , CHAR_ST_NORMAL ,    0              },//Speedometer
#endif
	{{ 180, 80},   CHR_TYPE_BALLOON   , BALLOON_ST_NA  ,    0              },//Balloon
	{{  80, 80},   CHR_TYPE_HAKO      , CHAR_ST_NORMAL ,    0              },//Box
	{{1600, 80},   CHR_TYPE_HAKO      , CHAR_ST_NORMAL ,    0              },//Box
	{{ 260, 92},   CHR_TYPE_HEIHO     , HEIHO_ST_NA    ,  230,   270,    0, 0},//hei
	{{ 850,120},   CHR_TYPE_HEIHO     , HEIHO_ST_NA    ,  700,  1000,    1, 1},//hei
	{{1100,120},   CHR_TYPE_HEIHO     , HEIHO_ST_NA    , 1078,  1190,    2, 2},//hei
	{{1600,120},   CHR_TYPE_HEIHO     , HEIHO_ST_NA    , 1560,  1800,    3, 3},//hei
	{{ 600, 80},   CHR_TYPE_HEIHOL    , HEIHO_ST_NA    ,  530,   650,    4,},//Shy Guy Large
	{{1250,160},   CHR_TYPE_HEIHOL    , HEIHO_ST_NA    , 1224,  1300,    4,},//Shy Guy Large
	{{ 860,110},   CHR_TYPE_HAKO      , CHAR_ST_NORMAL ,    0              },//Box
	{{ 300, 80},   CHR_TYPE_KILLER_S  , KILLERS_ST_NA  ,    0,     0,   -1,},//
	{{ 500, 80},   CHR_TYPE_KILLER_S  , KILLERS_ST_NA  ,    0,     0,   -1,},//
//	{{ 650, 60},   CHR_TYPE_KILLER_L  , KILLERS_ST_NA  ,    0,     0,   -1,},//
	{{1500, 80},   CHR_TYPE_KILLER_S  , KILLERS_ST_NA  ,    0,     0,    1,},//
	
	{{1750, 60},   CHR_TYPE_5T        , CHAR_ST_NA     ,    0,     0,    1,},//
	{{1800, 60},   CHR_TYPE_5T        , CHAR_ST_NA     ,    0,     0,    1,},//
	{{1850, 60},   CHR_TYPE_5T        , CHAR_ST_NA     ,    0,     0,    1,},//
	{{ 150, 60},   CHR_TYPE_5T        , CHAR_ST_NA     ,    0,     0,    1,},//
	{{ 350, 94},   CHR_TYPE_BOMB      , CHAR_ST_NA     ,  300,   400,    1,},//
	{{1500, 94},   CHR_TYPE_BOMB      , CHAR_ST_NA     , 1450,  1520,    1,},//
	{{1775,190},   CHR_TYPE_DOKAN     , CHAR_ST_NORMAL ,    0,     0,    0,},//
	{{1825,190},   CHR_TYPE_DOKAN     , CHAR_ST_NORMAL ,    0,     0,    0,},//
	{{ 350, 94},   CHR_TYPE_DOKAN     , CHAR_ST_NORMAL ,    0,     0,    0,},//
	{{ 440, 64},   CHR_TYPE_KUKI      , CHAR_ST_NORMAL ,    0,     0,    0,},//
	{{ 440, 38},   CHR_TYPE_HANA      , CHAR_ST_NORMAL ,    0,     0,    0,},//
	{{1750,124},   CHR_TYPE_KUKI      , CHAR_ST_NORMAL ,    0,     0,    0,},//
	{{1750, 98},   CHR_TYPE_HANA      , CHAR_ST_NORMAL ,    0,     0,    0,},//
	{{1430, 94},   CHR_TYPE_KUKI      , CHAR_ST_NORMAL ,    0,     0,    0,},//
	{{1430, 68},   CHR_TYPE_HANA      , CHAR_ST_NORMAL ,    0,     0,    0,},//
	{{ 800, 74},   CHR_TYPE_KUKI      , CHAR_ST_NORMAL ,    0,     0,    0,},//
	{{ 800, 48},   CHR_TYPE_HANA      , CHAR_ST_NORMAL ,    0,     0,    0,},//
	{{ 750, 10},   CHR_TYPE_KOKAMEK0  , CHAR_ST_NA     ,  600,   900,    1,},//
	{{ 750, 10},   CHR_TYPE_TOGE      , CHAR_ST_NA     ,    1,     0,    0,},//
	{{1078, 40},   CHR_TYPE_KOKAMEK0  , CHAR_ST_NA     , 1000,  1200,    1,},//
	{{1078, 40},   CHR_TYPE_TOGE      , CHAR_ST_NA     ,    1,     0,    0,},//
	{{   0,  0},                    -1}//end
};

//Ground Line
const xyPos p1_mapALine[]=
{
	//                                                                   ___________________________
	//                                              ____________________|                           |
	//                           __________________|                                                |
	//__________________________/                                                                   |
	{-200,0},{-200,190},{51,190},{108,158},{210,158},{210,143},{273,143},{273,94},{442,94},{442,340},
	
	//        ________________                       ____________________
	//       |                Å_                    /                    |_____________________
	//_______|                  Å__________________/                                           |
	{504,340},{504,94},{611,93},{809,190},{944,190},{1078,126},{1202,126},{1202,174},{1328,174},{1328,340},
	
	//         _____________________
	//        |                     |__________________
	//________|                       
	{1418,340},{1418,158},{1554,158},{1554,190},{2000,190},{-1,-1},
};

//Default OAM Data for Initialization
const u32 p1_OamData_Sample[1][2] = {{OAM_OBJ_OFF,(1<<12)+0x80}};

//Starting Position of Yoshi
const xyPos p1_yoshi_start_pos={0,DISP_Y};

//Characteristics of Characters
//   oam01,
//   oam2, col, mid, Aparam, pri, hit_flg(At the time of Appearance), 
const CharSpecData p1_charSpecData[]=
{
	{	OAM_SIZE_32x64|(AFN_WORK_YOS<<OAM_AFFINE_NO_SHIFT)|OAM_AFFINE_TWICE|OAM_COLOR_256,
		CNUM_YOSHI,{{- 8,-16},{ 8,17}}, { 16<<16,32<<16}, AFN_WORK_YOS, PRI_YOSHI,0},//Yoshi
	{	OAM_SIZE_32x32|(0<<OAM_AFFINE_NO_SHIFT)|OAM_COLOR_256|OAM_AFFINE_TWICE,
		CNUM_HEIHO0,{{- 8,-11},{ 8,18}}, { 16<<16,16<<16},          0, PRI_HEIHO,
		HIT_LR | HIT_T | HIT_B | HIT_YLR},//Shy Guy
	{	OAM_SIZE_32x32|(AFN_WORK_HAKO<<OAM_AFFINE_NO_SHIFT)|OAM_AFFINE_TWICE|OAM_COLOR_256,
		CNUM_HAKO,{{-12,-15},{12,16}}, {16<<16,16<<16}, AFN_WORK_HAKO, PRI_HAKO,
		HIT_LR | HIT_T | HIT_B },//Box
	{	OAM_SIZE_16x16|(AFN_WORK_EGG<<OAM_AFFINE_NO_SHIFT)|OAM_AFFINE_TWICE|OAM_COLOR_256,
		CNUM_EGG,{{ -8, -8},{ 8, 8}}, { 8<<16, 8<<16}, AFN_WORK_EGG, PRI_EGG,0},//Egg
	{	OAM_SIZE_32x32|OAM_COLOR_256,
		CNUM_SUN,{{-16,-16},{16,16}}, {16<<16,16<<16}, 0, PRI_GAGE,0},//Sun Gauge
	{	OAM_SIZE_32x32|(AFN_WORK_GL<<OAM_AFFINE_NO_SHIFT)|OAM_COLOR_256|OAM_AFFINE_TWICE,
		CNUM_KILLER_S0,{{-16,-13},{16,12}}, {16<<16,16<<16}, AFN_WORK_GL, PRI_KILLER,
		HIT_LR | HIT_T | HIT_B | HIT_YLR|HIT_D_H},//KILLER_S
	{	OAM_SIZE_64x64|(AFN_WORK_GL<<OAM_AFFINE_NO_SHIFT)|OAM_COLOR_256|OAM_AFFINE_TWICE,
		CNUM_KILLER_L,{{-24,-16},{24,16}}, {32<<16,32<<16}, AFN_WORK_GL, PRI_KILLER,
		HIT_LR | HIT_T | HIT_B | HIT_YLR},//KILLER_L
	{	OAM_SIZE_32x32|OAM_COLOR_256|OAM_AFFINE_TWICE,
		CNUM_KOKAMEK0,{{-16,-16},{16,16}}, {16<<16,16<<16},0, PRI_KOKAMEK_U,0},//Kokamek0
	{	OAM_SIZE_32x32|OAM_COLOR_256|OAM_AFFINE_TWICE,
		CNUM_KOKAMEK1,{{-16,-16},{16,16}}, {16<<16,16<<16},0, PRI_KOKAMEK_D,0},//Kokamek1
	{	OAM_SIZE_64x64|(AFN_WORK_HEIHOL<<OAM_AFFINE_NO_SHIFT)|OAM_COLOR_256|OAM_AFFINE_TWICE,
		CNUM_HEIHOL,{{-16,-24},{16,32}}, {32<<16,32<<16}, AFN_WORK_HEIHOL,   5,
		HIT_LR | HIT_T | HIT_B | HIT_YLR},//Shy Guy(L)

	{	OAM_SIZE_16x16|OAM_COLOR_256,
		CNUM_HANABIRA0,{{- 8,- 8},{ 8, 8}}, { 8<<16, 8<<16}, 0,   0, 0},//Petal0
	{	OAM_SIZE_16x16|OAM_COLOR_256,
		CNUM_HANABIRA3,{{- 8,- 8},{ 8, 8}}, { 8<<16, 8<<16}, 0,   0, 0},//Petal1
	{	OAM_SIZE_16x16|OAM_COLOR_256,
		CNUM_HANABIRA6,{{- 8,- 8},{ 8, 8}}, { 8<<16, 8<<16}, 0,   0, 0},//Petal2
	{	OAM_SIZE_16x16|OAM_COLOR_256|OAM_V_FLIP,
		CNUM_HANABIRA3,{{- 8,- 8},{ 8, 8}}, { 8<<16, 8<<16}, 0,   0, 0},//Petal3
	{	OAM_SIZE_16x16|OAM_COLOR_256|OAM_V_FLIP,
		CNUM_HANABIRA0,{{- 8,- 8},{ 8, 8}}, { 8<<16, 8<<16}, 0,   0, 0},//Petal4
	{	OAM_SIZE_16x16|OAM_COLOR_256|OAM_V_FLIP|OAM_H_FLIP,
		CNUM_HANABIRA3,{{- 8,- 8},{ 8, 8}}, { 8<<16, 8<<16}, 0,   0, 0},//Petal5
	{	OAM_SIZE_16x16|OAM_COLOR_256|OAM_H_FLIP,
		CNUM_HANABIRA6,{{- 8,- 8},{ 8, 8}}, { 8<<16, 8<<16}, 0,   0, 0},//Petal6
	{	OAM_SIZE_16x16|OAM_COLOR_256|OAM_H_FLIP,
		CNUM_HANABIRA3,{{- 8,- 8},{ 8, 8}}, { 8<<16, 8<<16}, 0,   0, 0},//Petal7
	{	OAM_SIZE_16x16|OAM_COLOR_256|OAM_AFFINE_NORMAL,
		CNUM_HANABIRA0,{{- 8,- 8},{ 8, 8}}, { 8<<16, 8<<16}, 0,   0, 0},//Petal8 (For Revolving)

	{	OAM_SIZE_16x16|OAM_COLOR_256|OAM_AFFINE_NORMAL,
		CNUM_KOUMORI,{{- 8,- 8},{ 8, 8}}, { 8<<16, 8<<16}, 0,   0, 0},//Bat
	{	OAM_SIZE_64x64|OAM_COLOR_256,
		CNUM_KUMO0  ,{{-32,-32},{32,32}}, {32<<16,32<<16}, 0,   0, 0},//Cloud Left
	{	OAM_SIZE_64x64|OAM_COLOR_256,
		CNUM_KUMO1  ,{{-32,-32},{32,32}}, {32<<16,32<<16}, 0,   0, 0},//Cloud Right
	{	OAM_SIZE_8x8|OAM_COLOR_256,
		0           ,{{ -4, -4},{ 4, 4}}, { 4<<16, 4<<16}, 0,   1, 0},//Star
	{	OAM_SIZE_32x32|OAM_COLOR_256,
		CNUM_KURUKEMU,{{ -16, -16},{16,16}}, {16<<16,16<<16}, 0,   1, 0},//Ground Pound Smoke
	{	OAM_SIZE_16x8 |OAM_COLOR_256|OAM_AFFINE_TWICE,//|(AFN_WORK_KAGE<<OAM_AFFINE_NO_SHIFT)
		CNUM_KAGE0  ,{{ -8, -4},{8,4}}, {8<<16,4<<16}, 0,   PRI_KAGE, 0},//Shadow0
	{	OAM_SIZE_16x16|OAM_COLOR_256,
		0           ,{{ -8, -8},{8,8}}, {8<<16,8<<16}, 0,   1, 0},//Dash Smoke
	{	OAM_SIZE_32x16|OAM_COLOR_256|OAM_AFFINE_TWICE|(AFN_WORK_GL<<OAM_AFFINE_NO_SHIFT),
		CNUM_KAGEL  ,{{ -16, -4},{16,4}}, {16<<16, 4<<16}, 0,   PRI_KAGE, 0},//Shadow Large
	{	OAM_SIZE_32x32|OAM_COLOR_256|OAM_AFFINE_TWICE|(AFN_WORK_BALLOON<<OAM_AFFINE_NO_SHIFT),
		CNUM_BALLOON,{{- 8,- 8},{ 8, 8}}, {16<<16,16<<16}, 0,   PRI_OT, HIT_LR | HIT_T | HIT_B},//Balloon
	{	OAM_SIZE_32x32|OAM_COLOR_256|OAM_AFFINE_TWICE,
		CNUM_5T     ,{{- 8,- 8},{ 8, 8}}, {16<<16,16<<16}, 0,   PRI_5T, HIT_LR | HIT_T | HIT_B | HIT_D_H},//5T
	{	OAM_SIZE_32x32|OAM_COLOR_256|OAM_AFFINE_TWICE,
		CNUM_BOMB   ,{{- 8,- 8},{ 8,18}}, {16<<16,16<<16}, 0,   1, HIT_LR | HIT_T | HIT_B | HIT_YLR},//BOMB
	{	OAM_SIZE_32x32|OAM_COLOR_256|OAM_AFFINE_TWICE,
		CNUM_DOKAN  ,{{- 8,-10},{ 8,14}}, {16<<16,16<<16}, 0,   1, HIT_LR | HIT_T | HIT_B },//Pipe
	{	OAM_SIZE_32x32|OAM_COLOR_256|OAM_AFFINE_TWICE|(AFN_WORK_HANA<<OAM_AFFINE_NO_SHIFT),
		CNUM_HANA   ,{{-16,-16},{16,16}}, {16<<16,16<<16}, 0,   PRI_HANA, 0},//Flower
	{	OAM_SIZE_32x32|OAM_COLOR_256|OAM_AFFINE_TWICE,
		CNUM_KUKI   ,{{-16,-16},{16,16}}, {16<<16,16<<16}, 0,   PRI_KUKI, 0},//Stem
	{	OAM_SIZE_32x32|OAM_COLOR_256|OAM_AFFINE_TWICE,
		CNUM_TOGE   ,{{- 8,- 8},{ 8, 8}}, {16<<16,16<<16}, 0,   PRI_TOGE, 0},//Thorn
};

//Table of OBJ Characters that are transferred in the beginning
const ObjChr p1_objChrTbl[]=
{//       pSource    ,    charNo     , size(char)
	{  _binary_killer_s1_imb_start, CNUM_KILLER_S0, 16},//
//	{  killer_l1_Char, CNUM_KILLER_L , 64},//
	{        _binary_egg_imb_start, CNUM_EGG      ,  4},//egg
	{  _binary_kokamek_a_imb_start, CNUM_KOKAMEK0 , 16},//kokamek0
	{  _binary_kokamek_c_imb_start, CNUM_KOKAMEK1 , 16},//kokamek1
	{  _binary_HANABIRA1_imb_start, CNUM_HANABIRA0,  4},//Petal0
	{  _binary_HANABIRA2_imb_start, CNUM_HANABIRA1,  4},//Petel1
	{  _binary_HANABIRA3_imb_start, CNUM_HANABIRA2,  4},//Petal2
	{_binary_HANABIRAn_1_imb_start, CNUM_HANABIRA3,  4},//Petal3
	{_binary_HANABIRAn_2_imb_start, CNUM_HANABIRA4,  4},//Petal4
	{_binary_HANABIRAn_3_imb_start, CNUM_HANABIRA5,  4},//Petal5
	{_binary_HANABIRAy_1_imb_start, CNUM_HANABIRA6,  4},//Petal6
	{_binary_HANABIRAy_2_imb_start, CNUM_HANABIRA7,  4},//Petal7
	{_binary_HANABIRAy_3_imb_start, CNUM_HANABIRA8,  4},//Petal8
//	{    _binary_koumori_imb_start, CNUM_KOUMORI  ,  4},//Bat
	{      _binary_hosi1_imb_start, CNUM_HOSI     ,  1},//Star0
	{      _binary_hosi2_imb_start, CNUM_HOSI1    ,  1},//Star1
	{      _binary_hosi3_imb_start, CNUM_HOSI2    ,  1},//Star2
	{      _binary_hosi4_imb_start, CNUM_HOSI3    ,  1},//Star3
	{      _binary_hosi5_imb_start, CNUM_HOSI4    ,  1},//Star4
	{      _binary_hosi6_imb_start, CNUM_HOSI5    ,  1},//Star5
	{      _binary_hosi7_imb_start, CNUM_HOSI6    ,  1},//Star6
	{      _binary_hosi8_imb_start, CNUM_HOSI7    ,  1},//Star7
	{      _binary_kage0_imb_start, CNUM_KAGE0    ,  2},//Shadow0
	{  _binary_batabata1_imb_start, CNUM_BATABATA0,  4},//BATABATA0
	{  _binary_batabata2_imb_start, CNUM_BATABATA1,  4},//BATABATA1
	{  _binary_batabata3_imb_start, CNUM_BATABATA2,  4},//BATABATA2
	{  _binary_batabata4_imb_start, CNUM_BATABATA3,  4},//BATABATA3
	{  _binary_batabata5_imb_start, CNUM_BATABATA4,  4},//BATABATA4
	{  _binary_batabata6_imb_start, CNUM_BATABATA5,  4},//BATABATA5
	{  _binary_batabata7_imb_start, CNUM_BATABATA6,  4},//BATABATA6
	{  _binary_batabata8_imb_start, CNUM_BATABATA7,  4},//BATABATA7
	{      _binary_kagel_imb_start, CNUM_KAGEL    ,  4},//Shadow Large
	{    _binary_balloon_imb_start, CNUM_BALLOON  , 16},//
	{    _binary_omori5t_imb_start, CNUM_5T       , 16},//
	{     _binary_bomb_1_imb_start, CNUM_BOMB     , 16},//
	{      _binary_dokan_imb_start, CNUM_DOKAN    , 16},//
	{       _binary_hana_imb_start, CNUM_HANA     , 16},//
	{       _binary_kuki_imb_start, CNUM_KUKI     , 16},//
	{       _binary_toge_imb_start, CNUM_TOGE     , 16},//
	{               0,              0,255}//end
};

//OBJ Data that is read when taken away to castle
const ObjChr p1_objChrTbl2[]=
{//       pSource    ,    charNo   , size(char)
	{_binary_kumo_nuki_l_imb_start, CNUM_KUMO0  , 64},//Cloud (L)
	{_binary_kumo_nuki_r_imb_start, CNUM_KUMO1  , 64},//Cloud (R)
	{    _binary_koumori_imb_start, CNUM_KOUMORI, 16},//Bat
	{               0,            0,255}//end
};

//For Initialization of Animation Work
const AnmInfo p1_anmInfo_def[ANM_WORK_MAX]=
{
	{(u8**)   p1_yoshi_pixel_tbl, (AnmTbl**)   p1_yoshi_anm_patern, CNUM_YOSHI    , 32},//Yoshi
	{(u8**)p1_kurukemu_pixel_tbl, (AnmTbl**)p1_kurukemu_anm_patern, CNUM_KURUKEMU , 16},//Ground Pound Smoke
	{(u8**)   p1_heiho_pixel_tbl, (AnmTbl**)   p1_heiho_anm_patern, CNUM_HEIHO0   , 16},//Shy Guy0
	{(u8**)   p1_heiho_pixel_tbl, (AnmTbl**)   p1_heiho_anm_patern, CNUM_HEIHO1   , 16},//      1
	{(u8**)   p1_heiho_pixel_tbl, (AnmTbl**)   p1_heiho_anm_patern, CNUM_HEIHO2   , 16},//      2
	
	{(u8**)   p1_heiho_pixel_tbl, (AnmTbl**)   p1_heiho_anm_patern, CNUM_HEIHO3   , 16},//      3
	{(u8**)   p1_heiho_pixel_tbl, (AnmTbl**)   p1_heiho_anm_patern, CNUM_HEIHO4   , 16},//      4
	{(u8**)   p1_heiho_pixel_tbl, (AnmTbl**)   p1_heiho_anm_patern, CNUM_HEIHO5   , 16},//      5
	{(u8**)  p1_heihoL_pixel_tbl, (AnmTbl**)   p1_heiho_anm_patern, CNUM_HEIHOL   , 64},//Shy Guy Large
	{(u8**)    p1_mbox_pixel_tbl, (AnmTbl**)    p1_mbox_anm_patern, CNUM_HAKO     , 16},//Box

	{(u8**)     p1_sun_pixel_tbl, (AnmTbl**)     p1_sun_anm_patern, CNUM_SUN      , 16},//Sun
	{(u8**)   p1_yoshi_pixel_tbl, (AnmTbl**)   p1_yoshi_anm_patern, CNUM_YOSHI    , 32},//Dash Smoke
	{(u8**) p1_killerS_pixel_tbl, (AnmTbl**) p1_killerS_anm_patern, CNUM_KILLER_S0, 16},//Killer
//	{(u8**) p1_killerL_pixel_tbl, (AnmTbl**) p1_killerL_anm_patern, CNUM_KILLER_L , 64},//Killer (L)
	{(u8**) p1_balloon_pixel_tbl, (AnmTbl**) p1_balloon_anm_patern, CNUM_BALLOON  , 16},//Balloon

	{(u8**)    p1_bomb_pixel_tbl, (AnmTbl**)    p1_bomb_anm_patern, CNUM_BOMB     , 16},//Bob-omb
};

//Petal Upper Left Coordinate
const xyPos p1_hanabira_pos[]=
{
	{24<<16, 6<<16},{36<<16,12<<16},{42<<16,24<<16},{36<<16,36<<16},
	{24<<16,42<<16},{12<<16,36<<16},{ 6<<16,24<<16},{12<<16,12<<16},
};
//Default Rotation Angle of Petals
s16 p1_hanabira_rot_tbl[]=
{
	0,0xe0,0xc0,0xa0, 0x80,0x60,0x40,0x20
};

//Value of Yoshi stretched vertically
const s32 p1_tatenobi_tbl[10]=
{
	0x1000,0x2000,0x3000,0x4000,0x5000,0x4000,0x3000,0x2000,0x1000,0x0
};


const u16 p1_obj_Palette[256] = {
0xffe0,0x001f,0x001f,0x001f,0x001f,0x841e,0x000d,0x883f,
0x041f,0x081f,0x0c3b,0x9477,0x0c38,0xc619,0x101f,0x880f,
0x1010,0x30f8,0x5a3f,0xfb9f,0xeebf,0xb14d,0xb050,0x6b5a,
0xeb3a,0x416f,0x64b4,0x2c27,0x0400,0x1022,0x592a,0x0400,
0x0000,0x7021,0x6f7b,0x1c20,0x8c00,0x0000,0x2c40,0x4880,
0xf922,0xffde,0xa0e7,0x6f7b,0x7ffe,0xf37b,0x1084,0x6f7a,
0x3103,0x4de8,0xe26c,0xef7b,0xc9a5,0x18a2,0xeef0,0x62d2,
0x5a49,0x7fb9,0xbd86,0x7752,0x3167,0x0c61,0x526c,0x0000,
0x0420,0x8420,0x0421,0xa94a,0xffff,0xb18c,0x77bd,0xc627,
0x632d,0xb9e6,0x8000,0x98c5,0x0841,0xc2c9,0xe7b3,0x2e64,
0x6bd8,0xb305,0x9662,0x9d86,0xd392,0x0000,0x6f7b,0x0040,
0x9ac7,0x9626,0x8080,0x80e1,0x0202,0x82a3,0x8785,0x0181,
0x8263,0x82e4,0x0344,0x02e4,0x8704,0x06e4,0x0b45,0x8fc8,
0x1fec,0x8a25,0xaead,0x1329,0xb3f1,0x8267,0xf3dd,0x1ff7,
0x0e2d,0x0b53,0x83d9,0x9f38,0x8fbd,0xcf18,0x83de,0x035a,
0x8000,0xa14a,0x8842,0xd294,0x6f9c,0x2d8c,0x6f7b,0xe318,
0x17ff,0xe3ff,0xefff,0x0108,0x47de,0xf7ff,0x37be,0x837e,
0x8ad9,0x1dcf,0x035e,0x0633,0x856d,0x8f7f,0xdb9d,0x073e,
0x2675,0xffff,0x833f,0x033e,0x031e,0x133d,0x8022,0x235f,
0x956d,0x86fd,0xe77c,0x6fde,0xd2b6,0x031f,0x0f3f,0x04a6,
0xbeb7,0x9ebb,0xdb3a,0x8aff,0x8443,0x027d,0x02bf,0x92df,
0x6b7b,0x99b2,0x825e,0x021a,0x0a5c,0x0593,0x90ea,0x35ce,
0x163c,0x91d7,0x1619,0xae9c,0x021f,0x125f,0x0000,0xa25d,
0xca53,0x01bf,0x04cd,0x09df,0xa54d,0x0558,0x097b,0x015f,
0x0465,0x04d2,0x919f,0x90ee,0x52fd,0x84d6,0x9933,0x80df,
0x0889,0x1538,0xdf1f,0x009f,0x847a,0x807d,0x0002,0x005f,
0x8007,0x003f,0x8c7d,0xb196,0x001f,0x001f,0x001e,0x001d,
0x001b,0x0000,0x0018,0x001f,0x8015,0x8012,0x801f,0x801d,
0x0004,0x843f,0x800a,0x8c7f,0x94be,0x1d1f,0x35df,0x8000,
0xfbdf,0xbdef,0x7fff,0x6f7b,0xfbde,0x6739,0xffff,0xffff,
0x7fff,0x7fff,0xf39c,0xef7b,0x6f7b,0x6f7b,0xeb5a,0x5ef7,
0x5ad6,0xc631,0xb5ad,0xa529,0xa108,0x0000,0x0000,0x0000,
};


//Kokamek surrounding position
const xyPos p1_kokamekPos[4]=
{
	{-17<<16,-16<<16},//Upper Left
	{ 17<<16,-16<<16},//Upper Right
	{-14<<16, 14<<16},//Lower Left
	{ 14<<16, 14<<16},//Lower Right
};

//Coordinate of Bats, Zoom
const s32 p1_koumoriDat[KOUMORI_NUM][3]=
{
	{ 90, 50, 0x09000},
	{100, 20, 0x08000},
	{170, 10, 0x06000},
	{190, 25, 0x08000},
};

#define RAND_V1 (0x8000)
#define RAND_V2 (0x4000)
const xyPos p1_balloon_randv_tbl[]=
{
	{ RAND_V1,       0},{ RAND_V2, RAND_V2},
	{       0,-RAND_V1},{-RAND_V2,-RAND_V2},
	{-RAND_V1,       0},{-RAND_V2, RAND_V2},
	{       0, RAND_V1},{ RAND_V2, RAND_V2},
};
//Initial Coordinate of Balloon
xyPos p1_balloon_pos[]=
{
	{ 140<<16, 90<<16}
};

u8 **p1_heiho_pix_tbl[]=
{
	(u8**)p1_heiho_pixel_tbl,//red
	(u8**)p1_heiho_y_pixel_tbl,//yellow
	(u8**)p1_heiho_g_pixel_tbl,//green
	(u8**)p1_heiho_b_pixel_tbl,//blue
};


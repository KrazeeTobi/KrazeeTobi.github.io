//======================================================
//    yos_game_dat.h
//    Data header for Sample Yoshi Game
//
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#ifndef YOS_GAME_DAT_H
#define YOS_GAME_DAT_H

extern const u32 p1_OamData_Sample[1][2];
extern const CharSpecData p1_charSpecData[];
extern const xyPos p1_curMovTbl[16];
extern const xyPos p1_kokamekPos[4];
extern const xyPos p1_yoshi_start_pos;
extern const xyPos p1_mapALine[];
extern const ObjChr p1_objChrTbl[];
extern const CharMapData p1_charMapData[];
extern const ObjChr p1_objChrTbl[];
extern const ObjChr p1_objChrTbl2[];
extern const AnmInfo p1_anmInfo_def[ANM_WORK_MAX];
extern const xyPos p1_hanabira_pos[8];
extern const s32 p1_tatenobi_tbl[10];
extern s16 p1_hanabira_rot_tbl[8];
extern const s32 p1_koumoriDat[KOUMORI_NUM][3];
extern const xyPos p1_balloon_randv_tbl[];
extern xyPos p1_balloon_pos[];
extern u8 **p1_heiho_pix_tbl[];
extern const u16 p1_obj_Palette[256];

#endif

//======================================================
//    ce_dat.h
//    Header file for color special effects sample data
//
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================
#ifndef CE_DAT_H
#define CE_DAT_H
extern const u32	ce_OamData_Sample[1][2];
extern char *ce_type_tbl[];

extern const u16 ce_bg1_Palette[256];
extern const u8 ce_bg1_Character[8*8*56];
extern const u16 ce_bg1_Map[32*20];
extern const u8 ce_bg3_Character[8*8*143];
extern const u16 ce_bg3_Map[32*20];
extern const u16 ce_PS_hey5_Palette[256];
extern const u8 ce_PS_hey5_Char[8*8*(32/8/1/1)*(64/8) + 0];
extern u32 ce_moji_Character[8*37];

#endif

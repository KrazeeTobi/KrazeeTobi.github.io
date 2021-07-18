/********************************************************************/
/*      obj.h                                                       */
/*          Personal OBJ Control Library   Header                   */
/*                                                                  */
/*              Copyright (C) 1999-2001 NINTENDO Co.,Ltd.           */
/********************************************************************/
#ifndef	__OBJ_H__
#define	__OBJ_H__

#include <AgbTypes.h>

#define OBJ_V_SIZE_64	0xc000
#define OBJ_V_SIZE_32	0x8000
#define OBJ_V_SIZE_16	0x4000
#define OBJ_V_SIZE_8	0x0000
#define OBJ_COLOR_256	0x2000
#define OBJ_COLOR_16	0x0000
#define OBJ_MOSAIC_ON	0x1000
#define OBJ_MOSAIC_OFF	0x0000
#define OBJ_MODE_WINDOW	0x0800
#define OBJ_MODE_BLEND	0x0400
#define OBJ_MODE_NORMAL	0x0000
#define OBJ_AFFINE_X2	0x0300
#define OBJ_AFFINE_X1	0x0100
#define OBJ_AFFINE_OFF	0x0000
#define OBJ_Y			0x00ff

#define OBJ_H_SIZE_64	0xc000
#define OBJ_H_SIZE_32	0x8000
#define OBJ_H_SIZE_16	0x4000
#define OBJ_H_SIZE_8	0x0000
#define OBJ_HV_FLIP		0x3000
#define OBJ_V_FLIP		0x2000
#define OBJ_H_FLIP		0x1000
#define OBJ_AFFINE_NO	0x3e00
#define OBJ_X			0x01ff

#define	OBJ_PLTT_NO		0xf000
#define OBJ_PRIORITY_1	0x0000
#define OBJ_PRIORITY_2	0x0400
#define OBJ_PRIORITY_3	0x0800
#define OBJ_PRIORITY_4	0x0c00
#define OBJ_CHAR_NO		0x03ff

// struct declaration-----------------------------------
typedef struct objBufferTag {
	u16			atr0;
	u16			atr1;
	u16			atr2;
	u16			atrx;
}objBuffer;

typedef struct objStatusTag {
	buffer 		buff;
}objStat;

/*
typedef struct AnimeTag {
	bool		onFlag;
	u16			nextFlame;
	u16			*topData;
	u16			*nowData;
}Anime;

typedef	struct MoveTag {
	bool		onFlag;
	u16			nextFlame;
	u16			*topData;
	u16			*nowData;
}Move;


typedef	struct ObjGroupTag {
	u16			member;
	u16			*p;
}
typedef	objManager
*/
typedef struct pos_objTag {
	u16			x;
	u16			y;
}pos_obj;

typedef struct csrDefineTag {
	const pos_obj *posList;
	const u16	*charList;
	u8			member;
	u8			objNo;
	u16			palette;
}csrDefine;

typedef struct cursorStatusTag {
	const csrDefine *define;
	u8			objNo;
	u8			oldNum;
	u8			animeChar;
	u8			animeCount;
}csrStat;

// function's prototype declaration---------------------
extern void SetOamBuffer(u16 *buff,u32 size);
extern void DmaOamBuffer();
extern void SetOamBufferRenewal(bool renewal);

extern void SetCursorStatus(const csrDefine *csr,u8 nowNum);
extern void SetCursorChar(u16 charNo,u16 palette);
extern void DeleteCursor();
extern u16	GetCurosrPosOnBg(u8 nowNum);
extern void CheckCursorPos(u8 *nowNum);
extern void CheckCursorPosRange(u8 *nowNum,u8 min,u8 max);
extern void MoveAndAnimeCursor(u8 nowNum);

#endif		// __OBJ_H__

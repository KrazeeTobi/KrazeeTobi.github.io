//======================================================
//    bgmanage.h                                      
//    Background management
//                                                     
//    Copyright (C) 1999, NINTENDO Co., Ltd.             
//======================================================

#ifndef	__BGMANAGE_H__
#define	__BGMANAGE_H__

#include <agb.h>
#include "background.h"
#include "node.h"

#define	BGNUMBER_TEXT0	(0)
#define	BGNUMBER_TEXT1	(1)
#define	BGNUMBER_TEXT2	(2)
#define	BGNUMBER_TEXT3	(3)
#define	BGNUMBER_SR	(0x80)
#define	BGNUMBER_SR2	(BGNUMBER_TEXT2|BGNUMBER_SR)
#define	BGNUMBER_SR3	(BGNUMBER_TEXT3|BGNUMBER_SR)

//----------------------------------------------------------------------
typedef struct
{
    Background* bg_ptr;
    u8  bg_number;
} bmBackgroundInstance;
//----------------------------------------------------------------------
typedef struct
{
    s16 x;
    s16 y;
} Point16;
typedef struct
{
    u16 w;
    u16 h;
} Size16;
//----------------------------------------------------------------------
void bmInitMapDataTransSet( u32 map_image_ID, s32 start_x, s32 start_y,
			    MapVram* map_vram_ptr);
void bmClear(void);
void bmInitBackgroundInstance( bmBackgroundInstance* bg_ins_ptr ,
			Background* bg_ptr, u8 bg_number );
void bmSetBackground(nodeEvalStruct* eval_ptr);
void bmEval( void );
void bmSetBGMode( u8 mode );
//----------------------------------------------------------------------

#endif	//  __BGMANAGE_H__
//
//
//

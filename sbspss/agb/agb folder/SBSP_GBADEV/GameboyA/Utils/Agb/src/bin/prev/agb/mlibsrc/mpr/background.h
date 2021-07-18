//======================================================
//    background.h                                      
//    Background processing functions
//                                                     
//    Copyright (C) 1999, NINTENDO Co., Ltd.             
//======================================================

#ifndef	__BACKGROUND_H__
#define	__BACKGROUND_H__

#include <agb.h>

//----------------------------------------------------------------------
typedef struct
{
    u32 vram_address;
    s32 x;
    s32 y;
    u8  block_bit_x;
    u8  block_bit_y;
    u8  text_flag;
    u8  dummy;
} MapVram;

typedef struct
{
    u32 NodeID;
    s32 x;		//  lower 8 bits is decimal
    s32 y;		//  lower 8 bits is decimal
    s32 old_x;
    s32 old_y;
//    s16 speed_x;	//  This multiplied by node's speed is
//    s16 speed_y;	//  the actual speed

    s16 move_x;
    s16 move_y;
    s16 scale_x;
    s16 scale_y;
    u8  rotation;
    u8  priority;
    u8  mosaic;
    u8  mode;
    u32 ch_vram_ptr;
    MapVram* map_vram_ptr;

    u16 max_time;
    u16 max_state;
    u16 time;
    u16 state;
    u16 old_time;
    u16 old_state;

    u16 default_bgcnt;
} Background;
//----------------------------------------------------------------------
Background* bgCreateBackground( u32 NodeID, u8 bgNumber,
				                s32 x, s32 y, u8 Priority,
				                u8 bg_map_vram_number, u8 bg_ch_vram_number,
				                u16 default_bgcnt );
void bgSetScale(Background* bg_ptr,s16 scale_x,s16 scale_y);
void bgMultiScale(Background* bg_ptr,s16 scale_x,s16 scale_y);
void bgSetRotation(Background* bg_ptr,u8 rotation);
void bgMultiRotation(Background* bg_ptr,u8 rotation);
void bgChangeMode(Background* bg_ptr,u8 objmode);
void bgSetMosaic(Background* bg_ptr);
void bgClearMosaic(Background* bg_ptr);
void bgChangePriority(Background* bg_ptr, u8 priority);
void bgEvaluate(Background* bg_ptr);
//----------------------------------------------------------------------

#endif	//  __BACKGROUND_H__
//
//
//

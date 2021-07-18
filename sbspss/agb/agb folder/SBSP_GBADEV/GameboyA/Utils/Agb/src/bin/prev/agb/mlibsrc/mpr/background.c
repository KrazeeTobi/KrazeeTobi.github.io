//======================================================
//    background.c                                      
//    Background processing functions
//                                                     
//    Copyright (C) 1999, NINTENDO Co., Ltd.             
//======================================================

#include <agb.h>
#include <isagbprint.h>
#include "background.h"
#include "bgmanage.h"
#include "node.h"
#include "node_background.h"
#include "node_image.h"

//----------------------------------------------------------------------
Background	bg[4];
MapVram		map_vram[4];
u8		bg_mode;
//----------------------------------------------------------------------
void bg_create_set_ch_DMA(u32 ImageID , u32 ch_vram_ptr);
//----------------------------------------------------------------------
void bgSetMode( u8 mode )
{
    bg_mode = mode;
}
//----------------------------------------------------------------------
Background* bgCreateBackground( u32 NodeID, u8 bgNumber,
				s32 x, s32 y, u8 Priority,
				u8 bg_map_vram_number, u8 bg_ch_vram_number,
				u16 default_bgcnt )
{
    Background* bg_ptr;
    MapVram* map_vram_ptr;
    nodeBackground* ndbg_ptr;
    register u16 bgcnt;

    bg_ptr = &bg[bgNumber];

    ndbg_ptr = (nodeBackground*)nodeGetAddressByID( NodeID );

    bgcnt = default_bgcnt;
    bgcnt |= (u16)(((u16)bg_map_vram_number<<8)|((u16)bg_ch_vram_number<<2));

    *((vu16*)REG_BG0CNT + bgNumber) = bgcnt;

    bg_ptr->default_bgcnt = bgcnt;
    bg_ptr->NodeID = NodeID;
	//  For initial location, try to use (0,0) as a standard
    bg_ptr->old_x = ((ndbg_ptr->start_x << 8) + x) & 0x7ff;
    bg_ptr->old_y = ((ndbg_ptr->start_y << 8) + y) & 0x7ff;
    bg_ptr->x = bg_ptr->old_x;
    bg_ptr->y = bg_ptr->old_y;
    bg_ptr->scale_x = 0x100;
    bg_ptr->scale_y = 0x100;
    bg_ptr->rotation = 0;
    bg_ptr->priority = Priority;
    bg_ptr->mosaic = 0;
    bg_ptr->mode = 0;

    bg_ptr->max_time = ndbg_ptr->max_time;
    bg_ptr->max_state = ndbg_ptr->max_state;
    bg_ptr->time = 0;
    bg_ptr->state = 0;
    bg_ptr->old_time = 0;
    bg_ptr->old_state = 0;

    bg_ptr->ch_vram_ptr = BG_VRAM + 0x4000 * bg_ch_vram_number;

    bg_create_set_ch_DMA(ndbg_ptr->map_char_ID, bg_ptr->ch_vram_ptr);

    map_vram_ptr = &map_vram[bgNumber];

    bg_ptr->map_vram_ptr = map_vram_ptr;

    map_vram_ptr->x = bg_ptr->x;
    map_vram_ptr->y = bg_ptr->y;
    map_vram_ptr->block_bit_x = ndbg_ptr->block_bit_x;
    map_vram_ptr->block_bit_y = ndbg_ptr->block_bit_y;
    map_vram_ptr->vram_address = BG_VRAM + bg_map_vram_number*(0x4000/8);
    map_vram_ptr->text_flag = ((bg_mode*bgNumber)<2) ? 1 : 0;

    bmInitMapDataTransSet( ndbg_ptr->map_image_ID,
			   ndbg_ptr->start_x, ndbg_ptr->start_y,
			   map_vram_ptr );

    return bg_ptr;
}
//----------------------------------------------------------------------
void bg_create_set_ch_DMA(u32 ImageID , u32 ch_vram_ptr)
{
    nodeImage* ndim_ptr;
    u8* image_ptr;

    ndim_ptr = (nodeImage*)nodeGetAddressByID( ImageID );
    dtSetDMA( ch_vram_ptr,
	      ndimGetAddress( (u32)ndim_ptr , 0 , 0 , 0 ),
	      (u16)ndimGetDataSize( (u32)ndim_ptr )*ndim_ptr->data_num,
	      3, 16 );
}
//----------------------------------------------------------------------
void bgSetScale(Background* bg_ptr,s16 scale_x,s16 scale_y)
{
    if( NULL != bg_ptr )
    {
	if( 0 != scale_x ) bg_ptr->scale_x = scale_x;
	if( 0 != scale_y ) bg_ptr->scale_y = scale_y;
    }
}
//----------------------------------------------------------------------
void bgMultiScale(Background* bg_ptr,s16 scale_x,s16 scale_y)
{
    s32 calc_tmp;
    if( NULL != bg_ptr )
    {
	if( (0 != scale_x) && (0x0100 != scale_x) )
	{
	    calc_tmp = (s32)bg_ptr->scale_x;
	    if( calc_tmp == 0x00000100 )
	    {
		bg_ptr->scale_x = scale_x;
	    }
	    else
	    {
		calc_tmp *= (s32)scale_x;
		calc_tmp >>= 8;
		bg_ptr->scale_x = (s16)calc_tmp;
	    }
	}
	if( (0x0 != scale_y) && (0x0100 != scale_y) )
	{
	    calc_tmp = (s32)bg_ptr->scale_y;
	    if( calc_tmp == 0x00000100 )
	    {
		bg_ptr->scale_y = scale_y;
	    }
	    else
	    {
		calc_tmp *= (s32)scale_y;
		calc_tmp >>= 8;
		bg_ptr->scale_y = (s16)calc_tmp;
	    }
	}
    }
}
//----------------------------------------------------------------------
void bgSetRotation(Background* bg_ptr,u8 rotation)
{
    if( NULL != bg_ptr )
    {
	bg_ptr->rotation = rotation;
    }
}
//----------------------------------------------------------------------
void bgMultiRotation(Background* bg_ptr,u8 rotation)
{
    u16 calc_tmp;
    if( NULL != bg_ptr )
    {
	calc_tmp = (u16)bg_ptr->rotation;
	calc_tmp += rotation;
	calc_tmp &= 0xff;
	bg_ptr->rotation = (u8)calc_tmp;
    }
}
//----------------------------------------------------------------------
void bgChangeMode(Background* bg_ptr,u8 mode)
{
    if( NULL != bg_ptr )
    {
	bg_ptr->mode = mode & 0x03;
    }
}
//----------------------------------------------------------------------
void bgSetMosaic(Background* bg_ptr)
{
    if( NULL != bg_ptr )
    {
	bg_ptr->mosaic = 1;
    }
}
//----------------------------------------------------------------------
void bgClearMosaic(Background* bg_ptr)
{
    if( NULL != bg_ptr )
    {
	bg_ptr->mosaic = 0;
    }
}
//----------------------------------------------------------------------
void bgChangePriority(Background* bg_ptr , u8 priority)
{
    if( NULL != bg_ptr )
    {
	bg_ptr->priority = priority & 0x03;
    }
}
//----------------------------------------------------------------------
void bgEvaluate(Background* bg_ptr)
{
    bmBackgroundInstance bmbi;
    nodeEvalStruct evstr;
    nodeBackground* ndbg_ptr;
    nodeImage* ndim_ptr;
    MapVram* map_vram_ptr;
    register s32 tmp;
    u8 bg_number;
    u32 move_x,move_y;
    if( NULL != bg_ptr )
    {
	bg_number = (u8)(u32)(((u32)bg_ptr-(u32)bg)/sizeof(Background));
	bmInitBackgroundInstance( &bmbi , bg_ptr , bg_number );
	nodeEvalStructInit( &evstr );
	evstr.time = bg_ptr->time;
	evstr.state = bg_ptr->state;
	evstr.old_time = bg_ptr->old_time;
	evstr.old_state = bg_ptr->old_state;
	evstr.instance_ptr = &bmbi;
	evstr.sr.sr.scale_x = bg_ptr->scale_x;
	evstr.sr.sr.scale_y = bg_ptr->scale_y;
	evstr.sr.sr.angle = bg_ptr->rotation;

	nodeCallEvalFunction( bg_ptr->NodeID , &evstr );
	bmSetBackground( &evstr );

	bg_ptr->old_time = evstr.time;
	bg_ptr->old_state = evstr.state;
	ndbg_ptr = (nodeBackground*)nodeGetAddressByID( bg_ptr->NodeID );
	ndim_ptr = (nodeImage*)nodeGetAddressByID( ndbg_ptr->map_image_ID );
	    //  Depending whether scroll stops at the both edges of screen
	    //  order may need to be switched.
	move_x = (s32)evstr.coord.coord.move_x + (s32)bg_ptr->move_x;
	move_y = (s32)evstr.coord.coord.move_y + (s32)bg_ptr->move_y;
	map_vram_ptr = bg_ptr->map_vram_ptr;
	if( !(evstr.flag & NODE_EVAL_USE_REF) )
	{

	    bg_ptr->x += move_x;
	    tmp = ndim_ptr->width << 11;
	    _wrapLimit( bg_ptr->x , 0 , tmp );
	    bg_ptr->y += move_y;
	    tmp = ndim_ptr->height << 11;
	    _wrapLimit( bg_ptr->y , 0 , tmp );

	    map_vram_ptr->x += move_x;
	    tmp = _BitValue(map_vram_ptr->block_bit_x) << 11;
	    _wrapLimit( map_vram_ptr->x , 0 , tmp );
	    map_vram_ptr->y += move_y;
	    tmp = _BitValue(map_vram_ptr->block_bit_y) << 11;
	    _wrapLimit( map_vram_ptr->y , 0 , tmp );

#if 0
	    _wrapChange(bg_ptr->x , move_x ,
			0,(ndim_ptr->width<<11) );
	    _wrapChange(bg_ptr->y , move_y ,
			0,(ndim_ptr->height<<11) );
	    _wrapChange(map_vram_ptr->x,move_x,
			0,(((s32)_BitValue(map_vram_ptr->block_bit_x))<<11) );
	    _wrapChange(map_vram_ptr->y,move_y,
			0,(((s32)_BitValue(map_vram_ptr->block_bit_y))<<11) );
#endif
	}
	bg_ptr->old_x = bg_ptr->x;
	bg_ptr->old_y = bg_ptr->y;
    }
}
//----------------------------------------------------------------------

//
//
//

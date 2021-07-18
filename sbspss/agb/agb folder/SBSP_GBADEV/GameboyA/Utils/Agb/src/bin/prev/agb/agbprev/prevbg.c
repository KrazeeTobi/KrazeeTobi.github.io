//======================================================
//    prevbg.c                          
//    BG Process Section of Previewer
//                                                     
//    Copyright (C) 1999, NINTENDO Co., Ltd.             
//======================================================

#include <agb.h>
#include <isagbprint.h>
#include <node.h>
#include <node_image.h>
#include <background.h>
#include <node_background.h>
#include <datatrans.h>
#include <controller.h>
#include "prevbg.h"
#include <util.h>

//----------------------------------------------------------------------
#define	PBG_CHAR_BLOCK_MEM_SIZE		(0x4000)
#define	PBG_SCREEN_BLOCK_MEM_SIZE	(PBG_CHAR_BLOCK_MEM_SIZE / 8)
#define	PBG_CHAR_BLOCK_SHIFT		(14)
#define	PBG_SCREEN_BLOCK_SHIFT		(PBG_CHAR_BLOCK_SHIFT - 3)
#define	PBG_CHAR_NOUSE_ID		(0xffffffff)
#define	PBG_MODE_TEXT			(2)
#define	PBG_MODE_SR			(1)
//----------------------------------------------------------------------
u32 pbg_mem_use_flag;
u32 pbg_char_block_ID[4];
Background* pbg_bg_ptr[4];
s8 pbg_control_flag;
//----------------------------------------------------------------------
u8 pbg_get_character_mem_block( u32 node_image_ID );
u8 pbg_get_screen_mem_block( u8 scr_w_bit, u8 scr_h_bit, u8 mode );
void pbg_set_character_dt( u32 node_image_ID, u8 character_block );
//----------------------------------------------------------------------
void pbgInit( void )
{
    pbg_mem_use_flag = 0;
    pbg_char_block_ID[0] = PBG_CHAR_NOUSE_ID;
    pbg_char_block_ID[1] = PBG_CHAR_NOUSE_ID;
    pbg_char_block_ID[2] = PBG_CHAR_NOUSE_ID;
    pbg_char_block_ID[3] = PBG_CHAR_NOUSE_ID;
    pbg_bg_ptr[0] = NULL;
    pbg_bg_ptr[1] = NULL;
    pbg_bg_ptr[2] = NULL;
    pbg_bg_ptr[3] = NULL;
    pbg_control_flag = -1;
}
//----------------------------------------------------------------------
void pbg_set_character_dt( u32 node_image_ID, u8 character_block )
{
    register u32 dest_address;
    register u32 src_address;
    register u16 size;
    register nodeImage* ndim_ptr;

    ndim_ptr = (nodeImage*)nodeGetAddressByID( node_image_ID );
    dest_address = VRAM + ((u32)character_block << PBG_CHAR_BLOCK_SHIFT);
    src_address = ndimGetAddressByIndex( (u32)ndim_ptr, 0 );
    size = (u16)ndimGetDataSize( (u32)ndim_ptr ) * ndim_ptr->data_num;
    dtSetDMA(dest_address, src_address, size, 3, 16 );
}
//----------------------------------------------------------------------
u8 pbg_get_character_mem_block( u32 node_image_ID )
{
    nodeImage* ndim_ptr;
    register u32 char_block_ID;
    register u32 use_block_size;
    register u32 use_block_flag;
    register u8 use_block;
    register int i;

	//  If there is a character aready, return its number
    for( i=0 ; i<4 ; ++i )
    {
	char_block_ID = pbg_char_block_ID[i];
	if( char_block_ID == node_image_ID ) return i;
    }

    ndim_ptr = (nodeImage*)nodeGetAddressByID(node_image_ID);

	//  Find the number of blocks that are used based on the number of screen blocks
    use_block_size = ndimGetDataSize( (u32)ndim_ptr );
    use_block_size *= ndim_ptr->data_num;
    use_block = (u8)(u32)(((use_block_size-1)>>PBG_SCREEN_BLOCK_SHIFT)+1);

    use_block_flag = (u32)_BitAnd( use_block );

    i=0;
    while( !(use_block_flag & 0xff000000) )
    {
	use_block_flag <<= 8;
	++i;
    }
    for( ; i>=0 ; --i )
    {
	if( !(use_block_flag & pbg_mem_use_flag) ) break;
	use_block_flag >>= 8;
    }
    if( -1 == i ) return 0xff;
    pbg_mem_use_flag |= use_block_flag;

    return i;
}
//----------------------------------------------------------------------
u8 pbg_get_screen_mem_block( u8 screen_width_bit, u8 screen_height_bit,
			     u8 mode )
{
    register u32 use_block_size;
    register u32 use_block_flag;
    register u8 use_block;
    register int i;

	//  Find the number of blocks that are used based on the number of screen blocks.
    use_block_size = (u32)(((u32)mode)<<(screen_width_bit+screen_height_bit));
    use_block = (u8)(u32)(((use_block_size-1)>>PBG_SCREEN_BLOCK_SHIFT)+1);
    use_block_flag = (u32)_BitAnd(use_block);

    i = 0;
    while( !(use_block_flag & 0x80000000) )
    {
	use_block_flag <<= 1;
	++i;
    }

    for( ; i>=0 ; --i )
    {
	if( !(use_block_flag & pbg_mem_use_flag) ) break;
	use_block_flag >>= 1;
    }
    if( -1 == i ) return 0xff;
    pbg_mem_use_flag |= use_block_flag;

    return i;
}
//----------------------------------------------------------------------
void pbgCreateBackground( u32 NodeID, u8 bgNumber, u8 Priority, u16 bgcnt )
{
    register nodeBackground *ndbg_ptr;
    register nodeImage *ndim_ptr;
    register u8 character_block,screen_block;
    register u8 mode;

    ndbg_ptr = (nodeBackground*)nodeGetAddressByID( NodeID );
    ndim_ptr = (nodeImage*)nodeGetAddressByID(ndbg_ptr->map_image_ID);

    mode = (ndim_ptr->bit_count == 16) ? PBG_MODE_TEXT : PBG_MODE_SR;

    character_block = pbg_get_character_mem_block(ndbg_ptr->map_char_ID);

    screen_block = pbg_get_screen_mem_block(
			ndbg_ptr->block_bit_x, ndbg_ptr->block_bit_y, mode );

    if( (0xff == character_block) || (0xff == screen_block) ) return;

    pbg_bg_ptr[bgNumber] =
		bgCreateBackground( NodeID, bgNumber,
				    0, 0, Priority,
				    screen_block, character_block,
				    bgcnt );

}
//----------------------------------------------------------------------
void pbgControl(void)
{
    register u16 button , trigger;
    s16 move_x,move_y;
    s16 scale_x,scale_y;
    u16 rotation;
    int i;
    Background* bg_ptr;
    button  = Cont;
    trigger = Trg;

    move_x = 0;
    move_y = 0;
    scale_x = 0;
    scale_y = 0;
    rotation = 0;

    if( button & B_BUTTON )
    {
	if( button & R_KEY )
	{
	    scale_x -= 0x8;
	}
	if( button & L_KEY )
	{
	    scale_x += 0x8;
	}
	if( button & D_KEY )
	{
	    scale_y += 0x8;
	}
	if( button & U_KEY )
	{
	    scale_y -= 0x8;
	}
	if( button & R_BUTTON )
	{
	    rotation += 254;
	}
	if( button & L_BUTTON )
	{
	    rotation += 2;
	}
	if( pbg_control_flag == -1 )
	{
	    for( i=0 ; i<4 ; ++i )
	    {
		bg_ptr = pbg_bg_ptr[i];
		if( NULL == bg_ptr ) continue;

		bg_ptr->scale_x += scale_x;
		if( bg_ptr->scale_x > 0x200 ) bg_ptr->scale_x = 0x200;
		if( bg_ptr->scale_x < 0x80 ) bg_ptr->scale_x = 0x80;
		bg_ptr->scale_y += scale_y;
		if( bg_ptr->scale_y > 0x200 ) bg_ptr->scale_y = 0x200;
		if( bg_ptr->scale_y < 0x80 ) bg_ptr->scale_y = 0x80;
		bg_ptr->rotation = (((u16)bg_ptr->rotation + rotation )& 0xff);
	    }
	}
	else
	{
	    bg_ptr = pbg_bg_ptr[pbg_control_flag];

	    bg_ptr->scale_x += scale_x;
	    if( bg_ptr->scale_x > 0x200 ) bg_ptr->scale_x = 0x200;
	    if( bg_ptr->scale_x < 0x80 ) bg_ptr->scale_x = 0x80;
	    bg_ptr->scale_y += scale_y;
	    if( bg_ptr->scale_y > 0x200 ) bg_ptr->scale_y = 0x200;
	    if( bg_ptr->scale_y < 0x80 ) bg_ptr->scale_y = 0x80;
	    bg_ptr->rotation = (((u16)bg_ptr->rotation + rotation )& 0xff);
	}
    }
    else
    {
	if( button & R_KEY )
	{
	    move_x += 0x200;
	}
	if( button & L_KEY )
	{
	    move_x -= 0x200;
	}
	if( button & D_KEY )
	{
	    move_y += 0x200;
	}
	if( button & U_KEY )
	{
	    move_y -= 0x200;
	}
	if( trigger & R_BUTTON )
	{
	    for( i=pbg_control_flag+1 ; i<4 ; ++i )
	    {
		if( NULL != pbg_bg_ptr[i] ) break;
	    }
	    pbg_control_flag = (i==4) ? -1 : i;
	}
	if( trigger & L_BUTTON )
	{
	    if( pbg_control_flag == -1 ) pbg_control_flag = 4;
	    for( i=pbg_control_flag-1 ; i>=0 ; --i )
	    {
		if( NULL != pbg_bg_ptr[i] ) break;
	    }
	    pbg_control_flag = i;
	}
	if( pbg_control_flag == -1 )
	{
	    for( i=0 ; i<4 ; ++i )
	    {
		bg_ptr = pbg_bg_ptr[i];
		if( NULL == bg_ptr ) continue;

		bg_ptr->move_x = move_x;
		bg_ptr->move_y = move_y;
	    }
	}
	else
	{
	    pbg_bg_ptr[pbg_control_flag]->move_x = move_x;
	    pbg_bg_ptr[pbg_control_flag]->move_y = move_y;
	}
    }
    if( button & START_BUTTON )
    {
	if( pbg_control_flag == -1 )
	{
	    for( i=0 ; i<4 ; ++i )
	    {
		bg_ptr = pbg_bg_ptr[i];
		if( NULL == bg_ptr ) continue;

		bg_ptr->scale_x = 0x100;
		bg_ptr->scale_y = 0x100;
		bg_ptr->rotation = 0;
	    }
	}
	else
	{
	    pbg_bg_ptr[pbg_control_flag]->scale_x = 0x100;
	    pbg_bg_ptr[pbg_control_flag]->scale_y = 0x100;
	    pbg_bg_ptr[pbg_control_flag]->rotation = 0;
	}
    }
}
//----------------------------------------------------------------------
void pbgLoopInit(void)
{
    int i;
    for( i=0 ; i<4 ; ++i )
    {
	if( NULL == pbg_bg_ptr[i] ) continue;

	pbg_bg_ptr[i]->move_x = 0;
	pbg_bg_ptr[i]->move_y = 0;

    }
}
//----------------------------------------------------------------------
void pbgEvaluate(void)
{
    int i;
    for( i=0 ; i<4 ; ++i )
    {
	if( NULL != pbg_bg_ptr[i] )
	{
	    bgEvaluate( pbg_bg_ptr[i] );
	}
    }
    bmEval();
}
//----------------------------------------------------------------------

//
//
//

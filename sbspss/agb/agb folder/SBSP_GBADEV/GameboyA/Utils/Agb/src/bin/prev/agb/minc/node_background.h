//======================================================
//    node_background.h                          
//    Background Node evaluation functions
//                                                     
//    Copyright (C) 1999, NINTENDO Co., Ltd.             
//======================================================

#ifndef	__NODE_BACKGROUND_H__
#define	__NODE_BACKGROUND_H__

#include <agb.h>
#include "node.h"

//----------------------------------------------------------------------
typedef struct
{
    nodeHead head;
    u32 map_image_ID;
    u32 map_char_ID;
    s16 start_x;		//  Initial location of map
    s16 start_y;
//    s16 speed_x;		//  Scroll speed, lower order 8 bits is decimal
//    s16 speed_y;
    u8  h_scroll_flag;	//  With horizontal scroll, if forced scroll direction
			            //  and scroll, stop or loop
    u8  v_scroll_flag;	//  With vertical scroll, if forced scroll direction
			            //  and scroll, stop or loop
    u8  block_bit_x;	//  Horizontal block bit on screen mode
    u8  block_bit_y;	//  Vertical block bit on screen mode
    u16 max_time;
    u16 max_state;
    u32 num_of_children;
#ifdef	__TEST_VERSION__
    const u32* child_node_ID;
#else
    u32 child_node_ID;
#endif	//  __TEST_VERSION__
} nodeBackground;
//----------------------------------------------------------------------
void ndbgEval( u32 node_address, nodeEvalStruct* evstr_ptr );
//----------------------------------------------------------------------

#endif	//  __NODE_BACKGROUND_H__
//
//
//

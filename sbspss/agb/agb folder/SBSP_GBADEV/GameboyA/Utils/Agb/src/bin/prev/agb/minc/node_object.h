//======================================================
//    node_object.h                          
//    Object Node
//                                                     
//    Copyright (C) 1999, NINTENDO Co., Ltd.             
//======================================================

#ifndef	__NODE_OBJECT_H__
#define	__NODE_OBJECT_H__

#include <agb.h>
#include "node.h"

#define	NDOB_COLOR_MODE_16	(0)
#define	NDOB_COLOR_MODE_256	(1)

typedef struct
{
    nodeHead head;
    u16 default_OAM[3];
    u8  width;
    u8  height;
    u8  palette_number;
    u8  flip;		//  Add mode to 0x0c bit
    s16 offset_x;	//  Fixed-point
    s16 offset_y;	//  Fixed-point
    u16 max_time;
    u16 max_state;
    u32 default_image_ID;
    u32 animation_ID;
    u16 num_of_children;
#ifdef	__TEST_VERSION__
    const u32* child_node_ID;
#else
    u32 child_node_ID;
#endif	//  __TEST_VERSION__
} nodeObject;

//----------------------------------------------------------------------
void ndobEval( u32 node_address ,nodeEvalStruct* evstr_ptr );
u32 ndobGetUseCharacterNum( u32 node_address );
u8  ndobGetColorMode( u32 node_address );
//----------------------------------------------------------------------

#endif	//  __NODE_OBJECT_H__

//======================================================
//    node_image.h                          
//    Image Node
//                                                     
//    Copyright (C) 1999, NINTENDO Co.,Ltd.             
//======================================================

#ifndef	__NODE_IMAGE_H__
#define	__NODE_IMAGE_H__

#include <agb.h>
#include "node.h"

typedef struct
{
    nodeHead head;
    u16 width;
    u16 height;
    u16 bit_count;
    u16 data_num;
#ifdef	__TEST_VERSION__
    const u8* data;
#else
    u8  data;
#endif	//  __TEST_VERSION__
} nodeImage;

//----------------------------------------------------------------------
void ndimEval(u32 node_address , nodeEvalStruct* evstr_ptr);
u32  ndimGetAddress( u32 node_address, u32 index , u32 x , u32 y );
u32  ndimGetAddressByIndex( u32 node_address, u32 index );
u32  ndimGetPitch( u32 node_address );
u32  ndimGetDataSize( u32 node_address );
//----------------------------------------------------------------------

#endif	//  __NODE_IMAGE_H__

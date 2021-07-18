//======================================================
//    node_image.c                          
//    Image Node
//                                                     
//    Copyright (C) 1999,NINTENDO Co.,Ltd.             
//======================================================

#include <agb.h>
#include "node.h"
#include "node_image.h"

//----------------------------------------------------------------------
void ndimEval(u32 node_address , nodeEvalStruct* evstr_ptr )
{
    (void)evstr_ptr;
    (void)node_address;
}
//----------------------------------------------------------------------
u32  ndimGetAddress( u32 node_address, u32 index , u32 x , u32 y )
{
    nodeImage* ndim_ptr;
    u32 ret_address;
    ndim_ptr = (nodeImage*)node_address;
#ifdef	__TEST_VERSION__
    ret_address = (u32)(ndim_ptr->data);
#else
    ret_address = (u32)(&ndim_ptr->data);
#endif	//  __TEST_VERSION__
    ret_address += ndimGetDataSize(node_address) * index;
    ret_address += ((y*ndim_ptr->width+x)*(ndim_ptr->bit_count))>>3;
    return ret_address;
}
//----------------------------------------------------------------------
u32  ndimGetAddressByIndex( u32 node_address, u32 index )
{
    nodeImage* ndim_ptr;
    u32 ret_address;
    ndim_ptr = (nodeImage*)node_address;
#ifdef	__TEST_VERSION__
    ret_address = (u32)(ndim_ptr->data);
#else
    ret_address = (u32)(&ndim_ptr->data);
#endif	//  __TEST_VERSION__
    ret_address += ndimGetDataSize(node_address) * index;
    return ret_address;
}
//----------------------------------------------------------------------
u32  ndimGetPitch( u32 node_address )
{
    nodeImage* ndim_ptr;
    ndim_ptr = (nodeImage*)node_address;
    return (ndim_ptr->width * ndim_ptr->bit_count)>>3;
}
//----------------------------------------------------------------------
u32  ndimGetDataSize( u32 node_address )
{
    u32 ret_value;
    nodeImage* ndim_ptr = (nodeImage*)node_address;
    ret_value  = (u32)ndim_ptr->width;
    ret_value *= (u32)ndim_ptr->height;
    ret_value *= (u32)ndim_ptr->bit_count;
    ret_value /= 8;
    return ret_value;
}
//----------------------------------------------------------------------


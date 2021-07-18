//======================================================
//    node_object.c                          
//    Object Node
//                                                     
//    Copyright (C) 1999,NINTENDO Co.,Ltd.             
//======================================================

#include <agb.h>
#include "node.h"
#include "node_object.h"
#include "objmanage.h"

//----------------------------------------------------------------------
void ndobEval( u32 node_address ,nodeEvalStruct* evstr_ptr )
{
    nodeObject* ndob_ptr;
    omObjectInstance* omoi_ptr;
    int i;
    u32* child_id_ptr;

    ndob_ptr = (nodeObject*)node_address;
    omoi_ptr = (omObjectInstance*)(evstr_ptr->instance_ptr);

	//  Assignment of default parameters

    omoi_ptr->width   = ndob_ptr->width;
    omoi_ptr->height  = ndob_ptr->height;
    omoi_ptr->palette = ndob_ptr->palette_number;
    omoi_ptr->flip    = ndob_ptr->flip;

	//  Evaluation of animation

    nodeCallEvalFunction( ndob_ptr->animation_ID , evstr_ptr );

	//  Call evaluation function of child node

#ifdef	__TEST_VERSION__
    child_id_ptr = (u32*)ndob_ptr->child_node_ID;
#else
    child_id_ptr = &ndob_ptr->child_node_ID;
#endif	//  __TEST_VERSION__
    for( i=0 ; i<ndob_ptr->num_of_children ; ++i )
    {
	nodeCallEvalFunction( *child_id_ptr , evstr_ptr );
	++child_id_ptr;
    }
}
//----------------------------------------------------------------------
u32 ndobGetUseCharacterNum( u32 node_address )
{
    nodeObject* ndobj_ptr;
    u32 use_character;
//    int i;
//    u32* child_ptr;

    ndobj_ptr = (nodeObject*)node_address;
    use_character = (u32)(ndobj_ptr->width >> 3);
    use_character *= (u32)(ndobj_ptr->height >> 3);
    if( ndobGetColorMode(node_address) == NDOB_COLOR_MODE_256 )
	use_character <<= 1;

	//  If revised evaluation comes in

//#ifdef	__TEST_VERSION__
//    child_ptr = ndobj_ptr->child_node_ID;
//#else
//    child_ptr = &ndobj_ptr->child_node_ID;
//#endif	//  __TEST_VERSION__
//    for( i=0 ; i<ndobj_ptr->num_of_children ; ++i )
//    {
//	use_character += ndobGetUseCharacterNum(
//				nodeGetAddressByID(*child_ptr++));
//    }

    return use_character;
}
//----------------------------------------------------------------------
u8 ndobGetColorMode( u32 node_address )
{
    nodeObject* ndobj_ptr;

    ndobj_ptr = (nodeObject*)node_address;
    return (ndobj_ptr->default_OAM[0] & 0x2000) ?
		NDOB_COLOR_MODE_256 : NDOB_COLOR_MODE_16 ;
}
//----------------------------------------------------------------------


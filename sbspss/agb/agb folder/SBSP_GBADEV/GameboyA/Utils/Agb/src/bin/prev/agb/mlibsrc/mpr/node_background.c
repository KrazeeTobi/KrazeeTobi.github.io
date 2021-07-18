//======================================================
//    node_background.c                          
//    Background Node evaluation functions
//                                                     
//    Copyright (C) 1999, NINTENDO Co., Ltd.             
//======================================================

#include <agb.h>
#include "node.h"
#include "node_background.h"
#include "background.h"
#include "bgmanage.h"

//----------------------------------------------------------------------
void ndbgEval( u32 node_address, nodeEvalStruct* evstr_ptr )
{
    register nodeBackground *ndbg_ptr;
    register u32* child_id_ptr;
    register int i;

    ndbg_ptr = (nodeBackground*)node_address;

	//  Call evaluation function of Child Node

#ifdef	__TEST_VERSION__
    child_id_ptr = (u32*)ndbg_ptr->child_node_ID;
#else
    child_id_ptr = &ndbg_ptr->child_node_ID;
#endif	//  __TEST_VERSION__
    for( i=0 ; i<ndbg_ptr->num_of_children ; ++i )
    {
	nodeCallEvalFunction( *child_id_ptr, evstr_ptr );
	++child_id_ptr;
    }
}
//----------------------------------------------------------------------

//
//
//

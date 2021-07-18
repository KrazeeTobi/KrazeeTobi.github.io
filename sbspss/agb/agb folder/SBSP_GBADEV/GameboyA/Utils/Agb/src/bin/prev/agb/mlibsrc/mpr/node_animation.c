//======================================================
//    node_animation.c                          
//    Animation evaluation functions
//                                                     
//    Copyright (C) 1999, NINTENDO Co., Ltd.             
//======================================================

#include <agb.h>
#include <util.h>
#include "node.h"
#include "node_animation.h"
#include "objmanage.h"
#include "node_object.h"
#include "datatrans.h"

//----------------------------------------------------------------------
void ndanEval( u32 node_address , nodeEvalStruct* evstr_ptr )
{
    nodeAnimation* ndan_ptr;
    int i;
    u32* child_id_ptr;

    ndan_ptr = (nodeAnimation*)node_address;

	//  Call evaluation function of Child Node

#ifdef	__TEST_VERSION__
    child_id_ptr = (u32*)ndan_ptr->child_ID;
#else
    child_id_ptr = &ndan_ptr->child_ID;
#endif	//  __TEST_VERSION__
    for( i=0 ; i<ndan_ptr->num_of_children ; ++i )
    {
	nodeCallEvalFunction( *child_id_ptr , evstr_ptr );
	++child_id_ptr;
    }
}
//----------------------------------------------------------------------
void ndswEval( u32 node_address , nodeEvalStruct* evstr_ptr )
{
    nodeSwitch* ndsw_ptr;
    nodeSwitchState* swst_ptr;
    int i;

    ndsw_ptr = (nodeSwitch*)node_address;
#ifdef	__TEST_VERSION__
    swst_ptr = (nodeSwitchState*)ndsw_ptr->state_start;
#else
    swst_ptr = &ndsw_ptr->state_start;
#endif	//  __TEST_VERSION__
    for( i=0 ; i<ndsw_ptr->num_of_states ; ++i )
    {
	if( evstr_ptr->state == swst_ptr->state ) break;
	++swst_ptr;
    }
    if( i == ndsw_ptr->num_of_states ) return;
    nodeCallEvalFunction( swst_ptr->child_ID , evstr_ptr );
}
//----------------------------------------------------------------------
void ndmsEval( u32 node_address , nodeEvalStruct* evstr_ptr )
{
    nodeMultiSwitch* ndms_ptr;
    nodeMultiSwitchState* msst_ptr;
    u32* child_ID_ptr;
    int i;

    ndms_ptr = (nodeMultiSwitch*)node_address;
#ifdef	__TEST_VERSION__
    child_ID_ptr = (u32*)ndms_ptr->child_ID;
    msst_ptr = (nodeMultiSwitchState*)ndms_ptr->state_start;
#else
    msst_ptr = &ndms_ptr->state_start;
    child_ID_ptr = ((u32)msst_ptr) +
		ndms_ptr->num_of_states * sizeof(nodeMultiSwitchState);
#endif	//  __TEST_VERSION__
    for( i=0 ; i<ndms_ptr->num_of_states ; ++i )
    {
	if( evstr_ptr->state == msst_ptr->state ) break;
	++msst_ptr;
    }
    if( i == ndms_ptr->num_of_states ) return;
    for( i=0 ; i<msst_ptr->num_of_children ; ++i )
    {
	nodeCallEvalFunction( child_ID_ptr[msst_ptr->start_index+i],
				evstr_ptr );
    }
}
//----------------------------------------------------------------------
void ndfbEval( u32 nodeaddress , nodeEvalStruct *evstr_ptr )
{
    nodeFlipBook* ndfb_ptr;
    nodeFlipBookKey* ndfbkey_ptr;
    omObjectInstance* omoi_ptr;
    nodeObject* ndobj_ptr;
    int i;
    u32 node_data_address;
    u16 time;
    u8  palette_bit;

    if( (void*)0 == evstr_ptr ) return;

    ndfb_ptr = (nodeFlipBook*)nodeaddress;
#ifdef	__TEST_VERSION__
    ndfbkey_ptr = (nodeFlipBookKey*)ndfb_ptr->key_start;
#else
    ndfbkey_ptr = &ndfb_ptr->key_start;
#endif	//  __TEST_VERSION__
    time = evstr_ptr->time % ndfb_ptr->max_time;

    for( i=0 ; i<ndfb_ptr->num_of_keys ; ++i )
    {
	if( time <= ndfbkey_ptr->time ) break;
	++ndfbkey_ptr;
    }
    if( i==ndfb_ptr->num_of_keys )
    {
#ifdef	__TEST_VERSION__
	ndfbkey_ptr = (nodeFlipBookKey*)ndfb_ptr->key_start;
#else
	ndfbkey_ptr = &ndfb_ptr->key_start;
#endif	//  __TEST_VERSION__
    }

    omoi_ptr = (omObjectInstance*)(evstr_ptr->instance_ptr);
    if( (time == ndfbkey_ptr->time)
     && ( (evstr_ptr->old_time != evstr_ptr->time)
       || (evstr_ptr->old_state != evstr_ptr->state) ) )
    {
	ndobj_ptr = (nodeObject*)nodeGetAddressByID(omoi_ptr->obj_ptr->NodeID);
	palette_bit = (ndobj_ptr->default_OAM[0] & 0x2000) ? 8:4;
	node_data_address = nodeGetAddressByID(ndfb_ptr->data_node_ID);
	dtSetDMA( OBJ_MODE0_VRAM + 32 * omoi_ptr->objNumber ,
		  ndimGetAddressByIndex(node_data_address,ndfbkey_ptr->frame) ,
		  ndimGetDataSize(node_data_address) ,
		  3 ,
		  16 );
    }

    omoi_ptr->flip ^= ndfbkey_ptr->flip;
}
//----------------------------------------------------------------------
void ndpaEval( u32 nodeaddress , nodeEvalStruct *evstr_ptr )
{
    nodePaletteAnim* ndpa_ptr;
    nodePaletteAnimKey* ndpakey_ptr;
    omObjectInstance* omoi_ptr;
    int i;
    u32 node_data_address;
    u16 time;

    if( (void*)0 == evstr_ptr ) return;

    ndpa_ptr = (nodePaletteAnim*)nodeaddress;
#ifdef	__TEST_VERSION__
    ndpakey_ptr = (nodePaletteAnimKey*)ndpa_ptr->key_start;
#else
    ndpakey_ptr = &ndpa_ptr->key_start;
#endif	//  __TEST_VERSION__
    time = evstr_ptr->time % ndpa_ptr->max_time;

    for( i=0 ; i<ndpa_ptr->num_of_keys ; ++i )
    {
	if( time <= ndpakey_ptr->time ) break;
	++ndpakey_ptr;
    }
    if( i==ndpa_ptr->num_of_keys ) return;

    omoi_ptr = (omObjectInstance*)(evstr_ptr->instance_ptr);
    if( (time == ndpakey_ptr->time)
     && ( (evstr_ptr->old_time != evstr_ptr->time)
       || (evstr_ptr->old_state != evstr_ptr->state) ) )
    {
	node_data_address = nodeGetAddressByID(ndpa_ptr->data_node_ID);
	dtSetDMA( OBJ_MODE0_VRAM + ((omoi_ptr->palette)<<5) ,
		  ndimGetAddressByIndex(node_data_address,ndpakey_ptr->index),
		  ndimGetDataSize(node_data_address) ,
		  3 ,
		  16 );
    }
}
//----------------------------------------------------------------------
void ndoaEval( u32 node_address , nodeEvalStruct *evstr_ptr )
{
    nodeOffsetAnim* ndoa_ptr;
    nodeOffsetAnimKey* ndoakey_ptr;
    nodeOffsetAnimKey* prev_ndoakey_ptr;
    register s32 add_x,add_y;
    register int i;
    register u16 time,next_time;

    if( evstr_ptr->flag & NODE_EVAL_USE_REF ) return;

    ndoa_ptr = (nodeOffsetAnim*)node_address;
#ifdef	__TEST_VERSION__
    ndoakey_ptr = (nodeOffsetAnimKey*)ndoa_ptr->key_start;
#else
    ndoakey_ptr = &ndoa_ptr->key_start;
#endif	//  __TEST_VERSION__
    time = evstr_ptr->time % ndoa_ptr->max_time;

    prev_ndoakey_ptr = NULL;
    for( i=0 ; i<ndoa_ptr->num_of_keys ; ++i )
    {
	if( time < ndoakey_ptr->time ) break;
	prev_ndoakey_ptr = ndoakey_ptr++;
    }
    if( i==ndoa_ptr->num_of_keys )
    {
#ifdef	__TEST_VERSION__
    ndoakey_ptr = (nodeOffsetAnimKey*)ndoa_ptr->key_start;
#else
	ndoakey_ptr = &ndoa_ptr->key_start;
#endif	//  __TEST_VERSION__
    }
    if( prev_ndoakey_ptr == NULL )
    {
#ifdef	__TEST_VERSION__
    ndoakey_ptr = (nodeOffsetAnimKey*)ndoa_ptr->key_start;
#else
	prev_ndoakey_ptr = &ndoa_ptr->key_start;
#endif	//  __TEST_VERSION__
    }

    if( ndoa_ptr->anim_type == NODE_ANIMTYPE_CONST )
    {
	add_x = (s32)prev_ndoakey_ptr->x;
	add_y = (s32)prev_ndoakey_ptr->y;
    }
    else
    {
	if( time == ndoakey_ptr->time )
	{
	    add_x = (s32)ndoakey_ptr->x;
	    add_y = (s32)ndoakey_ptr->y;
	}
	else
	{
	    next_time = prev_ndoakey_ptr->time;
	    if( next_time < time ) next_time = ndoa_ptr->max_time;
	    add_x = (s32)_Linear( time,
			     prev_ndoakey_ptr->time, prev_ndoakey_ptr->x ,
			     ndoakey_ptr->time, ndoakey_ptr->x );
	    add_y = (s32)_Linear( time,
			     prev_ndoakey_ptr->time, prev_ndoakey_ptr->y ,
			     ndoakey_ptr->time, ndoakey_ptr->y );
	}
    }

    evstr_ptr->coord.coord.offset_x += (s16)add_x;
    evstr_ptr->coord.coord.offset_y += (s16)add_y;

}
//----------------------------------------------------------------------
void ndraEval( u32 node_address , nodeEvalStruct *evstr_ptr )
{
    register nodeRotateAnim *ndra_ptr;
    register nodeRotateAnimKey *ndrakey_ptr;
    register nodeRotateAnimKey *prev_ndrakey_ptr;
    register int i;
    register u16 time,next_time;
    register u16 add_angle;

    if( evstr_ptr->flag & NODE_EVAL_USE_MATRIX ) return;

    ndra_ptr = (nodeRotateAnim*)node_address;
#ifdef	__TEST_VERSION__
    ndrakey_ptr = (nodeRotateAnimKey*)ndra_ptr->key_start;
#else
    ndrakey_ptr = &ndra_ptr->key_start;
#endif	//  __TEST_VERSION__
    time = evstr_ptr->time % ndra_ptr->max_time;

    prev_ndrakey_ptr = NULL;
    for( i=0 ; i<ndra_ptr->num_of_keys ; ++i )
    {
	if( time < ndrakey_ptr->time ) break;
	prev_ndrakey_ptr = ndrakey_ptr++;
    }
    if( i==ndra_ptr->num_of_keys )
    {
#ifdef	__TEST_VERSION__
	ndrakey_ptr = (nodeRotateAnimKey*)ndra_ptr->key_start;
#else
	ndrakey_ptr = &ndra_ptr->key_start;
#endif	//  __TEST_VERSION__
    }
    if( prev_ndrakey_ptr == NULL )
    {
#ifdef	__TEST_VERSION__
	prev_ndrakey_ptr = (nodeRotateAnimKey*)ndra_ptr->key_start;
#else
	prev_ndrakey_ptr = &ndra_ptr->key_start;
#endif	//  __TEST_VERSION__
    }

    if( ndra_ptr->anim_type == NODE_ANIMTYPE_CONST )
    {
	add_angle = (u16)prev_ndrakey_ptr->angle;
    }
    else
    {
	if( time == ndrakey_ptr->time )
	{
	    add_angle = (u16)prev_ndrakey_ptr->angle;
	}
	else
	{
	    next_time = prev_ndrakey_ptr->time;
	    if( next_time < time ) next_time = ndra_ptr->max_time;
	    add_angle = (u16)_Linear( time,
			     prev_ndrakey_ptr->time, prev_ndrakey_ptr->angle ,
			     ndrakey_ptr->time, ndrakey_ptr->angle );
	}
    }

    add_angle += evstr_ptr->sr.sr.angle;
    add_angle &= 0xff;
    evstr_ptr->sr.sr.angle = (u16)add_angle;
}
//----------------------------------------------------------------------
void ndsaEval( u32 node_address , nodeEvalStruct *evstr_ptr )
{
    register nodeScaleAnim *ndsa_ptr;
    register nodeScaleAnimKey *ndsakey_ptr;
    register nodeScaleAnimKey *prev_ndsakey_ptr;
    register s32 mul_x,mul_y;
    register int i;
    register u16 time,next_time;

    if( evstr_ptr->flag & NODE_EVAL_USE_MATRIX ) return;

    ndsa_ptr = (nodeScaleAnim*)node_address;
#ifdef	__TEST_VERSION__
    ndsakey_ptr = (nodeScaleAnimKey*)ndsa_ptr->key_start;
#else
    ndsakey_ptr = &ndsa_ptr->key_start;
#endif	//  __TEST_VERSION__
    time = evstr_ptr->time % ndsa_ptr->max_time;

    prev_ndsakey_ptr = NULL;
    for( i=0 ; i<ndsa_ptr->num_of_keys ; ++i )
    {
	if( time < ndsakey_ptr->time ) break;
	prev_ndsakey_ptr = ndsakey_ptr++;
    }
    if( i==ndsa_ptr->num_of_keys )
    {
#ifdef	__TEST_VERSION__
	ndsakey_ptr = (nodeScaleAnimKey*)ndsa_ptr->key_start;
#else
	ndsakey_ptr = &ndsa_ptr->key_start;
#endif	//  __TEST_VERSION__
    }
    if( prev_ndsakey_ptr == NULL )
    {
#ifdef	__TEST_VERSION__
	prev_ndsakey_ptr = (nodeScaleAnimKey*)ndsa_ptr->key_start;
#else
	prev_ndsakey_ptr = &ndsa_ptr->key_start;
#endif	//  __TEST_VERSION__
    }

    if( ndsa_ptr->anim_type == NODE_ANIMTYPE_CONST )
    {
	mul_x = (s32)prev_ndsakey_ptr->scale_x;
	mul_y = (s32)prev_ndsakey_ptr->scale_y;
    }
    else
    {
	if( time == ndsakey_ptr->time )
	{
	    mul_x = (s32)ndsakey_ptr->scale_x;
	    mul_y = (s32)ndsakey_ptr->scale_y;
	}
	else
	{
	    next_time = prev_ndsakey_ptr->time;
	    if( next_time < time ) next_time = ndsa_ptr->max_time;
	    mul_x = (s32)_Linear( time,
			     prev_ndsakey_ptr->time, prev_ndsakey_ptr->scale_x,
			     ndsakey_ptr->time, ndsakey_ptr->scale_x );
	    mul_y = (s32)_Linear( time,
			     prev_ndsakey_ptr->time, prev_ndsakey_ptr->scale_y,
			     ndsakey_ptr->time, ndsakey_ptr->scale_y );
	}
    }

    mul_x *= (s32)evstr_ptr->sr.sr.scale_x;
    mul_x >>= 8;
    mul_y *= (s32)evstr_ptr->sr.sr.scale_y;
    mul_y >>= 8;

    evstr_ptr->sr.sr.scale_x = (s16)mul_x;
    evstr_ptr->sr.sr.scale_y = (s16)mul_y;
}
//----------------------------------------------------------------------
void ndmaEval( u32 node_address , nodeEvalStruct *evstr_ptr )
{
    nodeMoveAnim* ndma_ptr;
    nodeMoveAnimKey* ndmakey_ptr;
    nodeMoveAnimKey* prev_ndmakey_ptr;
    register s32 add_x,add_y;
    register int i;
    register u16 time,next_time;

    if( evstr_ptr->flag & NODE_EVAL_USE_REF ) return;

    ndma_ptr = (nodeMoveAnim*)node_address;
#ifdef	__TEST_VERSION__
    ndmakey_ptr = (nodeMoveAnimKey*)ndma_ptr->key_start;
#else
    ndmakey_ptr = &ndma_ptr->key_start;
#endif	//  __TEST_VERSION__
    time = evstr_ptr->time % ndma_ptr->max_time;

    prev_ndmakey_ptr = NULL;
    for( i=0 ; i<ndma_ptr->num_of_keys ; ++i )
    {
	if( time < ndmakey_ptr->time ) break;
	prev_ndmakey_ptr = ndmakey_ptr++;
    }
    if( i==ndma_ptr->num_of_keys )
    {
#ifdef	__TEST_VERSION__
    ndmakey_ptr = (nodeMoveAnimKey*)ndma_ptr->key_start;
#else
	ndmakey_ptr = &ndma_ptr->key_start;
#endif	//  __TEST_VERSION__
    }
    if( prev_ndmakey_ptr == NULL )
    {
#ifdef	__TEST_VERSION__
    ndmakey_ptr = (nodeMoveAnimKey*)ndma_ptr->key_start;
#else
	prev_ndmakey_ptr = &ndma_ptr->key_start;
#endif	//  __TEST_VERSION__
    }

    if( ndma_ptr->anim_type == NODE_ANIMTYPE_CONST )
    {
	add_x = (s32)prev_ndmakey_ptr->x;
	add_y = (s32)prev_ndmakey_ptr->y;
    }
    else
    {
	if( time == ndmakey_ptr->time )
	{
	    add_x = (s32)ndmakey_ptr->x;
	    add_y = (s32)ndmakey_ptr->y;
	}
	else
	{
	    next_time = prev_ndmakey_ptr->time;
	    if( next_time < time ) next_time = ndma_ptr->max_time;
	    add_x = (s32)_Linear( time,
			     prev_ndmakey_ptr->time, prev_ndmakey_ptr->x ,
			     ndmakey_ptr->time, ndmakey_ptr->x );
	    add_y = (s32)_Linear( time,
			     prev_ndmakey_ptr->time, prev_ndmakey_ptr->y ,
			     ndmakey_ptr->time, ndmakey_ptr->y );
	}
    }

    evstr_ptr->coord.coord.move_x += (s16)add_x;
    evstr_ptr->coord.coord.move_y += (s16)add_y;

}
//----------------------------------------------------------------------

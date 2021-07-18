//======================================================
//    object.c                          
//    Object functions
//                                                     
//    Copyright (C) 1999,NINTENDO Co.,Ltd.             
//======================================================

#include <agb.h>
#include <isagbprint.h>
#include "node.h"
#include "object.h"
#include "objmanage.h"
#include "node_object.h"
#include "node_image.h"
#include "../utl/util.h"

//----------------------------------------------------------------------
#define	OBJECT_MAX_NUM	128
//----------------------------------------------------------------------
u16 objCount;
Object obj[OBJECT_MAX_NUM];
//----------------------------------------------------------------------
void obj_set_default_data(Object* obj_ptr);
//----------------------------------------------------------------------
void objInit( void )
{
    objCount = 0;
}
//----------------------------------------------------------------------
Object* objCreateObject(u32 NodeID, u16 CharacterNumber,
			s16 x, s16 y, u8 group)
{
    Object* ret_ptr;
    nodeObject* nobj_ptr;
    if( objCount >= OBJECT_MAX_NUM ) return NULL;
    nobj_ptr = (nodeObject*)nodeGetAddressByID( NodeID );
    ret_ptr = &obj[objCount++];
    ret_ptr->NodeID = NodeID;
    ret_ptr->x = (s32)x<<8;
    ret_ptr->y = (s32)y<<8;
    ret_ptr->scale_x = 0x100;
    ret_ptr->scale_y = 0x100;
    ret_ptr->rotation = 0;
    ret_ptr->group = group;
    ret_ptr->mosaic = 0;
    ret_ptr->objmode = 0;
    ret_ptr->objnumber = CharacterNumber;
    ret_ptr->max_time = nobj_ptr->max_time;
    ret_ptr->max_state = nobj_ptr->max_state;
    ret_ptr->time = 0;
    ret_ptr->state = 0;
    ret_ptr->old_time = 0;
    ret_ptr->old_state = 0;
    obj_set_default_data(ret_ptr);
    return ret_ptr;
}
//----------------------------------------------------------------------
void objSetScale(Object* obj_ptr,s16 scale_x,s16 scale_y)
{
    if( NULL != obj_ptr )
    {
	if( 0 != scale_x ) obj_ptr->scale_x = scale_x;
	if( 0 != scale_y ) obj_ptr->scale_y = scale_y;
    }
}
//----------------------------------------------------------------------
void objMultiScale(Object* obj_ptr,s16 scale_x,s16 scale_y)
{
    s32 calc_tmp;
    if( NULL != obj_ptr )
    {
	if( (0 != scale_x) && (0x0100 != scale_x) )
	{
	    calc_tmp = (s32)obj_ptr->scale_x;
	    if( calc_tmp == 0x00000100 )
	    {
		obj_ptr->scale_x = scale_x;
	    }
	    else
	    {
		calc_tmp *= (s32)scale_x;
		calc_tmp >>= 8;
		obj_ptr->scale_x = (s16)calc_tmp;
	    }
	}
	if( (0x0 != scale_y) && (0x0100 != scale_y) )
	{
	    calc_tmp = (s32)obj_ptr->scale_y;
	    if( calc_tmp == 0x00000100 )
	    {
		obj_ptr->scale_y = scale_y;
	    }
	    else
	    {
		calc_tmp *= (s32)scale_y;
		calc_tmp >>= 8;
		obj_ptr->scale_y = (s16)calc_tmp;
	    }
	}
    }
}
//----------------------------------------------------------------------
void objSetRotation(Object* obj_ptr,u8 rotation)
{
    if( NULL != obj_ptr )
    {
	obj_ptr->rotation = rotation;
    }
}
//----------------------------------------------------------------------
void objMultiRotation(Object* obj_ptr,u8 rotation)
{
    u16 calc_tmp;
    if( NULL != obj_ptr )
    {
	calc_tmp = (u16)obj_ptr->rotation;
	calc_tmp += rotation;
	calc_tmp &= 0xff;
	obj_ptr->rotation = (u8)calc_tmp;
    }
}
//----------------------------------------------------------------------
void objChangeObjMode(Object* obj_ptr,u8 objmode)
{
    if( NULL != obj_ptr )
    {
	obj_ptr->objmode = objmode & 0x03;
    }
}
//----------------------------------------------------------------------
void objSetMosaic(Object* obj_ptr)
{
    if( NULL != obj_ptr )
    {
	obj_ptr->mosaic = 1;
    }
}
//----------------------------------------------------------------------
void objClearMosaic(Object* obj_ptr)
{
    if( NULL != obj_ptr )
    {
	obj_ptr->mosaic = 0;
    }
}
//----------------------------------------------------------------------
void objChangeGroup(Object* obj_ptr , u8 group)
{
    if( NULL != obj_ptr )
    {
	obj_ptr->group = group & 0x0f;
    }
}
//----------------------------------------------------------------------
void objEvaluate(Object* obj_ptr)
{
    omObjectInstance omoi;
    nodeEvalStruct evstr;
    if( NULL != obj_ptr )
    {
	nodeEvalStructInit( &evstr );
	omInitObjectInstance( &omoi , obj_ptr );
	evstr.sr.sr.scale_x = obj_ptr->scale_x;
	evstr.sr.sr.scale_y = obj_ptr->scale_y;
	evstr.sr.sr.dummy = 0;
	evstr.sr.sr.angle = (u16)obj_ptr->rotation;
	evstr.time = obj_ptr->time;
	evstr.state = obj_ptr->state;
	evstr.old_time = obj_ptr->old_time;
	evstr.old_state = obj_ptr->old_state;
	evstr.instance_ptr = &omoi;

	nodeCallEvalFunction( obj_ptr->NodeID , &evstr );

	omSetObject( &evstr );
	if( !(evstr.flag & NODE_EVAL_USE_REF) )
	{
	    obj_ptr->x += (s32)evstr.coord.coord.move_x;
	    obj_ptr->y += (s32)evstr.coord.coord.move_y;
	}
	obj_ptr->old_time = evstr.time;
	obj_ptr->old_state = evstr.state;
    }
}
//----------------------------------------------------------------------
//----------------------------------------------------------------------
void obj_set_default_data(Object* obj_ptr)
{
    nodeObject* ndobj_ptr;
    u32 ndim_ptr;
    u16 data_size;
    u8  palette_bit;

    ndobj_ptr = (nodeObject*)nodeGetAddressByID( obj_ptr->NodeID );
    ndim_ptr = nodeGetAddressByID( ndobj_ptr->default_image_ID );

    palette_bit = (ndobj_ptr->default_OAM[0] & 0x2000) ? 8:4;
    dtSetDMA( OBJ_MODE0_VRAM + 32 * obj_ptr->objnumber ,
		ndimGetAddressByIndex(ndim_ptr,0) ,
		ndimGetDataSize(ndim_ptr) ,
		3 ,
		16 );

}
//----------------------------------------------------------------------


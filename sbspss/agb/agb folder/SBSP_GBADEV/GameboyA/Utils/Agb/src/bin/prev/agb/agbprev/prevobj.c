//======================================================
//    prevobj.c                          
//    Object process section of previewers.
//                                                     
//    Copyright (C) 1999, NINTENDO Co., Ltd.             
//======================================================

#include <agb.h>
#include <node.h>
#include <node_object.h>
#include "prevobj.h"
#include <object.h>
#include <util.h>
#include <ch_alloc.h>
#include <controller.h>

//----------------------------------------------------------------------
#define	PREVOBJECT_MAX_NUM	(128)
//----------------------------------------------------------------------
u16 pobjCount;
u16 pobjNumber;
Object* pobj_ptr[PREVOBJECT_MAX_NUM];
//----------------------------------------------------------------------
u8 active_object_number;
//----------------------------------------------------------------------
extern void omEval(void );
u16 pobjAllocCharacterNumber( u16 UseNum, u8 PaletteMode );
//----------------------------------------------------------------------
void pobjInit( void )
{
    pobjCount = 0;
    pobjNumber = 0;
    active_object_number = 0;
}
//----------------------------------------------------------------------
void pobjCreateObject( void )
{
    nodeObject* ndobj_ptr;
    u16 character_number;
    int i;

    for( i=0 ; i<nodeGetNumOfObjects() ; ++i )
    {
	if( pobjCount >= PREVOBJECT_MAX_NUM ) return;
	ndobj_ptr = (nodeObject*)nodeGetAddressByID( 
			nodeGetObjectIDByNumber( i ) );

	character_number = chalAlloc( ndobGetUseCharacterNum( (u32)ndobj_ptr ),
					ndobGetColorMode( (u32)ndobj_ptr ) );
	pobj_ptr[pobjCount++]=nodeCreateObject( i, character_number, 0, 0, 0 );
    }
}
//----------------------------------------------------------------------
void pobjControl(void)
{
    u16 button , trigger;
    Object* obj_ptr;
    button = Cont;
    trigger = Trg;
    obj_ptr = pobj_ptr[active_object_number];
    if( button & B_BUTTON )
    {
	if( button & R_KEY )
	{
	    if( obj_ptr->scale_x > 0x80 )
		obj_ptr->scale_x -= 4;
	}
	if( button & L_KEY )
	{
	    if( obj_ptr->scale_x < 0x200 )
		obj_ptr->scale_x += 8;
	}
	if( button & D_KEY )
	{
	    if( obj_ptr->scale_y < 0x200 )
		obj_ptr->scale_y += 8;
	}
	if( button & U_KEY )
	{
	    if( obj_ptr->scale_y > 0x80 )
		obj_ptr->scale_y -= 4;
	}
	if( button & R_BUTTON )
	{
	    obj_ptr->rotation = (u8)(u16)((obj_ptr->rotation + 254) & 0xff);
	}
	if( button & L_BUTTON )
	{
	    obj_ptr->rotation = (u8)(u16)((obj_ptr->rotation + 2) & 0xff);
	}
    }
    else
    {
	if( button & R_KEY )
	{
	    if( obj_ptr->x < (120<<8) )
		obj_ptr->x += 0x200;
	}
	if( button & L_KEY )
	{
	    if( obj_ptr->x > -(120<<8) )
		obj_ptr->x -= 0x200;
	}
	if( button & D_KEY )
	{
	    if( obj_ptr->y < (80<<8) )
		obj_ptr->y += 0x200;
	}
	if( button & U_KEY )
	{
	    if( obj_ptr->y > -(80<<8) )
		obj_ptr->y -= 0x200;
	}
	if( trigger & R_BUTTON )
	{
	    if( ++active_object_number >= pobjCount )
	    {
		active_object_number = 0;
	    }
	}
	if( trigger & L_BUTTON )
	{
	    if( active_object_number == 0 )
		active_object_number = pobjCount;
	    --active_object_number;
	}
	if( trigger & A_BUTTON )
	{
	    if( ++obj_ptr->state >= obj_ptr->max_state )
	    {
		obj_ptr->state = 0;
	    }
	}
    }
    if( trigger & START_BUTTON )
    {
	obj_ptr->scale_x = 0x100;
	obj_ptr->scale_y = 0x100;
	obj_ptr->rotation = 0;
	obj_ptr->x = 0;
	obj_ptr->y = 0;
    }
}
//----------------------------------------------------------------------
void pobjEvaluate(void)
{
    int i;
    for( i=0 ; i<pobjCount ; ++i )
    {
	if( ++pobj_ptr[i]->time >= pobj_ptr[i]->max_time )
	    pobj_ptr[i]->time = 0;
	if( pobj_ptr[i]->state != pobj_ptr[i]->old_state )
	    pobj_ptr[i]->time = 0;
	objEvaluate( pobj_ptr[i] );
    }
    omEval();
}
//----------------------------------------------------------------------


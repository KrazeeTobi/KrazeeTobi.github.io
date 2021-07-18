//======================================================
//    objmanage.h                          
//    Object management functions
//                                                     
//    Copyright (C) 1999, NINTENDO Co., Ltd.             
//======================================================

#ifndef	_OBJMANAGE_H_
#define	_OBJMANAGE_H_

#include <agb.h>
#include "object.h"
#include "node.h"
//----------------------------------------------------------------------
#define	OM_USE_SORT_KEY		(1)
#define	OM_NOUSE_SORT_KEY	(0)
//----------------------------------------------------------------------
//	For Object evaluation
//----------------------------------------------------------------------
typedef struct
{
    Object* obj_ptr;	//  Object pointer
    u16 objNumber;	//  Character name
    u8  group;		//  The smaller numerical value is drawn in the front.
			        //  Lower 4 bits are valid and upper 2 bits indicate
			        //  priority.
    u8  width;		//  Width of object
    u8  height;		//  Height of object
    u8  palette;	//  Palette number
    u8  mosaic;		//  1: Mosaic is added
    u8  flip;		//  1:h_flip 2:v_flip 3:hv_flip
    u8  objmode;	//  0:normal 1:transparent 2:window
    u8  dummy;
} omObjectInstance;
//----------------------------------------------------------------------
void omInit(u8 use_sort_key_flag);
void omClear(void);
void omInitObjectInstance( omObjectInstance* omoi_ptr , Object* obj_ptr );
void omSetObject( nodeEvalStruct* evstr_ptr );
void omEval(void);
//----------------------------------------------------------------------

#endif	//  _OBJMANAGE_H_

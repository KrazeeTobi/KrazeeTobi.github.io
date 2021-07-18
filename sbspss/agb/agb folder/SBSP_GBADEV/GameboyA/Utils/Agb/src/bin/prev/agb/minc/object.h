//======================================================
//    object.h                          
//    Object functions
//                                                     
//    Copyright (C) 1999, NINTENDO Co., Ltd.             
//======================================================

#ifndef	__OBJECT_H__
#define	__OBJECT_H__

#include <agb.h>

//----------------------------------------------------------------------
typedef struct
{
    u32 NodeID;
    s32 x;
    s32 y;
    s16 scale_x;
    s16 scale_y;
    u8  rotation;
    u8  group;
    u8  mosaic;
    u8  objmode;
    u16 objnumber;
    u16 sort_key;

    u16 max_time;
    u16 max_state;
    u16 time;
    u16 state;
    u16 old_time;
    u16 old_state;
} Object;
//----------------------------------------------------------------------
void objInit( void );
Object* objCreateObject(u32 NodeID, u16 objNumber, s16 x, s16 y, u8 group);
void objSetScale(Object* obj_ptr,s16 scale_x,s16 scale_y);
void objMultiScale(Object* obj_ptr,s16 scale_x,s16 scale_y);
void objSetRotation(Object* obj_ptr,u8 rotation);
void objMultiRotation(Object* obj_ptr,u8 rotation);
void objChangeObjMode(Object* obj_ptr,u8 objmode);
void objSetMosaic(Object* obj_ptr);
void objClearMosaic(Object* obj_ptr);
void objChangeGroup(Object* obj_ptr , u8 group);
void objEvaluate(Object* obj_ptr);
//----------------------------------------------------------------------

#endif	//  __OBJECT_H__

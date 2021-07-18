//======================================================
//    node_animation.h                          
//    Animation evaluation functions
//                                                     
//    Copyright (C) 1999, NINTENDO Co., Ltd.             
//======================================================

#ifndef	__NODE_OBJANIM_H__
#define	__NODE_OBJANIM_H__

#include <agb.h>
#include "node.h"
//----------------------------------------------------------------------
typedef struct
{
    nodeHead head;
    u32 num_of_children;
#ifdef	__TEST_VERSION__
    const u32* child_ID;
#else
    u32 child_ID;
#endif	//  __TEST_VERSION__
} nodeAnimation;
//----------------------------------------------------------------------
typedef struct
{
    u32 state;
    u32 child_ID;
} nodeSwitchState;

typedef struct
{
    nodeHead head;
    u32 num_of_states;
#ifdef	__TEST_VERSION__
    const nodeSwitchState* state_start;
#else
    nodeSwitchState state_start;
#endif	//  __TEST_VERSION__
} nodeSwitch;
//----------------------------------------------------------------------
typedef struct
{
    u32 state;
    u16 num_of_children;
    u16 start_index;
} nodeMultiSwitchState;

typedef struct
{
    nodeHead head;
    u32 num_of_states;
#ifdef	__TEST_VERSION__
    const nodeMultiSwitchState* state_start;
    const u32* child_ID;
#else
    nodeMultiSwitchState state_start;
#endif	//  __TEST_VERSION__
} nodeMultiSwitch;
//----------------------------------------------------------------------
typedef struct
{
    u16 time;
    u16 frame;
    u8  flip;
    u8  dummy;
} nodeFlipBookKey;

typedef struct
{
    nodeHead head;
    u32 data_node_ID;
    u16 max_time;
    u16 num_of_keys;
#ifdef	__TEST_VERSION__
    const nodeFlipBookKey* key_start;
#else
    nodeFlipBookKey key_start;
#endif	//  __TEST_VERSION__
} nodeFlipBook;
//----------------------------------------------------------------------
typedef struct
{
    u16 time;
    u16 index;
} nodePaletteAnimKey;

typedef struct
{
    nodeHead head;
    u32 data_node_ID;
    u16 num_of_keys;
    u16 max_time;
#ifdef	__TEST_VERSION__
    const nodePaletteAnimKey* key_start;
#else
    nodePaletteAnimKey key_start;
#endif	//  __TEST_VERSION__
} nodePaletteAnim;
//----------------------------------------------------------------------
typedef struct
{
    u16 time;
    s16 x;
    s16 y;
} nodeOffsetAnimKey;

typedef struct
{
    nodeHead head;
    u16 max_time;
    u16 anim_type;
    u16 num_of_keys;
#ifdef	__TEST_VERSION__
    const nodeOffsetAnimKey* key_start;
#else
    nodeOffsetAnimKey key_start;
#endif	//  __TEST_VERSION__
} nodeOffsetAnim;
//----------------------------------------------------------------------
typedef struct
{
    u16 time;
    u8  angle;
    u8  dummy;
} nodeRotateAnimKey;

typedef struct
{
    nodeHead head;
    u16 max_time;
    u16 anim_type;
    u16 num_of_keys;
#ifdef	__TEST_VERSION__
    const nodeRotateAnimKey* key_start;
#else
    nodeRotateAnimKey key_start;
#endif	//  __TEST_VERSION__
} nodeRotateAnim;
//----------------------------------------------------------------------
typedef struct
{
    u16 time;
    s16 scale_x;
    s16 scale_y;
} nodeScaleAnimKey;

typedef struct
{
    nodeHead head;
    u16 max_time;
    u16 anim_type;
    u16 num_of_keys;
#ifdef	__TEST_VERSION__
    const nodeScaleAnimKey* key_start;
#else
    nodeScaleAnimKey key_start;
#endif	//  __TEST_VERSION__
} nodeScaleAnim;
//----------------------------------------------------------------------
typedef struct
{
    u16 time;
    s16 x;
    s16 y;
} nodeMoveAnimKey;

typedef struct
{
    nodeHead head;
    u16 max_time;
    u16 anim_type;
    u16 num_of_keys;
#ifdef	__TEST_VERSION__
    const nodeMoveAnimKey* key_start;
#else
    nodeMoveAnimKey key_start;
#endif	//  __TEST_VERSION__
} nodeMoveAnim;
//----------------------------------------------------------------------
void ndanEval( u32 node_address , nodeEvalStruct* evstr_ptr );
void ndswEval( u32 node_address , nodeEvalStruct* evstr_ptr );
void ndfbEval( u32 node_address , nodeEvalStruct* evstr_ptr );
void ndpaEval( u32 node_address , nodeEvalStruct* evstr_ptr );
void ndoaEval( u32 node_address , nodeEvalStruct* evstr_ptr );
void ndsaEval( u32 node_address , nodeEvalStruct* evstr_ptr );
void ndraEval( u32 node_address , nodeEvalStruct* evstr_ptr );
void ndmaEval( u32 node_address , nodeEvalStruct* evstr_ptr );
//----------------------------------------------------------------------

#endif	//  __NODE_OBJANIM_H__

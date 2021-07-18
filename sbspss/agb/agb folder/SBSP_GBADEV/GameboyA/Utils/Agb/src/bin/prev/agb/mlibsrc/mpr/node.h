//======================================================
//    node.h                                      
//    Node functions
//                                                     
//    Copyright (C) 1999, NINTENDO Co., Ltd.             
//======================================================

#ifndef	__NODE_H__
#define	__NODE_H__

#pragma pack(2)

#include <agb.h>
#include <util.h>
#include "object.h"

#undef	__TEST_VERSION__
#define	__TEST_VERSION__

//----------------------------------------------------------------------
#define	NODE_ANIMTYPE_CONST	(0)
#define	NODE_ANIMTYPE_LINEAR	(1)
#define	NODE_EVAL_USE_MATRIX	(1)
#define	NODE_EVAL_USE_REF	(2)
//----------------------------------------------------------------------
#define	NODE_INVALID_ID		(0xffffffff)
//----------------------------------------------------------------------

    //  Header portion of Node
typedef struct
{
    u32 magic;
    u32 size;
    u32 name_index;
} nodeHead;

    //  General structure of Node
typedef struct
{
    nodeHead head;
    u8  data;
} nodeCommon;
//----------------------------------------------------------------------

    //  Structure that displays the amount of movement.
    //  Structure members consist of 1 bit for encoding, 7 bits for integer 
    //  part, and 8 bits for the fractional part accordingly.
typedef struct
{
    s16 move_x;
    s16 offset_x;
    s16 move_y;
    s16 offset_y;
} nodeCoordEval;

    //  By ordering the structure members this way,
    //  the exact same value used at the time of SRMatrix initialization
    //  can be used at the time of initialization.
typedef struct
{
    s16 scale_x;
    u16 angle;
    u16 dummy;
    s16 scale_y;
} nodeScaleRotateEval;

    //  Structure used at the time of Node Evaluation.
    //  instance_ptr is assigned a value based on the contents of the evaluation.
typedef struct
{
    u16 state;
    u16 time;
    u16 old_state;
    u16 old_time;
    u16 flag;
    u16 dummy;
    u32 animation_ID;
    union
    {
	nodeCoordEval coord;
	RefStartCoord ref;
    } coord;
    union
    {
	nodeScaleRotateEval sr;
	SRMatrix matrix;
    } sr;
    void* instance_ptr;
} nodeEvalStruct;
//----------------------------------------------------------------------
typedef struct
{
    nodeHead head;
#ifdef	__TEST_VERSION__
    const void* nodes_offset;
    const void* disp_header_offset;
    const void* root_objects_offset;
    const void* root_bgs_offset;
#else
    u32 nodes_offset;
    u32 disp_header_offset;
    u32 root_objects_offset;
    u32 root_bgs_offset;
#endif	//  __TEST_VERSION__
} nodeHeaderChunk;

    //  Structure that displays Node table
typedef struct
{
    u32 num_of_nodes;
#ifdef	__TEST_VERSION__
    const u32* offset;
#else
    u32 offset;
#endif	//  __TEST_VERSION__
} nodeOffsetTable;

    //  Structure that indicates the evaluation starting ID of Sprite Node
typedef struct
{
    u32 default_palette_ID;
    u16 num_of_objects;
#ifdef	__TEST_VERSION__
    const u32* object_ID;
#else
    u32 object_ID;
#endif	//  __TEST_VERSION__
} nodeRootObjects;

    //  Structure that indicates the evaluation starting ID of Background Node
typedef struct
{
    u32 default_palette_ID;
    u16 num_of_bgs;
    u16 priority_map;
    u16 bg_color;
    u32 bg_ID[4];
} nodeRootBGs;

    //  Structure that indicates BG Mode
typedef struct
{
    u16 dispcnt;
    u16 bg0cnt;
    u16 bg1cnt;
    u16 bg2cnt;
    u16 bg3cnt;
} nodeDispHeader;
//----------------------------------------------------------------------
void ndhcEvaluate( u32 nodeheaderchunk_address );
void nodeEvalStructInit( nodeEvalStruct* evstr_ptr );
u32  nodeGetAddressByID( u32 ID );
u32  nodeGetMagicByID( u32 ID );
u32  nodeGetNumOfObjects( void );
u32  nodeGetNumOfBGs( void );
u32  nodeGetObjectIDByNumber( u32 ObjNodeNumber );
Object* nodeCreateObject(u32 ObjNodeNumber, u16 CharacterNumber,
			 s16 x, s16 y, u8 group);
void nodeCallEvalFunction( u32 ID, nodeEvalStruct* evstr_ptr );
void mgCallEvalFunction(u32 magic,u32 node_address,
			nodeEvalStruct* evstr_ptr);
//----------------------------------------------------------------------

#endif	//  __NODE_H__

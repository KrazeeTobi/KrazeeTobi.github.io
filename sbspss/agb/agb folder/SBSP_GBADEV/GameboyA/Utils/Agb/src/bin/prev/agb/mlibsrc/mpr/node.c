//======================================================
//    node.c                                      
//    Node functions
//                                                     
//    Copyright (C) 1999, NINTENDO Co., Ltd.             
//======================================================

#include <agb.h>
#include <isagbprint.h>
#include <util.h>
#include "node.h"
#include "object.h"
#include "node_image.h"

//----------------------------------------------------------------------
u32* node_offset_table_ptr;
u32 nodeHeaderChunk_ptr;
u32* node_object_table_ptr;
u16 node_num_of_objects;
u16 node_num_of_bgs;
//----------------------------------------------------------------------
extern void bmSetBGMode( u8 mode );
//----------------------------------------------------------------------
void node_eval_disp_header( u32 disp_header_ptr );
void node_eval_nodes_offset( u32 nodes_offset_ptr );
void node_eval_objects( u32 root_objects_ptr );
void node_eval_bgs( u32 root_bgs_ptr, u32 disp_header_ptr );
//----------------------------------------------------------------------
void ndhcEvaluate( u32 nodeheaderchunk_address )
{
    nodeHeaderChunk* header_ptr;

    nodeHeaderChunk_ptr = nodeheaderchunk_address;

    header_ptr = (nodeHeaderChunk*)nodeheaderchunk_address;
#ifdef	__TEST_VERSION__
    node_eval_disp_header( (u32)header_ptr->disp_header_offset );
    node_eval_nodes_offset( (u32)header_ptr->nodes_offset );
    node_eval_objects( (u32)header_ptr->root_objects_offset );
    node_eval_bgs( (u32)header_ptr->root_bgs_offset,
		   (u32)header_ptr->disp_header_offset );
#else
    node_eval_disp_header( header_ptr->disp_header_offset
			   + nodeheaderchunk_address );
    node_eval_nodes_offset( header_ptr->nodes_offset
			   + nodeheaderchunk_address );
    node_eval_objects( header_ptr->root_objects_offset
			   + nodeheaderchunk_address );
    node_eval_bgs( header_ptr->root_bgs_offset
			   + nodeheaderchunk_address ,
		   header_ptr->disp_header_offset
			   + nodeheaderchunk_address );
#endif	//  __TEST_VERSION__
}
//----------------------------------------------------------------------
void nodeEvalStructInit( nodeEvalStruct* evstr_ptr )
{
    evstr_ptr->flag = 0;
    evstr_ptr->coord.ref.x_l = 0;
    evstr_ptr->coord.ref.x_h = 0;
    evstr_ptr->coord.ref.y_l = 0;
    evstr_ptr->coord.ref.y_h = 0;
    evstr_ptr->sr.matrix.dx  = 0x100;
    evstr_ptr->sr.matrix.dmx = 0;
    evstr_ptr->sr.matrix.dy  = 0;
    evstr_ptr->sr.matrix.dmy = 0x100;
    evstr_ptr->animation_ID = NODE_INVALID_ID;
}
//----------------------------------------------------------------------
u32  nodeGetAddressByID( u32 ID )
{
    if( (void*)0 == node_offset_table_ptr ) return 0;
    if( ID == NODE_INVALID_ID ) return 0;
#ifdef	__TEST_VERSION__
    return (node_offset_table_ptr[ID]);
#else
    return (node_offset_table_ptr[ID] + nodeHeaderChunk_ptr);
#endif	//  __TEST_VERSION
}
//----------------------------------------------------------------------
u32  nodeGetMagicByID( u32 ID )
{
    nodeCommon* node_ptr;

    if( (void*)0 == node_offset_table_ptr ) return -1;
    node_ptr = (nodeCommon*)(nodeGetAddressByID(ID));
    if( node_ptr == 0 )
    {
	return -1;
    }
    return node_ptr->head.magic;
}
//----------------------------------------------------------------------
void nodeCallEvalFunction( u32 ID, nodeEvalStruct* evstr_ptr )
{
    mgCallEvalFunction( nodeGetMagicByID(ID) ,
			nodeGetAddressByID(ID) ,
			evstr_ptr );
}
//----------------------------------------------------------------------
u32  nodeGetNumOfObjects( void )
{
    return (u32)node_num_of_objects;
}
//----------------------------------------------------------------------
u32  nodeGetNumOfBGs( void )
{
    return (u32)node_num_of_bgs;
}
//----------------------------------------------------------------------
u32 nodeGetObjectIDByNumber(u32 ObjNodeNumber)
{
    return node_object_table_ptr[ObjNodeNumber];
}
//----------------------------------------------------------------------
Object* nodeCreateObject(u32 ObjNodeNumber, u16 CharacterNumber,
			 s16 x, s16 y, u8 group)
{
    return objCreateObject( node_object_table_ptr[ObjNodeNumber],
			    CharacterNumber,x,y,group );
}
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
void node_eval_disp_header( u32 disp_header_ptr )
{
    nodeDispHeader* dh_ptr;

    dh_ptr = (nodeDispHeader*)disp_header_ptr;
    *(vu16*)REG_DISPCNT = dh_ptr->dispcnt;
    *(vu16*)REG_BG0CNT = dh_ptr->bg0cnt;
    *(vu16*)REG_BG1CNT = dh_ptr->bg1cnt;
    *(vu16*)REG_BG2CNT = dh_ptr->bg2cnt;
    *(vu16*)REG_BG3CNT = dh_ptr->bg3cnt;
}
//----------------------------------------------------------------------
void node_eval_nodes_offset( u32 nodes_offset_ptr )
{
    nodeOffsetTable* oftbl_ptr;
    oftbl_ptr = (nodeOffsetTable*)nodes_offset_ptr;
#ifdef	__TEST_VERSION__
    node_offset_table_ptr = (u32*)oftbl_ptr->offset;
#else
    node_offset_table_ptr = &(oftbl_ptr->offset);
#endif	//  __TEST_VERSION__
}
//----------------------------------------------------------------------
void node_eval_objects( u32 root_objects_ptr )
{
    nodeRootObjects* objects_ptr;
    nodeImage* pal_address;
    u16 trans_size;
//    u32* object_ID_ptr;
    int i;

    objects_ptr = (nodeRootObjects*)root_objects_ptr;
#ifdef	__TEST_VERSION__
    node_object_table_ptr = (u32*)objects_ptr->object_ID;
#else
    node_object_table_ptr = &objects_ptr->object_ID;
#endif	//  __TEST_VERSION__

	//  Transfer palette
    pal_address = (nodeImage*)nodeGetAddressByID(
				objects_ptr->default_palette_ID );

	//  Examine the number of palette colors
    if( pal_address->width == 256 )
    {
	trans_size = 256;
    }
    else
    {
	trans_size = pal_address->width * pal_address->data_num;
	if( trans_size > 256 ) trans_size = 256;
    }
    dtSetDMA( OBJ_PLTT ,
		ndimGetAddressByIndex((u32)pal_address,0) ,
		trans_size<<1 ,
		3 ,
		16 );

//    object_ID_ptr = node_object_table_ptr;
    node_num_of_objects = objects_ptr->num_of_objects;
//    for( i=0 ; i<node_num_of_objects ; ++i )
//    {
//	pobjCreateObject(*object_ID_ptr);
//	++object_ID_ptr;
//    }
}
//----------------------------------------------------------------------
void node_eval_bgs( u32 root_bgs_ptr, u32 disp_header_ptr)
{
    nodeRootBGs* bgs_ptr;
    nodeDispHeader* dh_ptr;
    nodeImage* pal_address;
    u16 trans_size;
    u16 bgcnt[4];
    u32* bg_ID_ptr;
    u8  priority[4];
    int i;

    bgs_ptr = (nodeRootBGs*)root_bgs_ptr;

    bg_ID_ptr = bgs_ptr->bg_ID;

	//  Transfer palette
    pal_address = (nodeImage*)nodeGetAddressByID(
				bgs_ptr->default_palette_ID );

    if( pal_address )
    {
	//  Examine the number of palette colors
	if( pal_address->width >= 256 )
	{
	    trans_size = 256;
	}
	else
	{
	    trans_size = pal_address->width * pal_address->data_num;
	    if( trans_size > 256 ) trans_size = 256;
	}
	dtSetDMA( BG_PLTT ,
		  ndimGetAddressByIndex((u32)pal_address,0) ,
		  trans_size<<1 ,
		  3 ,
		  16 );
    }
    else
    {
	dtSet( BG_PLTT , 1 ,
		&bgs_ptr->bg_color , 1 ,
		16 , 1 , 1 );
    }

    priority[0] = (u8)(u16)((bgs_ptr->priority_map & 0x3000)>>12);
    priority[1] = (u8)(u16)((bgs_ptr->priority_map & 0x300)>>8);
    priority[2] = (u8)(u16)((bgs_ptr->priority_map & 0x30)>>4);
    priority[3] = (u8)(u16)(bgs_ptr->priority_map & 0x3);

    node_num_of_bgs = bgs_ptr->num_of_bgs;
    dh_ptr = (nodeDispHeader*)disp_header_ptr;
    bmSetBGMode( (u8)(u16)(dh_ptr->dispcnt & 7) );
    bgcnt[0] = dh_ptr->bg0cnt;
    bgcnt[1] = dh_ptr->bg1cnt;
    bgcnt[2] = dh_ptr->bg2cnt;
    bgcnt[3] = dh_ptr->bg3cnt;
	//  For each BG, create BG if there is node

    for( i=0 ; i<4 ; ++i )
    {
	if( *bg_ID_ptr != 0xffffffff )
	{
	    pbgCreateBackground(*bg_ID_ptr, i, priority[i], bgcnt[i]);
	}
	++bg_ID_ptr;
    }
}
//----------------------------------------------------------------------
//
//	Call evaluation function from Magic
//
//----------------------------------------------------------------------
typedef void (*EvalFunction)(u32,nodeEvalStruct*);
//----------------------------------------------------------------------
//	If node is added, add it to the following sections
//----------------------------------------------------------------------

enum Magic
{
    magic_object = 0,
    magic_background ,
    magic_image ,
    magic_animation ,
    magic_switch ,
    magic_multi_switch ,
    magic_flipbook ,
    magic_rotate_animation ,
    magic_palette_animation ,
    magic_scale_animation ,
    magic_offset_animation ,
    magic_move_animation ,

    magic_max_num
};

extern void ndobEval( u32 node_address, nodeEvalStruct* evstr_ptr );
extern void ndbgEval( u32 node_address, nodeEvalStruct* evstr_ptr );
extern void ndimEval( u32 node_address, nodeEvalStruct* evstr_ptr );
extern void ndanEval( u32 node_address, nodeEvalStruct* evstr_ptr );
extern void ndswEval( u32 node_address, nodeEvalStruct* evstr_ptr );
extern void ndmsEval( u32 node_address, nodeEvalStruct* evstr_ptr );
extern void ndfbEval( u32 node_address, nodeEvalStruct* evstr_ptr );
extern void ndraEval( u32 node_address, nodeEvalStruct* evstr_ptr );
extern void ndpaEval( u32 node_address, nodeEvalStruct* evstr_ptr );
extern void ndsaEval( u32 node_address, nodeEvalStruct* evstr_ptr );
extern void ndoaEval( u32 node_address, nodeEvalStruct* evstr_ptr );
extern void ndmaEval( u32 node_address, nodeEvalStruct* evstr_ptr );

const EvalFunction eval_fnc_array[magic_max_num] =
{
    ndobEval ,
    ndbgEval ,
    ndimEval ,
    ndanEval ,
    ndswEval ,
    ndmsEval ,
    ndfbEval ,
    ndraEval ,
    ndpaEval ,
    ndsaEval ,
    ndoaEval ,
    ndmaEval ,
};

//----------------------------------------------------------------------
void mgCallEvalFunction( u32 magic, u32 node_address,
			 nodeEvalStruct* evstr_ptr)
{
    if( magic < magic_max_num )
    {
	(*eval_fnc_array[magic])(node_address , evstr_ptr);
    }
}
//----------------------------------------------------------------------


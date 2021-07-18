//======================================================
//    bgmanage.c                                      
//    Background management
//                                                     
//    Copyright (C) 1999, NINTENDO Co., Ltd.             
//======================================================

#include <agb.h>
#include <isagbprint.h>
#include <util.h>
#include "datatrans.h"
#include "bgmanage.h"
#include "background.h"
#include "node.h"
#include "node_background.h"
#include "node_image.h"

//----------------------------------------------------------------------
u16 bgRegDG[(0x40-0x08)/2];
u8  bg_mode;
//----------------------------------------------------------------------
#define	BGREGDG_BEGIN	(&bgRegDG[0])
#define	BGREGDG_BG0CNT	(&bgRegDG[0])
#define	BGREGDG_BG1CNT	(&bgRegDG[1])
#define	BGREGDG_BG2CNT	(&bgRegDG[2])
#define	BGREGDG_BG3CNT	(&bgRegDG[3])
#define	BGREGDG_BG0HOFS	(&bgRegDG[4])
#define	BGREGDG_BG0VOFS	(&bgRegDG[5])
#define	BGREGDG_BG1HOFS	(&bgRegDG[6])
#define	BGREGDG_BG1VOFS	(&bgRegDG[7])
#define	BGREGDG_BG2HOFS	(&bgRegDG[8])
#define	BGREGDG_BG2VOFS	(&bgRegDG[9])
#define	BGREGDG_BG3HOFS	(&bgRegDG[10])
#define	BGREGDG_BG3VOFS	(&bgRegDG[11])
#define	BGREGDG_BG2PA	(&bgRegDG[12])
#define	BGREGDG_BG2PB	(&bgRegDG[13])
#define	BGREGDG_BG2PC	(&bgRegDG[14])
#define	BGREGDG_BG2PD	(&bgRegDG[15])
#define	BGREGDG_BG2X_L	(&bgRegDG[16])
#define	BGREGDG_BG2X_H	(&bgRegDG[17])
#define	BGREGDG_BG2Y_L	(&bgRegDG[18])
#define	BGREGDG_BG2Y_H	(&bgRegDG[19])
#define	BGREGDG_BG3PA	(&bgRegDG[20])
#define	BGREGDG_BG3PB	(&bgRegDG[21])
#define	BGREGDG_BG3PC	(&bgRegDG[22])
#define	BGREGDG_BG3PD	(&bgRegDG[23])
#define	BGREGDG_BG3X_L	(&bgRegDG[24])
#define	BGREGDG_BG3X_H	(&bgRegDG[25])
#define	BGREGDG_BG3Y_L	(&bgRegDG[26])
#define	BGREGDG_BG3Y_H	(&bgRegDG[27])
//----------------------------------------------------------------------
RefStartCoord* ref_ptr[4] =
{
    NULL,NULL,
    (RefStartCoord*)BGREGDG_BG2X_L,
    (RefStartCoord*)BGREGDG_BG3X_L,
};
SRMatrix*   rsmtx_ptr[4] =
{
    NULL,NULL,
    (SRMatrix*)BGREGDG_BG2PA,
    (SRMatrix*)BGREGDG_BG3PA,
};
//----------------------------------------------------------------------
typedef struct
{
    nodeImage*	image_ptr;
    MapVram*	vram_ptr;
    Point16	dest;
    Point16	src;
    Size16	size;
} bmDataTransParam;
//----------------------------------------------------------------------
u16 bm_vram_get_true_coord( s32 coord , u8 block_bit );
static void bm_set_data_trans( bmDataTransParam* dtpm_ptr);
static void bm_set_data_trans_start( bmDataTransParam* dtpm_ptr );
static void bm_set_data_trans_sr( bmDataTransParam* dtpm_ptr );
static void bm_set_data_trans_tx_w256( bmDataTransParam* dtpm_ptr );
static void bm_set_data_trans_tx_w512( bmDataTransParam* dtpm_ptr );

typedef void (*set_dt_func)(bmDataTransParam* dtpm_ptr);

set_dt_func sdf;
//----------------------------------------------------------------------
void bmSetBGMode( u8 mode )
{
    if( mode <= 2 ) bg_mode = mode;
}
//----------------------------------------------------------------------
void bmInitMapDataTransSet( u32 map_image_ID, s32 start_x, s32 start_y,
			    MapVram* map_vram_ptr)
{
    nodeImage* ndim_ptr;
    u16 block_width,block_height;
    s32 tmp;
    bmDataTransParam dtpm;

    ndim_ptr = (nodeImage*)nodeGetAddressByID(map_image_ID);
    block_width  = _BitValue(map_vram_ptr->block_bit_x);
    block_height = _BitValue(map_vram_ptr->block_bit_y);

    dtpm.image_ptr = ndim_ptr;

    tmp = (start_x >> 11) - (block_width >> 1);
    _wrapLowerLimit( tmp , 0 , ndim_ptr->width );
    dtpm.src.x = (s16)tmp;

    tmp = (start_y >> 11) - (block_height >> 1);
    _wrapLowerLimit( tmp , 0 , ndim_ptr->height );
    dtpm.src.y = (s16)tmp;

    dtpm.vram_ptr = map_vram_ptr;
    dtpm.dest.x = 0;
    dtpm.dest.y = 0;

    dtpm.size.w = block_width;
    dtpm.size.h = block_height;

    bm_set_data_trans( &dtpm );
}
//----------------------------------------------------------------------
void bmClear(void)
{
    *(vu16*)BGREGDG_BG0CNT = 0;
    *(vu16*)BGREGDG_BG1CNT = 0;
    *(vu16*)BGREGDG_BG2CNT = 0;
    *(vu16*)BGREGDG_BG3CNT = 0;
    RefStartCoordSetIdent( ref_ptr[2] , 0 , 0 );
    RefStartCoordSetIdent( ref_ptr[3] , 0 , 0 );
    SRMatrixSetIdent( rsmtx_ptr[2] );
    SRMatrixSetIdent( rsmtx_ptr[3] );
    *BGREGDG_BG0HOFS = 0;
    *BGREGDG_BG0VOFS = 0;
    *BGREGDG_BG1HOFS = 0;
    *BGREGDG_BG1VOFS = 0;
    *BGREGDG_BG2HOFS = 0;
    *BGREGDG_BG2VOFS = 0;
    *BGREGDG_BG3HOFS = 0;
    *BGREGDG_BG3VOFS = 0;
    sdf = bm_set_data_trans_sr;
}
//----------------------------------------------------------------------
void bmInitBackgroundInstance( bmBackgroundInstance* bg_ins_ptr ,
			Background* bg_ptr, u8 bg_number )
{
    bg_ins_ptr->bg_ptr = bg_ptr;
    bg_ins_ptr->bg_number = bg_number;
}
//----------------------------------------------------------------------
void bmSetBackground(nodeEvalStruct* eval_ptr)
{
    bmBackgroundInstance* bmbi_ptr;
    nodeBackground* ndbg_ptr;
    nodeImage* ndim_ptr;
    Background* bg_ptr;
    MapVram* map_vram_ptr;
    bmDataTransParam dtpm;
    register s32 tmp;
    s16 move_x , move_y;
    s32 vram_new_x,vram_new_y;
    s32 new_x , new_y;
    s16 def_x , def_y;
    u16 vram_block_width , vram_block_height;
    s32 rel;

    bmbi_ptr = (bmBackgroundInstance*)eval_ptr->instance_ptr;
    ndbg_ptr = (nodeBackground*)nodeGetAddressByID( bmbi_ptr->bg_ptr->NodeID );
    ndim_ptr = (nodeImage*)nodeGetAddressByID( ndbg_ptr->map_image_ID );
    bg_ptr = bmbi_ptr->bg_ptr;
    map_vram_ptr = bg_ptr->map_vram_ptr;

	//  Read value from the quantity changed

    def_x = bg_ptr->move_x;
    def_y = bg_ptr->move_y;

    if( eval_ptr->flag & NODE_EVAL_USE_REF )
    {
	//  It is necessary to examine the value inserted here
	def_x += 0;
	def_y += 0;
    }
    else
    {
	def_x += eval_ptr->coord.coord.move_x;
	def_y += eval_ptr->coord.coord.move_y;
	def_x += eval_ptr->coord.coord.offset_x;
	def_y += eval_ptr->coord.coord.offset_y;
    }
    new_x = bg_ptr->old_x + def_x;
    new_y = bg_ptr->old_y + def_y;
    vram_new_x = map_vram_ptr->x + def_x;
    vram_new_y = map_vram_ptr->y + def_y;

	//  Find the amount of movement by block

    move_x = (s16)(s32)((new_x >> 11)-(bg_ptr->old_x >> 11));
    move_y = (s16)(s32)((new_y >> 11)-(bg_ptr->old_y >> 11));

	//  Adjust new coordinate

    tmp = ndim_ptr->width << 11;
    _wrapLimit( new_x , 0 , tmp );
    tmp = ndim_ptr->height << 11;
    _wrapLimit( new_y , 0 , tmp );

    vram_block_width  = _BitValue(map_vram_ptr->block_bit_x);
    vram_block_height = _BitValue(map_vram_ptr->block_bit_y);
    vram_new_x &= (( vram_block_width  << 11 ) -1);
    vram_new_y &= (( vram_block_height << 11 ) -1);

    dtpm.image_ptr = ndim_ptr;
    dtpm.vram_ptr = map_vram_ptr;

    if( move_x )
    {
	dtpm.src.y = (s16)((s32)(new_y >> 11)-(vram_block_height>>1));
	_wrapLowerLimit( dtpm.src.y , 0 , ndim_ptr->height );
	dtpm.dest.y = (s16)((s32)(vram_new_y >> 11));
	dtpm.size.h = vram_block_height;

	if( move_x < 0 )
	{
		//  Set the value in data transfer structure

	    dtpm.size.w = (u16)(-move_x);

		//  Map

	    dtpm.src.x = (s16)((s32)(new_x >> 11)-(vram_block_width>>1))
			 ;
	    _wrapLimit( dtpm.src.x , 0 , ndim_ptr->width );

		//  VRAM

	    dtpm.dest.x = ((s16)(s32)(vram_new_x >> 11))
			& (vram_block_width - 1);

	    if( (map_vram_ptr->text_flag == 1)
	     || (move_x < -1)
	     || ((dtpm.dest.x & 1)== 1) )
	    {
		bm_set_data_trans( &dtpm );
	    }
	}
	else
	{
		//  Set the value in data transfer structure

	    dtpm.size.w = move_x;

	    dtpm.src.x = (s16)((s32)(new_x >> 11) + (vram_block_width >> 1))
			- move_x-1;
	    dtpm.dest.x = (s16)((s32)(vram_new_x>>11))
			- move_x-1;

	    _wrapLimit( dtpm.src.x , 0 , ndim_ptr->width );
	    dtpm.dest.x &= (vram_block_width-1);

	    if( (map_vram_ptr->text_flag == 1)
	     || (move_x > 1)
	     || ((dtpm.dest.x & 1)== 0) )
	    {
		bm_set_data_trans( &dtpm );
	    }
	}
    }

    if( move_y )
    {
	dtpm.src.x = (s16)((s32)(new_x >> 11)-(vram_block_width>>1)
			- 1 + map_vram_ptr->text_flag);
	_wrapLowerLimit( dtpm.src.x , 0 , ndim_ptr->width );
	dtpm.dest.x = (s16)((s32)(vram_new_x >> 11)
			- 1 + map_vram_ptr->text_flag)
			& (vram_block_width - 1);
	dtpm.size.w = vram_block_width;

	if( move_y < 0 )
	{
		//  Set the value in data transfer structure

	    dtpm.size.h = (u16)(-move_y);

		//  Map

	    dtpm.src.y = (s16)((s32)(new_y >> 11)-(vram_block_height>>1));
	    _wrapLimit( dtpm.src.y , 0 , ndim_ptr->height );

		//  VRAM

	    dtpm.dest.y = ((s16)(s32)(vram_new_y >> 11))
			& (vram_block_height - 1);

	    bm_set_data_trans( &dtpm );
	}
	else
	{
		//  Set the value in data transfer structure

	    dtpm.size.h = move_y;

		//  Map

	    dtpm.src.y = (s16)((s32)(new_y >> 11) + (vram_block_height >> 1))
			- move_y;
	    _wrapLimit( dtpm.src.y , 0 , ndim_ptr->height );

		//  VRAM

	    dtpm.dest.y = ((s16)((s32)vram_new_y>>11) - move_y)
			& ((vram_block_height)-1);

	    bm_set_data_trans( &dtpm );
	}
    }

	//  Scaling/rotation and scroll evaluation

    if( map_vram_ptr->text_flag )
    {
	BGREGDG_BG0HOFS[(bmbi_ptr->bg_number)*2] =
		bm_vram_get_true_coord( vram_new_x ,
					map_vram_ptr->block_bit_x );
	BGREGDG_BG0HOFS[(bmbi_ptr->bg_number)*2 + 1] =
		bm_vram_get_true_coord( vram_new_y ,
					map_vram_ptr->block_bit_y );
    }
    else
    {
	if( eval_ptr->flag & NODE_EVAL_USE_MATRIX )
	{
	    _SRMatrixCopy( rsmtx_ptr[bmbi_ptr->bg_number] ,
			   &eval_ptr->sr.matrix );
	}
	else
	{
	    SRMatrixSet( rsmtx_ptr[bmbi_ptr->bg_number],
			 eval_ptr->sr.sr.scale_x, eval_ptr->sr.sr.scale_y,
			 eval_ptr->sr.sr.angle );
	}
	if( eval_ptr->flag & NODE_EVAL_USE_REF )
	{
	    _RefStartCoordCopy( ref_ptr[bmbi_ptr->bg_number],
				&eval_ptr->coord.ref );
	}
	else
	{
		//  Calculate central coordinate.
		//  (vram_block_*) * 8 / 2
	    RefStartCoordSet( ref_ptr[bmbi_ptr->bg_number],
			      rsmtx_ptr[bmbi_ptr->bg_number],
		bm_vram_get_true_coord( vram_new_x ,
					map_vram_ptr->block_bit_x )
		+ (vram_block_width << 2),
		bm_vram_get_true_coord( vram_new_y ,
					map_vram_ptr->block_bit_y )
		+ (vram_block_height << 2) );
	}

    }

	//  Create BGCNT: Leave it for later
    bgRegDG[bmbi_ptr->bg_number] = bg_ptr->default_bgcnt;

}
//----------------------------------------------------------------------
u16 bm_vram_get_true_coord( s32 coord , u8 block_bit )
{
    s16 ret_value;
    register u16 width;

    width = _BitValue(block_bit+3);

    ret_value = (s16)(s32)(coord >> 8);
    ret_value &= (width-1);
    if( (coord < 0) && (ret_value != 0) )
    {
	ret_value = width - ret_value;
    }
    return (u16)ret_value;
}
//----------------------------------------------------------------------
//                 set_data_trans
//----------------------------------------------------------------------
static void bm_set_data_trans_no_check( bmDataTransParam* dtpm_ptr );
static void bm_set_data_trans( bmDataTransParam* dtpm_ptr )
{
    MapVram *map_vram_ptr;
    map_vram_ptr = dtpm_ptr->vram_ptr;

    if( map_vram_ptr->text_flag )
    {
	if( map_vram_ptr->block_bit_x == 5 )
	{
	    sdf = bm_set_data_trans_tx_w256;
	}
	else
	{
	    sdf = bm_set_data_trans_tx_w512;
	}
    }
    else
    {
	sdf = bm_set_data_trans_sr;
    }
    bm_set_data_trans_start( dtpm_ptr );
}

static void bm_set_data_trans_start( bmDataTransParam* dtpm_ptr )
{
    u16 src_bound,dest_bound;
    u16 tmp0 , tmp1 , tmp2 , tmp_size;

	//  Split transfer by srcX's value

    src_bound = dtpm_ptr->image_ptr->width;
    dest_bound = _BitValue(dtpm_ptr->vram_ptr->block_bit_x);
    if( dtpm_ptr->src.x + dtpm_ptr->size.w > src_bound )
    {

	    //  Set the transfer quantity for the left side of the screen --> recursive call

	tmp_size = dtpm_ptr->size.w;
	tmp0 = src_bound - dtpm_ptr->src.x;
	dtpm_ptr->size.w = tmp0;

	bm_set_data_trans_start( dtpm_ptr );

	    //  Set the transfer quantity (and other things) for the left side of the 
	    //  screen --> recursive call

	dtpm_ptr->size.w = tmp_size - tmp0;
	tmp1 = dtpm_ptr->src.x;
	dtpm_ptr->src.x = 0;
	tmp2 = dtpm_ptr->dest.x;
	dtpm_ptr->dest.x += tmp0;
	dtpm_ptr->dest.x &= (dest_bound-1);	// dest_bound is always power of 2

	bm_set_data_trans_start( dtpm_ptr );

	    //  Return value and end function

	dtpm_ptr->src.x = tmp1;
	dtpm_ptr->dest.x = tmp2;
	dtpm_ptr->size.w = tmp_size;

	return;
    }

	//  Split transfer by SrcY value

    src_bound = dtpm_ptr->image_ptr->height;
    dest_bound = _BitValue(dtpm_ptr->vram_ptr->block_bit_y);
    if( dtpm_ptr->src.y + dtpm_ptr->size.h > src_bound )
    {

	    //  Set the transfer quantity for the upper portion of the screen --> recursive call

	tmp_size = dtpm_ptr->size.h;
	tmp0 = src_bound - dtpm_ptr->src.y;
	dtpm_ptr->size.h = tmp0;

	bm_set_data_trans_start( dtpm_ptr );

	    //  Set the transfer quantity for the lower portion of the screen --> recursive call

	dtpm_ptr->size.h = tmp_size - tmp0;
	tmp1 = dtpm_ptr->src.y;
	dtpm_ptr->src.y = 0;
	tmp2 = dtpm_ptr->dest.y;
	dtpm_ptr->dest.y += tmp0;
	dtpm_ptr->dest.y &= (dest_bound-1);	// dest_bound is always power of 2

	bm_set_data_trans_start( dtpm_ptr );

	    //  Return value and end function

	dtpm_ptr->src.y = tmp1;
	dtpm_ptr->dest.y = tmp2;
	dtpm_ptr->size.h = tmp_size;

	return;
    }

	//  Split transfer by DestX value

    src_bound = dtpm_ptr->image_ptr->width;
    dest_bound = _BitValue(dtpm_ptr->vram_ptr->block_bit_x);
    if( dtpm_ptr->dest.x + dtpm_ptr->size.w > dest_bound )
    {

	    //  Set the transfer quantity for the left side of the screen --> recursive call

	tmp_size = dtpm_ptr->size.w;
	tmp0 = dest_bound - dtpm_ptr->dest.x;
	dtpm_ptr->size.w = tmp0;

	bm_set_data_trans_start( dtpm_ptr );

	    //  Set the transfer quantity (and other things) for the right side of the 
	    //  screen --> recursive call

	dtpm_ptr->size.w = tmp_size - tmp0;
	tmp1 = dtpm_ptr->src.x;
	dtpm_ptr->src.x += tmp0;
	tmp2 = dtpm_ptr->dest.x;
	dtpm_ptr->dest.x = 0;
	_wrapUpperLimit( dtpm_ptr->src.x , 0 , src_bound );

	bm_set_data_trans_start( dtpm_ptr );

	    //  Return the value and end function

	dtpm_ptr->src.x = tmp1;
	dtpm_ptr->dest.x = tmp2;
	dtpm_ptr->size.w = tmp_size;

	return;
    }

	//  Split transfer by Dest Y Value

    src_bound = dtpm_ptr->image_ptr->height;
    dest_bound = _BitValue(dtpm_ptr->vram_ptr->block_bit_y);
    if( dtpm_ptr->dest.y + dtpm_ptr->size.h > dest_bound )
    {

	    //  Set the transfer quantity for the upper portion of the screen --> recursive call

	tmp_size = dtpm_ptr->size.h;
	tmp0 = dest_bound - dtpm_ptr->dest.y;
	dtpm_ptr->size.h = tmp0;

	bm_set_data_trans_start( dtpm_ptr );

	    //  Set the transfer quantity (and other things) for the lower portion of the 
	    //  screen --> recursive call

	dtpm_ptr->size.h = tmp_size - tmp0;
	tmp1 = dtpm_ptr->src.y;
	dtpm_ptr->src.y += tmp0;
	tmp2 = dtpm_ptr->dest.y;
	dtpm_ptr->dest.y = 0;
	_wrapUpperLimit( dtpm_ptr->src.y,0,src_bound );

	bm_set_data_trans_start( dtpm_ptr );

	    //  Return value

	dtpm_ptr->src.y = tmp1;
	dtpm_ptr->dest.y = tmp2;
	dtpm_ptr->size.h = tmp_size;

	return;
    }

    (*sdf)( dtpm_ptr );
}
//----------------------------------------------------------------------
static void bm_set_data_trans_sr( bmDataTransParam* dtpm_ptr )
{
    register u32 src_address;
    register u32 dest_address;
    register u8  block_bit_x;

	//  Prepare to transfer

    block_bit_x = dtpm_ptr->vram_ptr->block_bit_x;
    src_address = ndimGetAddress( (u32)dtpm_ptr->image_ptr , 0 ,
					dtpm_ptr->src.x & -2 ,
					dtpm_ptr->src.y );
    dest_address = dtpm_ptr->vram_ptr->vram_address;
    dest_address += (dtpm_ptr->dest.x &-2)+(dtpm_ptr->dest.y << block_bit_x);

    dtSet( dest_address , _BitValue( block_bit_x ) ,
	   src_address , (u16)ndimGetPitch( (u32)dtpm_ptr->image_ptr ) ,
	   16 , ( dtpm_ptr->size.w + 1 ) >> 1 , dtpm_ptr->size.h );
}
//----------------------------------------------------------------------
static void bm_set_data_trans_tx_w256( bmDataTransParam* dtpm_ptr )
{
    register u32 src_address;
    register u32 dest_address;
    register u8  block_bit_x;

	//  Prepare to transfer

    block_bit_x = dtpm_ptr->vram_ptr->block_bit_x + 1;
    src_address = ndimGetAddress( (u32)dtpm_ptr->image_ptr , 0 ,
					dtpm_ptr->src.x ,
					dtpm_ptr->src.y );
    dest_address = dtpm_ptr->vram_ptr->vram_address;
    dest_address += (dtpm_ptr->dest.x << 1)+(dtpm_ptr->dest.y << block_bit_x);

    dtSet( dest_address , _BitValue(block_bit_x) ,
	   src_address , ndimGetPitch( (u32)dtpm_ptr->image_ptr ) ,
	   16 , dtpm_ptr->size.w , dtpm_ptr->size.h );
}
//----------------------------------------------------------------------
static void bm_set_data_trans_tx_w512( bmDataTransParam* dtpm_ptr )
{
    MapVram     bm_dt_mv;
    MapVram*	old_vram_ptr;
    u16 tmp_size;
    s16 tmp_coord;

    bm_dt_mv.block_bit_y = dtpm_ptr->vram_ptr->block_bit_y;;
    bm_dt_mv.text_flag = 1;

    bm_dt_mv.block_bit_x = 5;

    if( dtpm_ptr->dest.x >= 32 )
    {
	old_vram_ptr = dtpm_ptr->vram_ptr;

	dtpm_ptr->dest.x -= 32;
	bm_dt_mv.vram_address = old_vram_ptr->vram_address
				 + 0x800<<(dtpm_ptr->vram_ptr->block_bit_y-5);
	dtpm_ptr->vram_ptr = &bm_dt_mv;

	bm_set_data_trans_tx_w256( dtpm_ptr );

	dtpm_ptr->vram_ptr = old_vram_ptr;
	dtpm_ptr->dest.x += 32;

	return;
    }
    if( dtpm_ptr->dest.x + dtpm_ptr->size.w > 32 )
    {
	old_vram_ptr = dtpm_ptr->vram_ptr;

	tmp_size = dtpm_ptr->size.w;
	dtpm_ptr->size.w = 32 - dtpm_ptr->dest.x;
	bm_dt_mv.vram_address = old_vram_ptr->vram_address;
	dtpm_ptr->vram_ptr = &bm_dt_mv;

	bm_set_data_trans_tx_w256( dtpm_ptr );

	tmp_coord = dtpm_ptr->src.x;
	dtpm_ptr->src.x += dtpm_ptr->size.w;
	dtpm_ptr->size.w = tmp_size - dtpm_ptr->size.w;
	dtpm_ptr->src.x += (32 - dtpm_ptr->dest.x);

	dtpm_ptr->dest.x = 0;
	bm_dt_mv.vram_address += 0x800<<(dtpm_ptr->vram_ptr->block_bit_y-5);

	bm_set_data_trans_tx_w256( dtpm_ptr );

	dtpm_ptr->vram_ptr = old_vram_ptr;
	dtpm_ptr->src.x = tmp_coord;
	dtpm_ptr->dest.x = dtpm_ptr->size.w + 32 - tmp_size;
	dtpm_ptr->size.w = tmp_size;

	return;
    }
    bm_set_data_trans_tx_w256( dtpm_ptr );
}
//----------------------------------------------------------------------
void bmEval( void )
{
    dtSetDMA( REG_BG0CNT, (u32)BGREGDG_BEGIN, sizeof(bgRegDG), 3, 16 );
}
//----------------------------------------------------------------------


//
//
//

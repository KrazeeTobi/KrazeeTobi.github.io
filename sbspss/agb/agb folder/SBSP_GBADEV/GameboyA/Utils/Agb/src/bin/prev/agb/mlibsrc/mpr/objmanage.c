//======================================================
//    objmanage.c                          
//    Object management functions
//                                                     
//    Copyright (C) 1999, NINTENDO Co., Ltd.             
//======================================================

#include <agb.h>
#include <util.h>
#include "objmanage.h"
#include "object.h"
#include "node_object.h"
#include "datatrans.h"

//----------------------------------------------------------------------
#define	OMRSP_MAX_NUM	(32)
#define	OMOP_MAX_NUM	(128)
#define OMLIST_INVALID_NUMBER	(255)
//----------------------------------------------------------------------
typedef struct
{
    u16 oam0;
    u16 oam1;
    u16 oam2;
} omOamParam;

typedef SRMatrix omRotateScaleParam;

typedef struct
{
    u8  head;
    u8  tail;
} omObjectList;

typedef struct
{
    u8  data;
    u8  next;
} omObjectListNode;
//----------------------------------------------------------------------
	//  Sort System
u8  om_use_sort_key_flag;
u16 om_sort_key[OMOP_MAX_NUM];	//  The smaller the value is, the closer 
                                //  to the front it is to be displayed
u8  om_sort_number[OMOP_MAX_NUM];
//----------------------------------------------------------------------
	//  List System
u8  omObjLNCount;
omObjectList oml[16];
omObjectListNode omlnode[OMOP_MAX_NUM];
//----------------------------------------------------------------------
u16 omOamDG[512];	//  Duplication of oam
u8  omOPCount;
u8  omSRCount;
omOamParam omop[OMOP_MAX_NUM];
omRotateScaleParam omrsp[OMRSP_MAX_NUM];
//----------------------------------------------------------------------
u8 omSetMatrix( SRMatrix* src_ptr );
u8 omSetScaleRotate( s16 ScaleX , s16 ScaleY , u8 Rotation );
void omlistSet( u8 group , u8 set_num );
//----------------------------------------------------------------------
//	Initialize class
//----------------------------------------------------------------------
void omInit(u8 use_sort_key_flag)
{
    register u8 i;
    om_use_sort_key_flag = (use_sort_key_flag) ? 1 : 0;
    for( i=0 ; i<OMOP_MAX_NUM ; ++i )
    {
	om_sort_number[i] = i;
    }
    omClear();
}
//----------------------------------------------------------------------
//	Conduct initialization at every loop
//----------------------------------------------------------------------
static void omclear_odg( void );
static void omclear_list( void );
//----------------------------------------------------------------------
void omClear( void )
{
    register int i;
    omOPCount = 0;
    omSRCount = 0;
    omObjLNCount = 0;
    omclear_list();
    omclear_odg();
    if( om_use_sort_key_flag )
    {
	for( i=0 ; i<OMOP_MAX_NUM ; ++i )
	{
	    om_sort_key[OMOP_MAX_NUM] = 0xffff;
	}
    }
}
//----------------------------------------------------------------------
static void omclear_odg( void )
{
    int i;
    u16* clr_ptr = &omOamDG[0];
    for( i=0 ; i<32 ; ++i )
    {
	*clr_ptr++ = 0x0200;
	*clr_ptr++ = 0x0000;
	*clr_ptr++ = 0x0000;
	*clr_ptr++ = 0x0100;
	*clr_ptr++ = 0x0200;
	*clr_ptr++ = 0x0000;
	*clr_ptr++ = 0x0000;
	*clr_ptr++ = 0x0000;
	*clr_ptr++ = 0x0200;
	*clr_ptr++ = 0x0000;
	*clr_ptr++ = 0x0000;
	*clr_ptr++ = 0x0000;
	*clr_ptr++ = 0x0200;
	*clr_ptr++ = 0x0000;
	*clr_ptr++ = 0x0000;
	*clr_ptr++ = 0x0100;
    }
}
//----------------------------------------------------------------------
static void omclear_list( void )
{
    int i;
    for( i=0 ; i<16 ; ++i )
    {
	oml[i].head = OMLIST_INVALID_NUMBER;
    }
    omObjLNCount = 0;
}
//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void omInitObjectInstance( omObjectInstance* omoi_ptr , Object* obj_ptr )
{
    if( (NULL == omoi_ptr) || (NULL == obj_ptr) ) return;
    omoi_ptr->obj_ptr = obj_ptr;
    omoi_ptr->objNumber    = obj_ptr->objnumber;
    omoi_ptr->group        = obj_ptr->group;
    omoi_ptr->width        = 0;
    omoi_ptr->height       = 0;
    omoi_ptr->palette      = 0;
    omoi_ptr->mosaic       = obj_ptr->mosaic;
    omoi_ptr->flip         = 0;
    omoi_ptr->objmode      = obj_ptr->objmode;
}
//----------------------------------------------------------------------
void omCalcOffsetFromMatrix( s16* offset_x_ptr, s16* offset_y_ptr,
			     SRMatrix* mtx_ptr );
void omCalcOffsetFromScaleRotate( s16* offset_x_ptr, s16* offset_y_ptr,
				  s16 ScaleX, s16 ScaleY, u8 Rotation );
//----------------------------------------------------------------------
void omSetObject( nodeEvalStruct* evstr_ptr )
{
    omOamParam* omop_ptr;
    Object*	obj_ptr;
    nodeObject*	ndobj_ptr;
    register omObjectInstance* omoi_ptr;
    register u8  sr_number;
    register s16 scale_x,scale_y;
    register s32 offset_x , offset_y;
    register s32 x,y;
    register s16 width,height;
    register u8  rotation;

    if( (NULL == evstr_ptr) || (omOPCount >= OMOP_MAX_NUM) ) return;

    omoi_ptr = evstr_ptr->instance_ptr;
    obj_ptr = omoi_ptr->obj_ptr;
    ndobj_ptr = (nodeObject*)nodeGetAddressByID( obj_ptr->NodeID );


    omop_ptr = &omop[omOPCount];

    omop_ptr->oam0 = ndobj_ptr->default_OAM[0];
    omop_ptr->oam1 = ndobj_ptr->default_OAM[1];
    omop_ptr->oam2 = ndobj_ptr->default_OAM[2];

	//  Set character number

    omop_ptr->oam2 |= ((omoi_ptr->objNumber) & 0x03ff);
    sr_number = 255;

	//  When using scaling/rotation

    scale_x = evstr_ptr->sr.sr.scale_x;
    scale_y = evstr_ptr->sr.sr.scale_y;
    rotation = (u8)(u16)(evstr_ptr->sr.sr.angle & 0xff);
    if( (scale_x != 0x100)
     || (scale_y != 0x100)
     || (rotation != 0) )
    {
	if( evstr_ptr->flag & NODE_EVAL_USE_MATRIX )
	{
	    sr_number = omSetMatrix( &evstr_ptr->sr.matrix );
	    omCalcOffsetFromMatrix( &evstr_ptr->coord.coord.offset_x,
				    &evstr_ptr->coord.coord.offset_y,
				    &evstr_ptr->sr.matrix );
	}
	else
	{
	    if( omoi_ptr->flip & 1 ) scale_x = -scale_x;
	    if( omoi_ptr->flip & 2 ) scale_y = -scale_y;
	    sr_number = omSetScaleRotate( scale_x, scale_y, rotation );
	    omCalcOffsetFromScaleRotate( &evstr_ptr->coord.coord.offset_x,
					 &evstr_ptr->coord.coord.offset_y,
					 scale_x, scale_y, rotation );
	}
    }
    x = obj_ptr->x;
    x += (s32)evstr_ptr->coord.coord.move_x;
    x += (s32)evstr_ptr->coord.coord.offset_x;
    y = obj_ptr->y;
    y += (s32)evstr_ptr->coord.coord.move_y;
    y += (s32)evstr_ptr->coord.coord.offset_y;
    width = (s16)omoi_ptr->width << 8;
    height = (s16)omoi_ptr->height << 8;

	//  Do not display if object is out of screen area

    if( (x + (120<<8) + width < 0)
     || (x - (120<<8) - width > 0 ) ) return;
    if( (y + (80<<8) + height < 0)
     || (y - (80<<8) - height > 0 ) ) return;

	//  Use different processes when using and not using scaling/rotation.
	//  It is also necessary to move coordinate of object

    x += (120<<8);
    y += (80<<8);
    if( sr_number < OMRSP_MAX_NUM )
    {
	omop_ptr->oam1 &= ~( 0x001f << 9 );
	omop_ptr->oam1 |= ( ( ((u16)sr_number) & 0x001f ) << 9 );
	omop_ptr->oam0 |= 0x0300;	//  Turn on the expansion/reduction rotation
	omop_ptr->oam0 |= (u16)((s32)((y - height)>>8) & 0x00ff);
	omop_ptr->oam1 |= (u16)((s32)((x - width )>>8) & 0x01ff);
    }
    else
    {
	omop_ptr->oam0 &= ~0x0300;
	omop_ptr->oam1 &= ~0x3e00;
	omop_ptr->oam1 |= ( ( ((u16)omoi_ptr->flip) &0x0003 ) << 12 );
	omop_ptr->oam0 |= (u16)((s32)((y - (height>>1))>>8) & 0x00ff);
	omop_ptr->oam1 |= (u16)((s32)((x - (width >>1))>>8) & 0x01ff);
    }

	//  Set palette

    omop_ptr->oam2 |= ( ( ((u16)omoi_ptr->palette) & 0x000f ) << 12 );

	//  Set mosaic, priority and display mode

    if( omoi_ptr->mosaic ) omop_ptr->oam0 |= 0x1000;
    omop_ptr->oam2 |= ( ( ((u16)omoi_ptr->group) & 0x000c ) << 8 );
    omop_ptr->oam0 |= ( ( ((u16)omoi_ptr->objmode) & 0x0003 ) << 10 );

	//  Add to the object list

    omlistSet( omoi_ptr->group , omOPCount );

    ++omOPCount;
}
//----------------------------------------------------------------------
u8 omSetMatrix( SRMatrix* src_ptr )
{
    u8 ret_value = 255;
    s32 tmp_value;
    s32 set_value;
    s16 sin_value;
    s16 cos_value;
    omRotateScaleParam* omrsp_ptr;

    if( omSRCount >= OMRSP_MAX_NUM ) return ret_value;
    ret_value = omSRCount;
    omrsp_ptr = &omrsp[omSRCount++];

    _SRMatrixCopy( omrsp_ptr , src_ptr );

    return ret_value;
}
//----------------------------------------------------------------------
u8 omSetScaleRotate( s16 ScaleX , s16 ScaleY , u8 Rotation )
{
    u8 ret_value = 255;
    s32 tmp_value;
    s32 set_value;
    s16 sin_value;
    s16 cos_value;
    omRotateScaleParam* omrsp_ptr;

    if( (0 == ScaleX) || (0 == ScaleY ) ) return ret_value;
    if( omSRCount >= OMRSP_MAX_NUM ) return ret_value;
    ret_value = omSRCount;
    omrsp_ptr = &omrsp[omSRCount++];

    SRMatrixSet( omrsp_ptr , ScaleX , ScaleY , Rotation );

    return ret_value;
}
//----------------------------------------------------------------------
#define	OM_IGNORE_MIN	(0xff00)
#define	OM_IGNORE_MAX	(0x10100)
//----------------------------------------------------------------------
void omCalcOffsetFromMatrix( s16* offset_x_ptr, s16* offset_y_ptr,
			     SRMatrix* mtx_ptr )
{
    register s32 det;
    register s32 new_offset_x,new_offset_y;
    SRMatrix l_mtx;

    if( *offset_x_ptr == 0 && *offset_y_ptr == 0 ) return;

    det = (s32)mtx_ptr->dx * (s32)mtx_ptr->dmy
	- (s32)mtx_ptr->dmx * (s32)mtx_ptr->dy;

    if( OM_IGNORE_MIN <= det && det <= OM_IGNORE_MAX )
    {
	l_mtx.dx  =  mtx_ptr->dmy;
	l_mtx.dmx = -mtx_ptr->dmx;
	l_mtx.dy  = -mtx_ptr->dy;
	l_mtx.dmy =  mtx_ptr->dx;
    }
    else if( -OM_IGNORE_MAX <= det && det <= -OM_IGNORE_MIN )
    {
	l_mtx.dx  = -mtx_ptr->dmy;
	l_mtx.dmx =  mtx_ptr->dmx;
	l_mtx.dy  =  mtx_ptr->dy;
	l_mtx.dmy = -mtx_ptr->dx;
    }
    else
    {
	det = 0x10000 / (det >> 8);
	l_mtx.dx  = (s16)(s32)(((s32)( det * (s32)mtx_ptr->dmy)) >> 8);
	l_mtx.dmx = (s16)(s32)(((s32)(-det * (s32)mtx_ptr->dmx)) >> 8);
	l_mtx.dy  = (s16)(s32)(((s32)(-det * (s32)mtx_ptr->dy )) >> 8);
	l_mtx.dmy = (s16)(s32)(((s32)( det * (s32)mtx_ptr->dx )) >> 8);
    }

    new_offset_x = (s32)*offset_x_ptr * (s32)l_mtx.dx
		 + (s32)*offset_y_ptr * (s32)l_mtx.dmx;
    new_offset_y = (s32)*offset_x_ptr * (s32)l_mtx.dy
		 + (s32)*offset_y_ptr * (s32)l_mtx.dmy;

    *offset_x_ptr = (s16)(s32)(new_offset_x >> 8);
    *offset_y_ptr = (s16)(s32)(new_offset_y >> 8);
}
//----------------------------------------------------------------------
void omCalcOffsetFromScaleRotate( s16* offset_x_ptr, s16* offset_y_ptr,
				  s16 ScaleX, s16 ScaleY, u8 Rotation )
{
    register s32 tmp;
    register s32 new_offset_x,new_offset_y;
    register s16 sin,cos;
    SRMatrix l_mtx;

    if( *offset_x_ptr == 0 && *offset_y_ptr == 0 ) return;

    sin = Sin( Rotation );
    cos = Cos( Rotation );

    if( ScaleX == 0x100 )
    {
	l_mtx.dx =  cos;
	l_mtx.dy = -sin;
    }
    else if( ScaleX == -0x100 )
    {
	l_mtx.dx = -cos;
	l_mtx.dy =  sin;
    }
    else
    {
	tmp = 0x10000 / ScaleX;
	l_mtx.dx = ( cos * tmp ) >> 8;
	l_mtx.dy = (-sin * tmp ) >> 8;
    }
    if( ScaleY == 0x100 )
    {
	l_mtx.dmy = cos;
	l_mtx.dmx = sin;
    }
    else if( ScaleY == -0x100 )
    {
	l_mtx.dmy = -cos;
	l_mtx.dmx = -sin;
    }
    else
    {
	tmp = 0x10000 / ScaleY;
	l_mtx.dmy = (cos * tmp) >> 8;
	l_mtx.dmx = (sin * tmp) >> 8;
    }

    new_offset_x = (s32)*offset_x_ptr * (s32)l_mtx.dx
		 + (s32)*offset_y_ptr * (s32)l_mtx.dmx;
    new_offset_y = (s32)*offset_x_ptr * (s32)l_mtx.dy
		 + (s32)*offset_y_ptr * (s32)l_mtx.dmy;

    *offset_x_ptr = (s16)(s32)(new_offset_x >> 8);
    *offset_y_ptr = (s16)(s32)(new_offset_y >> 8);
}
//----------------------------------------------------------------------
void omlistSet( u8 group , u8 set_num )
{
    if( oml[group].head == OMLIST_INVALID_NUMBER )
    {
	oml[group].head = omObjLNCount;
    }
    else
    {
	omlnode[oml[group].tail].next = omObjLNCount;
    }
    oml[group].tail = omObjLNCount;
    omlnode[omObjLNCount].data = set_num;
    omlnode[omObjLNCount].next = OMLIST_INVALID_NUMBER;
    ++omObjLNCount;
}
//----------------------------------------------------------------------
//   After evaluation, arrange information, and summarize V Blank information.
//----------------------------------------------------------------------
static void omeval_rs_create_data( void );
static void omeval_create_data_from_list( void );
//----------------------------------------------------------------------
void omEval(void)
{
    omeval_create_data_from_list();
    omeval_rs_create_data();
    dtSetDMA( OAM , (u32)&omOamDG[0] , 0x400 , 3 , 32 );
}
//----------------------------------------------------------------------
static void omeval_rs_create_data( void )
{
    u16* set_ptr = &omOamDG[3];
    int i;
    for( i=0 ; i< omSRCount ; ++i )
    {
	*set_ptr = omrsp[i].dx;
	set_ptr += 4;
	*set_ptr = omrsp[i].dmx;
	set_ptr += 4;
	*set_ptr = omrsp[i].dy;
	set_ptr += 4;
	*set_ptr = omrsp[i].dmy;
	set_ptr += 4;
    }
}
//----------------------------------------------------------------------
static void omeval_create_data_from_list_no_sort( void );
static void omeval_create_data_from_list_with_sort( void );
//----------------------------------------------------------------------
static void omeval_create_data_from_list( void )
{
    register int i;

    register u16* oamdg_ptr;
    register u8*  sort_number_ptr;
    register omOamParam* omop_ptr;

    oamdg_ptr = &omOamDG[0];
    sort_number_ptr = om_sort_number;

    if( om_use_sort_key_flag )
    {
	omeval_create_data_from_list_with_sort();
    }
    else
    {
	omeval_create_data_from_list_no_sort();
    }
    for( i=0 ; i<omOPCount ; ++i )
    {
	omop_ptr = &omop[*sort_number_ptr++];
	*oamdg_ptr++ = omop_ptr->oam0;
	*oamdg_ptr++ = omop_ptr->oam1;
	*oamdg_ptr++ = omop_ptr->oam2;
	++oamdg_ptr;
    }
}
//----------------------------------------------------------------------
static void omeval_create_data_from_list_no_sort( void )
{
    register int i;
    register u8  num;
    register u8* sort_ptr;
    sort_ptr = om_sort_number;
    for( i=0 ; i<16 ; ++i )
    {
	num = oml[i].head;
	while( num != OMLIST_INVALID_NUMBER )
	{
	    *sort_ptr++ = num;
	    num = omlnode[num].next;
	}
    }
}
//----------------------------------------------------------------------
static void omeval_create_data_from_list_with_sort( void )
{
    register int i;
    register u8  num;		//  The number under evaluation
    register u8* sort_ptr;
    register u8* sort_tmp;
    register u8* sort_start;
    register u8* sort_end;
    register u16 sort_key;

    sort_end = om_sort_number;
    for( i=0 ; i<16 ; ++i )
    {
	num = oml[i].head;
	sort_start = sort_end;
	while( num != OMLIST_INVALID_NUMBER )
	{
		//  Use insert sort for sort
	    sort_key = om_sort_key[num];

		//  Retrieve insert location
	    for( sort_ptr=sort_start ; sort_ptr!=sort_end ; ++sort_ptr )
	    {
		if( sort_key < om_sort_key[*sort_ptr] ) break;
	    }
		//  Slide the area between the insert location and evaluated end backwards
	    sort_tmp = sort_end++;
	    for( sort_tmp = sort_end++ ; sort_tmp != sort_ptr ; )
	    {
		*sort_tmp-- = *(sort_tmp-1);
	    }
	    *sort_ptr = num;
	    num = omlnode[num].next;
	}
    }
}
//----------------------------------------------------------------------


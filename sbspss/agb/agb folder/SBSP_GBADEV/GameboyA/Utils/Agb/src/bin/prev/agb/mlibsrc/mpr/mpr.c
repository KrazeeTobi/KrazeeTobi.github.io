//======================================================
//    mpr.c                                      
//    Initialization of Node and V Blanc functions
//                                                     
//    Copyright (C) 1999, NINTENDO Co., Ltd.             
//======================================================

#include <agb.h>
#include "mpr.h"

//--------------------------------------------------------------
extern void ndhcEvaluate( u32 );
extern void bmClear( void );
extern void dtClear( void );
extern void objInit( void );
extern void omInit( u8 );
extern void chalInit( u16 , u16 );
//--------------------------------------------------------------
void mprInit( mprInitInfo* initinfo_ptr )
{
    objInit();
    dtClear();
    bmClear();
    omInit( initinfo_ptr->use_sort_key_flag );

    chalInit( initinfo_ptr->char_number_start,
		initinfo_ptr->char_number_end );
    ndhcEvaluate( initinfo_ptr->nodeheaderchunk_address );
}
//----------------------------------------------------------------------
void mprVBlankFnc( void )
{
    dtDo();
    dtClear();
    bmClear();
    omClear();
}
//----------------------------------------------------------------------

//
//
//

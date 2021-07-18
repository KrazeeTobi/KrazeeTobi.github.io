//======================================================
//    mpr.h                                      
//    Node and V Blank initialization functions
//                                                     
//    Copyright (C) 1999, NINTENDO Co., Ltd.             
//======================================================

#ifndef	__MPR_H__
#define	__MPR_H__

#include <agbtypes.h>

//----------------------------------------------------------------------
typedef struct
{
    u32 nodeheaderchunk_address;
    u16 char_number_start;
    u16 char_number_end;
    u8  use_sort_key_flag;
} mprInitInfo;

//----------------------------------------------------------------------
void mprInit( mprInitInfo* initinfo_ptr );
void mprVBlankFnc( void );
//----------------------------------------------------------------------

#endif	//  __MPR_H__
//
//
//

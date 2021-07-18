//======================================================
//    ch_alloc.h                                      
//    Character number management functions
//                                                     
//    Copyright (C) 1999, NINTENDO Co., Ltd.             
//======================================================

#ifndef	__CH_ALLOC_H__
#define	__CH_ALLOC_H__

#include <agbtypes.h>
//--------------------------------------------------------------
void chalInit(u16 start_number,u16 end_number);
u16  chalAlloc(u16 size,u8 boundary_bit);
u16  chalFree(u16 number);
//--------------------------------------------------------------

#endif	//  __CH_ALLOC_H__
//
//
//

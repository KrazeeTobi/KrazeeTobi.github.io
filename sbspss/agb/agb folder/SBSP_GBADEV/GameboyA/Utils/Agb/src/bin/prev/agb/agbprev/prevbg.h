//======================================================
//    prevbg.h                          
//    BG Process section of previewers.
//                                                     
//    Copyright (C) 1999, NINTENDO Co., Ltd.             
//======================================================

#ifndef	__PREVBG_H__
#define	__PREVBG_H__

#include <agb.h>
//----------------------------------------------------------------------
void pbgInit(void);
void pbgCreateBackground( u32 NodeID, u8 bgNumber, u8 Priority, u16 bgcnt );
void pbgControl(void);
void pbgEvaluate(void);
//----------------------------------------------------------------------

#endif	//  __PREVBG_H__
//
//
//

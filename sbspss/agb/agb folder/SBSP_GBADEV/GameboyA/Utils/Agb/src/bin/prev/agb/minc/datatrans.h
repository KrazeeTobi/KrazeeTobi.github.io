//======================================================
//    datatrans.h                                      
//    Data transfer management functions
//                                                     
//    Copyright (C) 1999, NINTENDO Co., Ltd.             
//======================================================

#ifndef	_DATATRANS_H_
#define	_DATATRANS_H_

#include <agb.h>

//--------------------------------------------------------------
void dtClear(void);
void dtSet(u32 DestAddress, u16 DestAddressStep,
		   u32 SrcAddress, u16 SrcAddressStep,
		   u8 OneDataBit, u8 OneDataNum, u16 StepNum );
void dtSetDMA(u32 DestAddress, u32 SrcAddress, u16 DMASize,
		      u8 DMANumber, u8 BitWidth );
void dtDo(void);
//--------------------------------------------------------------

#endif	// _USEDMA_H_

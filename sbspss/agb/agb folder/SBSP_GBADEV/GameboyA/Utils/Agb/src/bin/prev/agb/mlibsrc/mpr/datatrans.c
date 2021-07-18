//======================================================
//    datatrans.c                                      
//    Data transfer management functions
//                                                     
//    Copyright (C) 1999, NINTENDO Co., Ltd.             
//======================================================

#include <agb.h>
#include <util.h>
#include "datatrans.h"

#define	DTPARAM_MAX_NUM		(128)
#define	DTDMAPARAM_MAX_NUM	(128)

//--------------------------------------------------------------
typedef struct
{
    u32 DestAddress;
    u32 SrcAddress;
    u16 DataSize;
    u8  BitWidth;
    u8  DMANumber;
} dtDMAParam;

typedef struct
{
    u32 DestAddress;
    u16 DestStep;
    u32 SrcAddress;
    u16 SrcStep;
    u8  OneDataBit;
    u8  OneDataNum;
    u16 StepNum;
} dtParam;

const u32 dtDMAREGADDRESS[4] =
{
    REG_DMA0 ,
    REG_DMA1 ,
    REG_DMA2 ,
    REG_DMA3 ,
};
//--------------------------------------------------------------
u16 dtCount;
u16 dtDMACount;
dtParam dtpm[DTPARAM_MAX_NUM];
dtDMAParam dtdmapm[DTDMAPARAM_MAX_NUM];
//--------------------------------------------------------------
void dtDMADo(void);
void dtStepTransDo(void);
void dtOneStepTransDo( dtParam* dtpm_ptr );
void dtOneDMADo( dtDMAParam* dmapm_ptr );
//--------------------------------------------------------------
void dtClear(void)
{
    dtCount=0;
    dtDMACount = 0;
}
//--------------------------------------------------------------
void dtSet(u32 DestAddress , u16 DestAddressStep ,
	   u32 SrcAddress ,  u16 SrcAddressStep ,
	   u8 OneDataBit , u8 OneDataNum , u16 StepNum )
{
    if( dtCount >= DTPARAM_MAX_NUM ) return;
    dtpm[dtCount].DestAddress = DestAddress;
    dtpm[dtCount].DestStep    = DestAddressStep;
    dtpm[dtCount].SrcAddress  = SrcAddress;
    dtpm[dtCount].SrcStep     = SrcAddressStep;
    dtpm[dtCount].OneDataBit  = OneDataBit;
    dtpm[dtCount].OneDataNum  = OneDataNum;
    dtpm[dtCount].StepNum     = StepNum;
    ++dtCount;
}
//--------------------------------------------------------------
void dtSetDMA(u32 DestAddress , u32 SrcAddress , u16 DMASize ,
	      u8 DMANumber , u8 BitWidth )
{
    if( dtDMACount >= DTDMAPARAM_MAX_NUM ) return;
    dtdmapm[dtDMACount].DestAddress = DestAddress;
    dtdmapm[dtDMACount].SrcAddress = SrcAddress;
    dtdmapm[dtDMACount].DataSize = DMASize / (BitWidth/8);
    dtdmapm[dtDMACount].DMANumber = DMANumber;
    dtdmapm[dtDMACount].BitWidth = BitWidth;
    ++dtDMACount;
}
//--------------------------------------------------------------
void dtDo(void)
{
    dtDMADo();
    dtStepTransDo();
}
//--------------------------------------------------------------
//--------------------------------------------------------------
void dtStepTransDo(void)
{
    u16 loop;
    for( loop=0 ; loop<dtCount ; ++loop )
    {
	dtOneStepTransDo( &dtpm[loop] );
    }
}
//--------------------------------------------------------------
void dtOneStepTransDo( dtParam* dtpm_ptr )
{
    u16 loop;
    u32 onetransloop;
    u32 src_address;
    u32 dest_address;
    dest_address = dtpm_ptr->DestAddress;
    src_address  = dtpm_ptr->SrcAddress;
    for( loop=0 ; loop<dtpm_ptr->StepNum ; ++loop )
    {
	switch( dtpm_ptr->OneDataBit )
	{
	    case 8 :
		for( onetransloop=0 ; onetransloop<dtpm_ptr->OneDataNum ;
		     ++onetransloop )
		{
		    *(((vu8*)dest_address) + onetransloop) =
			*(((vu8*)src_address) + onetransloop);
		}
		break;
	    case 16 :
		for( onetransloop=0 ; onetransloop<dtpm_ptr->OneDataNum ;
		     ++onetransloop )
		{
		    *(((vu16*)dest_address) + onetransloop) =
			*(((vu16*)src_address) + onetransloop);
		}
		break;
	    case 32 :
		for( onetransloop=0 ; onetransloop<dtpm_ptr->OneDataNum ;
		     ++onetransloop )
		{
		    *(((vu32*)dest_address) + onetransloop) =
			*(((vu32*)src_address) + onetransloop);
		}
		break;
	}
	dest_address += (u32)dtpm_ptr->DestStep;
	src_address  += (u32)dtpm_ptr->SrcStep;
    }
}
//--------------------------------------------------------------
void dtDMADo(void)
{
    u16 loop;
    char str[8];
    dtDMAParam *dmapm_ptr = &dtdmapm[0];
    for( loop=0 ; loop<dtDMACount ; ++loop )
    {
	dtOneDMADo( dmapm_ptr++ );
    }
}
//--------------------------------------------------------------
void dtOneDMADo( dtDMAParam* dmapm_ptr )
{
    vu32* dma_reg_ptr;
    u32 DMAState;
    if( NULL != dmapm_ptr )
    {
	dma_reg_ptr = (vu32*)dtDMAREGADDRESS[dmapm_ptr->DMANumber];
	DMAState = DMA_ENABLE | DMA_TIMMING_IMM |
		   DMA_SRC_INC | DMA_DEST_INC;
	if( dmapm_ptr->BitWidth == 32 )
	    DMAState |= DMA_32BIT_BUS;
	DMAState |= (u32)dmapm_ptr->DataSize;
	*dma_reg_ptr++ = dmapm_ptr->SrcAddress;
	*dma_reg_ptr++ = dmapm_ptr->DestAddress;
	*dma_reg_ptr   = DMAState;
    }
}
//--------------------------------------------------------------

//======================================================
//    oam_proc.c
//    Sample YoshiOAM Process Routine 
//
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================
//#define CODE32

#include "agb.h"
#include "yos_main.h"
#include "yos_main.ext"
#include "yos_type.h"
#include "oam_proc.h"

s8		OamList[OAM_LIST_MAX];//Oam List 
u8		oamNode_end;
u8		oamWaitFlg;
OamListNode	OamNode[OAM_LIST_NODE_MAX];//Oam List Node 
AffineParamWork affineWork[AFFINE_WORK_MAX]; //Affine Parameter Work  

//DMA
DmaReqDat dmaReqArray[DMA_REQ_DAT_MAX];
u16 dmaReqNum;

AnmWork         anmWork[ANM_WORK_MAX];       //Animation Work 

////////////////////////////////////////////////////////////////////////////
//Create OamBak from List
void make_OamBuf(void)
{
	u8 i,oam_num;
	s8 node_num;
	OamData *pOam;
	oamWaitFlg = 1;
	
	oam_num = 0;
	for(i=0; i<OAM_LIST_MAX; i++)
	{
		node_num = OamList[i];
		while(node_num >= 0)
		{
			gMain.OamBuf[oam_num] = OamNode[node_num].OamDat;
			oam_num++;
			//Next Node
			node_num = OamNode[node_num].nextPos;
		}
	}
	for(i=oam_num; i<128; i++)
	{
		gMain.OamBuf[i].AffineMode=2;
	}
	for(i=0; i<32; i++)
	{
		pOam = &gMain.OamBuf[i<<2];
		pOam->AffineParam = affineWork[i].param[0];
		pOam++;
		pOam->AffineParam = affineWork[i].param[1];
		pOam++;
		pOam->AffineParam = affineWork[i].param[2];
		pOam++;
		pOam->AffineParam = affineWork[i].param[3];
//		gMain.OamBuf[i*4  ].AffineParam = affineWork[i].param[0];
//		gMain.OamBuf[i*4+1].AffineParam = affineWork[i].param[1];
//		gMain.OamBuf[i*4+2].AffineParam = affineWork[i].param[2];
//		gMain.OamBuf[i*4+3].AffineParam = affineWork[i].param[3];
	}
	oamWaitFlg=0;
}

////////////////////////////////////////////////////////////////////////////
//Clear List
void clear_OamList(void)
{
	u8 i;
	
	for(i=0; i<OAM_LIST_MAX; i++)OamList[i] = -1;
	oamNode_end = 0;
}

////////////////////////////////////////////////////////////////////////////
//Add to the head of List
//Add Node to ListNum List 
void add_OamList(u8 ListNum, s8 OamNodeNum)
{
	OamNode[OamNodeNum].nextPos = OamList[ListNum];
	OamList[ListNum] = OamNodeNum;
}

////////////////////////////////////////////////////////////////////////////
//Add Node to ListNum List and Return the Pointer
OamData *new_OamData(u8 ListNum)
{
	if(oamNode_end >= OAM_LIST_NODE_MAX)return 0;//Prevent Overflow
	add_OamList(ListNum, oamNode_end);//Add
	oamNode_end++;
	return &OamNode[oamNode_end-1].OamDat;
}

////////////////////////////////////////////////////////////////////////////
//Set to DMA Transfer Request Array
//dest is at VRAM Position (Character Number)
void dmaReqSet(u8 *addr_from, u16 dest, u16 size)
{
	if(dmaReqNum >= DMA_REQ_DAT_MAX)return;//Prevent Array Overflow
	
	dmaReqArray[dmaReqNum].addr_from = addr_from;
	dmaReqArray[dmaReqNum].addr_dest = (u8*)OBJ_MODE0_VRAM + dest * (32);
	dmaReqArray[dmaReqNum].size      = size * (32 * 2);//256 Colors
	dmaReqNum++;
}

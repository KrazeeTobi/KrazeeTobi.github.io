//======================================================
//    oam_proc.h
//    Sample Yoshi OAM Process Routine Header 
//
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#ifndef OAM_PROC_H
#define OAM_PROC_H

//OamList
typedef struct OamListNode_tag
{
	OamData OamDat;
	s8	nextPos;//Number of Next Node
	u8 pad;
}OamListNode;
//Affine Parameter Work Structure 
typedef struct AffineParamWork_tag
{
	xyPos zoom;
	s16 rot;//Rotation Angle (0x100 = 360degrees)
	s16 param[4];//AffineParam
	s16 work0;
	u8  Hflip:1;//
	u8 pad;
}AffineParamWork;

//Structure for DMA Transfer
//Used when Rewrite Animation
typedef struct DmaReqDat_tag
{
	u8 *addr_from;	//Address from which it is transfered
	u8 *addr_dest;	//Address to which it is transfered
	u16 size;		//Transfer Size
}DmaReqDat;
//Animation Table Structure 
typedef struct AnmTbl_tag
{
	u8 anm_ptn;		//Obtain Picture Data with this 0-255
	s8 time;		//Duration Period  Return to the Start at -1
	s8 dir;			//Direction
}AnmTbl;

//Animation Work Structure 
typedef struct AnmWork_tag
{
	AnmTbl *pTbl;	//Pointer for Current AnmTbl
	AnmTbl **ppTbl;	//Pointer for AnmTbl Array 
	u8 **pPixTbl;	//Pointer for Array of Pixel Data that is to be transferred
	s16 chr;		//(Character Conversion)VRAM Position(0-)
	s8 flg;			//Flag to Indicate Changes(1:Update 0:No Update -1:Inactive)
	s8 anm_ptn;		//Pattern which is currently on VRAM
	s8 time;		//Until becomes 0 (Fix if -1)
	s8 size;		//Number of Characters that are to be transferred(with 16 colors)
}AnmWork;

//Animation Work Initialization Structure 
typedef struct AnmInfo_tag
{
	u8 **pPixTbl;	//Image Data Table Pointer 
	AnmTbl **ppTbl;	//Animation Data Table Pointer 
	s16 chr;		//VRAM Position (Character Unit)
	s8 size;		//Number of Characters that are to be transferred(with 16colors)
}AnmInfo;

#define OAM_LIST_MAX         (10)		//Oam List Number(At Priority Stage)
#define OAM_LIST_NODE_MAX    (128)		//Number of Node
#define AFFINE_WORK_MAX (32)//Number of Affine Parameter Work
#define DMA_REQ_DAT_MAX (64)//Size of the Array that is to be transferred using DMA
#define ANM_WORK_MAX    (64)
extern s8		OamList[OAM_LIST_MAX];//0am List 
extern u8		oamNode_end;
extern u8		oamWaitFlg;
extern OamListNode	OamNode[OAM_LIST_NODE_MAX];//0am List Node 
extern AffineParamWork affineWork[AFFINE_WORK_MAX]; //Work of Affine Parameter

void make_OamBuf(void);		//Create OamBuf from List
void clear_OamList(void);	//Clear List
void add_OamList(u8 ListNum, s8 OamNodeNum);//Add to the head of List
OamData *new_OamData(u8 ListNum);

//DMA
extern DmaReqDat dmaReqArray[DMA_REQ_DAT_MAX];
extern u16 dmaReqNum;

extern AnmWork         anmWork[ANM_WORK_MAX];       //Animation Work 
void dmaReqSet(u8 *addr_from, u16 dest, u16 size);//Add to Transfer Request Array of DMA

#endif //OAM_PROC_H

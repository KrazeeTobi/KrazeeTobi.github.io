/********************************************************************/
/*      bg.h                                                        */
/*          BG Control Personal Library Header                      */
/*                                                                  */
/*              Copyright (C) 1999-2001 NINTENDO Co.,Ltd.           */
/********************************************************************/
#ifndef	__BG_PUBLIC_H__
#define	__BG_PUBLIC_H__

#include <AgbTypes.h>
#include "myTypes.h"

// struct declaration-----------------------------------
typedef struct pos_2dTag {
	s32		x;
	s32		y;
}pos_2d;

// function's prototype declaration---------------------
/*******************
 Initialize
*******************/
extern void InitBg();
/*******************
 BgMode
*******************/
extern void SetBgMode(u16 modeNo);
extern u16	GetBgMode();
/*******************
 BgxBuff
*******************/
extern void	SetBgxBuffer(u8 bgNo,u16 *buff,u32 size);
extern void	SetBgxBuffRenewal(u8 bgNo,bool renewal);
extern buffer *GetBgxBuffer(u8 bgNo);
extern u16 	*GetBgxBuffPointer(u8 bgNo);
extern u32	GetBgxBuffSize(u8 bgNo);
extern void	ClearBgxBuffer(u8 bgNo,u16 clearCode);
extern void	DmaBgxBuffer(u8 bgNo);
extern void	DmaAllBgxBuffer();
extern void	TrmScreenDataToBgxBufferByFunc(u8 bgNo,void (*SetBgSc)(u16 *pBuff,u32 size));
extern void	TrmScreenDataToBgxBuffer(u8 bgNo,const u16 *screen,u32 size);
extern void	ClearBgxScreenRect(u8 bgNo,u16 topPos,u8 height,u8 width);
/*******************
 FlameBuff
*******************/
extern void	SetFlameBuff(u8 flameNo,u16 *flameBuff);
extern u16	*GetFlameBuff(u8 flameNo);
/*******************
 ScreenSize
*******************/
extern void	SetScreenSize(u8 bgNo,u16 screenSize);
extern u16	GetScreenSize(u8 bgNo);
/*******************
 ScreenBase Block & Address
*******************/
extern void	SetBgxScreenBaseBlock(u8 bgNo,u16 baseBlock);
extern u16	GetBgxScreenBaseBlock(u8 bgNo);
extern void	SetBgxScreenBaseAdr(u8 bgNo,u32 baseAdr);
extern u32	GetBgxScreenBaseAdr(u8 bgNo);
/*******************
 Mosaic
*******************/
extern void	SetMosaicEnable(u8 tgtBg);
extern void	SetBgxMosaicEnable(u8 bgNo,u16 enable);
extern u16	GetBgxMosaicEnable(u8 bgNo);
/*******************
 ColorMode
*******************/
extern void	SetBgxColorMode(u8 bgNo,u16 colorMode);
extern u16	GetBgxColorMode(u8 bgNo);
/*******************
 CharBase Block & Address
*******************/
extern void	SetBgxCharBaseBlock(u8 bgNo,u16 baseBlock);
extern u16	GetBgxCharBaseBlock(u8 bgNo);
extern void	SetBgxCharBaseAdr(u8 bgNo,u32 baseAdr);
extern u32	GetBgxCharBaseAdr(u8 bgNo);
/*******************
 Priority
*******************/
extern void	SetBgxPriority(u8 bgNo,u16 priority);
extern u16	GetBgxPriority(u8 bgNo);
/*******************
 AreaOver
*******************/
extern void	SetBgxAreaOver(u8 bgNo,u16 area);
extern u16	GetBgxAreaOver(u8 bgNo);
/*******************
 Scroll
*******************/
extern void	SetBgxPosX(u8 bgNo,u16 pos_x);
extern u16	GetBgxPosX(u8 bgNo);
extern void	RelativeScrollBgxPosX(u8 bgNo,u16 relative_x);
extern void	SetBgxPosY(u8 bgNo,u16 pos_y);
extern u16	GetBgxPosY(u8 bgNo);
extern void	RelativeScrollBgxPosY(u8 bgNo,u16 relative_y);
/*==============================================================

	Rotation/Scaling BG Control Functions

==============================================================*/
extern void	SetRbgxHVflip(u8 bgNo,bool hFlip,bool vFlip);
extern void	CalcRbgxAffineValue(u8 bgNo,s16 magnifyX,s16 magnifyY,u8 theta);
extern void	CalcRbgxReferenceStartPos(u8 bgNo,pos_2d center,pos_2d view);
extern void	RotateZoomRbgx(u8 bgNo);
extern void	RevBgxAffineValue(u8 bgNo,u8 no);
/*==============================================================

	BG Draw Functions

==============================================================*/
/***********************
	Paragraph(line feed)
***********************/
extern void	SetParagraph(bool enable,u8 length,u16 topPos);
/***********************
	Draw Character on BG
***********************/
extern u16	DrawAsciiCharOnBgx(u8 bgNo,u16 topPos,u16 attr,const u8 *c,u8 length);
extern u16	DrawAsciiStringOnBgx(u8 bgNo,u16 topPos,u16 attr,const u8 *str);
extern u16	DrawHexOnBgx(u8 bgNo,u16 topPos,u16 attr,const void *value,u8 length);
extern u16	DrawHalfByteHexOnBgx(u8 bgNo,u16 topPos,u16 attr,const void *value,u8 selHiLo);
extern u16	DrawUIntOnBgx(u8 bgNo,u16 topPos,u16 attr,const void *data,u8 length,u8 size);
extern u16	DrawSIntOnBgx(u8 bgNo,u16 topPos,u16 attr,const void *data,u8 length,u8 size);

#endif		// __BG_PUBLIC_H__

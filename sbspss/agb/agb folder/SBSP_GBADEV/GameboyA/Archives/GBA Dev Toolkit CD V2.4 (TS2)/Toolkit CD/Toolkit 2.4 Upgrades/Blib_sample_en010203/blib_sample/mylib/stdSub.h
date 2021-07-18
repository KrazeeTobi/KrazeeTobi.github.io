/********************************************************************/
/*      stdSub.h                                                    */
/*          Standard Routine Personal Library Header                */
/*                                                                  */
/*              Copyright (C) 1999-2001 NINTENDO Co.,Ltd.           */
/********************************************************************/
#ifndef	__STDSUB_PUBLIC_H__
#define	__STDSUB_PUBLIC_H__

#include <AgbTypes.h>
#include "myTypes.h"
#include "obj.h"

// struct declaration-----------------------------------
typedef struct keyStatusTag
{
	u16		Cont;
	u16		Trg;
	u16		Rapid;
	u16		rapidFlag;
	u16		intervalCount;
	u8		intervalGear;
	u8		interval[4];
	u8		count[10];
	bool	enable;
}keyStatus;

typedef struct setFuncTableTag
{
	const void 	*define;
	u8			(*func)(u16 *);
}setFuncTable;

// InputHexData
typedef struct inputHexDefineTag
{
	u32		*value;
	u8		*unit;
	u32		max;
	u32		min;
	u16		pos;
	u16		attr;
	u8		size;
	u8		bgNo;
	u8		numMax;
	u8		numMin;
	bool	range;
	bool	finish;
}inputHexDef;

// SelectStrings
typedef struct selStrDefineTag
{
	const u8	*const *str;
	u8			*value;
	u16			pos;
	u16			attr;
	u8			count;
	u8			bgNo;
}selStrDef;

// ToggleSwitch
typedef struct toggleSwDefineTag
{
	// toggle switch side
	const csrDefine	*oldCsr;
	const csrDefine	*newCsr;
	u8			*sw;
	u16			posOfs;
	u16			charCode;
	u16			attr;
	u8			bgNo;
	// slave strings side
	bool		strOn;
	u16			strPos;
	u16			strAttr;
	u8			strBgNo;
}toggleSwDef;

//------------------------------------------------------
extern keyStatus key;

// function's prototype declaration---------------------
extern void WaitHblank();
extern void WaitPressKey(u8 bgNo,u16 pos);
/***********************
	Read Key
***********************/
extern void SetKeyRapidEnable(bool enable);
extern void AddRapidKey(u16 rapidKey);
extern void SubRapidKey(u16 rapidOffkey);
extern void SetKeyRapid(u16 rapidFlag,u8 interval1,u8 interval2,u8 interval3);
extern void ReadKeyPlus();
extern void ReadKey();
/***********************
	control Task
***********************/
void ChangeTask(u8 c_p,void (*init)(u8),void (*func)());
void ExecuteTask();
/***********************
	Calc Affine
***********************/
extern void CalcAffineValue(s16 magnifyX,s16 magnifyY,u8 theta,affine *af);
/***********************
	Clear **RAM
***********************/
extern u8 ClearWram(u32 offsetAddress,u32 clearSize,u16 clearCode);
extern u8 ClearVram(u32 offsetAddress,u32 clearSize,u16 clearCode);
extern u8 ClearOam(u32 offsetAddress,u32 clearSize,u32 clearCode);
extern u8 ClearPalette(selObjBg objBg,u16 clearCode);
/***********************
	Transmit to RAM
***********************/
extern u8 TrmCharData(selObjBg objBg,const u16 *pSrc,u32 size,u8 charBaseBlock);
extern u8 TrmPaletteData(selObjBg objBg,const u16 *pSrc,u16 plttNo,u16 plttCount);
/***********************
	Input Data by Key
***********************/
extern void SetInputHexData(const inputHexDef *define);
extern u8	InputHexData(u16 *setFlag);
extern u8	SelectStrings(u16 *setFlag);
extern void DrawNowSelectString(u8 stanby,const selStrDef *sel);
extern u8	ToggleSwitch(u16 *setFlag);
extern void DrawNowToggleSwitchChar(u8 stanby,const toggleSwDef *tog);
extern void DrawNowToggleSwitchString(u8 stanby,const toggleSwDef *tog);
extern u8	ClearNowAllSetting(u16 *setFlag);
extern void InitSetFunc(u8 nowNum,const setFuncTable *setFt);
extern void DrawNowAllSetting(u16 setFlag,const setFuncTable *setting);

#endif			// __STDSUB_PUBLIC_H__

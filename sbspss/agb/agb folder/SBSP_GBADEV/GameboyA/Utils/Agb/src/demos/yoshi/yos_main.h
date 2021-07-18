//======================================================
//    yos_main.h
//    Sample Yoshi Main Routine Header
//
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#ifndef YOS_MAIN_H
#define YOS_MAIN_H

#define ENABLE_PREFETCH  //Enable pre-fetch
#define USE_HDMA         //Use H Blank DMA (with title)

#define SOUND_ON         //Sound On
#ifdef SOUND_ON          //Only when sound is on
#define BGM_ON           //BGM is ON
//#define USE_SOUND_SYSCALL //Uses sound system call
#endif//SOUND_ON

enum
{
	PROC_0,
	PROC_GAME,
};
typedef void (*IntrFuncp)(void);

typedef struct gMainVal_tag
{
	OamData	OamBuf[128];			// OAM 
	u32		IntrMainBuf[0x200];		// Buffer for Interrupt Main Routine
	u32		main_timer;
	void	(*pVBlankFunc)(void);
	vu16	IntrCheck;				// Interrupt check
	u16		Cont, Trg;				// Key Input
	u8		proc_num;
	u8		main_status;
	u8		pad[2];
}gMainVal;

extern void IntrDummy(void);

#endif//YOS_MAIN_H

/********************************************************************/
/*      myTypes.h                                                   */
/*           Personal LibraryType Definition Data                   */
/*                                                                  */
/*              Copyright (C) 1999-2001 NINTENDO Co.,Ltd.           */
/********************************************************************/
#ifndef	__MYTYPES_H__
#define	__MYTYPES_H__

#include <AgbTypes.h>

#define NULL			0x00000000

#define BG_PLTT_WHITE	( 8<<BG_SC_PLTT_SHIFT)
#define	BG_PLTT_ORANGE	( 9<<BG_SC_PLTT_SHIFT)
#define BG_PLTT_RED		(10<<BG_SC_PLTT_SHIFT)
#define BG_PLTT_BLUE	(11<<BG_SC_PLTT_SHIFT)
#define BG_PLTT_YELLOW	(12<<BG_SC_PLTT_SHIFT)
#define BG_PLTT_GREEN	(13<<BG_SC_PLTT_SHIFT)
#define BG_PLTT_PURPLE	(14<<BG_SC_PLTT_SHIFT)

#define OBJ_PLTT_WHITE	  8
#define	OBJ_PLTT_ORANGE	  9
#define OBJ_PLTT_RED	 10
#define OBJ_PLTT_BLUE	 11
#define OBJ_PLTT_YELLOW	 12
#define OBJ_PLTT_GREEN	 13
#define OBJ_PLTT_PURPLE	 14

#define false			0
#define	true			1

// AGING STATE
#define AGING_STATE_INITIAL		0
#define AGING_STATE_EXECUTE		1
#define AGING_STATE_COMPLETE	2
#define AGING_STATE_BREAK		3
#define AGING_STATE_ERROR		4
// DEVICE
#define	DEVICE_DACS				0
#define	DEVICE_EEPROM			1
#define	DEVICE_FLASH			2
#define	DEVICE_SRAM				3
#define	DEVICE_EMPTY			7

// common
typedef u8 bool;

typedef struct funcTableTag
{
	void (*initFunc)(u8 c_p);
	void (*func)();
}funcTable;


// bg.h, bg_private.h, obj.h
typedef struct bufferTag {
	u16 	*p;
	u32 	size;
	bool	renewal;
}buffer;

// bg.h, bg_private.h, obj.h, stdSub.h
typedef struct magnifyTag {
	s16		x;
	s16		y;
}mag;

typedef struct affineTag {
	s16		a;
	s16		b;
	s16		c;
	s16		d;
}affine;

// display.h, stdSub.h
typedef enum selObjBgTag {
	selBg,
	selObj
} selObjBg;

typedef struct agingStateTag {
	u32 count;
	u8  state;
	u8	now_wrpatt;
	u8	type;
}agingState;

typedef struct chipIDTag {
	u8	vendor;
	u8	device;
} chipID;

typedef enum haltFlagTag {
	halt,
	active
} haltFlag;

#endif		// __MYTYPES_H__

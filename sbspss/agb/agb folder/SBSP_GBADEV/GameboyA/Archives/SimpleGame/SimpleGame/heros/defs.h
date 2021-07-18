/*============================================================================
		Nintendo of America Developer Support
		Scott Perras
============================================================================*/
#ifndef _DEFS_H
#define _DEFS_H

/*-------------------------- defines ------------------------------ */
#define PAL_16_SIZE			(16*2)
#define PAL_256_SIZE		(256*2)

/*-------------------------- structs ------------------------------ */
typedef unsigned short u_short;
typedef unsigned long u_long;
typedef unsigned char u_char;
typedef signed long BOOL;

//typedef	enum _bool {FALSE=0,TRUE}	BOOL;
//enum {NO =0,YES};
//enum {OFF=0,ON};

typedef struct _xyPos
{
	s32 x;
	s32 y;
} xyPos;

typedef struct _u8xyPos
{
	u8 x;
	u8 y;
} U8_XY_POS;

typedef struct _s16xyPos
{
	s16 x;
	s16 y;
} s16xyPos;

typedef struct _long2 {
  long x;
  long y;
} LONG2;

typedef struct _space3d {
  LONG2 pos;
//	LONG2 rot;
  LONG2 vel;
} SPACE3D;

typedef struct _simple_actor
{
	SPACE3D s3d;

	short status;

	short oamIndex;
	short animTick;
	short animFrame;
	short animIndex;

	short pad;

} SIMPLE_ACTOR;

typedef union {
	float *f;
	long  *l;
	short *s;
	char  *c;
	int    i;
	void  *v;
	unsigned long  *ul;
	unsigned short *us;
	unsigned char  *uc;
	unsigned int    ui;
} GENPTR;

/*-------------------------- external vars -------------------------*/

/*-------------------------- external functs -----------------------*/

/*-------------------------- end -----------------------------------*/
#endif // _DEFS_H


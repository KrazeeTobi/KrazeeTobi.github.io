/*============================================================================
		Nintendo of America Developer Support
		Scott Perras
============================================================================*/
#ifndef _DEFS_H
#define _DEFS_H

/*-------------------------- defines ------------------------------ */
#define COLOR_16_PAL_SIZE			(16*2)
#define COLOR_256_PAL_SIZE		(256*2)

/*-------------------------- structs ------------------------------ */
typedef unsigned short 	u_short;
typedef unsigned long 	u_long;
typedef unsigned char 	u_char;
typedef signed long 		BOOL;

typedef struct _xypos
{
	s32 x;
	s32 y;
} XY_POS;


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

#endif // _DEFS_H


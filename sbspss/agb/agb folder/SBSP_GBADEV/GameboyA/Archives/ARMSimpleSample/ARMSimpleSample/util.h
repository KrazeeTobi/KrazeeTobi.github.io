/*============================================================================
		Nintendo of America Developer Support
		Scott Perras
============================================================================*/
#ifndef _UTIL_H
#define _UTIL_H

/*-------------------------- defines ------------------------------ */
#define MAX_PRINT_BUF_SIZE 	(256)
#define MAX_DEBUG_FLAGS			(5)

#define	_Sin( a ) (sin_cos_table[(a)])
#define	_Cos( a ) (sin_cos_table[(a)+64])

#define FIXED_POINT_SHIFT (12)

#define FIXED_PT_UP(val) (val << FIXED_POINT_SHIFT)
#define FIXED_PT_DN(val) (val >> FIXED_POINT_SHIFT)


/*-------------------------- structs ------------------------------ */

/*-------------------------- external vars -------------------------*/
extern const s16 sin_cos_table[256+64];

extern char global_printBuffer[MAX_PRINT_BUF_SIZE];
extern long debugFlags[MAX_DEBUG_FLAGS];
/*-------------------------- external functs -----------------------*/
extern void (*debugPrint)(unsigned char *buf);

extern void clearRamAll(void);
extern void clearWorkRam(void);
extern void clearGraphicRam(void);
extern void clearVram(void);
extern void clearOamRam(void);
extern void clearPaletteRam(void);

extern void setLCDOn(void);
extern void setLCDOff(void);

extern void setLCDOn_WaitVBlank(void);
extern void setLCDOff_WaitVBlank(void);

extern void fadeOut(u_long fadeMask);
extern void fadeIn(u_long fadeMask);

extern void mosaicBGOut(u_long bgMask);
extern void mosaicBGIn(u_long bgMask);

extern long initRandom(void);
extern long getMidRangedRandomPos(long min, long max, long midMin, long midMax);
extern long rangedRandom(long min, long max);
extern short rangedRandomShort(short min, short max);

extern s16 fix_mul(s16 a, s16 b);
extern s16 fix_inverse(s16 b);

#endif //!_UTIL_H


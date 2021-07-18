/*============================================================================
		Nintendo of America Developer Support
		Scott Perras
============================================================================*/
#ifndef _UTIL_H
#define _UTIL_H

/*-------------------------- defines ------------------------------ */
#define MAX_PRINT_BUF_SIZE 	(256)
#define MAX_DEBUG_FLAGS			(5)

#define FIXED_POINT_SHIFT (12)
#define FIXED_PT_UP(val) 	(val << FIXED_POINT_SHIFT)
#define FIXED_PT_DN(val) 	(val >> FIXED_POINT_SHIFT)
#define FP_ONE						(1 << FIXED_POINT_SHIFT)

#define LCD_ON  ( *(vu16 *) REG_DISPCNT &= ~(DISP_LCDC_OFF) )
#define LCD_OFF ( *(vu16 *) REG_DISPCNT |= DISP_LCDC_OFF)

/*-------------------------- structs ------------------------------ */


/*-------------------------- external vars -------------------------*/
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

/*-------------------------- end -----------------------------------*/
#endif // _UTIL_H


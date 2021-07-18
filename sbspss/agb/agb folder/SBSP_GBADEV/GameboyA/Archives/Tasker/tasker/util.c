/*============================================================================
		Nintendo of America Developer Support
		Scott Perras
============================================================================*/
#include "project.h"
#include "util.h"
#include "interrupt.h"

// =========================================================================
//
//					 EXTERNAL FUCTIONS/VARS
//
// =========================================================================

// =========================================================================
//
//					 GLOBAL VARIABLES
//
// =========================================================================
char global_printBuffer[MAX_PRINT_BUF_SIZE];
long global_debugFlags[MAX_DEBUG_FLAGS];

// =========================================================================
//
//					 LOCAL DEFINES
//
// =========================================================================

// =========================================================================
//
//					 LOCAL PROTOS
//
// =========================================================================

// =========================================================================
//
//					 LOCAL VARIABLES
//
// =========================================================================

/*
 *	void clearRamAll(void)
 *
 *  PARAMETERS:		None
 *
 *  DESCRIPTION:	Clears all RAM
 *
 *  RETURNS:			Nothing
 */
void clearRamAll(void)
{
  clearWorkRam();
  clearGraphicRam();
}

/*
 *	void clearWorkRam(void)
 *
 *  PARAMETERS:		None
 *
 *  DESCRIPTION:	Clears WRAM
 *
 *  RETURNS:			Nothing
 */
void clearWorkRam(void)
{
	DmaClear(3, 0, EX_WRAM, EX_WRAM_SIZE, 32);
  DmaClear(3, 0, CPU_WRAM, CPU_WRAM_SIZE - 0x200, 32);
}

/*
 *	void clearGraphicRam(void)
 *
 *  PARAMETERS:		None
 *
 *  DESCRIPTION:	Clears VRAM, OAM, and palette RAM
 *
 *  RETURNS:			Nothing
 */
void clearGraphicRam(void)
{
	clearVram();
  clearOamRam();
  clearPaletteRam();
}

/*
 *	void clearVram(void)
 *
 *  PARAMETERS:		None
 *
 *  DESCRIPTION:	Clears VRAM
 *
 *  RETURNS:			Nothing
 */
void clearVram(void)
{
	DmaClear(3, 0, VRAM, VRAM_SIZE, 16);
}

/*
 *	void clearOamRam(void)
 *
 *  PARAMETERS:		None:
 *
 *  DESCRIPTION:	Clears OAM
 *
 *  RETURNS:			Nothing
 */
void clearOamRam(void)
{
	DmaClear(3, 0, OAM, OAM_SIZE, 32);
}

/*
 *	void clearPaletteRam(void)
 *
 *  PARAMETERS:		None
 *
 *  DESCRIPTION:	Clear palette RAM
 *
 *  RETURNS:			Nothing
 */
void clearPaletteRam(void)
{
	DmaClear(3, 0, PLTT, PLTT_SIZE, 16);
}

/*
 *	void setLCDOff(void)
 *
 *  PARAMETERS:		None
 *
 *  DESCRIPTION:	Turns off LCD
 *
 *  RETURNS:			Nothing
 */
void setLCDOff(void)
{
	*(vu16 *) REG_DISPCNT |= DISP_LCDC_OFF;
}

/*
 *	void setLCDOn(void)
 *
 *  PARAMETERS:		None
 *
 *  DESCRIPTION:	Turns on LCD
 *
 *  RETURNS:			Nothing
 */
void setLCDOn(void)
{
	*(vu16 *) REG_DISPCNT &= ~(DISP_LCDC_OFF);
}

/*
 *	void setLCDOff_WaitVBlank(void)
 *
 *  PARAMETERS:		None
 *
 *  DESCRIPTION:	Turns off LCD after VBLANK
 *
 *  RETURNS:			Nothing
 */
void setLCDOff_WaitVBlank(void)
{
	//waitForVBlank();

	while (1) {

		if (*(vu16 *) REG_STAT & (STAT_V_BLANK)) {

			*(vu16 *)REG_DISPCNT |= DISP_LCDC_OFF;
			break;
		}
	}
}

/*
 *	void setLCDOn_WaitVBlank(void)
 *
 *  PARAMETERS:		None
 *
 *  DESCRIPTION:	Turns on LCD after VBLANK
 *
 *  RETURNS:			Nothing
 */
void setLCDOn_WaitVBlank(void)
{
	//waitForVBlank();

	while (1) {

		if (*(vu16 *) REG_STAT & (STAT_V_BLANK)) {
			*(vu16 *)REG_DISPCNT &= ~(DISP_LCDC_OFF);
			break;
		}
	}
}

/*
 *	void fadeOut(u_long fadeMask)
 *
 *  PARAMETERS:		fadeMask:	BG/OBJ mask
 *
 *  DESCRIPTION:	Fades out items contained in fadeMask
 *
 *  RETURNS:			Nothing
 */
void fadeOut(u_long fadeMask)
{
	long fadeVal;

	*(vu16*)REG_BLDCNT = (BLD_DOWN_MODE | fadeMask);

	for (fadeVal=0; fadeVal<=16; fadeVal++) {

		*(vu16*)REG_BLDY = fadeVal;

		waitForVBlank();
		waitForVBlank();
		waitForVBlank();
		//waitForVBlank();
	}
}

/*
 *	void fadeIn(u_long fadeMask)
 *
 *  PARAMETERS:		fadeMask:	BG/OBJ mask
 *
 *  DESCRIPTION:	Fades in items contained in fadeMask
 *
 *  RETURNS:			Nothing
 */
void fadeIn(u_long fadeMask)
{
	long fadeVal = 16;

	*(vu16*)REG_BLDCNT = (BLD_DOWN_MODE | fadeMask);

	while (fadeVal >= 0) {

		*(vu16*)REG_BLDY = fadeVal;
		fadeVal--;

		waitForVBlank();
		waitForVBlank();
		waitForVBlank();
		//waitForVBlank();

	}
}

/*
 *	void mosaicBGOut(u_long bgMask)
 *
 *  PARAMETERS:		bgMask:	BG mask
 *
 *  DESCRIPTION:	Mosaics BG's out contained in bgMask
 *
 *  RETURNS:			Nothing
 */
void mosaicBGOut(u_long bgMask)
{
	long hMosaic = 0;
	long vMosaic = 0;

	//enable MOSAIC flags for BG's selected
	if (bgMask & DISP_BG0_ON) {
		*(vu16*) REG_BG0CNT |= BG_MOS_ON;
	}

	if (bgMask & DISP_BG1_ON) {
		*(vu16*) REG_BG1CNT |= BG_MOS_ON;
	}

	if (bgMask & DISP_BG2_ON) {
		*(vu16*) REG_BG2CNT |= BG_MOS_ON;
	}

	if (bgMask & DISP_BG3_ON) {
		*(vu16*) REG_BG3CNT |= BG_MOS_ON;
	}

	while (hMosaic < 16) {

		//*(vu16*) REG_MOSAIC &= ~(MOS_BG_H_SIZE_MASK|MOS_BG_V_SIZE_MASK);
		*(vu16*) REG_MOSAIC = ((vMosaic << MOS_BG_V_SIZE_SHIFT) | (hMosaic));

		hMosaic++;
		vMosaic++;

		waitForVBlank();
		waitForVBlank();
		waitForVBlank();
		waitForVBlank();
	}
}

/*
 *	void mosaicBGIn(u_long bgMask)
 *
 *  PARAMETERS:		bgMask:	BG mask
 *
 *  DESCRIPTION:	Mosaics BG's in contained in bgMask
 *
 *  RETURNS:			Nothing
 */
void mosaicBGIn(u_long bgMask)
{
	long hMosaic = 15;
	long vMosaic = 15;

	//enable MOSAIC flags for BG's selected
	if (bgMask & DISP_BG0_ON) {
		*(vu16*) REG_BG0CNT |= BG_MOS_ON;
	}

	if (bgMask & DISP_BG1_ON) {
		*(vu16*) REG_BG1CNT |= BG_MOS_ON;
	}

	if (bgMask & DISP_BG2_ON) {
		*(vu16*) REG_BG2CNT |= BG_MOS_ON;
	}

	if (bgMask & DISP_BG3_ON) {
		*(vu16*) REG_BG3CNT |= BG_MOS_ON;
	}

	while (hMosaic >= 0) {

		//*(vu16*) REG_MOSAIC &= ~(MOS_BG_H_SIZE_MASK|MOS_BG_V_SIZE_MASK);
		*(vu16*) REG_MOSAIC = ((vMosaic << MOS_BG_V_SIZE_SHIFT) | (hMosaic));

		hMosaic--;
		vMosaic--;

		waitForVBlank();
		waitForVBlank();
		waitForVBlank();
		waitForVBlank();
	}
}


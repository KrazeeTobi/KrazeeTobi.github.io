/*============================================================================
		Nintendo of America Developer Support
		Scott Perras
============================================================================*/
#include "project.h"
#include "util.h"
//#include "interrupt.h"

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
long debugFlags[MAX_DEBUG_FLAGS];

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

//AGBPrint
//void debugPrint

/*
 *	void clearRamAll(void)
 *
 *  PARAMETERS:
 *
 *  DESCRIPTION:
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
 *  PARAMETERS:
 *
 *  DESCRIPTION:
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
 *  PARAMETERS:
 *
 *  DESCRIPTION:
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
 *  PARAMETERS:
 *
 *  DESCRIPTION:
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
 *  PARAMETERS:
 *
 *  DESCRIPTION:
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
 *  PARAMETERS:
 *
 *  DESCRIPTION:
 *
 *  RETURNS:			Nothing
 */
void clearPaletteRam(void)
{
	DmaClear(3, 0, PLTT, PLTT_SIZE, 16);
}

/*
 *
 *
 *  PARAMETERS:
 *
 *  DESCRIPTION:
 *
 *  RETURNS:			Nothing
 */
void setLCDOff(void)
{
	*(vu16 *)REG_DISPCNT |= DISP_LCDC_OFF;
}

/*
 *
 *
 *  PARAMETERS:
 *
 *  DESCRIPTION:
 *
 *  RETURNS:			Nothing
 */
void setLCDOn(void)
{
	*(vu16 *)REG_DISPCNT &= ~(DISP_LCDC_OFF);
}

/*
 *
 *
 *  PARAMETERS:
 *
 *  DESCRIPTION:
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
 *
 *
 *  PARAMETERS:
 *
 *  DESCRIPTION:
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

#if 0

/*
 *
 *
 *  PARAMETERS:
 *
 *  DESCRIPTION:
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
 *
 *
 *  PARAMETERS:
 *
 *  DESCRIPTION:
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
 *
 *
 *  PARAMETERS:
 *
 *  DESCRIPTION:
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
 *
 *
 *  PARAMETERS:
 *
 *  DESCRIPTION:
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
#endif

#if 1
/*
 *	s16 fix_mul(s16 a, s16 b)
 *
 *  PARAMETERS:
 *
 *  DESCRIPTION:
 *
 *  RETURNS:
 */
s16 fix_mul(s16 a, s16 b)
{
  s32 tmp;
  tmp = a;
  tmp *= b;
  tmp /= 0x100;
  return (s16)tmp;
}

/*
 *	s16 fix_div(s16 a, s16 b)
 *
 *  PARAMETERS:
 *
 *  DESCRIPTION:
 *
 *  RETURNS:
 */
s16 fix_div(s16 a, s16 b)
{
  s32 tmp;
  tmp = a;
  tmp *= 0x100;
  tmp /= b;
  return (s16)tmp;
}

/*
 *	s16 fix_inverse(s16 b)
 *
 *  PARAMETERS:
 *
 *  DESCRIPTION:
 *
 *  RETURNS:
 */
s16 fix_inverse(s16 b)
{
  s32 tmp;
  tmp = 0x10000;
  tmp /= b;
  return (s16)tmp;
}

#if 0
const s16 sin_cos_table[256+64]={
	0x0000,0x0006,0x000c,0x0012,0x0019,0x001f,0x0025,0x002b,
	0x0031,0x0038,0x003e,0x0044,0x004a,0x0050,0x0056,0x005c,
	0x0061,0x0067,0x006d,0x0073,0x0078,0x007e,0x0083,0x0088,
	0x008e,0x0093,0x0098,0x009d,0x00a2,0x00a7,0x00ab,0x00b0,
	0x00b5,0x00b9,0x00bd,0x00c1,0x00c5,0x00c9,0x00cd,0x00d1,
	0x00d4,0x00d8,0x00db,0x00de,0x00e1,0x00e4,0x00e7,0x00ea,
	0x00ec,0x00ee,0x00f1,0x00f3,0x00f4,0x00f6,0x00f8,0x00f9,
	0x00fb,0x00fc,0x00fd,0x00fe,0x00fe,0x00ff,0x00ff,0x00ff,
	0x0100,0x00ff,0x00ff,0x00ff,0x00fe,0x00fe,0x00fd,0x00fc,
	0x00fb,0x00f9,0x00f8,0x00f6,0x00f4,0x00f3,0x00f1,0x00ee,
	0x00ec,0x00ea,0x00e7,0x00e4,0x00e1,0x00de,0x00db,0x00d8,
	0x00d4,0x00d1,0x00cd,0x00c9,0x00c5,0x00c1,0x00bd,0x00b9,
	0x00b5,0x00b0,0x00ab,0x00a7,0x00a2,0x009d,0x0098,0x0093,
	0x008e,0x0088,0x0083,0x007e,0x0078,0x0073,0x006d,0x0067,
	0x0061,0x005c,0x0056,0x0050,0x004a,0x0044,0x003e,0x0038,
	0x0031,0x002b,0x0025,0x001f,0x0019,0x0012,0x000c,0x0006,
	0x0000,0xfffa,0xfff4,0xffee,0xffe7,0xffe1,0xffdb,0xffd5,
	0xffcf,0xffc8,0xffc2,0xffbc,0xffb6,0xffb0,0xffaa,0xffa4,
	0xff9f,0xff99,0xff93,0xff8d,0xff88,0xff82,0xff7d,0xff78,
	0xff72,0xff6d,0xff68,0xff63,0xff5e,0xff59,0xff55,0xff50,
	0xff4b,0xff47,0xff43,0xff3f,0xff3b,0xff37,0xff33,0xff2f,
	0xff2c,0xff28,0xff25,0xff22,0xff1f,0xff1c,0xff19,0xff16,
	0xff14,0xff12,0xff0f,0xff0d,0xff0c,0xff0a,0xff08,0xff07,
	0xff05,0xff04,0xff03,0xff02,0xff02,0xff01,0xff01,0xff01,
	0xff00,0xff01,0xff01,0xff01,0xff02,0xff02,0xff03,0xff04,
	0xff05,0xff07,0xff08,0xff0a,0xff0c,0xff0d,0xff0f,0xff12,
	0xff14,0xff16,0xff19,0xff1c,0xff1f,0xff22,0xff25,0xff28,
	0xff2c,0xff2f,0xff33,0xff37,0xff3b,0xff3f,0xff43,0xff47,
	0xff4b,0xff50,0xff55,0xff59,0xff5e,0xff63,0xff68,0xff6d,
	0xff72,0xff78,0xff7d,0xff82,0xff88,0xff8d,0xff93,0xff99,
	0xff9f,0xffa4,0xffaa,0xffb0,0xffb6,0xffbc,0xffc2,0xffc8,
	0xffcf,0xffd5,0xffdb,0xffe1,0xffe7,0xffee,0xfff4,0xfffa,
	0x0000,0x0006,0x000c,0x0012,0x0019,0x001f,0x0025,0x002b,
	0x0031,0x0038,0x003e,0x0044,0x004a,0x0050,0x0056,0x005c,
	0x0061,0x0067,0x006d,0x0073,0x0078,0x007e,0x0083,0x0088,
	0x008e,0x0093,0x0098,0x009d,0x00a2,0x00a7,0x00ab,0x00b0,
	0x00b5,0x00b9,0x00bd,0x00c1,0x00c5,0x00c9,0x00cd,0x00d1,
	0x00d4,0x00d8,0x00db,0x00de,0x00e1,0x00e4,0x00e7,0x00ea,
	0x00ec,0x00ee,0x00f1,0x00f3,0x00f4,0x00f6,0x00f8,0x00f9,
	0x00fb,0x00fc,0x00fd,0x00fe,0x00fe,0x00ff,0x00ff,0x00ff,
};
#endif

long initRandom(void)
{
	long z;

	z += (global_systemInfoPtr->vBlankCounter << 4) + (global_systemInfoPtr->controlPad << 2) + global_systemInfoPtr->controlPadOld;

	if (z==0)
		z=rand()%0xfff1f + 1;

	global_systemInfoPtr->vbiCounter++;
	z = z * global_systemInfoPtr->vbiCounter * global_systemInfoPtr->vbiCounter * global_systemInfoPtr->vbiCounter;

	//global_systemInfoPtr->vBlankCounter++;
	//z = z * global_systemInfoPtr->vBlankCounter * global_systemInfoPtr->vBlankCounter * global_systemInfoPtr->vBlankCounter;

	srand(z);

	return (z);
}

/*
 *
 *
 *  PARAMETERS:
 *
 *  DESCRIPTION:
 *
 *  RETURNS:			Nothing
 */

//need timeout?

long getMidRangedRandomPos(long min, long max, long midMin, long midMax)
{
	long pos;

	do {

		pos = rangedRandom(min, max);

	} while ((pos > midMin) && (pos < midMax));

	return (pos);
}

/*
 *
 *
 *  PARAMETERS:
 *
 *  DESCRIPTION:
 *
 *  RETURNS:			Nothing
 */
long rangedRandom(long min, long max)
{
	unsigned long r;
	long w;
	long bigResult;

	r = rand() & 0x7fff;

	bigResult = r * (long)(max-min);

	w = bigResult>>15;

	return min + w;
}


short rangedRandomShort(short min, short max)
{
	short	range	= max-min+1;
	long	i = rand();

	i = (i*range) >> 15;

	return (min+i);
}




#endif



#if 0
///////////////////////////////////////////////////////////////////////////
//
// Random_min_max
//
// Returns a number from  min <= n <= max
// limited to 0..32767
//
///////////////////////////////////////////////////////////////////////////

short Random_min_max(short min, short max)
{
	short	range	= max-min+1;		// Get range of random distribution

	long	i		= rand();		// Get a random number 0-0x7fff

	i = (i*range) >>15;

	return(min+i);
}

///////////////////////////////////////////////////////////////////////////
//
// short Random_max(short max)
//
//	Return a random number.
//
// Max value = MAX.
// Min Value = 0
//
//
///////////////////////////////////////////////////////////////////////////

short Random_max(short max)
{
	long	i		= rand();		// Get a random number 0-0x7fff

	i = (i*(max+1)) >> 15;

	return(i);
}

///////////////////////////////////////////////////////////////////////////
//
//	short Random_signmax(short max)
//
// Returns number between -max and +max
//
///////////////////////////////////////////////////////////////////////////

short Random_signmax(short max)
{
	long i;

	i = (( rand() * ((max<<1)+1) ) >>15)-max;

	return(i);
}

///////////////////////////////////////////////////////////////////////////
//
// short Random_percent(short percent,short max)
//
//	Determines probability of something.
//
//	Call with:
// percent	= 0-100 (call with 100 for always TRUE, 0 for always FALSE)
//
//	Returns:
//	TRUE or FALSE
//
///////////////////////////////////////////////////////////////////////////

BOOL Random_percent(short percent, short max)
{
	long	i;

	i = ( rand() * (max+1) ) >> 15;

	if (percent < i)
		return(FALSE);

	return(TRUE);
}

///////////////////////////////////////////////////////////////////////////
//
// int Ranged_random(int min, int max)
//
//	Returns a random value (min <= randomValue < max)
// min and max can be 32-bit signed values
//
///////////////////////////////////////////////////////////////////////////

long Ranged_random(long min, long max)
{
	unsigned long r;
	long w;
	long bigResult;

	r = rand() & 0x7fff;

	bigResult = r * (long)(max-min);

	w = bigResult>>15;

	return min + w;
}

#endif



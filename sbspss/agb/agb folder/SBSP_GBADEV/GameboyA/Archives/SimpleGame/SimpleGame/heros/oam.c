/*============================================================================
		Nintendo of America Developer Support
		Scott Perras
============================================================================*/
#include "project.h"
#include "interrupt.h"
#include "oam.h"

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
OamData global_oamData[MAX_OAM];
AffineParamWork affineWork[AFFINE_WORK_MAX];

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
const u32 defaultOAM[1][2] = {{ OAM_OBJ_OFF | OAM_COLOR_16 | OAM_SIZE_32x32, 0}};

/*
 *	void initOamBuffer(void)
 *
 *  PARAMETERS:		None
 *
 *  DESCRIPTION:	Inits the OAM buffer
 *
 *  RETURNS:			Nothing
 */
void initOamBuffer(void)
{
	long i;

	//init OAM to default
	for (i=0; i<MAX_OAM; i++) {
		global_oamData[i] = *(OamData *) defaultOAM;
  }

	//transfer to OAM
	DmaArrayCopy(3, global_oamData, OAM, 32);
}

/*
 *	void setOamIndexOn(long oamIndex)
 *
 *  PARAMETERS:		oamIndex:	Oam index
 *
 *  DESCRIPTION:	Turns on object
 *
 *  RETURNS:			Nothing
 */
void setOamIndexOn(long oamIndex)
{
	global_oamData[oamIndex].AffineMode = 0;
}

/*
 *	void setOamIndexOff(long oamIndex)
 *
 *  PARAMETERS:		oamIndex:	Oam index
 *
 *  DESCRIPTION:	Turns off object
 *
 *  RETURNS:			Nothing
 */
void setOamIndexOff(long oamIndex)
{
	global_oamData[oamIndex].AffineMode = 2;
}

/*
 *	void debug_moveOamIndexWithController(long oamIndex)
 *
 *  PARAMETERS:		oamIndex:	Oam index
 *
 *  DESCRIPTION:	Moves obj with controller
 *
 *  RETURNS:			Nothing
 */
void debug_moveOamIndexWithController(long oamIndex)
{
	if (global_systemInfoPtr->controlPad & U_KEY) {
		global_oamData[oamIndex].VPos -= 1;
	}

	else if (global_systemInfoPtr->controlPad & D_KEY) {
		global_oamData[oamIndex].VPos += 1;
	}

	if (global_systemInfoPtr->controlPad & R_KEY) {
		global_oamData[oamIndex].HPos += 1;
	}

	else if (global_systemInfoPtr->controlPad & L_KEY) {
		global_oamData[oamIndex].HPos -= 1;
	}

}




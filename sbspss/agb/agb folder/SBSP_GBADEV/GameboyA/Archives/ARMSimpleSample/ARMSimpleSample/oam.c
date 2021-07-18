/*============================================================================
		Nintendo of America Developer Support
		Scott Perras
============================================================================*/
#include "project.h"
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
const u32 defaultOAM[1][2] = {{OAM_OBJ_OFF | OAM_COLOR_16 | OAM_SIZE_32x32, 0}};

/*
 *	void initOamBuffer(void)
 *
 *  PARAMETERS:
 *
 *  DESCRIPTION:
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

	//Transfer to OAM
	DmaArrayCopy(3, global_oamData, OAM, 32);
}

void setOamIndexOn(long index)
{
	global_oamData[index].AffineMode = 0;
}

void setOamIndexOff(long index)
{
	global_oamData[index].AffineMode = 2;
}





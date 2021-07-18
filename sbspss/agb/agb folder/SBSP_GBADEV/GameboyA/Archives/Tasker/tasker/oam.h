/*============================================================================
		Nintendo of America Developer Support
		Scott Perras
============================================================================*/
#ifndef _OAM_H
#define _OAM_H

/*-------------------------- defines ------------------------------ */
#define MAX_OAM 				(128)
#define AFFINE_WORK_MAX (32)

/*-------------------------- structs ------------------------------ */
//Affine Parameter Work Structure
typedef struct _affine_param_work
{
	XY_POS 	zoom;
	s16 		rot;				//Rotation Angle (0x100 = 360degrees)
	s16 		param[4];		//AffineParam
	s16 		work0;
	u8  		Hflip:1;
	u8 			pad;
} AFFINE_PARAM_WORK;

/*-------------------------- external functs -----------------------*/
extern void initOamBuffer(void);

extern void setOamIndexOff(long oamIndex);
extern void setOamIndexOn(long oamIndex);
extern void debug_moveOamIndexWithController(long oamIndex);
/*-------------------------- external vars -------------------------*/
extern OamData global_oamData[MAX_OAM];
extern AFFINE_PARAM_WORK affineWork[AFFINE_WORK_MAX];

#endif // _OAM_H

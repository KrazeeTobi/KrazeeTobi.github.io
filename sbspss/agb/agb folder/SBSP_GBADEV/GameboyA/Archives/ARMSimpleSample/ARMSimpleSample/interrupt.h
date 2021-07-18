/*============================================================================
		Nintendo of America Developer Support
		Scott Perras
============================================================================*/
#ifndef _INTERRUPT_H
#define _INTERRUPT_H

/*-------------------------- defines ------------------------------ */

/*-------------------------- structs ------------------------------ */
typedef void (*IntrFuncp)(void);

typedef struct _system_info
{
	IntrFuncp	vBlankFunctionPtr;
	IntrFuncp	hBlankFunctionPtr;
	IntrFuncp	vCountFunctionPtr;

	u32 timer0Counter;
	u32 timer1Counter;
	u32 timer2Counter;
	u32 timer3Counter;

	u32	vBlankCounter;
	u32	hBlankCounter;
	u32	vCountCounter;

	u32 vbiCounter;
	u32 cycleCount;
	u32 frameRate;

	u16 controlPad;
	u16 controlPadOld;
	u16 controlPadTrigger;

	u16 updateOAM;
	u16 forceBlank;
	u16 useDebugFont;

	vu32 temp;
	vu32 temp1;
	vu32 temp2;
	vu32 temp3;



} SYSTEM_INFO;


/*-------------------------- external vars -------------------------*/
extern SYSTEM_INFO global_systemInfo;
extern SYSTEM_INFO *global_systemInfoPtr;

/*-------------------------- external functs -----------------------*/
extern void initVBlank(void);
extern void setVBlankFunction(IntrFuncp fnc);
extern void setHBlankFunction(IntrFuncp fnc);
extern void setVCountFunction(IntrFuncp fnc);

extern void waitForVBlank(void);

extern void enableVCountInterrupt(long vCount);
extern void disableVCountInterrupt(void);

void controllerInit(void);
void controllerRead(void);

#endif //!_INTERRUPT_H


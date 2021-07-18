/*============================================================================
		Nintendo of America Developer Support
		Scott Perras
============================================================================*/
#ifndef _INTERRUPT_H
#define _INTERRUPT_H

/*-------------------------- defines ------------------------------ */

/*-------------------------- structs ------------------------------ */
typedef void (*IRQFunction)(void);

typedef struct _system_info
{
	u32 intrMainBuf[0x200];
	vu16 interruptStatusFlag;

	IRQFunction	vBlankFunctionPtr;
	IRQFunction	hBlankFunctionPtr;
	IRQFunction	vCountFunctionPtr;

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
extern void waitForVBlank(void);

extern void initVBlank(void);
extern void setVBlankFunction(IRQFunction function);
extern void setHBlankFunction(IRQFunction function);
extern void setVCountFunction(IRQFunction function);

extern void enableVCountInterrupt(long vCount);
extern void disableVCountInterrupt(void);

void controllerInit(void);
void controllerRead(void);

#endif // _INTERRUPT_H


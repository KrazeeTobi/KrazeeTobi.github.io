/*============================================================================
		Nintendo of America Developer Support
		Scott Perras
============================================================================*/
#include "project.h"
#include "util.h"
#include "oam.h"
#include "interrupt.h"

// =========================================================================
//
//					 EXTERNAL FUCTIONS/VARS
//
// =========================================================================
extern void intr_main(void);

extern void VBlankIntr(void);
extern OamData OamBak[128];                // OAM バックアップ


extern void intr_main(void);
extern void irqEnable(void);
extern void irqDisable(void);

// =========================================================================
//
//					 GLOBAL VARIABLES
//
// =========================================================================
SYSTEM_INFO global_systemInfo;
SYSTEM_INFO *global_systemInfoPtr;

// =========================================================================
//
//					 LOCAL DEFINES
//
// =========================================================================
#define CLEAR_IRQ(irq) 	interruptStatusFlag &= ~(irq)
#define SET_IRQ(irq) 		*(vu16 *) REG_IF = irq; \
												interruptStatusFlag |= irq


// =========================================================================
//
//					 LOCAL PROTOS
//
// =========================================================================
static void vBlankInterrupt(void);
static void hBlankInterrupt(void);
static void vCountInterrupt(void);

static void timer0Interrupt(void);
static void timer1Interrupt(void);
static void timer2Interrupt(void);
static void timer3Interrupt(void);
static void dummyInterrupt(void);


// =========================================================================
//
//					 LOCAL VARIABLES
//
// =========================================================================
u32 intrMainBuf[0x200];
vu16 interruptStatusFlag;


//static volatile s32 irqNest;

#if 0
IntrFuncp IntrTable[14] =
{
	vBlankInterrupt,										//V Blank Interrupt
	hBlankInterrupt,                    //H Blank Interrupt
	vCountInterrupt,				            //V Counter Interrupt
	timer0Interrupt, //controllerRead,   //Timer 0 Interrupt
	timer1Interrupt,		        				//Timer 1 Interrupt
	timer2Interrupt,            				//Timer 2 Interrupt
	timer3Interrupt,		               	//Timer 3 Interrupt
	dummyInterrupt,                     //Serial Communication Interrupt
	dummyInterrupt,		                  //DMA0 Interrupt
	dummyInterrupt,                     //DMA1 Interrupt
	dummyInterrupt,		                  //DMA2 Interrupt
	dummyInterrupt,                     //DMA3 Interrupt
	dummyInterrupt,		                  //Key Interrupt
	dummyInterrupt,                     //Cassette Interrupt
};
#endif

const IntrFuncp IntrTable[14] =
{
	vBlankInterrupt,										//V Blank Interrupt
	dummyInterrupt,                    //H Blank Interrupt
	dummyInterrupt,				            //V Counter Interrupt
	dummyInterrupt, //controllerRead,   //Timer 0 Interrupt
	dummyInterrupt,		        				//Timer 1 Interrupt
	dummyInterrupt,            				//Timer 2 Interrupt
	dummyInterrupt,		               	//Timer 3 Interrupt
	dummyInterrupt,                     //Serial Communication Interrupt
	dummyInterrupt,		                  //DMA0 Interrupt
	dummyInterrupt,                     //DMA1 Interrupt
	dummyInterrupt,		                  //DMA2 Interrupt
	dummyInterrupt,                     //DMA3 Interrupt
	dummyInterrupt,		                  //Key Interrupt
	dummyInterrupt,                     //Cassette Interrupt
};


/*
 *	void initVBlank(void)
 *
 *  PARAMETERS:
 *
 *  DESCRIPTION:
 *
 *  RETURNS:			Nothing
 */
void initVBlank(void)
{
	//set global ptr to sys info
	global_systemInfoPtr = &global_systemInfo;

  DmaCopy(3, intr_main, intrMainBuf, sizeof(intrMainBuf), 32);
  //IntrAddrSet(global_systemInfoPtr->intrMainBuf);
  *(vu32 *)INTR_VECTOR_BUF = (vu32 ) intrMainBuf;

  //DmaCopy(3, intr_main, global_systemInfoPtr->intrMainBuf, sizeof(global_systemInfoPtr->intrMainBuf), 32);
  //IntrAddrSet(global_systemInfoPtr->intrMainBuf);
  //*(vu32 *)INTR_VECTOR_BUF = (vu32 ) global_systemInfoPtr->intrMainBuf;

	#if 0
  *(vu16 *)REG_IME	=  1; //IME_FLAG;
	*(vu16 *)REG_IE		= V_BLANK_INTR_FLAG;
	*(vu16 *)REG_STAT = STAT_V_BLANK_IF_ENABLE;
	CLEAR_IRQ(V_BLANK_INTR_FLAG);
	#endif

	//init controller
	controllerInit();

	//init OAM buffer
	//initOamBuffer();

	//irqNest = 0;

	global_systemInfoPtr->vBlankFunctionPtr = NULL;
	global_systemInfoPtr->hBlankFunctionPtr = NULL;
	global_systemInfoPtr->vCountFunctionPtr = NULL;

	global_systemInfoPtr->vBlankCounter	= 0;
	global_systemInfoPtr->hBlankCounter	= 0;
	global_systemInfoPtr->vCountCounter	= 0;

	global_systemInfoPtr->timer0Counter = 0;
	global_systemInfoPtr->timer1Counter = 0;
	global_systemInfoPtr->timer2Counter = 0;
	global_systemInfoPtr->timer3Counter = 0;

	global_systemInfoPtr->vbiCounter		= 0;
	global_systemInfoPtr->cycleCount		= 0;
	global_systemInfoPtr->frameRate	    = 0;

	//flag for NO OAM update
	global_systemInfoPtr->updateOAM			= 0;
	global_systemInfoPtr->forceBlank		= 0;
	global_systemInfoPtr->useDebugFont	= 0;

	//temps
	global_systemInfoPtr->temp					= 0;
	global_systemInfoPtr->temp1					= 0;
	global_systemInfoPtr->temp2					= 0;
	global_systemInfoPtr->temp3					= 0;
}

/*
 *	void waitForVBlank(void)
 *
 *  PARAMETERS:
 *
 *  DESCRIPTION:
 *
 *  RETURNS:			Nothing
 */
void waitForVBlank(void)
{
	//WHAT IF VBLANK JUST FINISHED, THIS WILL WAIT ANOTHER BLANK!?
	//WHAT IF VBLANK JUST FINISHED, THIS WILL WAIT ANOTHER BLANK!?
	//WHAT IF VBLANK JUST FINISHED, THIS WILL WAIT ANOTHER BLANK!?

	//check dispstat fot vblank!

	CLEAR_IRQ(V_BLANK_INTR_FLAG);

	while(1) {

		//Halt(); //Should I use this?

		if(interruptStatusFlag & V_BLANK_INTR_FLAG)
	    break;
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
 *  RETURNS:
 */
void setVBlankFunction(IntrFuncp fnc)
{
	global_systemInfoPtr->vBlankFunctionPtr = fnc;
}

/*
 *
 *
 *  PARAMETERS:
 *
 *  DESCRIPTION:
 *
 *  RETURNS:
 */
void setHBlankFunction(IntrFuncp fnc)
{
	global_systemInfoPtr->hBlankFunctionPtr = fnc;
}

/*
 *
 *
 *  PARAMETERS:
 *
 *  DESCRIPTION:
 *
 *  RETURNS:
 */
void setVCountFunction(IntrFuncp fnc)
{
	global_systemInfoPtr->vCountFunctionPtr = fnc;
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
void disableVCountInterrupt(void)
{
	*(vu16 *) REG_IE	 &= ~(V_COUNT_INTR_FLAG);
	*(vu16 *) REG_STAT &= ~(STAT_V_COUNT_IF_ENABLE);
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
void enableVCountInterrupt(long vCount)
{
	*(vu16 *) REG_IE		|= V_COUNT_INTR_FLAG;
	*(vu16 *) REG_STAT	|= ((vCount << STAT_VCOUNT_CMP_SHIFT) | STAT_V_COUNT_IF_ENABLE);
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
static void clearInterruptFlag(u_long irq)
{
  global_systemInfoPtr->interruptStatusFlag &= ~(irq);
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
static void setInterruptFlag(u_long irq)
{
	*(vu16 *) REG_IF |= irq;
  global_systemInfoPtr->interruptStatusFlag |= irq;
}
#endif
/*
 *
 *
 *  PARAMETERS:
 *
 *  DESCRIPTION:
 *
 *  RETURNS:			Nothing
 */
static void vBlankInterrupt(void)
{
	//protect against nested VBL interrupts...
	//if (irqNest++ == 0) {

		//setLCDOff();

		//irqEnable();

	#if 0
		//call secondary vBlank function if set
		if (global_systemInfoPtr->vBlankFunctionPtr != NULL)
			(*global_systemInfoPtr->vBlankFunctionPtr)();

		//DMA OAM if requested
		if (global_systemInfoPtr->updateOAM) {
			DmaArrayCopy(3, global_oamData, OAM, 32);
		}

		//DEBUG ONLY
		if (global_systemInfoPtr->useDebugFont) {
			FontPrintSync();
			FontPrintCls();
		}
		#endif

		DmaArrayCopy(3, OamBak, OAM, 32);

		//read Controller
		controllerRead();

		//inc frame counter
		global_systemInfoPtr->vBlankCounter++;

		//inc vbiCounter for frameRate;
		global_systemInfoPtr->vbiCounter++;

		//compute frame rate
		if (global_systemInfoPtr->vbiCounter >= 60) {
			global_systemInfoPtr->frameRate		= global_systemInfoPtr->cycleCount;
			global_systemInfoPtr->vbiCounter	= global_systemInfoPtr->cycleCount = 0;
		}

		//setLCDOn();

		//Done with interrupt
		SET_IRQ(V_BLANK_INTR_FLAG);
		//global_systemInfoPtr->interruptStatusFlag = V_BLANK_INTR_FLAG;
	//}

	//--irqNest;
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
static void hBlankInterrupt(void)
{
	//inc counter
	global_systemInfoPtr->hBlankCounter++;

	//call secondary hBlank function if set
	//if (global_systemInfoPtr->hBlankFunctionPtr != NULL)
	//	(*global_systemInfoPtr->hBlankFunctionPtr)();

	//Done with interrupt
	//*(vu16 *) REG_IF = H_BLANK_INTR_FLAG;
  //global_systemInfoPtr->interruptStatusFlag |= H_BLANK_INTR_FLAG;

	SET_IRQ(H_BLANK_INTR_FLAG);
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
static void vCountInterrupt(void)
{
	global_systemInfoPtr->vCountCounter++;

	//if (global_systemInfoPtr->vCountFunctionPtr != NULL)
	//	(*global_systemInfoPtr->vCountFunctionPtr)();

	//Done with interrupt
	SET_IRQ(V_COUNT_INTR_FLAG);
}

/*
 *
 *
 *  PARAMETERS:
 *
 *  DESCRIPTION:
 *
 *  RETURNS:
 */
static void timer0Interrupt(void)
{
	global_systemInfoPtr->timer0Counter++;

	//Done with interrupt
	SET_IRQ(TIMER0_INTR_FLAG);
}

/*
 *
 *
 *  PARAMETERS:
 *
 *  DESCRIPTION:
 *
 *  RETURNS:
 */
static void timer1Interrupt(void)
{
	global_systemInfoPtr->timer1Counter++;

	//Done with interrupt
	SET_IRQ(TIMER1_INTR_FLAG);
}

/*
 *
 *
 *  PARAMETERS:
 *
 *  DESCRIPTION:
 *
 *  RETURNS:
 */
static void timer2Interrupt(void)
{
	global_systemInfoPtr->timer2Counter++;

	//Done with interrupt
	SET_IRQ(TIMER2_INTR_FLAG);
}

/*
 *
 *
 *  PARAMETERS:
 *
 *  DESCRIPTION:
 *
 *  RETURNS:
 */
static void timer3Interrupt(void)
{
	global_systemInfoPtr->timer3Counter++;

	//*(vu16 *) REG_IF = TIMER3_INTR_FLAG;

	//Done with interrupt
	SET_IRQ(TIMER3_INTR_FLAG);
}

/*
 *	static void dummyInterrupt(void)
 *
 *  PARAMETERS:
 *
 *  DESCRIPTION:
 *
 *  RETURNS:			Nothing
 */
static void dummyInterrupt(void)
{

}

/*
 *	void controllerInit(void)
 *
 *  PARAMETERS:
 *
 *  DESCRIPTION:
 *
 *  RETURNS:			Nothing
 */
void controllerInit(void)
{
	global_systemInfoPtr->controlPad = global_systemInfoPtr->controlPadTrigger = 0;
}

/*
 *	void controllerRead(void)
 *
 *  PARAMETERS:
 *
 *  DESCRIPTION:
 *
 *  RETURNS:			Nothing
 */
void controllerRead(void)
{
	u16 readData = (*(vu16 *)REG_KEYINPUT ^ 0xffff);

	global_systemInfoPtr->controlPadOld = global_systemInfoPtr->controlPad;
  global_systemInfoPtr->controlPadTrigger = readData & (readData ^ global_systemInfoPtr->controlPad);
  global_systemInfoPtr->controlPad = readData;
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
static void clearVBlankInterruptFlag(void)
{
	global_systemInfoPtr->interruptStatusFlag &= V_BLANK_INTR_FLAG ^ 0xffff;
	//global_systemInfoPtr->interruptStatusFlag &= ~(V_BLANK_INTR_FLAG);
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
static void setVBlankInterruptFlag(void)
{
	*(vu16 *) REG_IF	|= V_BLANK_INTR_FLAG;
	//*(vu16 *)REG_IF	= V_BLANK_INTR_FLAG;
  global_systemInfoPtr->interruptStatusFlag |= V_BLANK_INTR_FLAG;
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
static void clearHBlankInterruptFlag(void)
{
	global_systemInfoPtr->interruptStatusFlag &= ~(H_BLANK_INTR_FLAG);
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
static void setHBlankInterruptFlag(void)
{
	*(vu16 *)REG_IF	= H_BLANK_INTR_FLAG;
  global_systemInfoPtr->interruptStatusFlag |= H_BLANK_INTR_FLAG;
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
static void clearVCInterruptFlag(void)
{
	global_systemInfoPtr->interruptStatusFlag &= ~(V_COUNT_INTR_FLAG);
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
static void setVCInterruptFlag(void)
{
	//*(vu16 *) REG_IF = V_COUNT_INTR_FLAG;
	*(vu16 *) REG_IF |= V_COUNT_INTR_FLAG;
  global_systemInfoPtr->interruptStatusFlag |= V_COUNT_INTR_FLAG;
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
static void clearTimerInterruptFlag(unsigned long timer)
{
	global_systemInfoPtr->interruptStatusFlag &= ~(timer);
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
static void setTimerInterruptFlag(unsigned long timer)
{
	*(vu16 *) REG_IF |= timer;
  global_systemInfoPtr->interruptStatusFlag |= timer;
}
#endif


